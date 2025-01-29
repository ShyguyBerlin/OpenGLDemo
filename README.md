# Requirements
to get all the packages needed to build the project run the following:
```
(Ubuntu)
$ sudo apt install libglfw3-dev libgl-dev cmake
```

for windows you install [MSYS2](https://github.com/msys2/msys2-installer/releases/download/2024-12-08/msys2-x86_64-20241208.exe)
and run
```
pacman -S mingw-w64-ucrt-x86_64-toolchain
```

and 
```
pacman -S mingw-w64-x86_64-glfw
```

in the msys2 console.
after that you add
```
list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake/glfw3")

find_package(glfw3 3.4 REQUIRED)
```

or whatever your msys64 path is to CMakeLists.txt

# Build
Optimally you can run any cmake wrapper in your IDE. There is a really nice extension for VSCode that does that for you, with a bit of configuration. Else you can also run the following command:
```
$ figure this out I have no idea
```