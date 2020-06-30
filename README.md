# Handwritten Digit Recognition
Implemented with a simple convolutional neural network, for practice.  
## Current Progress
Implementation: Nodes  
Language: C++20  
CNN: Backpropagation  
GUI: Windowed Display  
## Contributors
Eric Lam - C++20 (CNN)  
Simon Wu - C++20 (GUI)  
## Dependencies
wxWidgets 3.1.3
## Compiling Instructions
To compile with the source code, the user should have CMake 3.17.3 or earlier. You should place the FULL path to wxWidgets, e.g., `C:\wxWidgets-3.1.3` in a User Variable called `WXWIN` in your environment variables. 

If you are using MinGW, please run this CMake command in the base project directory in the command prompt:
```
cmake <your project directory path> -G "MinGW Makefiles"
```
This creates a folder and a series of files. The important one is the makefile, which can be used with MinGW. If you are using a different compiler, please use `cmake --help` and scroll to the "Generators" section to locate the appropriate one. 

To compile the executable using the makefile, run this command:
```
mingw32-make 
```
digits.exe should be in the directory now. Run it using:
```
./digits.exe
```
