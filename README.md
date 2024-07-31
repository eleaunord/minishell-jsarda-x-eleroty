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

### => Tokenization to do list

1/ Identify Tokens: List all possible tokens (e.g., commands, flags, arguments, operators like |, >, <, etc.).

2/ Write a Tokenizer: Create a function to split the input string into tokens.

-> Handle quotes (single and double) to allow spaces within arguments.

-> Consider escape characters.

3/ Test Tokenizer: Write tests to ensure the tokenizer handles various edge cases (e.g., dq_flagiple spaces, quoted strings, escape sequences).


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
