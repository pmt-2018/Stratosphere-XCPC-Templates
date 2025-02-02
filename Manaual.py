# coding=utf-8
import os
import sys
import json

TexHead = r"""
\documentclass[twoside]{article}
\usepackage[colorlinks,linkcolor=black]{hyperref}
\usepackage{xeCJK}
\usepackage{svg}
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
\definecolor{mygreen}{rgb}{0,0.6,0}
\definecolor{mygray}{rgb}{0.5,0.5,0.5}
\definecolor{mymauve}{rgb}{0.58,0,0.82}
\lstset{ 
  backgroundcolor=\color{white},        % choose the background color; you must add \usepackage{color} or \usepackage{xcolor}; should come as last argument
  basicstyle=\footnotesize\ttfamily,    % the size of the fonts that are used for the code
  breakatwhitespace=false,              % sets if automatic breaks should only happen at whitespace
  breaklines=true,                      % sets automatic line breaking
  captionpos=b,                         % sets the caption-position to bottom
  columns=fullflexible,
  commentstyle=\color{mygreen},         % comment style
  deletekeywords={...},                 % if you want to delete keywords from the given language
  escapeinside={\%*}{*)},               % if you want to add LaTeX within your code
  extendedchars=true,                   % lets you use non-ASCII characters; for 8-bits encodings only, does not work with UTF-8
  firstnumber=1,                     % start line enumeration with line 1000
  frame=single,	                        % adds a frame around the code
  keepspaces=true,                      % keeps spaces in text, useful for keeping indentation of code (possibly needs columns=flexible)
  keywordstyle=\color{blue},            % keyword style
  language=c++,                         % the language of the code
  lineskip=-0.2ex,
  morekeywords={*,...},                 % if you want to add more keywords to the set
  numbers=left,                         % where to put the line-numbers; possible values are (none, left, right)
  numbersep=5pt,                        % how far the line-numbers are from the code
  numberstyle=\tiny\color{mygray},      % the style that is used for the line-numbers
  rulecolor=\color{black},              % if not set, the frame-color may be changed on line-breaks within not-black text (e.g. comments (green here))
  rulesepcolor=\color{red!20!green!20!blue!20},
  showspaces=false,                     % show spaces everywhere adding particular underscores; it overrides 'showstringspaces'
  showstringspaces=false,               % underline spaces within strings only
  showtabs=true,                        % show tabs within strings adding particular underscores
  % stepnumber=2,                       % the step between two line-numbers. If it's 1, each line will be numbered
  stringstyle=\color{mymauve}\ttfamily, % string literal style
  tabsize=4,	                        % sets default tabsize to 2 spaces
  tab={\rule[-.2\baselineskip]{.4pt}{\baselineskip}\kern 1.5em}
}
\usepackage{indentfirst}
\setlength{\parindent}{2em}
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
        TargetFile.write(first_line)
        TargetFile.write('\n')
    
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
    
    os.system('clang-format -i ./**/*.cpp --style=file')

    InitSetting()

    TargetFile = open('%s.tex' % FILE, 'w')


    # Output Head File
    TargetFile.write(TexHead)
    TargetFile.write('\\title{%s}\n' % TITLE)
    TargetFile.write('\\author{%s}\n' % TEAM)
    TargetFile.write('\\pagestyle{fancy}\n\\fancyhf{}\n\\fancyhead[C]{%s, %s}\n' % (TITLE, TEAM))
    TargetFile.write('\\begin{document}\\small\n')
    TargetFile.write('\\begin{titlepage}\n\\begin{center}\n\\vspace*{0.5cm}\\includesvg[width=0.75\\textwidth]{logo.svg} \\\\ [2cm]\n')
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
