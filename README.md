# Handwritten Digit Recognition
Implemented with a simple convolutional neural network, for practice.  
**ON HOLD**  
## Current Progress
Implementation: Nodes  
Language: C++20  
CNN: Training  
GUI: Complete
## Contributors
Eric Lam - C++20 (CNN)  
Simon Wu - C++20 (GUI)  
## Dependencies
wxWidgets 3.1.3
## Launch Codes
Prerequisites: CMake 3.17.3, wxWidgets 3.1.3  
If CMake can't find wxWidgets, either move wxWidgets into C:/ or set the wxWidgets_ROOT_DIR and wxWidgets_LIB_DIR environment variables.

**MinGW:**  
Run the following commands in the root of the project directory
```
cmake <absolute path to project directory> -G "MinGW Makefiles"
mingw32-make 
./digits.exe
```
For other compilers, run `cmake --help` and scroll to the "Generators" section to locate the appropriate generator.
