/**
 * @file    CLI.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */
#ifndef   CLI_H
#define   CLI_H

/* Includes ******************************************************************/
#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines *******************************************************************/
#define SUCCESS 0

/* Types *********************************************************************/
/**
 * This pointer type defines the function signature expected by CLI callbacks.
 *
 * @param argc number of arguments
 * @param argv a list of string arguments
 * @return Error Code, 0 means success
 */
typedef int (*CLI_CommandFunction) (int argc, char** argv);
//typedef int (*CLI_CommandFunction) (int argc, char** argv, char* out, size_t out_size);

typedef struct CLI_CommandEntry
{
  const char* command;
  // const char* helpText;
  // const ArgParse arguments;
  CLI_CommandFunction callBack;
} CLI_CommandEntry;

/* Interfaces ****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
extern const char* (*CLI_getPrompt) (void);

/* Data **********************************************************************/

/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
void CLI_registerCommandEntryTable ( const CLI_CommandEntry* table, size_t size );

/**
 * [Description]
 *
 * @param
 * @return
 */
void CLI_loop(void);

/**
 * [Description]
 *
 * @param
 * @return
 */
int CLI_getLastReturnCode (void);


#ifdef  __cplusplus
}
#endif

#endif // CLI_H
