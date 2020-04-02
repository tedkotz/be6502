# be6502
Collection of notes, software and upgrades for Ben Eater's 6502 Computer

## Description
I've been having a ton of fun with this project. Probably to the point my coworkers are sick of hearing about it. I had a lot of the parts list for the computer laying around, so I just ordered Ben's Clock kit. While I waiting for that I used my arduino mega to generate the clock as well as look at the signals. Which was fun because I could clock up to 8Mhz.

## Hardware
### 65C816 CPU
I'm using the W65C816 instead of the W65C02, which is an almost identical CPU, but can be put into a 16-bit mode if I want to try to extend this project later. It required a slight adjustment to how the control pins are tied, but as of the second video it is still working well. If any one is interested:
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
### 4 Row Display
### Address Decoding logic
#### NAND (7400)
#### 3 to 8 Line decoder (74138)
#### GAL16V8
## Software
Looking good I threw together this little snippet of code that uses the rotate and conditional instructions to create a bouncing light effect
    0xa9, 0xff, // lda 0xff
    0x8d, 0x02, 0x60, // sta 0x6002
    0x18, // clc
    0xa9, 0x01, // lda 0x01
    0x8d, 0x00, 0x60, // sta 0x6000
    0x2a, // rol
    0x90, -6, // bcc -6
    0x18, // clc
    0xa9, 0x80, // lda 0x80
    0x8d, 0x00, 0x60, // sta 0x6000
    0x6a, // ror
    0x90, -6, // bcc -6
    0x4c, 0x05, 0x80, // jmp 0x8005
### Simple Machine Code Generator
### CA65 and linker file
### C runtime fro CA55
## To Do
### 65C51 serial interface
### SAA 1099P Sound Chips
### ENC28J60 8k RAM Ethernet MAC&PHY
### I2C
### Protoboard backplane
### PS/2 Keyboard support
### Use 16-bit mode
## Links






