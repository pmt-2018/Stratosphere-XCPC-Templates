# coding=utf-8
import os
import sys
import json

TexHead = r"""
\documentclass[twoside]{article}
\usepackage[colorlinks,linkcolor=black]{hyperref}
\usepackage{xeCJK}
\usepackage{fancyhdr}
\usepackage{amsmath, amsthm}
\usepackage{listings,xcolor}
\usepackage{geometry}
\usepackage{fontspec}
\usepackage{graphicx}
\setsansfont{Monaco}
\setmonofont[Mapping={}]{Monaco}
\newcommand{\HRule}{\rule{\linewidth}{0.5mm}}
\geometry{left=2.5cm,right=2.5cm,top=2.5cm,bottom=2.5cm}
\lstset{
    language    = c++,
    numbers     = left,
    numberstyle = \tiny,
    breaklines  = true,
    captionpos  = b,
    tabsize     = 4,
    frame       = single,
    columns     = fullflexible,
    commentstyle = \color[RGB]{0,128,0},
	keywordstyle ={
		\color[RGB]{0,51,153}
		\fontspec{Consolas Bold}	
	},
    basicstyle   = \small\ttfamily,
    stringstyle  = \color[RGB]{148,0,209}\ttfamily,
	rulesepcolor = \color{red!20!green!20!blue!20},
    showstringspaces = false,                    
}
"""


def InitSetting():
    try:
        SettingFile = open('setting.dat')
        SettingData = json.load(SettingFile)
        print (u'读取到保存的设置: ')
        for key in SettingData:
            print ('[%s] %s' % (key, SettingData[key]))
        op = input('是否使用已保存的设置？[Y/n]')
        if not op in ['n', 'N', 'no', 'No', 'NO']:
            global TITLE, SCHOOL, TEAM, FILE
            for key in ['TITLE', 'SCHOOL', 'TEAM', 'FILE']:
                globals()[key] = SettingData[key]
        else:
            NewSetting()
    except:
        print (u'读取设置失败')
        NewSetting()


def NewSetting():
    global TITLE, SCHOOL, TEAM, FILE
    TITLE = input('请输入标题: ')
    SCHOOL = input('请输入学校: ')
    TEAM = input('请输入队名: ')
    FILE = input('请输入文件名: ')
    Data = dict()
    for key in ['TITLE', 'SCHOOL', 'TEAM', 'FILE']:
        Data[key] = globals()[key]
    json.dump(Data, open('setting.dat', 'w'))
 
# 删除当前目录下的所有中间临时文件
def Clear():
    for suffix in ['aux', 'log', 'toc', 'out']:
        filename = '%s.%s' % (FILE, suffix)
        if os.path.exists(filename):
            os.remove(filename)

def Generate():
    Clear()
    os.system('xelatex %s.tex' % FILE)
    os.system('xelatex %s.tex' % FILE)
    os.system('xelatex %s.tex' % FILE)
    Clear()
    os.system('open %s.pdf' % FILE)


def ReadCpp(file):
    f = open(file, 'r')
    first_line = f.readline().strip()  # 读取第一行并去掉两边的空白字符
    if first_line == '// ---':  # 判断第一行是否等于 '// ---'
        Tex = 1
    else:
        Tex = 0
        TargetFile.write('\\begin{lstlisting}\n')
    
    for line in f:  # 循环读取剩下的内容
        if line.strip() == '// ---':  # 判断当前行是否为 '// ---'
            Tex = not Tex
            ToWrite = '\\%s{lstlisting}\n' % ('begin', 'end')[Tex]
            TargetFile.write(ToWrite)
            continue
        TargetFile.write(line[(0, 3)[Tex]:])  # 根据 Tex 值决定是否跳过前三个字符
    TargetFile.write('\\end{lstlisting}\n')
    f.close()


def ReadTex(file):
    f = open(file, 'r')
    for line in f:
        TargetFile.write(line)
    f.close()


def Search(level, pwd, folder=''):
    ls = os.popen('ls "%s"| grep [0-9]_' % pwd).read().split('\n')[:-1]
    if folder:
        TargetFile.write(SECTION[level] % folder[3:])
    for item in ls:
        item.replace(' ', '\\ ')
        if '.cpp' in item:
            if not item[:2] == '00':
                TargetFile.write(SECTION[level + 1] % item[3:-4])
            ReadCpp(pwd + item)
        elif '.tex' in item:
            if not item[:2] == '00':
                TargetFile.write(SECTION[level + 1] % item[3:-4])
            ReadTex(pwd + item)
        else:
            cd = os.popen('cd "%s%s/"' % (pwd, item)).read()
            if 'Not a directory' in cd or 'No such file or directory' in cd:
                print ('[Unknown File] %s/%s' % (pwd, item))
            else:
                Search(level + 1, pwd + item + '/', item)


if __name__ == '__main__':
    # 全局设置
    TITLE, SCHOOL, TEAM, FILE = '', '', '', ''
    SECTION = ['', '\\clearpage\\section{%s}\n',
               '\\subsection{%s}\n', '\\subsubsection{%s}\n']

    InitSetting()

    TargetFile = open('%s.tex' % FILE, 'w')


    # Output Head File
    TargetFile.write(TexHead)
    TargetFile.write('\\title{%s}\n' % TITLE)
    TargetFile.write('\\author{%s}\n' % TEAM)
    TargetFile.write('\\pagestyle{fancy}\n\\fancyhf{}\n\\fancyhead[C]{%s, %s}\n' % (TITLE, TEAM))
    TargetFile.write('\\begin{document}\\small\n')
    TargetFile.write('\\begin{titlepage}\n\\begin{center}\n\\vspace*{0.5cm}\\includegraphics[width=0.75\\textwidth]{logo.jpg} \\\\ [2cm]\n')
    TargetFile.write('\\HRule \\\\ [1cm]\n')
    TargetFile.write('\\textbf{\\Huge{%s}} \\\\ [0.5cm]\n' % TITLE)
    TargetFile.write('\\HRule \\\\ [4cm]\n')
    TargetFile.write('\\textbf{\\Huge{%s}} \\\\ [1cm]\n\\LARGE{%s}\n' % (SCHOOL, TEAM))
    TargetFile.write('\\vfill\n\\Large{\\today}\n\\end{center}\n')
    TargetFile.write('\\clearpage\n\end{titlepage}\n')
    TargetFile.write('\\tableofcontents\\clearpage\n')
    TargetFile.write('\\pagestyle{fancy}\n\\lfoot{}\n\\cfoot{\\thepage}\\rfoot{}\n')
    TargetFile.write('\\setcounter{section}{-1}\n\\setcounter{page}{1}\n')

    # Search Files
    Search(0, './')

    # End Output
    TargetFile.write('\n\\end{document}\n')
    TargetFile.close()

    # Gen
    Generate()
