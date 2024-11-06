# Dash - Dallas Shell
## Description
Dash (Dallas Shell) is a simple Unix shell implementation developed as part of the CS 5348 Operating Systems course. It provides basic shell functionality, including command execution, built-in commands, redirection, and parallel command execution.
## Table of Contents
 - Features
 - Installation
 - Usage
 - Built-in Commands
 - Redirection
 - Parallel Commands
## Features
 - Interactive and batch mode execution
 - Command parsing and execution
 - Built-in commands: exit, cd, path
 - Output redirection
 - Parallel command execution
 - Basic error handling
## Installation
- Clone the repository
- Navigate to the project directory
- Compile the program
```console
bash> git clone https://github.com/Asvataman/dash_custom_bash.git
bash> cd dash-shell
bash> gcc dash.c -o dash -Wall -Werror -O -std=gnu99
```
## Usage
### Interactive Mode
- Run the shell in interactive mode:
- You will see the prompt dash> where you can enter commands.
```console
bash> ./dash
dash> _
```

### Batch Mode
- Run the shell in batch mode by providing a file with commands
```console
bash> ./dash batch.txt
```
## Built-in Commands
- exit: Exits the shell
- cd <directory>: Changes the current working directory
- path <directory1> <directory2> ...: Sets the search path for executables
## Redirection
- Redirect output to a file using the > operator:
```console
dash> ls -la /tmp > output.txt
```
## Parallel Commands
- Execute commands in parallel using the & operator:
```console
dash> cmd1 & cmd2 args1 args2 & cmd3 args1
```
## Error Handling
- The shell prints a single error message for all types of errors:
```console
dash> An error has occurred
```
