#!/bin/sh

ca65 vectorTable.s
ca65 bounce.s
ld65 bounce.o vectorTable.o -C link.cfg
hexdump -C a.out.rom.bin
