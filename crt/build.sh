#!/bin/sh

cc65 -t none -O --cpu 65sc02 main.c
ca65 vectors.s
ca65 main.s
ca65 crt0.s
ca65 interrupt.s
ld65 main.o vectors.o crt0.o interrupt.o be6502.lib -C be6502.cfg
hexdump -C a.out.rom.bin
## minipro -p AT28C256 -w a.out.rom.bin
