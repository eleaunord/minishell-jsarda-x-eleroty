# 🐚 minishell

*The project was developed collaboratively by Julien Sarda (jsarda) and Éléonore Roty (eleroty).*

## Overview

**minishell** is a small-scale reimplementation of a Unix shell written in C. The project focuses on replicating Bash-like behavior for command parsing, execution, piping, and redirection. It involves working closely with system calls, process management, and file descriptors to simulate how a real shell works.

> The goal is to build your own fully functional shell—no shortcuts, no external parsing libraries—just raw logic, low-level C, and lots of debugging.

---

## 📚 What we Learned

This project helped me develop a much deeper understanding of:

* **Process and signal management** (`fork`, `execve`, `waitpid`, etc.)
* Writing a proper **parser** that handles quotes, pipes, escape characters, and expansions.
* Implementing **built-in commands** directly within the main shell process.
* **File descriptor redirection**: managing input/output redirections, pipes, and heredocs.
* Handling **signals** properly (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)—including tricky cases like heredoc interruptions.
* Clean memory management: freeing everything properly to avoid leaks and crashes.
* Structuring a mid-sized C project with modular, readable code.

---

## ✅ Mandatory Features

* Custom prompt with history (using `readline`)
* Command parsing with:

  * Spaces and quotes (`'`, `"`)
  * Pipes (`|`) and redirections (`<`, `>`, `<<`, `>>`)
  * Environment variable expansion (`$VAR`, `$?`)
* Execution system:

  * Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
  * External commands with `PATH` resolution
  * Pipes between multiple commands
* Signal handling:

  * `Ctrl+C` triggers a new prompt
  * `Ctrl+D` exits the shell
  * `Ctrl+\` is ignored
* Exit status (`$?`) updated properly

---

## 🔧 How Execution Works

1. **Prompt & Input**
   Uses `readline()` to read user input and store history.

2. **Parsing**
   Tokenizes the input while respecting quoting and expansion rules.

3. **Execution**

   * Forks and executes commands
   * Handles pipes using `dup2` and multiple child processes
   * Redirects input/output based on redirection operators
   * Runs built-ins in the parent process when needed

4. **Cleanup**

   * Frees all allocated memory
   * Restores file descriptors
   * Handles errors and resets signals safely

---

## 🚧 Difficulties Faced

* Handling edge cases in parsing (quotes within quotes, escaped characters, etc.)
* Managing multiple pipes and redirections simultaneously
* Correctly implementing heredoc with signals and temporary file cleanup
* Avoiding memory leaks, especially when reusing structures in the execution loop
* Recreating Bash-like behavior accurately, even for built-ins and exit codes

---

## 🛠️ Build & Run

```bash
make
./minishell
```

Example usage:

```bash
minishell> echo hello | cat -e > out.txt
minishell> cat out.txt
hello$
```

---

## 📎 References

* [execve man page](https://fr.manpages.org/execve/2)
* [execve video explanation](https://youtu.be/iq7puCxsgHQ?si=86cOQmlYwsrHcmRP)
* [42-minishell repo (community example)](https://github.com/Hqndler/42-minishell)

---

## 🧠 Final Thoughts

Rebuilding a shell was both the most painful and most rewarding project we’ve done at 42 so far. It’s a huge lesson in **how Unix works behind the scenes**, how to handle processes responsibly, and how to keep a large C project organized and maintainable. Watching my shell evolve from a single `echo` to a working pipeline with redirections was incredibly satisfying.

> It’s not just about launching commands—it’s about doing it *right*, reliably, and cleanly.
