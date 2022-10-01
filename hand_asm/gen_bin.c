/**
 * This file helps with hand assembling programs or generating rom images.
 * I wrote it for use with the first few videos in ben eater's 6502 computer
 * series, with a design similar to his python script for the same purpose.
 *
 * It fills memory with nop instructions, Copies the hand assembled code in prog
 * into the beginning of the EEPROM image and points the reset vector to the
 * start of ROM.
 *
 * Use:
 * - gcc gen_bin.c
 * - ./a.out > prog.bin
 * - hexdump -C prog.bin
 * - minipro -p AT28C256 -w prog.bin
 */

#include <stdio.h>

// NOP
char prog[] =
{
  0xea,             // nop
};

// prog1 - test write to VIA outputs
//char prog[] =
//{
//  0xa9, 0x42,       // lda 0x42
//  0x8d, 0x00, 0x60  // sta 0x6000
//};

// prog2 - alternate blink odd/even VIA outputs.
//char prog[] =
//{
//  0xa9, 0xff,       // lda 0xff
//  0x8d, 0x02, 0x60, // sta 0x6002
//  0xa9, 0xaa,       // lda 0xaa
//  0x8d, 0x00, 0x60  // sta 0x6000
//  0xa9, 0x55,       // lda 0x55
//  0x8d, 0x00, 0x60  // sta 0x6000
//  0x4c, 0x05, 0x80, // jmp 0x8005
//};

// prog3 - chasing lights VIA outputs.
//char prog[] =
//{
//  0xa9, 0xff,       // lda 0xff
//  0x8d, 0x02, 0x60, // sta 0x6002
//  0xa9, 0x01,       // lda 0x01
//  0x8d, 0x00, 0x60, // sta 0x6000
//  0x2a,             // rol
//  0x4c, 0x07, 0x80, // jmp 0x8005
//};

// prog4 - bouncing lights VIA outputs.
//char prog[] =
//{
//  0xa9, 0xff,       // lda 0xff
//  0x8d, 0x02, 0x60, // sta 0x6002
//  0x18,             // clc
//  0xa9, 0x01,       // lda 0x01
//  0x8d, 0x00, 0x60, // sta 0x6000
//  0x2a,             // rol
//  0x90, -6,         // bcc -6
//  0x18,             // clc
//  0xa9, 0x80,       // lda 0x80
//  0x8d, 0x00, 0x60, // sta 0x6000
//  0x6a,             // ror
//  0x90, -6,         // bcc -6
//  0x4c, 0x05, 0x80, // jmp 0x8005
//};


int main(int argc, char** argv)
{
  static const unsigned int ROM_SIZE = 0x8000;
  static const unsigned int ROM_START = 0x8000;
  static const unsigned int RESET_VECTOR_ADDR = 0xFFFC;
  static const unsigned int START_ADDR = ROM_START;

  char mem[ROM_SIZE];
  int i;

  // Initially fill memory with NOOP
  for(i = 0; i<ROM_SIZE; i++)
  {
    mem[i]=0xea;
  }

  // Set reset vector LSB
  mem[RESET_VECTOR_ADDR-ROM_START]  = START_ADDR       & 0x00FF;

  // Set reset vector MSB
  mem[(RESET_VECTOR_ADDR-ROM_START)+1]=(START_ADDR >> 8) & 0x00FF;

  // Copy program into start of ROM
  for( i=0; i<sizeof(prog); ++i )
  {
    mem[i]=prog[i];
  }

  // Dump ROM image raw to stdout
  for(i = 0; i<ROM_SIZE; i++)
  {
    printf("%c", mem[i]);
  }

  return 0;
}
