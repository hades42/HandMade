I'm currently learning how to make a game from scratch to solidify my knowledge about computer

# Compile Code

## Requirement

* You should install Visual Studio (making to check for C/C++ tool kit in the process of installing VS because we are going to take the x64 compiler from there to compile the bulid for the game)  

* To get the path of the compiler for VS2022(which is the current version I'm using):

```
# Go to
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build

# Run this program in the terminal to active the compiler
vcvars64.bat

# Troubleshooting (This command is the shortcut for running the x64 compiler)
cl
```
**Note**: If the path to the compiler is diffrent (In case you are going to use another vertion of VS): Please change the path in `\misc\shell.bat`

* If 2 steps above works as expected, you can just run `shell.bat` to active compiler right away

## Compile Bulid version

* Go to the `code` folder
* run `./build.bat` in the termninal





