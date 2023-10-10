# Simple Shell

This is a simple UNIX command-line interpreter developed as part of a group project for ALX SE. The project aims to create a basic shell that can execute commands entered by the user.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Features](#features)
- [Installation](#installation)
- [Project Requirements](#project-requirements)
- [Contributors](#contributors)

## Introduction

This shell program provides a simple command-line interface where users can enter commands, and the shell will execute them. It supports basic command execution, handling of command line arguments, PATH variable lookup, and built-in commands like `exit` and `env`. It is designed to be a minimalistic shell and does not support more advanced features like pipes, redirection, or complex scripting.

## Usage

To run the shell, execute the following command in your terminal:

```bash
./hsh
```

Once the shell is running, you can enter commands, and it will execute them. Here's an example of how to use it:

```bash
$ ./hsh
($) /bin/ls
file1.txt file2.txt
($) echo "Hello, World!"
Hello, World!
($) exit
$
```

### Supported Commands

- Simple commands without arguments or options.
- Commands with arguments and options (e.g., `/bin/ls -l`).
- Built-in command `exit` to exit the shell.
- Built-in command `env` to display the current environment variables.

### Unsupported Features

The shell does not support more advanced features like pipes (`|`), input/output redirection (`>`, `<`), environment variable assignment, or complex scripting.

## Features

- Accepts user commands and executes them.
- Handles basic command line arguments and options.
- Searches for commands in the PATH environment variable.
- Supports built-in commands: `exit` and `env`.
- Provides a simple and user-friendly interface.

## Installation

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Project Requirements

- The code follows the Betty style guidelines.
- No memory leaks are present in the code.
- The project compiles without errors or warnings.
- The shell passes the provided test cases.
- All functions are well-documented and organized.

## Contributors

This project was completed as part of a group effort by:
- SONTO MTIMDE

For more information on the project, refer to the [ALX SE Framework](https://intranet.alxswe.com/concepts/559).
