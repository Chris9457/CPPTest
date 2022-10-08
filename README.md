# CPPTest
This application in intended to check the skills of the candidate through an implementation of an exercice

# Needed configuration
To build this project, the following configuration is required:
 - OS: Windows 10
 - CMake version >= 3.20
 - Visual Studio 2019 min - in the Visual Studio Installer, in the section "Développement Desktop en C++":
     - Check "Outils C++ CMake pour Windows" is checked
     - Check "Adaptateur de test pour Google Test" is checked
     
 
# Cloning the project
To clone the project, tape the commands:

    git clone https://github.com/Chris9457/CPPTest.git
    git submodule update --init
    
# Open the project with Visual Studio (2019)
Right-click on / in the folder containing the cloned project => Open with Visual Studio
Wait until the CMake generation is finished

# Build the project
In Visual Studio, select the project "Cpp_Test_Reverse" &  run Build
   OR
In a VS console, at the location of the repo tape the commands:

    cmake --preset=release
    cmake --build --preset=release
    
The generated application is at the location : out/release/src/CPP_Test_Reverse.exe

# installation

# Running the Unit Tests
In Visual Studio:
    - open Test/Test explorer
    - use the UI to run the unit tests
In a VS console:
    - tape the command:

    ctest --preset=release
   
# Execution
The application is located at: out/release/src/CPP_Test_Reverse

    Cpp_Test_Reverse [OPTIONS] <filename>

    <filename> : name of the file to parse

    OPTIONS:
       --table : to generate a table
       --reverse : to generate a reverted file