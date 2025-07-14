# Matlab-C++ Library
The library contains classes equivalent to common data structures used in **Matlab** by *ADCS* of [Parikshit](https://www.parikshitspace.in/). The classes are intended to be used in most *Matlab-C++* code conversion tasks, simplifying the process & improving code readability. All classes overload common arthmetic operators. Three classes are currently provided in separate header files:
- **Vector<sub>3</sub>**
- **Vector<sub>4</sub>**
- **Matrix<sub>3x3</sub>**

All classes use the `<vector>` C++ The repository's main files are organised as:
- *class*D**Math**.hpp - The class header files containing their definitions and operations.
- *class*D**UT**.cpp - Basic testing files for each class which run the class' operations and check if the outputs are valid.
- unified**Math**.hpp - The file combines the class header files and adds few cross-class functions.
> Vector<sub>4</sub> class doesn't currently have a testing file. The [Vector<sub>3</sub>'s file](#vector3utcpp) can be modified for testing if required.

## Vector classes
### `vector3Math.hpp` & `vector4Math.hpp`
-
### `vector3UT.cpp`
-

## Matrix<sub>3x3</sub> class
### `matrix3Math.hpp`
-
### `matrix3UT.cpp`
-

## Using all classes together
### `unifiedMath.hpp`
-