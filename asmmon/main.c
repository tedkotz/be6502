#include "io_echo.h"
#include "CLI.h"
#include "asm.h"
#include <conio.h>
#include <stdio.h>

static char shared_val=0;
#define DEFAULT_ADDR 0x500

void main_interrupt( void) {
    shared_val++;
}

/**
 * Simple example starting place main callback.
 * A good example to copy to start.
 *
 * look for the commandEntryTable to see how this function is included.
 *
 * @param argc number of arguments
 * @param argv a list of string arguments
 * @return Error Code, 0 means success
 */
int hw_main (int /*argc*/, char** /*argv*/)
{
  while( !kbhit() )
  {
    printf("Hello World\n");
  }

  return 0;
}

char vischar( char c )
{
    if( c<' ' || c>'~' )
    {
        return '.';
    }
    return c;
}


void printDump( const char* addr )
{
    printf("%04X %02X %02X %02X %02X%c%c%c%c\n",
           (int)addr,
              (int)addr[0],     (int)addr[1],     (int)addr[2],     (int)addr[3],
           vischar(addr[0]), vischar(addr[1]), vischar(addr[2]), vischar(addr[3])
          );
}

int dump_main (int argc, char** argv)
{
    static char* addr=(char *)DEFAULT_ADDR;
    if( argc > 1 )
    {
        addr = (char *)strtol(argv[1], NULL, 16);
    }
    printDump( addr );
    addr += 4;
    return (int)addr;
}

int enter_main (int argc, char** argv)
{
    register char* addr;
    char* startAddr;
    int i;
    if( argc < 2 )
    {
        return -1;
    }
    startAddr = addr = (char *)strtol(argv[1], NULL, 16);

    for( i=2; i<argc; ++i )
    {
        *addr++ = (char)strtol(argv[i], NULL, 16);
    }

    printDump( startAddr );
    return (int)addr;
}

int fill_main (int argc, char** argv)
{
    // Fundamentally this is enter and then copy
    register char* addr;
    register char* src;
    char* startAddr;
    char* endAddr;
    int i;

    if( argc < 4 )
    {
        return -1;
    }
    startAddr = src = addr = (char *)strtol(argv[1], NULL, 16);
    endAddr = (char *)strtol(argv[2], NULL, 16);

    // Enter
    for( i=3; i<argc; ++i )
    {
        *addr++ = (char)strtol(argv[i], NULL, 16);
    }

    // Copy
    while( addr != endAddr )
    {
        *addr++ = *src++;
    }
    *addr++ = *src++;

    printDump( startAddr );
    return (int)addr;
}

int go_main (int argc, char** argv)
{
    int (*addr) (int) = (int(*)(int))DEFAULT_ADDR;
    int arg = 0;
    if( argc > 1 )
    {
        addr = (int(*)(int))strtol(argv[1], NULL, 16);
    }
    if( argc > 2 )
    {
        arg = (int)strtol(argv[2], NULL, 16);
    }
    return addr(arg);
}

int hex_main (int argc, char** argv)
{
    int returnVal;
    int arg1 = 0;
    int arg2 = 0;
    if( argc > 1 )
    {
        arg1 = (int)strtol(argv[1], NULL, 16);
    }
    if( argc > 2 )
    {
        arg2 = (int)strtol(argv[2], NULL, 16);
    }
    returnVal = arg1-arg2;
    printf("S=%04X D=%04X\n", arg1+arg2, returnVal);

    return returnVal;
}

int move_main (int argc, char** argv)
{
    register char* dst;
    register char* src;
    char* startAddr;
    char* endAddr;
    char* destAddr;
    if( argc < 4 )
    {
        return -1;
    }
    startAddr = (char *)strtol(argv[1], NULL, 16);
    endAddr = (char *)strtol(argv[2], NULL, 16);
    destAddr = (char *)strtol(argv[3], NULL, 16);

    if( (destAddr <= endAddr) && (destAddr > startAddr) )
    {
        // region overlap requires reverse copy
        src = endAddr;
        dst = destAddr + (endAddr - startAddr);
        while( src != startAddr )
        {
            *dst-- = *src--;
        }
    }
    else
    {
        src=startAddr;
        dst=destAddr;
        while( src != endAddr )
        {
            *dst++ = *src++;
        }
    }
    *dst = *src;

    printDump( destAddr );
    return 1 + (int)destAddr + (int)endAddr - (int)startAddr;
}

int unassemble_main (int argc, char** argv)
{
    char output[16];
    uint8_t bytes;
    static char* addr=(char *)DEFAULT_ADDR;
    if( argc > 1 )
    {
        addr = (char *)strtol(argv[1], NULL, 16);
    }
    bytes = unassemble( output, addr );
    printf("%04X %s\n", (int)addr, output);
    addr += bytes;
    return (int)addr;
}


/**
 * [Description]
 *
 * @param
 * @return
 */
const char* getPrompt (void)
{
  static char prompt[32];
  snprintf(prompt, 31, "\r%X>", CLI_getLastReturnCode() );
  return prompt;
}

int main( )
{
    static const CLI_CommandEntry commandEntryTable[] =
    {
      { "D"       , dump_main       },
      { "DUMP"    , dump_main       },
      { "E"       , enter_main      },
      { "ENTER"   , enter_main      },
      { "F"       , fill_main       },
      { "FILL"    , fill_main       },
      { "G"       , go_main         },
      { "GO"      , go_main         },
      { "H"       , hex_main        },
      { "HEX"     , hex_main        },
      { "M"       , move_main       },
      { "MOVE"    , move_main       },
      { "U"       , unassemble_main },
      { "UNASM"   , unassemble_main },
      { "HW"      , hw_main         },
    };

    /* Data ******************************************************************/
    //char tmp[32];

    /* Setup *****************************************************************/
    printDump( (const char*)DEFAULT_ADDR );

    CLI_registerCommandEntryTable( commandEntryTable, sizeof(commandEntryTable)/sizeof(commandEntryTable[0]));
    CLI_getPrompt = getPrompt;

    /* Loop ******************************************************************/
    for(;;)
    {
        CLI_loop();
    }

    return 0;
}

