/*
Requirements

The Personal Diary is a CLI (Command Line Interface) software that consists of four programs:

pdadd
pdlist [ ]
pdshow
pdremove
pdadd is used to add an entity to the diary for the date. If an entity of the same date is in the diary, the existing one will be replaced. pdadd reads lines of the diary from the stdin, 
line by line, until a line with a single . character or the EOF character (Ctrl-D in Unix and Ctrl-Z in Windows).
pdlist lists all entities in the diary ordered by date. If start and end dates are provided through command line parameters, 
it lists entities between the start and the end only. This program lists to the stdout.
pdshow prints the content of the entity specified by the date to the stdout.
pdremove removes one entity of the date. It returns 0 on success and -1 on failure.
The software stores the diary in one data file, and reads it to the memory at the beginning of each program, and stores it back to the file at the end of the process.

Evaluation standard

C++ code quality (clean, compact, and reasonable)
Comments quality
Common classes and functions should be shared between programs
These programs are physically independent, so direct interaction is not permitted
These programs are able to work together by means of redirection
These programs are able to be used in a shell/batch 

要求
个人日记是由四个程序组成的 CLI（命令行界面）软件：
pdadd 
pdlist [ ] 
pdshow 
pdremove
pdadd用于在日记中添加日期实体。pdadd从 stdin 逐行读取日记行，直到读到一个.字符或EOF字符（Unix 中为Ctrl-D，Windows 中为Ctrl-Z）。
pdlist列出日记中按日期排序的所有实体。如果通过命令行参数提供了开始和结束日期，则只列出开始和结束日期之间的实体。该程序会将列表输出到 stdout。
pdshow将日期指定的实体内容打印到 stdout。
pdremove删除一个日期实体。成功时返回 0，失败时返回-1。
软件将日记存储在一个数据文件中，在每个程序开始时将其读入内存，并在程序结束时将其存回文件。
评估标准
C++ 代码质量（简洁、紧凑、合理）
注释质量
程序之间应共享共用类和函数
这些程序在物理上是独立的，因此不允许直接交互
这些程序可通过重定向方式协同工作
这些程序可在 shell/批处理脚本中使用
提交的文件
请准备一个 .zip 包，其中包括以下项目： 1.
源代码
包含多个软件使用案例的 shell/batch 脚本（涵盖所有程序）

通过DeepL.com（免费版）翻译
*/
//初始化
//checkdate