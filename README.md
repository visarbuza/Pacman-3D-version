# Windows

## Setup using Visual Studio's integrated CMake tools

1. Get the [Visual C++ tools for CMake](https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp?view=vs-2017) accessible through the Visual Studio Installer: `Tools→Get Tools and Featurs→Desktop development with C++`

2. Open The CMake project, either by `File→Open→Folder...`, or `File→Open→CMake...` and locate the Folder containing the `CMakeLists.txt` file relevant to this lab.

3. Visual Studio will run CMake on the file and generate the some needed project files based on the instuctions in the file.

4. Notice configurations defined within CMakeSettings.json, you might want to change the `buildRoot` property to something more sensible - This is essentially where your project will end up being built. 

   - to match the folder layout with Linux setup, `buildRoot` can be set to this: `"${projectDir}\\build"`
   - however, seeing as VS makes it easy to switch build configurations on the fly, it might be a good idea to account for that when working in VS to not mess up the CMake-generated files; hence setting `buildRoot` to `"${projectDir}\\build\\${name}"` might be more feasible.

   Having said that, keeping it as is will also be fine, but the built executable will be harder to find on your system.

   An example of this: `C:/Users/empoyee427/CMakeBuilds/621c328c-e411-0639-97bb-a40cd0883fa6/build/x64-Release/labxx.exe`

## Setup using CMake-GUI

1. Obtain [CMake-GUI](https://cmake.org/download/) and run it.
2. Set the source code file to the root directory containing `"CMakeLists.txt"`
3. Binaries can be built in the directory of your choice, e.g. `"<projectDir>/build/"`
4. Click the configure button and select which generator you would like to use
5. Click the generate button
6. If your generator is an IDE such as Visual Studio, then open up the newly created .sln file and build ``ALL_BUILD``. After this you might want to set `labxx` as you StartUp Project.

# Linux (Ubuntu)

#### Initial Setup
* Obtain Clang++ 5.0 (needed c++17 features, which the CMakeLists.txt currently assumes)
```bash
sudo apt-get install clang++-5.0
```
* Install CMake (`apt-get install cmake` will get you a fairly outdated version, so we'll obtain it manually instead)
```bash
#Remove previous installations of cmake
sudo apt-get remove --purge cmake
# make a temp folder for the CMake binaries
mkdir ~/temp 
cd ~/temp
# obtain the latest CMake version
wget https://cmake.org/files/v3.13/cmake-3.13.0-Linux-x86_64.tar.gz
# unzip the binaries
tar -xzvf cmake-3.13.0-Linux-x86_64.tar.gz
cd ~/temp/cmake-3.13.0-Linux-x86_64/
    
#place the binaries
cp -r ./bin     /usr/    
cp -r ./doc     /usr/share/
cp -r ./man     /usr/share/
cp -r ./share   /usr/

cmake --version  # verify the new installation:
                 # expected: cmake version 3.13.0
rm -r ~/temp     # cleanup temp directory, it's no longer needed
```
#### Building the Project
```bash
cd .../<Your_Labxx_Folder>
mkdir build/
cd build/

# Configure and Generate CMake files.
# verify success by looking for "CMake configured Labxx successfully!"
# The "CMAKE_CXX_COMPILER" flag is used to set clang++ 5.0 as the compiler,
# (though any c++17 compatible compiler should in theory work here)
cmake .. -DCMAKE_CXX_COMPILER=clang++-5.0 
# Build the project
make
# Run the executable
./lab<xx>
```

# MacOS
#### Initial Setup
* Get CMake
```bash
# Should by default get you a fairly new version of CMake
brew install cmake 
# Verify that cmake version is over 3.8
cmake --version
```
#### Building the Project
```bash
mkdir build/
cd build/
# Configure and Generate CMake files.
# verify success by looking for "CMake configured Labxx successfully!"
# On MacOS Clang is the default compiler, and so we don't need to specify it like on Linux
cmake .. 
# Build the project
make
# Run the executable
./lab<xx>
```

