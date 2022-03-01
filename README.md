# Coverett

**Coverett** - C library for interacting with **HLAPI** devices of the [**OpenComputers II**](https://github.com/fnuecke/oc2) mod.

![Coverett logo](https://raw.githubusercontent.com/Bs0Dd/Coverett/master/covlogo.bmp)

## Warning!!!

The library is in alpha stage, so it can contain a bunch of nasty bugs, glitches and other things.  
Documentation available [here](https://github.com/Bs0Dd/Coverett/wiki).

## Complectation

* `libcoverett.so` - The library itself in a dynamic version. Required for the utilities supplied with it.

* `fimexu` - File IMport/EXport Utility. Exchanges files between the mod's computer and a real PC (faster than standard `import.lua` and `export.lua`). 

* `lshldev` - Just lists all HLAPI devices on the system. `lsdev.lua` analog.

* `redstone` - Small program for Redstone Interface Block or Redstone Interface Card control.

* `seplay` - Small Sound effects player for Sound Card. Can search effects names by query.

## Building note

Firstly you need to download a **MUSL** compiler for **RISC-V 64** architecture. You can download it in [this site](https://musl.cc/) or directly by [this link (Linux)](https://musl.cc/riscv64-linux-musl-cross.tgz). Unfortunately Windows version is not available now.  
Now you need to have **git** on your machine. Write this commands to clone repo:
```
git clone https://github.com/Bs0Dd/Coverett.git
cd Coverett/
git submodule init
git submodule update
```

For building you need to have **CMake**. Type this to generate a makefile:
```
CC='<folder with downloaded compiler>/bin/riscv64-linux-musl-gcc' cmake CMakeLists.txt
```
And type `make` to start making process.

**It's all!** Compiled files will be placed in directory with cloned repo.
