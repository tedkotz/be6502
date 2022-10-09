/**
 * @file    CLI.cpp
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */

/* Includes ******************************************************************/
/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */

#include "CLI.h"

#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>


#define MAX_IO_BUFFER 128
#define F(X) X
#define strcpy_P strcpy
#define strncpy_P strncpy
#define E2BIG (-7)
#define ENOMSG (-5)


static int returnCode = 0;
static const CLI_CommandEntry* commandEntryTable=NULL;
static size_t commandEntryTableSize=0;

static const char* DEFAULTgetPrompt (void)
{
  return "\r> ";
}

const char* (*CLI_getPrompt) (void) = DEFAULTgetPrompt;

void CLI_registerCommandEntryTable ( const CLI_CommandEntry* table, size_t size )
{
  commandEntryTable = table;
  commandEntryTableSize = size;
}

int CLI_getLastReturnCode (void)
{
  return returnCode;
}


static bool commandTest( const char* input, const char* testValue )
{
  while( *testValue != '\0' && *input != '\0')
  {
    if( toupper(*input++) != *testValue++ )
    {
      return false;
    }
  }

  return ( toupper(*input) == *testValue );
}

static int evaluate ( char* out, size_t out_size, char* in )
{
  char* argv[16];
  int argc=0;
//  char delim[5];
//  strcpy_P(delim, (const char*)F(" \t\n\r"));
  char delim[5] = " \t\n\r";
  char* token;
  size_t i,j;
  token=strtok(in, delim);

  while( token != NULL )
  {
    if (argc >= 16)
    {
      printf( F("Syntax Error. Argument list(%d) too long.\n"), argc);
      return -E2BIG;
    }
    argv[argc++]=token;
    token=strtok(NULL, delim);
  }

  for( i=0; i<commandEntryTableSize; ++i )
  {
    if ( commandTest( argv[0], commandEntryTable[i].command ) )
    {
      //return commandEntryTable[i].callBack(argc, argv, out, out_size);
      //strncpy_P( out, (const char *)F("\nDone.\n"), out_size-1);
      return commandEntryTable[i].callBack(argc, argv);
    }
  }

  if ( commandTest( argv[0], "HELP" ) )
  {
    for( i=0; out_size > 1 && i<commandEntryTableSize; ++i )
    {
      j=0;
      while( out_size > 2 && commandEntryTable[i].command[j] != '\0' )
      {
        *out++ = commandEntryTable[i].command[j++];
        --out_size;
      }
      *out++ = ' ';
      --out_size;
    }
    *out++ = '\n';
    *out++ = '\0';
    --out_size;
    return CLI_getLastReturnCode();
  }

  printf( out, out_size-1, F("Syntax Error. Unknown command \"%s\".\n"), argv[0]);
  return -ENOMSG;
}


int read(int /*fildes*/, char *buf, size_t nbyte);

int read_until(char *buf, size_t nbyte, char term)
{
  size_t index=0;
  while( index<nbyte )
  {
      index += read(0, &buf[index], 1);
      if( buf[index-1] == term )
      {
          return index;
      }
  }
  return index;
}

void CLI_loop(void)
{
  size_t OutIndex;
  static char iobuffer[MAX_IO_BUFFER];
  // The Main REPL of the CLI

  // Read

  // Print Prompt
  printf("%s", CLI_getPrompt() );
  //puts( CLI_getPrompt() );
  OutIndex = read_until(iobuffer, MAX_IO_BUFFER - 1, '\n');

  while( OutIndex == 0 )
  {
    //puts( CLI_getPrompt() );
    printf("%s", CLI_getPrompt() );
    OutIndex = read_until(iobuffer, MAX_IO_BUFFER - 1, '\n');
  }
  iobuffer[OutIndex++]='\0';
  iobuffer[OutIndex]='\0';

  // Evaluate
  returnCode=evaluate(&iobuffer[OutIndex],MAX_IO_BUFFER-OutIndex, iobuffer);

  // Print
  //puts(&iobuffer[OutIndex]);
  printf("%s", &iobuffer[OutIndex]);
}
