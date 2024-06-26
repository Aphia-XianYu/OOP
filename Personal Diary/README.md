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
