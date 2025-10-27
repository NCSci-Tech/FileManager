File Management Utility (C)

A simple console-based file management program written in C.
This utility allows users to perform basic file operations such as reading, writing, appending, deleting files, and listing directory contents directly from the terminal.

Features

Read the contents of a text file.

Write and create new text files.

Append additional text to existing files.

Delete files safely (with confirmation).

List the files and directories in the current working directory.

Cross-platform: Works on both Windows and Unix/Linux/macOS systems.

Usage
1. Compilation

Use any standard C compiler (e.g., GCC or Clang).

gcc file_manager.c -o file_manager

2. Running the Program
./file_manager


Once launched, the program will display a title banner and a menu:

________________
|1. read
|2. write
|3. append
|4. delete
|5. list directory
|6. Quit
|Option:

Menu Options
1. Read a File

Displays the content of a text file.

Example:

Enter file name: example.txt


The contents of example.txt will be printed to the screen.

2. Write a File

Creates a new file (or overwrites an existing one) and allows the user to enter text.

Example:

Enter file name: notes.txt
Enter text to write (end with an empty line):
This is a new file.
Hello world!

[Press Enter on an empty line to finish]

3. Append to a File

Adds new text to the end of an existing file.

Example:

Enter file name: notes.txt
Enter text to append (end with an empty line):
Additional notes go here.

[Press Enter on an empty line to finish]

4. Delete a File

Deletes a specified file after user confirmation.

Example:

Enter file name: old.txt
Are you sure you want to delete 'old.txt'? (y/n): y
File deleted successfully.

5. List Directory Contents

Displays the files and directories in the current folder.

On Windows, it uses the dir command.

On Unix/Linux/macOS, it uses the ls -l command.

6. Quit

Exits the program gracefully.

Error Handling

Memory allocation failures (malloc, realloc) are caught and reported.

File operations include error messages when opening, writing, or deleting fails.

Empty input (no filename entered) is handled safely.

Code Overview
Function	Description
titleSequence()	Displays the ASCII title banner.
getFile()	Dynamically reads user input for filenames or text lines.
listDir()	Lists the directory contents using system commands.
readF()	Reads and displays a file’s content.
writeF()	Creates and writes text to a file.
appendF()	Appends text to an existing file.
delFile()	Deletes a file with user confirmation.
main()	Handles the main menu and user interaction loop.
Notes

Make sure you have the necessary permissions to read/write/delete files in the current directory.

Input is buffered line-by-line, and memory allocation is dynamic for flexible input length.

This program is designed for learning and demonstration purposes — ideal for beginners practicing C file I/O and memory management.
