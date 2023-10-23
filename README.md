# Emulador
Emulador de CPU | C++ | Collab w @1andre19 &amp; @carloSalda



This program emulates the functionality of a CPU in C++
Including instructions from the assembly lenguage, it displays what the "CPU" is currently doing and the program counter

==========

Functionality

The program will ask the user to input a int, after that it will ask for the direction where you want to save that data
After that the program will cycle for you to input (n) data at n directions
You can input ("-1") to go on to the code phase
The user is asked to input the instruction they want to used followed by the directioning type and the direction

for EXAMPLE

11 1 500
This represents
LDA - 11
Abs - 1
Direction - 500

Then the program will cycle for you to input more instructions, if you are done you input "q" and the program
will display what is going on on the CPU at each instance

=========

Instructions available

CLA
LDA
STA
SUB
ADD
JMP
JMN
JMZ
HLT

=========

