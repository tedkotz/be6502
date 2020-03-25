#!/bin/sh

ca65 vectorTable.s
ca65 main.s
ld65 main.o vectorTable.o -C link.cfg
hexdump -C a.out.rom.bin
