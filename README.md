# Project3: Writing your own shell interpreter

You are working for a company that hires interns regularly and develops software in Linux. You are their favorite employee, and they asked you to write a **restricted** shell interpreter to be used by the interns. In this project, you are going to implement **rsh**, the **r**estricted **sh**ell, which will allow only a handful of commands to be executed from the shell prompt. To be precise, there are twelve commands that can be executed:

1: cp  
2: touch  
3: mkdir  
4: ls  
5: pwd  
6: cat  
7: grep  
8: chmod  
9: diff  
10: cd  
11: exit  
12: help  

The help command should print the list of commands as their appear above. The first 9 commands are programs that you are going to **spawn** as separate processes using the **posix_spawn()** system call. An example program that spawns an echo command is provided in the repository: myspawn.c. By using this example program, you are going to write your own shell interpreter that can execute the commands above. Commands 10, 11, and 12 can be considered as built-in shell commands, which will not spawn a separate process. The handling of commands 11 and 12 by your program is trivial. For the "cd" command, you are going to use the **chdir()** system call to change the directory to a target directory. However, if the user specifies more than one argument to the cd command, similar to bash, you should print the following error message and do not perform any cd action:

-rsh: cd: too many arguments

When the program is run, the shell prompt "rsh>" should be displayed. The shell should be in an infinite loop until the command **exit** is entered at which point the shell program should be terminated with a "return 0".

If the user enters any command or try to execute any program, you should display the following message and return to the prompt:

NOT ALLOWED!

Similar to project2, a sample executable is provided for convenience in the solution_executable folder.

You are not expected to support background processes, piping, or input/output redirection in this project.

You can use the starter code rsh.c to complete the project. A Makefile is also provided for convenience.

**Useful tips:**
 - You can use fgets() to get a line of input from the rsh prompt. Note that, fgets() also retains the end of line character at the end of the string. You can get rid of that by simply line[strlen(line)-1]='\0'.
 - You need to create and argument vector (argv in the sample program myspawn.c) to be passed to the posix_spawn() call. That argument vector is an array of strings terminated with a NULL pointer, which are basically the individual strings that the user enters from the command prompt separated by space. For example, if the user enters "mkdir a b c d", argv should be {"mkdir","a","b","c","d",NULL}. If you want to dynamically resize the argv array while parsing the input, you can use the realloc() function to do so.
 - strtok() destroys/modifies the original string as it tokenizes it. If you want to restart strtok() a second time on the same string from the beginning, you should first make a separate copy of that string before running strtok() the first time and start strtok() on the copied string the second time. 
