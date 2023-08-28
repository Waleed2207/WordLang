# WordLang Compiler

WordLang is a programming language compiler that runs on the PC environment.

## Getting Started

Follow these instructions to compile and run the WordLang compiler on your PC.

### Prerequisites

- GCC (GNU Compiler Collection) should be installed on your system.

### Compilation

1. Open a terminal.

2. Navigate to the WordLang directory.

3. Run the following command to compile the WordLang compiler:
   
   ```bash
   make
### Usage
Example 1:
- ./wordlang test00.wl t0.c
- gcc -o t0 t0.c utils.c
- ./t0

Example 2:
- ./wordlang test01.wl t1.c
- gcc -o t1 t1.c utils.c
- ./t1

### Cleaning Up
To clean up the generated files, you can use the following command:
   ```bash
   make clean
[WordLang1.pdf](https://github.com/Waleed2207/WordLang/files/12456910/WordLang1.pdf)
