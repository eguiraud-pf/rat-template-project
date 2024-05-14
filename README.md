![Logo](./figs/RATLogo.png)

# Template project for Rat's C++ API
<em>Good starting point for beginner, yes?</em>

Based on the original https://gitlab.com/Project-Rat/rat-template, adds a devcontainer with RAT pre-installed.

## Installation
This template allows you to get started with the Rat libraries.
It already contains the CMake file and a simple example so that you can get started more easily.
To build the example file run the following commands in the terminal:

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
