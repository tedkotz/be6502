

/**
 * Based on the instruction list for the 65816 a super-set of the 6502
 * instructions.
 */
const AsmInst AsmInstLibrary[256] =
{
    { "BRK", 2, RegMode_StackInterrupt              }, // 00
    { "ORA", 2, RegMode_DirectIndexXIndirect        }, // 01
    { "COP", 2, RegMode_StackInterrupt              }, // 02
    { "ORA", 2, RegMode_StackRelative               }, // 03
    { "TSB", 2, RegMode_Direct                      }, // 04
    { "ORA", 2, RegMode_Direct                      }, // 05
    { "ASL", 2, RegMode_Direct                      }, // 06
    { "ORA", 2, RegMode_DirectIndirectLong          }, // 07
    { "PHP", 1, RegMode_Stack                       }, // 08
    { "ORA", 2, RegMode_Immediate                   }, // 09
    { "ASL", 1, RegMode_Accum                       }, // 0A
    { "PHD", 1, RegMode_Stack                       }, // 0B
    { "TSB", 3, RegMode_Absolute                    }, // 0C
    { "ORA", 3, RegMode_Absolute                    }, // 0D
    { "ASL", 3, RegMode_Absolute                    }, // 0E
    { "ORA", 4, RegMode_AbsoluteLong                }, // 0F

    { "BPL", 2, RegMode_PcRelative                  }, // 10
    { "ORA", 2, RegMode_DirectIndirectIndexY        }, // 11
    { "ORA", 2, RegMode_DirectIndirect              }, // 12
    { "ORA", 2, RegMode_StackRelativeIndirectIndexY }, // 13
    { "TRB", 2, RegMode_Direct                      }, // 14
    { "ORA", 2, RegMode_DirectIndexX                }, // 15
    { "ASL", 2, RegMode_DirectIndexX                }, // 16
    { "ORA", 2, RegMode_DirectIndirectLongIndexY    }, // 17
    { "CLC", 1, RegMode_Implied                     }, // 18
    { "ORA", 3, RegMode_AbsoluteIndexY              }, // 19
    { "INC", 1, RegMode_Accum                       }, // 1A
    { "TCS", 1, RegMode_Implied                     }, // 1B
    { "TRB", 3, RegMode_Absolute                    }, // 1C
    { "ORA", 3, RegMode_AbsoluteIndexX              }, // 1D
    { "ASL", 3, RegMode_AbsoluteIndexX              }, // 1E
    { "ORA", 4, RegMode_AbsoluteLongIndexX          }, // 1F

    { "JSR", 3, RegMode_Absolute                    }, // 20
    { "AND", 2, RegMode_DirectIndirectIndexX        }, // 21
    { "JSR", 4, RegMode_AbsoluteLong                }, // 22
    { "AND", 2, RegMode_StackRelative               }, // 23
    { "BIT", 2, RegMode_Direct                      }, // 24
    { "AND", 2, RegMode_Direct                      }, // 25
    { "ROL", 2, RegMode_Direct                      }, // 26
    { "AND", 2, RegMode_DirectIndirectLong          }, // 27
    { "PLP", 1, RegMode_Stack                       }, // 28
    { "AND", 2, RegMode_Immediate                   }, // 29
    { "ROL", 1, RegMode_Accum                       }, // 2A
    { "PLD", 1, RegMode_Stack                       }, // 2B
    { "BIT", 3, RegMode_Absolute                    }, // 2C
    { "AND", 3, RegMode_Absolute                    }, // 2D
    { "ROL", 3, RegMode_Absolute                    }, // 2E
    { "AND", 4, RegMode_AbsoluteLong                }, // 2F

    { "BMI", 2, RegMode_PcRelative                  }, // 30
    { "AND", 2, RegMode_DirectIndirectIndexY        }, // 31
    { "AND", 2, RegMode_DirectIndirect              }, // 32
    { "AND", 2, RegMode_StackRelativeIndirectIndexY }, // 33
    { "BIT", 2, RegMode_DirectIndexX                }, // 34
    { "AND", 2, RegMode_DirectIndexX                }, // 35
    { "ROL", 2, RegMode_DirectIndexX                }, // 36
    { "AND", 2, RegMode_DirectIndirectLongIndexY    }, // 37
    { "SEC", 1, RegMode_Implied                     }, // 38
    { "AND", 3, RegMode_AbsoluteIndexY              }, // 39
    { "DEC", 1, RegMode_Accum                       }, // 3A
    { "TSC", 1, RegMode_Implied                     }, // 3B
    { "BIT", 3, RegMode_AbsoluteIndexX              }, // 3C
    { "AND", 3, RegMode_AbsoluteIndexX              }, // 3D
    { "ROL", 3, RegMode_AbsoluteIndexX              }, // 3E
    { "AND", 4, RegMode_AbsoluteLongIndexX          }, // 3F

    { "RTI", 1, RegMode_Stack                       }, // 40
    { "EOR", 2, RegMode_DirectIndirectIndexX        }, // 41
    { "WDM", 2, RegMode_WDM                         }, // 42
    { "EOR", 2, RegMode_StackRelative               }, // 43
    { "MVP", 3, RegMode_BlockMove                   }, // 44
    { "EOR", 2, RegMode_Direct                      }, // 45
    { "LSR", 2, RegMode_Direct                      }, // 46
    { "EOR", 2, RegMode_DirectIndirectLong          }, // 47
    { "PHA", 1, RegMode_Stack                       }, // 48
    { "EOR", 2, RegMode_Immediate                   }, // 49
    { "LSR", 1, RegMode_Accum                       }, // 4A
    { "PHK", 1, RegMode_Stack                       }, // 4B
    { "JMP", 3, RegMode_Absolute                    }, // 4C
    { "EOR", 3, RegMode_Absolute                    }, // 4D
    { "LSR", 3, RegMode_Absolute                    }, // 4E
    { "EOR", 4, RegMode_AbsoluteLong                }, // 4F

    { "BVC", 2, RegMode_PcRelative                  }, // 50
    { "EOR", 2, RegMode_DirectIndirectIndexY        }, // 51
    { "EOR", 2, RegMode_DirectIndirect              }, // 52
    { "EOR", 2, RegMode_StackRelativeIndirectIndexY }, // 53
    { "MVN", 3, RegMode_BlockMove                   }, // 54
    { "EOR", 2, RegMode_DirectIndexX                }, // 55
    { "LSR", 2, RegMode_DirectIndexX                }, // 56
    { "EOR", 2, RegMode_DirectIndirectLongIndexY    }, // 57
    { "CLI", 1, RegMode_Implied                     }, // 58
    { "EOR", 3, RegMode_AbsoluteIndexY              }, // 59
    { "PHY", 1, RegMode_Stack                       }, // 5A
    { "TCD", 1, RegMode_Implied                     }, // 5B
    { "JMP", 4, RegMode_AbsoluteLong                }, // 5C
    { "EOR", 3, RegMode_AbsoluteIndexX              }, // 5D
    { "LSR", 3, RegMode_AbsoluteIndexX              }, // 5E
    { "EOR", 4, RegMode_AbsoluteLongIndexX          }, // 5F

    { "RTS", 1, RegMode_Stack                       }, // 60
    { "ADC", 2, RegMode_DirectIndirectIndexX        }, // 61
    { "PER", 3, RegMode_PcRelativeLong              }, // 62
    { "ADC", 2, RegMode_StackRelative               }, // 63
    { "STZ", 2, RegMode_Direct                      }, // 64
    { "ADC", 2, RegMode_Direct                      }, // 65
    { "ROR", 2, RegMode_Direct                      }, // 66
    { "ADC", 2, RegMode_DirectIndirectLong          }, // 67
    { "PLA", 1, RegMode_Stack                       }, // 68
    { "ADC", 2, RegMode_Immediate                   }, // 69
    { "ROR", 1, RegMode_Accum                       }, // 6A
    { "RTL", 1, RegMode_Stack                       }, // 6B
    { "JMP", 3, RegMode_AbsoluteIndirect            }, // 6C
    { "ADC", 3, RegMode_Absolute                    }, // 6D
    { "ROR", 3, RegMode_Absolute                    }, // 6E
    { "ADC", 4, RegMode_AbsoluteLong                }, // 6F

    { "BVS", 2, RegMode_PcRelative                  }, // 70
    { "ADC", 2, RegMode_DirectIndirectIndexY        }, // 71
    { "ADC", 2, RegMode_DirectIndirect              }, // 72
    { "ADC", 2, RegMode_StackRelativeIndirectIndexY }, // 73
    { "STZ", 2, RegMode_DirectIndexX                }, // 74
    { "ADC", 2, RegMode_DirectIndexX                }, // 75
    { "ROR", 2, RegMode_DirectIndexX                }, // 76
    { "ADC", 2, RegMode_DirectIndirectLongIndexY    }, // 77
    { "SEI", 1, RegMode_Implied                     }, // 78
    { "ADC", 3, RegMode_AbsoluteIndexY              }, // 79
    { "PLY", 1, RegMode_Stack                       }, // 7A
    { "TDC", 1, RegMode_Implied                     }, // 7B
    { "JMP", 4, RegMode_AbsoluteIndexXIndirect      }, // 7C
    { "ADC", 3, RegMode_AbsoluteIndexX              }, // 7D
    { "ROR", 3, RegMode_AbsoluteIndexX              }, // 7E
    { "ADC", 4, RegMode_AbsoluteLongIndexX          }, // 7F


};
