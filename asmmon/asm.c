#include "asm.h"

/**
 * Based on the instruction list for the 65816 a super-set of the 6502
 * instructions.
 */
const AsmInst AsmInstLibrary[256] =
{
    { "BRK", RegMode_StackInterrupt              }, // 00    2,
    { "ORA", RegMode_DirectIndexXIndirect        }, // 01    2,
    { "COP", RegMode_StackInterrupt              }, // 02    2,
    { "ORA", RegMode_StackRelative               }, // 03    2,
    { "TSB", RegMode_Direct                      }, // 04    2,
    { "ORA", RegMode_Direct                      }, // 05    2,
    { "ASL", RegMode_Direct                      }, // 06    2,
    { "ORA", RegMode_DirectIndirectLong          }, // 07    2,
    { "PHP", RegMode_Stack                       }, // 08    1,
    { "ORA", RegMode_Immediate                   }, // 09    2,
    { "ASL", RegMode_Accum                       }, // 0A    1,
    { "PHD", RegMode_Stack                       }, // 0B    1,
    { "TSB", RegMode_Absolute                    }, // 0C    3,
    { "ORA", RegMode_Absolute                    }, // 0D    3,
    { "ASL", RegMode_Absolute                    }, // 0E    3,
    { "ORA", RegMode_AbsoluteLong                }, // 0F    4,

    { "BPL", RegMode_PcRelative                  }, // 10    2,
    { "ORA", RegMode_DirectIndirectIndexY        }, // 11    2,
    { "ORA", RegMode_DirectIndirect              }, // 12    2,
    { "ORA", RegMode_StackRelativeIndirectIndexY }, // 13    2,
    { "TRB", RegMode_Direct                      }, // 14    2,
    { "ORA", RegMode_DirectIndexX                }, // 15    2,
    { "ASL", RegMode_DirectIndexX                }, // 16    2,
    { "ORA", RegMode_DirectIndirectLongIndexY    }, // 17    2,
    { "CLC", RegMode_Implied                     }, // 18    1,
    { "ORA", RegMode_AbsoluteIndexY              }, // 19    3,
    { "INC", RegMode_Accum                       }, // 1A    1,
    { "TCS", RegMode_Implied                     }, // 1B    1,
    { "TRB", RegMode_Absolute                    }, // 1C    3,
    { "ORA", RegMode_AbsoluteIndexX              }, // 1D    3,
    { "ASL", RegMode_AbsoluteIndexX              }, // 1E    3,
    { "ORA", RegMode_AbsoluteLongIndexX          }, // 1F    4,

    { "JSR", RegMode_Absolute                    }, // 20    3,
    { "AND", RegMode_DirectIndexXIndirect        }, // 21    2,
    { "JSR", RegMode_AbsoluteLong                }, // 22    4,
    { "AND", RegMode_StackRelative               }, // 23    2,
    { "BIT", RegMode_Direct                      }, // 24    2,
    { "AND", RegMode_Direct                      }, // 25    2,
    { "ROL", RegMode_Direct                      }, // 26    2,
    { "AND", RegMode_DirectIndirectLong          }, // 27    2,
    { "PLP", RegMode_Stack                       }, // 28    1,
    { "AND", RegMode_Immediate                   }, // 29    2,
    { "ROL", RegMode_Accum                       }, // 2A    1,
    { "PLD", RegMode_Stack                       }, // 2B    1,
    { "BIT", RegMode_Absolute                    }, // 2C    3,
    { "AND", RegMode_Absolute                    }, // 2D    3,
    { "ROL", RegMode_Absolute                    }, // 2E    3,
    { "AND", RegMode_AbsoluteLong                }, // 2F    4,

    { "BMI", RegMode_PcRelative                  }, // 30    2,
    { "AND", RegMode_DirectIndirectIndexY        }, // 31    2,
    { "AND", RegMode_DirectIndirect              }, // 32    2,
    { "AND", RegMode_StackRelativeIndirectIndexY }, // 33    2,
    { "BIT", RegMode_DirectIndexX                }, // 34    2,
    { "AND", RegMode_DirectIndexX                }, // 35    2,
    { "ROL", RegMode_DirectIndexX                }, // 36    2,
    { "AND", RegMode_DirectIndirectLongIndexY    }, // 37    2,
    { "SEC", RegMode_Implied                     }, // 38    1,
    { "AND", RegMode_AbsoluteIndexY              }, // 39    3,
    { "DEC", RegMode_Accum                       }, // 3A    1,
    { "TSC", RegMode_Implied                     }, // 3B    1,
    { "BIT", RegMode_AbsoluteIndexX              }, // 3C    3,
    { "AND", RegMode_AbsoluteIndexX              }, // 3D    3,
    { "ROL", RegMode_AbsoluteIndexX              }, // 3E    3,
    { "AND", RegMode_AbsoluteLongIndexX          }, // 3F    4,

    { "RTI", RegMode_Stack                       }, // 40    1,
    { "EOR", RegMode_DirectIndexXIndirect        }, // 41    2,
    { "WDM", RegMode_WDM                         }, // 42    2,
    { "EOR", RegMode_StackRelative               }, // 43    2,
    { "MVP", RegMode_BlockMove                   }, // 44    3,
    { "EOR", RegMode_Direct                      }, // 45    2,
    { "LSR", RegMode_Direct                      }, // 46    2,
    { "EOR", RegMode_DirectIndirectLong          }, // 47    2,
    { "PHA", RegMode_Stack                       }, // 48    1,
    { "EOR", RegMode_Immediate                   }, // 49    2,
    { "LSR", RegMode_Accum                       }, // 4A    1,
    { "PHK", RegMode_Stack                       }, // 4B    1,
    { "JMP", RegMode_Absolute                    }, // 4C    3,
    { "EOR", RegMode_Absolute                    }, // 4D    3,
    { "LSR", RegMode_Absolute                    }, // 4E    3,
    { "EOR", RegMode_AbsoluteLong                }, // 4F    4,

    { "BVC", RegMode_PcRelative                  }, // 50    2,
    { "EOR", RegMode_DirectIndirectIndexY        }, // 51    2,
    { "EOR", RegMode_DirectIndirect              }, // 52    2,
    { "EOR", RegMode_StackRelativeIndirectIndexY }, // 53    2,
    { "MVN", RegMode_BlockMove                   }, // 54    3,
    { "EOR", RegMode_DirectIndexX                }, // 55    2,
    { "LSR", RegMode_DirectIndexX                }, // 56    2,
    { "EOR", RegMode_DirectIndirectLongIndexY    }, // 57    2,
    { "CLI", RegMode_Implied                     }, // 58    1,
    { "EOR", RegMode_AbsoluteIndexY              }, // 59    3,
    { "PHY", RegMode_Stack                       }, // 5A    1,
    { "TCD", RegMode_Implied                     }, // 5B    1,
    { "JMP", RegMode_AbsoluteLong                }, // 5C    4,
    { "EOR", RegMode_AbsoluteIndexX              }, // 5D    3,
    { "LSR", RegMode_AbsoluteIndexX              }, // 5E    3,
    { "EOR", RegMode_AbsoluteLongIndexX          }, // 5F    4,

    { "RTS", RegMode_Stack                       }, // 60    1,
    { "ADC", RegMode_DirectIndexXIndirect        }, // 61    2,
    { "PER", RegMode_PcRelativeLong              }, // 62    3,
    { "ADC", RegMode_StackRelative               }, // 63    2,
    { "STZ", RegMode_Direct                      }, // 64    2,
    { "ADC", RegMode_Direct                      }, // 65    2,
    { "ROR", RegMode_Direct                      }, // 66    2,
    { "ADC", RegMode_DirectIndirectLong          }, // 67    2,
    { "PLA", RegMode_Stack                       }, // 68    1,
    { "ADC", RegMode_Immediate                   }, // 69    2,
    { "ROR", RegMode_Accum                       }, // 6A    1,
    { "RTL", RegMode_Stack                       }, // 6B    1,
    { "JMP", RegMode_AbsoluteIndirect            }, // 6C    3,
    { "ADC", RegMode_Absolute                    }, // 6D    3,
    { "ROR", RegMode_Absolute                    }, // 6E    3,
    { "ADC", RegMode_AbsoluteLong                }, // 6F    4,

    { "BVS", RegMode_PcRelative                  }, // 70    2,
    { "ADC", RegMode_DirectIndirectIndexY        }, // 71    2,
    { "ADC", RegMode_DirectIndirect              }, // 72    2,
    { "ADC", RegMode_StackRelativeIndirectIndexY }, // 73    2,
    { "STZ", RegMode_DirectIndexX                }, // 74    2,
    { "ADC", RegMode_DirectIndexX                }, // 75    2,
    { "ROR", RegMode_DirectIndexX                }, // 76    2,
    { "ADC", RegMode_DirectIndirectLongIndexY    }, // 77    2,
    { "SEI", RegMode_Implied                     }, // 78    1,
    { "ADC", RegMode_AbsoluteIndexY              }, // 79    3,
    { "PLY", RegMode_Stack                       }, // 7A    1,
    { "TDC", RegMode_Implied                     }, // 7B    1,
    { "JMP", RegMode_AbsoluteIndexXIndirect      }, // 7C    3,
    { "ADC", RegMode_AbsoluteIndexX              }, // 7D    3,
    { "ROR", RegMode_AbsoluteIndexX              }, // 7E    3,
    { "ADC", RegMode_AbsoluteLongIndexX          }, // 7F    4,

    { "BRA", RegMode_PcRelative                  }, // 80    2,
    { "STA", RegMode_DirectIndexXIndirect        }, // 81    2,
    { "BRL", RegMode_PcRelativeLong              }, // 82    3,
    { "STA", RegMode_StackRelative               }, // 83    2,
    { "STY", RegMode_Direct                      }, // 84    2,
    { "STA", RegMode_Direct                      }, // 85    2,
    { "STX", RegMode_Direct                      }, // 86    2,
    { "STA", RegMode_DirectIndirectLong          }, // 87    2,
    { "DEY", RegMode_Implied                     }, // 88    1,
    { "BIT", RegMode_Immediate                   }, // 89    2,
    { "TXA", RegMode_Implied                     }, // 8A    1,
    { "PHB", RegMode_Stack                       }, // 8B    1,
    { "STY", RegMode_Absolute                    }, // 8C    3,
    { "STA", RegMode_Absolute                    }, // 8D    3,
    { "STX", RegMode_Absolute                    }, // 8E    3,
    { "STA", RegMode_AbsoluteLong                }, // 8F    4,

    { "BCC", RegMode_PcRelative                  }, // 90    2,
    { "STA", RegMode_DirectIndirectIndexY        }, // 91    2,
    { "STA", RegMode_DirectIndirect              }, // 92    2,
    { "STA", RegMode_StackRelativeIndirectIndexY }, // 93    2,
    { "STY", RegMode_DirectIndexX                }, // 94    2,
    { "STA", RegMode_DirectIndexX                }, // 95    2,
    { "STX", RegMode_DirectIndexY                }, // 96    2,
    { "STA", RegMode_DirectIndirectLongIndexY    }, // 97    2,
    { "TYA", RegMode_Implied                     }, // 98    1,
    { "STA", RegMode_AbsoluteIndexY              }, // 99    3,
    { "TXS", RegMode_Implied                     }, // 9A    1,
    { "TXY", RegMode_Implied                     }, // 9B    1,
    { "STZ", RegMode_Absolute                    }, // 9C    3,
    { "STA", RegMode_AbsoluteIndexX              }, // 9D    3,
    { "STZ", RegMode_AbsoluteIndexX              }, // 9E    3,
    { "STA", RegMode_AbsoluteLongIndexX          }, // 9F    4,

    { "LDY", RegMode_Immediate                   }, // A0    2,
    { "LDA", RegMode_DirectIndexXIndirect        }, // A1    2,
    { "LDX", RegMode_Immediate                   }, // A2    2,
    { "LDA", RegMode_StackRelative               }, // A3    2,
    { "LDY", RegMode_Direct                      }, // A4    2,
    { "LDA", RegMode_Direct                      }, // A5    2,
    { "LDX", RegMode_Direct                      }, // A6    2,
    { "LDA", RegMode_DirectIndirectLong          }, // A7    2,
    { "TAY", RegMode_Implied                     }, // A8    1,
    { "LDA", RegMode_Immediate                   }, // A9    2,
    { "TAX", RegMode_Implied                     }, // AA    1,
    { "PLB", RegMode_Stack                       }, // AB    1,
    { "LDY", RegMode_Absolute                    }, // AC    3,
    { "LDA", RegMode_Absolute                    }, // AD    3,
    { "LDX", RegMode_Absolute                    }, // AE    3,
    { "LDA", RegMode_AbsoluteLong                }, // AF    4,

    { "BCS", RegMode_PcRelative                  }, // B0    2,
    { "LDA", RegMode_DirectIndirectIndexY        }, // B1    2,
    { "LDA", RegMode_DirectIndirect              }, // B2    2,
    { "LDA", RegMode_StackRelativeIndirectIndexY }, // B3    2,
    { "LDY", RegMode_DirectIndexX                }, // B4    2,
    { "LDA", RegMode_DirectIndexX                }, // B5    2,
    { "LDX", RegMode_DirectIndexY                }, // B6    2,
    { "LDA", RegMode_DirectIndirectLongIndexY    }, // B7    2,
    { "CLV", RegMode_Implied                     }, // B8    1,
    { "LDA", RegMode_AbsoluteIndexY              }, // B9    3,
    { "TSX", RegMode_Implied                     }, // BA    1,
    { "TYX", RegMode_Implied                     }, // BB    1,
    { "LDY", RegMode_AbsoluteIndexX              }, // BC    3,
    { "LDA", RegMode_AbsoluteIndexX              }, // BD    3,
    { "LDX", RegMode_AbsoluteIndexY              }, // BE    3,
    { "LDA", RegMode_AbsoluteLongIndexX          }, // BF    4,

    { "CPY", RegMode_Immediate                   }, // C0    2,
    { "CMP", RegMode_DirectIndexXIndirect        }, // C1    2,
    { "REP", RegMode_Immediate                   }, // C2    2,
    { "CMP", RegMode_StackRelative               }, // C3    2,
    { "CPY", RegMode_Direct                      }, // C4    2,
    { "CMP", RegMode_Direct                      }, // C5    2,
    { "DEC", RegMode_Direct                      }, // C6    2,
    { "CMP", RegMode_DirectIndirectLong          }, // C7    2,
    { "INY", RegMode_Implied                     }, // C8    1,
    { "CMP", RegMode_Immediate                   }, // C9    2,
    { "DEX", RegMode_Implied                     }, // CA    1,
    { "WAI", RegMode_Implied                     }, // CB    1,
    { "CPY", RegMode_Absolute                    }, // CC    3,
    { "CMP", RegMode_Absolute                    }, // CD    3,
    { "DEC", RegMode_Absolute                    }, // CE    3,
    { "CMP", RegMode_AbsoluteLong                }, // CF    4,

    { "BNE", RegMode_PcRelative                  }, // D0    2,
    { "CMP", RegMode_DirectIndirectIndexY        }, // D1    2,
    { "CMP", RegMode_DirectIndirect              }, // D2    2,
    { "CMP", RegMode_StackRelativeIndirectIndexY }, // D3    2,
    { "PEI", RegMode_DirectIndirect              }, // D4    2,
    { "CMP", RegMode_DirectIndexX                }, // D5    2,
    { "DEC", RegMode_DirectIndexX                }, // D6    2,
    { "CMP", RegMode_DirectIndirectLongIndexY    }, // D7    2,
    { "CLD", RegMode_Implied                     }, // D8    1,
    { "CMP", RegMode_AbsoluteIndexY              }, // D9    3,
    { "PHX", RegMode_Stack                       }, // DA    1,
    { "STP", RegMode_Implied                     }, // DB    1,
    { "JML", RegMode_AbsoluteIndirect            }, // DC    3,
    { "CMP", RegMode_AbsoluteIndexX              }, // DD    3,
    { "DEC", RegMode_AbsoluteIndexX              }, // DE    3,
    { "CMP", RegMode_AbsoluteLongIndexX          }, // DF    4,

    { "CPX", RegMode_Immediate                   }, // E0    2,
    { "SBC", RegMode_DirectIndexXIndirect        }, // E1    2,
    { "SEP", RegMode_Immediate                   }, // E2    2,
    { "SBC", RegMode_StackRelative               }, // E3    2,
    { "CPX", RegMode_Direct                      }, // E4    2,
    { "SBC", RegMode_Direct                      }, // E5    2,
    { "INC", RegMode_Direct                      }, // E6    2,
    { "SBC", RegMode_DirectIndirectLong          }, // E7    2,
    { "INX", RegMode_Implied                     }, // E8    1,
    { "SBC", RegMode_Immediate                   }, // E9    2,
    { "NOP", RegMode_Implied                     }, // EA    1,
    { "XBA", RegMode_Implied                     }, // EB    1,
    { "CPX", RegMode_Absolute                    }, // EC    3,
    { "SBC", RegMode_Absolute                    }, // ED    3,
    { "INC", RegMode_Absolute                    }, // EE    3,
    { "SBC", RegMode_AbsoluteLong                }, // EF    4,

    { "BEQ", RegMode_PcRelative                  }, // F0    2,
    { "SBC", RegMode_DirectIndirectIndexY        }, // F1    2,
    { "SBC", RegMode_DirectIndirect              }, // F2    2,
    { "SBC", RegMode_StackRelativeIndirectIndexY }, // F3    2,
    { "PEA", RegMode_Absolute                    }, // F4    3,
    { "SBC", RegMode_DirectIndexX                }, // F5    2,
    { "INC", RegMode_DirectIndexX                }, // F6    2,
    { "SBC", RegMode_DirectIndirectLongIndexY    }, // F7    2,
    { "SED", RegMode_Implied                     }, // F8    1,
    { "SBC", RegMode_AbsoluteIndexY              }, // F9    3,
    { "PLX", RegMode_Stack                       }, // FA    1,
    { "XCE", RegMode_Implied                     }, // FB    1,
    { "JSR", RegMode_AbsoluteIndexXIndirect      }, // FC    3,
    { "SBC", RegMode_AbsoluteIndexX              }, // FD    3,
    { "INC", RegMode_AbsoluteIndexX              }, // FE    3,
    { "SBC", RegMode_AbsoluteLongIndexX          }, // FF    4,


};

typedef struct RegModeDesc
{
    uint16_t size;
    const char* desc;
} RegModeDesc;

const RegModeDesc RegModeLibrary[] =
{
    { 2, "%1%0"      }, // RegMode_Absolute,
    { 2, "%1%0,X"    }, // RegMode_AbsoluteIndexX,
    { 2, "(%1%0,X)"  }, // RegMode_AbsoluteIndexXIndirect,
    { 2, "%1%0,Y"    }, // RegMode_AbsoluteIndexY,
    { 2, "(%1%0)"    }, // RegMode_AbsoluteIndirect,
    { 3, "%2%1%0"    }, // RegMode_AbsoluteLong,
    { 3, "%2%1%0,X"  }, // RegMode_AbsoluteLongIndexX,
    { 0, "A"         }, // RegMode_Accum,
    { 2, "%1,%0"     }, // RegMode_BlockMove,
    { 1, "%0"        }, // RegMode_Direct,
    { 1, "%0,X"      }, // RegMode_DirectIndexX,
    { 1, "(%0,X)"    }, // RegMode_DirectIndexXIndirect,
    { 1, "%0,Y"      }, // RegMode_DirectIndexY,
    { 1, "(%0)"      }, // RegMode_DirectIndirect,
    { 1, "(%0),Y"    }, // RegMode_DirectIndirectIndexY,
    { 1, "[%0]"      }, // RegMode_DirectIndirectLong,
    { 1, "[%0],Y"    }, // RegMode_DirectIndirectLongIndexY,
    { 1, "#%0"       }, // RegMode_Immediate,
    { 0, ""          }, // RegMode_Implied,
    { 1, "%0,PC"     }, // RegMode_PcRelative,
    { 2, "%1%0,PC"   }, // RegMode_PcRelativeLong,
    { 0, ""          }, // RegMode_Stack,
    { 1, "#%0"       }, // RegMode_StackInterrupt,?
    { 1, "%0,S"      }, // RegMode_StackRelative,
    { 1, "(%0,S),Y"  }, // RegMode_StackRelativeIndirectIndexY,
    { 1, "?%0"       }, // RegMode_WDM,?
};

const char hex2digit[16] =
{
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void byte2hex( char* dst, uint8_t data )
{
    dst[0] = hex2digit[ data >>  4 ];
    dst[1] = hex2digit[ data & 0xF ];
}

int unassemble(  char* dst, uint8_t* data)
{
    // Decode Instruction Mnemonic
    const AsmInst* inst = &AsmInstLibrary[ *data ];
    const RegModeDesc* rm = &RegModeLibrary[ inst->registerMode ];
    const char* src=rm->desc;

    // Display Mnemonic
    *dst++=inst->mnemonic[0];
    *dst++=inst->mnemonic[1];
    *dst++=inst->mnemonic[2];
    *dst++=' ';

    // Decode Register Mode
    data += rm->size;
    while( *src != '\0' )
    {
        if('%' == *src)
        {
            *dst++ = hex2digit[ *data >>  4 ];
            *dst++ = hex2digit[ *data & 0xF ];
            data--;
            src+=2;
        }
        else
        {
            *dst++=*src++;
        }
    }

    // Terminate output string
    *dst='\0';

    // return number of bytes decoded
    return (rm->size+1);
}
