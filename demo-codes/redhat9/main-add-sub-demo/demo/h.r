ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x8048278
  Start of program headers:          52 (bytes into file)
  Start of section headers:          7460 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         6
  Size of section headers:           40 (bytes)
  Number of section headers:         34
  Section header string table index: 31

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .interp           PROGBITS        080480f4 0000f4 000013 00   A  0   0  1
  [ 2] .note.ABI-tag     NOTE            08048108 000108 000020 00   A  0   0  4
  [ 3] .hash             HASH            08048128 000128 000028 04   A  4   0  4
  [ 4] .dynsym           DYNSYM          08048150 000150 000050 10   A  5   1  4
  [ 5] .dynstr           STRTAB          080481a0 0001a0 00004c 00   A  0   0  1
  [ 6] .gnu.version      VERSYM          080481ec 0001ec 00000a 02   A  4   0  2
  [ 7] .gnu.version_r    VERNEED         080481f8 0001f8 000020 00   A  5   1  4
  [ 8] .rel.dyn          REL             08048218 000218 000008 08   A  4   0  4
  [ 9] .rel.plt          REL             08048220 000220 000010 08   A  4   b  4
  [10] .init             PROGBITS        08048230 000230 000017 00  AX  0   0  4
  [11] .plt              PROGBITS        08048248 000248 000030 04  AX  0   0  4
  [12] .text             PROGBITS        08048278 000278 000164 00  AX  0   0  4
  [13] .fini             PROGBITS        080483dc 0003dc 00001b 00  AX  0   0  4
  [14] .rodata           PROGBITS        080483f8 0003f8 00001a 00   A  0   0  4
  [15] .eh_frame         PROGBITS        08048414 000414 000004 00   A  0   0  4
  [16] .data             PROGBITS        08049418 000418 00000c 00  WA  0   0  4
  [17] .dynamic          DYNAMIC         08049424 000424 0000c8 08  WA  5   0  4
  [18] .ctors            PROGBITS        080494ec 0004ec 000008 00  WA  0   0  4
  [19] .dtors            PROGBITS        080494f4 0004f4 000008 00  WA  0   0  4
  [20] .jcr              PROGBITS        080494fc 0004fc 000004 00  WA  0   0  4
  [21] .got              PROGBITS        08049500 000500 000018 04  WA  0   0  4
  [22] .bss              NOBITS          08049518 000518 000004 00  WA  0   0  4
  [23] .comment          PROGBITS        00000000 000518 000132 00      0   0  1
  [24] .debug_aranges    PROGBITS        00000000 000650 000078 00      0   0  8
  [25] .debug_pubnames   PROGBITS        00000000 0006c8 000025 00      0   0  1
  [26] .debug_info       PROGBITS        00000000 0006ed 000a84 00      0   0  1
  [27] .debug_abbrev     PROGBITS        00000000 001171 000138 00      0   0  1
  [28] .debug_line       PROGBITS        00000000 0012a9 00027c 00      0   0  1
  [29] .debug_frame      PROGBITS        00000000 001528 000014 00      0   0  4
  [30] .debug_str        PROGBITS        00000000 00153c 0006ba 01  MS  0   0  1
  [31] .shstrtab         STRTAB          00000000 001bf6 00012b 00      0   0  1
  [32] .symtab           SYMTAB          00000000 002274 0006c0 10     33  54  4
  [33] .strtab           STRTAB          00000000 002934 0003f2 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  PHDR           0x000034 0x08048034 0x08048034 0x000c0 0x000c0 R E 0x4
  INTERP         0x0000f4 0x080480f4 0x080480f4 0x00013 0x00013 R   0x1
      [Requesting program interpreter: /lib/ld-linux.so.2]
  LOAD           0x000000 0x08048000 0x08048000 0x00418 0x00418 R E 0x1000
  LOAD           0x000418 0x08049418 0x08049418 0x00100 0x00104 RW  0x1000
  DYNAMIC        0x000424 0x08049424 0x08049424 0x000c8 0x000c8 RW  0x4
  NOTE           0x000108 0x08048108 0x08048108 0x00020 0x00020 R   0x4

 Section to Segment mapping:
  Segment Sections...
   00     
   01     .interp 
   02     .interp .note.ABI-tag .hash .dynsym .dynstr .gnu.version .gnu.version_r .rel.dyn .rel.plt .init .plt .text .fini .rodata .eh_frame 
   03     .data .dynamic .ctors .dtors .jcr .got .bss 
   04     .dynamic 
   05     .note.ABI-tag 

Dynamic segment at offset 0x424 contains 20 entries:
  Tag        Type                         Name/Value
 0x00000001 (NEEDED)                     Shared library: [libc.so.6]
 0x0000000c (INIT)                       0x8048230
 0x0000000d (FINI)                       0x80483dc
 0x00000004 (HASH)                       0x8048128
 0x00000005 (STRTAB)                     0x80481a0
 0x00000006 (SYMTAB)                     0x8048150
 0x0000000a (STRSZ)                      76 (bytes)
 0x0000000b (SYMENT)                     16 (bytes)
 0x00000015 (DEBUG)                      0x0
 0x00000003 (PLTGOT)                     0x8049500
 0x00000002 (PLTRELSZ)                   16 (bytes)
 0x00000014 (PLTREL)                     REL
 0x00000017 (JMPREL)                     0x8048220
 0x00000011 (REL)                        0x8048218
 0x00000012 (RELSZ)                      8 (bytes)
 0x00000013 (RELENT)                     8 (bytes)
 0x6ffffffe (VERNEED)                    0x80481f8
 0x6fffffff (VERNEEDNUM)                 1
 0x6ffffff0 (VERSYM)                     0x80481ec
 0x00000000 (NULL)                       0x0

Relocation section '.rel.dyn' at offset 0x218 contains 1 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
08049514  00000406 R_386_GLOB_DAT    00000000   __gmon_start__

Relocation section '.rel.plt' at offset 0x220 contains 2 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
0804950c  00000107 R_386_JUMP_SLOT   08048258   __libc_start_main
08049510  00000207 R_386_JUMP_SLOT   08048268   printf

There are no unwind sections in this file.

Symbol table '.dynsym' contains 5 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 08048258   251 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.0 (2)
     2: 08048268    57 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.0 (2)
     3: 080483fc     4 OBJECT  GLOBAL DEFAULT   14 _IO_stdin_used
     4: 00000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__

Symbol table '.symtab' contains 108 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 080480f4     0 SECTION LOCAL  DEFAULT    1 
     2: 08048108     0 SECTION LOCAL  DEFAULT    2 
     3: 08048128     0 SECTION LOCAL  DEFAULT    3 
     4: 08048150     0 SECTION LOCAL  DEFAULT    4 
     5: 080481a0     0 SECTION LOCAL  DEFAULT    5 
     6: 080481ec     0 SECTION LOCAL  DEFAULT    6 
     7: 080481f8     0 SECTION LOCAL  DEFAULT    7 
     8: 08048218     0 SECTION LOCAL  DEFAULT    8 
     9: 08048220     0 SECTION LOCAL  DEFAULT    9 
    10: 08048230     0 SECTION LOCAL  DEFAULT   10 
    11: 08048248     0 SECTION LOCAL  DEFAULT   11 
    12: 08048278     0 SECTION LOCAL  DEFAULT   12 
    13: 080483dc     0 SECTION LOCAL  DEFAULT   13 
    14: 080483f8     0 SECTION LOCAL  DEFAULT   14 
    15: 08048414     0 SECTION LOCAL  DEFAULT   15 
    16: 08049418     0 SECTION LOCAL  DEFAULT   16 
    17: 08049424     0 SECTION LOCAL  DEFAULT   17 
    18: 080494ec     0 SECTION LOCAL  DEFAULT   18 
    19: 080494f4     0 SECTION LOCAL  DEFAULT   19 
    20: 080494fc     0 SECTION LOCAL  DEFAULT   20 
    21: 08049500     0 SECTION LOCAL  DEFAULT   21 
    22: 08049518     0 SECTION LOCAL  DEFAULT   22 
    23: 00000000     0 SECTION LOCAL  DEFAULT   23 
    24: 00000000     0 SECTION LOCAL  DEFAULT   24 
    25: 00000000     0 SECTION LOCAL  DEFAULT   25 
    26: 00000000     0 SECTION LOCAL  DEFAULT   26 
    27: 00000000     0 SECTION LOCAL  DEFAULT   27 
    28: 00000000     0 SECTION LOCAL  DEFAULT   28 
    29: 00000000     0 SECTION LOCAL  DEFAULT   29 
    30: 00000000     0 SECTION LOCAL  DEFAULT   30 
    31: 00000000     0 SECTION LOCAL  DEFAULT   31 
    32: 00000000     0 SECTION LOCAL  DEFAULT   32 
    33: 00000000     0 SECTION LOCAL  DEFAULT   33 
    34: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    35: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    36: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    37: 00000000     0 FILE    LOCAL  DEFAULT  ABS <built-in>
    38: 00000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.S
    39: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    40: 00000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.S
    41: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    42: 00000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.S
    43: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    44: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    45: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    46: 00000000     0 FILE    LOCAL  DEFAULT  ABS <built-in>
    47: 00000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.S
    48: 00000000     0 FILE    LOCAL  DEFAULT  ABS init.c
    49: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    50: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    51: 00000000     0 FILE    LOCAL  DEFAULT  ABS initfini.c
    52: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    53: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    54: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    55: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    56: 00000000     0 FILE    LOCAL  DEFAULT  ABS <built-in>
    57: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    58: 0804829c     0 FUNC    LOCAL  DEFAULT   12 call_gmon_start
    59: 00000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    60: 080494ec     0 OBJECT  LOCAL  DEFAULT   18 __CTOR_LIST__
    61: 080494f4     0 OBJECT  LOCAL  DEFAULT   19 __DTOR_LIST__
    62: 08048414     0 OBJECT  LOCAL  DEFAULT   15 __EH_FRAME_BEGIN__
    63: 080494fc     0 OBJECT  LOCAL  DEFAULT   20 __JCR_LIST__
    64: 08049420     0 OBJECT  LOCAL  DEFAULT   16 p.0
    65: 08049518     1 OBJECT  LOCAL  DEFAULT   22 completed.1
    66: 080482c0     0 FUNC    LOCAL  DEFAULT   12 __do_global_dtors_aux
    67: 080482fc     0 FUNC    LOCAL  DEFAULT   12 frame_dummy
    68: 00000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    69: 080494f0     0 OBJECT  LOCAL  DEFAULT   18 __CTOR_END__
    70: 080494f8     0 OBJECT  LOCAL  DEFAULT   19 __DTOR_END__
    71: 08048414     0 OBJECT  LOCAL  DEFAULT   15 __FRAME_END__
    72: 080494fc     0 OBJECT  LOCAL  DEFAULT   20 __JCR_END__
    73: 080483b8     0 FUNC    LOCAL  DEFAULT   12 __do_global_ctors_aux
    74: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    75: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    76: 00000000     0 FILE    LOCAL  DEFAULT  ABS initfini.c
    77: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    78: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    79: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    80: 00000000     0 FILE    LOCAL  DEFAULT  ABS <command line>
    81: 00000000     0 FILE    LOCAL  DEFAULT  ABS <built-in>
    82: 00000000     0 FILE    LOCAL  DEFAULT  ABS /usr/src/build/231499-i38
    83: 00000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
    84: 08049424     0 OBJECT  GLOBAL DEFAULT   17 _DYNAMIC
    85: 080483f8     4 OBJECT  GLOBAL DEFAULT   14 _fp_hw
    86: 08049418     0 NOTYPE  GLOBAL DEFAULT  ABS __fini_array_end
    87: 0804941c     0 OBJECT  GLOBAL HIDDEN   16 __dso_handle
    88: 08048384    52 FUNC    GLOBAL DEFAULT   12 __libc_csu_fini
    89: 08048230     0 FUNC    GLOBAL DEFAULT   10 _init
    90: 08048278     0 FUNC    GLOBAL DEFAULT   12 _start
    91: 08049418     0 NOTYPE  GLOBAL DEFAULT  ABS __fini_array_start
    92: 08048354    48 FUNC    GLOBAL DEFAULT   12 __libc_csu_init
    93: 08049518     0 NOTYPE  GLOBAL DEFAULT  ABS __bss_start
    94: 08048328    41 FUNC    GLOBAL DEFAULT   12 main
    95: 08048258   251 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_
    96: 08049418     0 NOTYPE  GLOBAL DEFAULT  ABS __init_array_end
    97: 08049418     0 NOTYPE  WEAK   DEFAULT   16 data_start
    98: 08048268    57 FUNC    GLOBAL DEFAULT  UND printf@@GLIBC_2.0
    99: 080483dc     0 FUNC    GLOBAL DEFAULT   13 _fini
   100: 08049518     0 NOTYPE  GLOBAL DEFAULT  ABS _edata
   101: 08049500     0 OBJECT  GLOBAL DEFAULT   21 _GLOBAL_OFFSET_TABLE_
   102: 0804951c     0 NOTYPE  GLOBAL DEFAULT  ABS _end
   103: 08049418     0 NOTYPE  GLOBAL DEFAULT  ABS __init_array_start
   104: 080483fc     4 OBJECT  GLOBAL DEFAULT   14 _IO_stdin_used
   105: 08049418     0 NOTYPE  GLOBAL DEFAULT   16 __data_start
   106: 00000000     0 NOTYPE  WEAK   DEFAULT  UND _Jv_RegisterClasses
   107: 00000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__

Histogram for bucket list length (total of 3 buckets):
 Length  Number     % of total  Coverage
      0  0          (  0.0%)
      1  2          ( 66.7%)     50.0%
      2  1          ( 33.3%)    100.0%

Version symbols section '.gnu.version' contains 5 entries:
 Addr: 00000000080481ec  Offset: 0x0001ec  Link: 4 (.dynsym)
  000:   0 (*local*)       2 (GLIBC_2.0)     2 (GLIBC_2.0)     1 (*global*)   
  004:   0 (*local*)    

Version needs section '.gnu.version_r' contains 1 entries:
 Addr: 0x00000000080481f8  Offset: 0x0001f8  Link to section: 5 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 1
  0x0010: Name: GLIBC_2.0  Flags: none  Version: 2
