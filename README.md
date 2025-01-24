# Raylib Intro

This repo is an intro to raylib for myself.

## Setup

### Msys2

Follow the tutorial [here](https://code.visualstudio.com/docs/cpp/config-mingw) to install Msys2 on Windows then install the toolchain (leveraging the UCRT is perferred).

Next you'll need to add the Msys2 tools to your PATH.

```
C:\msys64\usr\bin
C:\msys64\usr\local\bin
C:\msys64\bin
C:\msys64\opt\bin
C:\msys64\usr\ucrt64\bin
```

If you need more tools, check out the Msys packages [here](https://packages.msys2.org/queue)

### Cmake

Install [Cmake](https://cmake.org/download/)

### Ninja

Install [Ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)

### Powershell

On Windows, it's recommended to use Powershell over other terminals, such as git bash. Go ahead and install the latest [Powershell](https://learn.microsoft.com/en-us/powershell/scripting/whats-new/migrating-from-windows-powershell-51-to-powershell-7?view=powershell-7.5) and add it to your PATH. With all the Msys2 tools, you'll feel just about at home with Powershell over Git Bash.

> While you **could** get smart and find ways to incorporate more tools into Msys2 and use them directly, this is NOT recommended. There is a very real chance you install a "Linux flavor" of a binary when using Msys2. So while the binary may run on a Windows system, it's going to behave in a way that expects a *nix OS (file paths for one are a hot topic).