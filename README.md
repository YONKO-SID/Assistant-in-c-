# Jarvis Assistant in C (First Iteration)

## Overview

This project is a beginner-friendly desktop assistant written in C. The current version is a simple command-line program that can:

- Greet the user
- Accept typed commands
- Open Notepad or Firefox
- Respond to 'say hello'
- Exit on 'exit'
- Handle unknown commands gracefully

## How It Works

- The program uses a loop to continuously prompt the user for input.
- It compares the input string to known commands using `strcmp` from `<string.h>`.
- It uses the `system()` function to open applications like Notepad or Firefox.
- The loop exits when the user types 'exit'.

## How to Compile

Make sure you have GCC installed. Open your terminal in the project directory and run:

```
gcc jarvis.c -o jarvis
```

## How to Run

After compiling, run the program with:

- On Windows:

  ```
  jarvis.exe
  ```

- On Linux/Mac (if ported):

  ```
  ./jarvis
  ```

## Example Usage

```
Hello! I am hackoid, your assistant.
Type any command (e.g., 'open notepad', 'say hello', 'exit'):
> say hello
Hello, human!
> open notepad
// Notepad opens
> firefox
// Firefox opens
> exit
Goodbye!
```
