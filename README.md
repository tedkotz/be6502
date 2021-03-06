# be6502
Collection of notes, software and upgrades for Ben Eater's 6502 Computer

## Description
I've been having a ton of fun with this project. Probably to the point my coworkers are sick of hearing about it. I had a lot of the parts list for the computer laying around, so I just ordered Ben's Clock kit. While I was waiting for that I used my arduino mega to generate the clock as well as look at the signals. Which was fun because I could clock up to 8Mhz. This was only up through one of the very early videos so does not necessarily run with RAM and the additional decode logic at that speed.

## Arduino
### clock generation

## Hardware
### 65C816 CPU
I'm using the W65C816 instead of the W65C02, which is an almost identical CPU, but can be put into a 16-bit mode if I want to try to extend this project later. It required a slight adjustment to how the control pins are tied, but as of the 6th video it is still working well. If any one is interested:
|Pin |Name   |Connection |
|----|-------|-----------|
|1   |VPB    |FLOAT      |
|2   |RDY    |HIGH       |
|3   |ABORT  |HIGH       |
|4   |IRQB   |HIGH       |
|5   |MLB    |FLOAT      |
|6   |NMIB   |HIGH       |
|7   |VPA    |FLOAT      |
|35  |E      |FLOAT      |
|36  |BE     |HIGH       |
|38  |MX     |FLOAT      |
|39  |VDA    |FLOAT      |

### ZIF socket ROM
This is incredibly straight forward, but has been a very nice addition. I had a ZIF socket 
that would fit the ROM chip so I put the ZIF socket on some standoffs to give it a little 
more room on the board. This makes swapping the program a little easier.

### 4 Row Display
I didn't have a 2 row LCD display, but I did have a 4 row version. The 4 row
is actually wired up in the exact same way as the 2 row version. The strange
thing about the 4 row versions is that if you just overrun the end of the line
it overflows in a not immediately intuitive order row 1, 3, 2, then 4. This should 
not provide a software compatibility problem as the display will just have 
blank lines if software only uses 2 rows.

My eventual goal is to get the C runtime for this to properly format newlines by advancing
to the next line from the user point of view and having the text scroll off the top as one
would expect when calling printf on a short terminal. I will try to writ the software to
work with both 2 and 4 row models, but it may require a compile time setting be set. The
committed version will probably default to 2 ROw to be compatible with the be6502's as
originally spec'd.

### 3.7152 MHz Clock
The only oscillator on hand that was close to 1MHz was a 3.7152 Mhz oscillator. It wired up 
exactly the same as the 1Mhz clock and ran without issue.

### Address Decoding logic
Ben said that the address layout was some what wasteful of address space. The engineering tradeoff goal was to reduce the complexity of the decoder. In fact, all his decoding logic only uses 3 nand gates, a pretty impressive feat.

##### Original Ben Eater Memory Layout

| Address Range   | Description                      |
|-----------------|----------------------------------|
| 0x0000 - 0x00FF | Zero Page (6502 Fast access RAM) |
| 0x0100 - 0x01FF | Call Stack (6502 Stack)          |
| 0x0200 - 0x3FFF | Main RAM                         |
| 0x4000 - 0x5FFF | Reserved                         |
| 0x6000 - 0x6003 | VIO Interface                    |
| 0x6004 - 0x7FFF | Reserved                         |
| 0x8000 - 0xFFF8 | Main ROM                         |
| 0xFFFA - 0xFFFF | Vector ROM (6502 Vector Table)   |

#### Target Compatible Memory Layout

The goal of this memory layout is to slightly more efficiently allocate the addresses
that are used reserved for the IO area. Our trade space will allow for an increase in
the amount of logic, but try to not go too far maybe at most 2 chips. Still keep is
fairly simple i.e. a single contiguous RAM area. The final requirement is backwards compatibility
so anything designed to run on the original be6502 will still run on this. That means we cant move
anything that is used we can only shift around the reserved space.

To that end the first step is to allocate all addresses below 0x6000 to actual RAM going from 16k to 24k RAM.
The next priority is splitting out enable signals that each correspond to 1k of I/O address space.
Then maybe each of those could be used for a different one of the chips in the future expansion section below.
Once a serial loader is available the ROM address space could probably be greatly reduced, but if we wanted to
keep the Main RAM section contiguous then we would have to move the VIO and that would make it no longer compatible.
##### Alternate Memory Layout
| Address Range   | Description                      |
|-----------------|----------------------------------|
| 0x0000 - 0x00FF | Zero Page (6502 Fast access RAM) |
| 0x0100 - 0x01FF | Call Stack (6502 Stack)          |
| 0x0200 - 0x5FFF | Main RAM                         |
| 0x6000 - 0x6003 | VIO Interface                    |
| 0x6004 - 0x63FF | Reserved                         |
| 0x6400 - 0x67FF | Reserved for 65C51               |
| 0x6800 - 0x6BFF | Reserved for Device 4            |
| 0x6C00 - 0x6FFF | Reserved for Device 5            |
| 0x7000 - 0x73FF | Reserved for Device 6            |
| 0x7400 - 0x77FF | Reserved for Device 7            |
| 0x7800 - 0x7BFF | Reserved for Device 8            |
| 0x7C00 - 0x7FFF | Reserved for Device 9            |
| 0x8000 - 0xFFF8 | Main ROM                         |
| 0xFFFA - 0xFFFF | Vector ROM (6502 Vector Table)   |

#### NAND (7400)
The circuit as originally designed only uses 3 of the 4 NAND gates on the 7400.
This brings to mind the question can the extra NAND gate be used to get us closer 
to the target memory map above?

The answer is yes, with the caveat that we have to sacrifice a little robustness
in the design. in particular we have to assume no one is going to try to write
to the ROM. if they did it could actually mirror thru  to the lower addresses of
RAM. For 50% more RAM this seems like a fair trade off.

Fundamentally we want to change when the RAM is selected from when A14 is not
high to when A14 and A13 are both not high. We can do this by changing the
equations for /CS and /OE for the RAM from:
```
   /CS = NOT( NOT(A15) & CLK )
   /OE = A14
```
to:
```
   /CS = NOT( NOT(A14 & A13) & CLK )
   /OE = A15
```

You get this by first changing the RAM /OE(pin22) from A14(RAM pin1) to
A15(CPU pin25). The extra NAND gate is input A14(already connected to another
NAND gate) and A13(CPU pin23). Finally, where the output from the not of A15 is
fed into the adjacent NAND gate to combine with the clock instead feed in the
output of the new NAND gate.

Weirdly, having NOT(A14&A13) can free up one of the NAND gates used by the VIA.
Changing its CS inputs from:
```
   /CS = NOT( NOT(A15) & A14 )
    CS = A13
```
to
```
   /CS = NOT(A14 & A13)
    CS = NOT(A15)
```

So now the question is can we use this reclaimed NAND gate to either get us back
protection on writes to ROM changing RAM? Maybe we  get A15 back into the
calculation for the RAM chip select.

```
   /CS = NOT( NOT(A14 & A13) & CLK )
   /OE = A15
```
to:
```
   /CS = NOT( NOT(A15) & CLK )
   /OE = NOT( NOT(A14 & A13) )
```

**TL;DR** So in the end you can use all 4 NAND gates to increase the RAM by 50%
without any loss of functionality by changing the bus selection logic from:
```
ROM:
   /CS = NOT(A15)
RAM:
   /CS = NOT( NOT(A15) & CLK )
   /OE = A14
VIA:
   /CS = NOT( NOT(A15) & A14 )
    CS = A13
```
to:
```
ROM:
   /CS = NOT(A15)
RAM:
   /CS = NOT( NOT(A15) & CLK )
   /OE = NOT( NOT(A14 & A13) )
VIA:
   /CS = NOT(A14 & A13)
    CS = NOT(A15)
```

#### 3 to 8 Line decoder (74138)
#### GAL16V8
## Software
With the bank of LEDs on the outputs of the VIO, This little snippet of code uses the rotate and conditional instructions to create a bouncing light effect
```
    0xa9, 0xff,       // lda 0xff
    0x8d, 0x02, 0x60, // sta 0x6002
    0x18,             // clc
    0xa9, 0x01,       // lda 0x01
    0x8d, 0x00, 0x60, // sta 0x6000
    0x2a,             // rol
    0x90, -6,         // bcc -6
    0x18,             // clc
    0xa9, 0x80,       // lda 0x80
    0x8d, 0x00, 0x60, // sta 0x6000
    0x6a,             // ror
    0x90, -6,         // bcc -6
    0x4c, 0x05, 0x80, // jmp 0x8005
```

### Simple Machine Code Generator
I threw together a simple C program to facilitate building the binary files with specified machine code.
I used this instead of the script Ben used, but it is functionally identical. 

- [ ] Add the code.

### CA65 and linker file
### C runtime for CC65
### PS/2 Keyboard support (Bit Banging)
This started with the code from <http://sbc.rictor.org/io/pckb6522.html>.

I had to massage it to get it to work with CA65, the pins I was using PA0-1 and
interoperate with the C runtime environment I'm using.

It could be used with a USB keyboard that supports ps/2 signalling (most do with this adpater).

<https://www.instructables.com/USB-to-PS2-convertor/>

- [ ] Add USB wiring diagram
- [ ] Make it easier to change pin configuration

## To Do
### Create a makefile for the C build
### 65C51 serial interface
### SAA 1099P Sound Chips
### ENC28J60 8k RAM Ethernet MAC&PHY
### I2C
### Protoboard backplane
### PS/2 Keyboard support (65C22 shift registers)
### NES Gamepad
### Use 16-bit mode
### Serial loader
### Simple debugger
### BASIC ROM
### FORTH ROM
### Assembly monitor/debugger

## Links
https://eater.net/6502

https://www.cc65.org/

https://www.cc65.org/doc/customizing.html









