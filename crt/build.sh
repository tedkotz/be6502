#!/bin/sh

# This c runtime is based off the instruction to build a custom runtime for cc65 here:
# https://www.cc65.org/doc/customizing.html

cc65 -t none -O --cpu 65c02 main.c
ca65 --cpu 65c02 vectors.s
ca65 --cpu 65c02 main.s
ca65 --cpu 65c02 crt0.s
ca65 --cpu 65c02 pckybd.s
ca65 --cpu 65c02 interrupt.s
ld65 -C be6502.cfg -m memory.map main.o vectors.o crt0.o interrupt.o be6502.lib pckybd.o
#hexdump -C a.out.rom.bin
## minipro -p AT28C256 -w a.out.rom.bin
