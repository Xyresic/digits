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
## Compiling instructions
To compile with the source code, the user should have CMake 3.17.3 or earlier. If you are using MinGW, please run these two lines in the base project directory:
```
cmake <your project directory path> -G "MinGW Makefiles"
mingw32-make 
```
If you are using a different compiler, please use `cmake --help` and scroll to the "Generators" section to locate the appropriate one.
