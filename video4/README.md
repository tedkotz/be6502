Video 4
=======

My code for the fourth video in Ben Eaters 6502 series.
https://www.youtube.com/watch?v=FY3zTUaykVo

This code and build infrastructure is in place to build the images using the ca65 assembler that comes with the cc65 C compiler, that is in Debian.
https://packages.debian.org/source/sid/cc65


Files
-----

|Name           | Description                                                   |
|---------------|---------------------------------------------------------------|
|build.sh       | A simple build shell                                          |
|link.cfg       | Linker command file lays out memmory to match BE6502 Computer |
|main.s         | The main hello world program                                  |
|vectorTable.s  | Initializaes the interrupt vector table. Particularly reset.  |


