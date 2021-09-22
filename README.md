# Coverett

**Coverett** - C library for interacting with **HLAPI** devices of the [**OpenComputers II**](https://github.com/fnuecke/oc2) mod.

![Coverett logo](https://raw.githubusercontent.com/Bs0Dd/Coverett/master/covlogo.bmp)

## Warning!!!

The library is in alpha stage, so it can contain a bunch of nasty bugs, glitches and other things.
In addition, the documentation is not yet ready, but after analyzing the library files and the utilities code (they are attached here as an example), you will probably understand how to work with it.
Good luck!

## Complectation

* `libcoverett.so` - The library itself in a dynamic version. Required for the utilities supplied with it.

* `fimexu` - File IMport/EXport Utility. Exchanges files between the mod's computer and a real PC (faster than standard `import.lua` and `export.lua`). 

* `lshldev` - Just lists all HLAPI devices on the system. `lsdev.lua` analog.

* `redstone` - Small program for Redstone Interface Block or Redstone Interface Card control.

* `seplay` - Small Sound effects player for Sound Card. Can search effects names by query.

