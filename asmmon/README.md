Assembly Monitor
================

The purpose of this tool it to try to craft a simple Assembly Debug/Monitor  tool
to allow someone using the computer to manually enter, update and debug programs.
This gives the system a usable initial state.

The inspirations for this are the APPLE 1 wozmonitor, but with an interface more
directly based off the DOS DEBUG command.

Initial Features
----------------

The minimum set of commands needed are to dump memory, enter RAM and then JMP into memory.

Here is a table of commands in approximately implementation order.

|   |Name       | Command                                     |Notes                                                                                       |Status                                    |
|---|-----------|---------------------------------------------|--------------------------------------------------------------------------------------------|------------------------------------------|
| X |dump       | D address                                   |Displays the contents of a portion of memory                                                |                                          |
| X |enter      | E address [list]                            |Enters data into memory starting at a specified address                                     |                                          |
| X |move       | M range address                             |Copies the contents of a block of memory                                                    |                                          |
| X |fill       | F range list                                |Fills a range of memory with specified values                                               |                                          |
| X |go         | G [address] [parameter]                     |Calls into the specified address storing the parameter in register X:A                      |                                          |
| X |help       | ?                                           |Displays a list of commands                                                                 |                                          |
|   |hex        | H value1 value2                             |Performs hexadecimal arithmetic (2's Complement)                                            |                                          |
|   |compare    | C range address                             |Compares two portions of memory                                                             |                                          |
|   |search     | S range list                                |Searches a portion of memory for a specified pattern of one or more byte values             |                                          |
| X |unassemble | U [range]                                   |Disassembles bytes and displays the corresponding source statements                         |Needs Mnemonic Table                      |
|   |assemble   | A [address]                                 |Assembles mnemonics                                                                         |Needs Mnemonic Table                      |
|   |register   | R [register]                                |Displays or alters the contents of one or more registers                                    |Needs to access state/maybe BRK context   |
|   |trace/step | T [=address] [number]                       |Executes one instruction and then displays CPU state                                        |Needs to access state/maybe BRK context   |
|   |proceed    | P [=address] [number]                       |Executes a loop, a repeated string instruction, a software interrupt, or a subroutine       |Needs to access state/maybe BRK context   |
|   |quit       | Q                                           |Stops the Debug session                                                                     |Reboot?                                   |


### Other Potential Requirements
- Must work on 2x16 display from Base Kit
- Support menu arrow keys based entry first input can be any command rest are limited to hex-digit and space.
- named jumps for at least basic single argument functions: cgetc/GTC, cputc/PTC, cgets/GTS, cputs/PTS, cputhex/PTH


### TODO
- [ ] Repeat Last Instruction.
- [ ] Syntax maintains return code.
- [ ] Pass return code into next CLI
- [ ] Implement in ASM
- [ ] Quoted string support to Enter text
- [ ] have make file automatically build echo_console for dependencies
- [ ] calculate header dependencies
- [ ] delete does not actually erase input
- [ ] Environment variable support could allow named jumps into ROM



Links and References
--------------------

### Old DOS commands

|Name       | Command                                     |Notes                                                                                                                                                                         |
|-----------|---------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|help       | ?                                           |Displays a list of debug commands                                                                                                                                             |
|assemble   | A [address]                                 |Assembles 8086/8087/8088 mnemonics                                                                                                                                            |
|compare    | C range address                             |Compares two portions of memory                                                                                                                                               |
|dump       | D [range]                                   |Displays the contents of a portion of memory                                                                                                                                  |
|enter      | E address [list]                            |Enters data into memory starting at a specified address                                                                                                                       |
|fill       | F range list                                |Fills a range of memory with specified values                                                                                                                                 |
|go         | G [=address] [addresses]                    |Runs the executable file that is in memory                                                                                                                                    |
|hex        | H value1 value2                             |Performs hexadecimal arithmetic (2's Complement)                                                                                                                              |
|input      | I port                                      |Displays one byte value from a specified port                                                                                                                                 |
|load       | L [address] [drive] [firstsector] [number]  |Loads the contents of a file or disk sectors into memory                                                                                                                      |
|move       | M range address                             |Copies the contents of a block of memory                                                                                                                                      |
|name       | N [pathname] [arglist]                      |Specifies a file for an l or w command, or specifies the parameters for the file you are testing                                                                              |
|output     | O port byte                                 |Sends a single byte value to an output port                                                                                                                                   |
|proceed    | P [=address] [number]                       |Executes a loop, a repeated string instruction, a software interrupt, or a subroutine                                                                                         |
|quit       | Q                                           |Stops the Debug session                                                                                                                                                       |
|register   | R [register]                                |Displays or alters the contents of one or more registers                                                                                                                      |
|search     | S range list                                |Searches a portion of memory for a specified pattern of one or more byte values                                                                                               |
|trace/step | T [=address] [number]                       |Executes one instruction and then displays the contents of all registers, the status of all flags, and the decoded form of the instruction that Debug will execute next       |
|unassemble | U [range]                                   |Disassembles bytes and displays the corresponding source statements                                                                                                           |
|write      | W [address] [drive] [firstsector] [number]  |Writes the file being tested to a disk                                                                                                                                        |
|XMMS alloc | XA                                          |Allocates expanded memory                                                                                                                                                     |
|XMMS del   | XD                                          |Deallocates expanded memory                                                                                                                                                   |
|XMMS map   | XM                                          |Maps expanded memory pages                                                                                                                                                    |
|XMMS stats | XS                                          |Displays the status of expanded memory                                                                                                                                        |




- [DOS DEBUG](https://thestarman.pcministry.com/asm/debug/debug2.htm)
- [WOZ MON](https://www.sbprojects.net/projects/apple1/wozmon.php)



### Format Notes
```
Output:
0100 00 01 02 03....
0104 04 05 06 07

0100:ASMA (0123)

e 500 a9 ef a2 be 60
```
