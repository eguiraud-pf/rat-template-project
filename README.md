![Logo](./figs/RATLogo.png)
# Template for C++ API
<em>Good starting point for beginner, yes?</em>

## Installation
This template allows you to get started with the Rat libraries. It already contains the CMake file and a simple example so that you can get started more easily. To build the example file run the following commands in the terminal:
```bash
cd rat-template
mkdir build
cd build
cmake ..
make
```

To run the solenoid model that is part of this template run the following command from the build directory.
```bash
./Release/bin/solenoid --od ./mydata
```

The paraview files will be stored in the ./mydata directory.