# MINISHELL

## GENERAL

- No need to to follow the POSIX norm. (Portable Operating System Interface)

### USEFUL LINK

- https://github.com/Hqndler/42-minishell
-   https://fr.manpages.org/execve/2https://fr.manpages.org/execve/2 (execve doc)
- https://youtu.be/iq7puCxsgHQ?si=86cOQmlYwsrHcmRP (execve video)

### PROMPT

- COMMAND :
	LS, CAT, ECHO

- REDIRECTION :
	<, >, <<, >>

## PARSING

- TOKEN :
	Need to create a string of TOKEN and an INT for each node.
	The string is the node and the int is the TOKEN.
	ex : cat|ls
		token 1 : the string is cat who is a COMMAND type token (ex : 6)
		token 2 : the string is | who is a PIPE type token (ex : 5)
		token 3 : the string is ls who is a COMMAND type token (ex : 6)
	This token will be define in the .h

## EXEC

### Handling Simple Commands

#### Creating a Child Process with fork()
   - Use fork() to create a new process.
    - fork() returns a process ID (PID). The PID is 0 for the child process, and for the parent process, it is the child's PID.

#### Replacing the Process Image with execve()
    - Use execve() in the child process to replace the process image with the specified command.
    - execve() takes three arguments: the path to the executable, an array of arguments, and an array of environment variables.

#### Waiting for the Child Process to Finish with waitpid()
    - Use waitpid() in the parent process to wait for the child process to finish.
    - waitpid() takes the child process's PID and a pointer to an integer where the exit status will be stored.

#### Error Handling
   - Handle possible errors for fork(), execve(), and waitpid() using perror() and appropriate return code
