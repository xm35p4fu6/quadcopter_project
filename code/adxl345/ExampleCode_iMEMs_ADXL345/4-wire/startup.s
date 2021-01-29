/***********************************************************************/
/*  This file is part of the CA ARM C Compiler package                 */
/*  Copyright KEIL ELEKTRONIK GmbH 2002-2005                           */
/***********************************************************************/
/*                                                                     */
/*  STARTUP.S:  Startup file for ADI ADuC702x device series            */
/*                                                                     */
/***********************************************************************/


/* 
//*** <<< Use Configuration Wizard in Context Menu >>> *** 
*/


/*
 *  The STARTUP.S code is executed after CPU Reset. This file may be 
 *  translated with the following SET symbols. In uVision these SET 
 *  symbols are entered under Options - ASM - Set.
 *
 *  RAM_INTVEC: when set the startup code copies exception vectors 
 *  from on-chip Flash to on-chip RAM and remaps RAM to address 0.
 */


// Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

        Mode_USR  EQU      0x10
        Mode_FIQ  EQU      0x11
        Mode_IRQ  EQU      0x12
        Mode_SVC  EQU      0x13
        Mode_ABT  EQU      0x17
        Mode_UND  EQU      0x1B
        Mode_SYS  EQU      0x1F

        I_Bit     EQU      0x80    /* when I bit is set, IRQ is disabled */
        F_Bit     EQU      0x40    /* when F bit is set, FIQ is disabled */


/*
// <h> Stack Configuration (Stack Sizes in Bytes)
//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:4>
//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:4>
//   <o2> Abort Mode          <0x0-0xFFFFFFFF:4>
//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:4>
//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:4>
//   <o5> User/System Mode    <0x0-0xFFFFFFFF:4>
// </h>
*/
        UND_Stack_Size  EQU     0x00000004
        SVC_Stack_Size  EQU     0x00000004
        ABT_Stack_Size  EQU     0x00000004
        FIQ_Stack_Size  EQU     0x00000004
        IRQ_Stack_Size  EQU     0x00000080
        USR_Stack_Size  EQU     0x00000400

AREA   STACK, DATA, READWRITE, ALIGN=2
        DS   (USR_Stack_Size+3)&~3  ; Stack for User/System Mode 
        DS   (SVC_Stack_Size+3)&~3  ; Stack for Supervisor Mode
        DS   (IRQ_Stack_Size+3)&~3  ; Stack for Interrupt Mode
        DS   (FIQ_Stack_Size+3)&~3  ; Stack for Fast Interrupt Mode 
        DS   (ABT_Stack_Size+3)&~3  ; Stack for Abort Mode
        DS   (UND_Stack_Size+3)&~3  ; Stack for Undefined Mode
Top_Stack:


// MMR definitions
        MMR_BASE        EQU     0xFFFF0000      ; MMR Base Address
        REMAP_OFFSET    EQU         0x0220
        PREMAP_OFFSET   EQU         0x0224
        POWKEY1_OFFSET  EQU         0x0404
        POWCON_OFFSET   EQU         0x0408
        POWKEY2_OFFSET  EQU         0x040C


// <e> PLL Setup
//   <o1.0..2>  CD: CPU Clock Divider
//               <0-7>
//               <i> CD Value Selection
//               <i> Clock Divider = 2^CD
//   <o1.3>     FINT: Fast Interrupt
//               <0-1>
//               <i> Switches to CD0 for FIQ
// </e>
        PLL_SETUP       EQU     1
        PLLCFG_Val      EQU     0x00000001


// <e> Pin Setup
        GPIO_SETUP      EQU     0
        GPIOBASE        EQU     0xFFFFF400

//   <h>  Port 0
//     <o.0..1>    P0.0  <0=> GPIO      <1=> CMPOUT    <2=> MS2     <3=> PLAI[7]
//     <o.4..5>    P0.1  <0=> GPIO      <1=> PWM2H     <2=> BLE     <3=> ---
//     <o.8..9>    P0.2  <0=> GPIO      <1=> PWM2L     <2=> BHE     <3=> ---
//     <o.12..13>  P0.3  <0=> GPIO      <1=> TRST      <2=> A16     <3=> ADCBUSY
//     <o.16..17>  P0.4  <0=> GPIO/IRQ0 <1=> PWMTRIP   <2=> MS1     <3=> PLAO[1]
//     <o.20..21>  P0.5  <0=> GPIO/IRQ1 <1=> ADCBUSY   <2=> MS0     <3=> PLAO[2]
//     <o.24..25>  P0.6  <0=> GPIO/T1   <1=> MRST      <2=> AE      <3=> PLAO[3]
//     <o.28..29>  P0.7  <0=> GPIO      <1=> ECLK/XCLK <2=> SIN     <3=> PLAO[4]
//   </h>
        GP0CON_Val      EQU     0x00000000

//   <h>  Port 1
//     <o.0..1>    P1.0  <0=> GPIO/T1   <1=> SIN       <2=> I2C0SCL <3=> PLAI[0]
//     <o.4..5>    P1.1  <0=> GPIO      <1=> SOUT      <2=> I2C0SDA <3=> PLAI[1]
//     <o.8..9>    P1.2  <0=> GPIO      <1=> RTS       <2=> I2C1SCL <3=> PLAI[2]
//     <o.12..13>  P1.3  <0=> GPIO      <1=> CTS       <2=> I2C1SDA <3=> PLAI[3]
//     <o.16..17>  P1.4  <0=> GPIO/IRQ2 <1=> RI        <2=> SPICLK  <3=> PLAI[4]
//     <o.20..21>  P1.5  <0=> GPIO/IRQ3 <1=> DCD       <2=> SPIMISO <3=> PLAI[5]
//     <o.24..25>  P1.6  <0=> GPIO      <1=> DSR       <2=> SPIMOSI <3=> PLAI[6]
//     <o.28..29>  P1.7  <0=> GPIO      <1=> DTR       <2=> SPICSL  <3=> PLAO[0]
//   </h>
        GP1CON_Val      EQU     0x00000000

//   <h>  Port 2
//     <o.0..1>    P2.0  <0=> GPIO      <1=> CONVSTART <2=> SOUT    <3=> PLAO[5]
//     <o.4..5>    P2.1  <0=> GPIO      <1=> PWM0H     <2=> WS      <3=> PLAO[6]
//     <o.8..9>    P2.2  <0=> GPIO      <1=> PWM0L     <2=> RS      <3=> PLAO[7]
//     <o.12..13>  P2.3  <0=> GPIO      <1=> ---       <2=> AE      <3=> ---
//     <o.16..17>  P2.4  <0=> GPIO      <1=> PWM0H     <2=> MS0     <3=> ---
//     <o.20..21>  P2.5  <0=> GPIO      <1=> PWM0L     <2=> MS1     <3=> ---
//     <o.24..25>  P2.6  <0=> GPIO      <1=> PWM1H     <2=> MS2     <3=> ---
//     <o.28..29>  P2.7  <0=> GPIO      <1=> PWM1L     <2=> MS3     <3=> ---
//   </h>
        GP2CON_Val      EQU     0x00000000

//   <h>  Port 3
//     <o.0..1>    P3.0  <0=> GPIO      <1=> PWM0H     <2=> AD0     <3=> PLAI[8]
//     <o.4..5>    P3.1  <0=> GPIO      <1=> PWM0L     <2=> AD1     <3=> PLAI[9]
//     <o.8..9>    P3.2  <0=> GPIO      <1=> PWM1H     <2=> AD2     <3=> PLAI[10]
//     <o.12..13>  P3.3  <0=> GPIO      <1=> PWM1L     <2=> AD3     <3=> PLAI[11]
//     <o.16..17>  P3.4  <0=> GPIO      <1=> PWM2H     <2=> AD4     <3=> PLAI[12]
//     <o.20..21>  P3.5  <0=> GPIO      <1=> PWM2L     <2=> AD5     <3=> PLAI[13]
//     <o.24..25>  P3.6  <0=> GPIO      <1=> PWMTRIP   <2=> AD6     <3=> PLAI[14]
//     <o.28..29>  P3.7  <0=> GPIO      <1=> PWMSYNC   <2=> AD7     <3=> PLAI[15]
//   </h>
        GP3CON_Val      EQU     0x00000000

//   <h>  Port 4
//     <o.0..1>    P4.0  <0=> GPIO      <1=> ---       <2=> AD8     <3=> PLAO[8]
//     <o.4..5>    P4.1  <0=> GPIO      <1=> ---       <2=> AD9     <3=> PLAO[9]
//     <o.8..9>    P4.2  <0=> GPIO      <1=> ---       <2=> AD10    <3=> PLAO[10]
//     <o.12..13>  P4.3  <0=> GPIO      <1=> ---       <2=> AD11    <3=> PLAO[11]
//     <o.16..17>  P4.4  <0=> GPIO      <1=> ---       <2=> AD12    <3=> PLAO[12]
//     <o.20..21>  P4.5  <0=> GPIO      <1=> ---       <2=> AD13    <3=> PLAO[13]
//     <o.24..25>  P4.6  <0=> GPIO      <1=> ---       <2=> AD14    <3=> PLAO[14]
//     <o.28..29>  P4.7  <0=> GPIO      <1=> ---       <2=> AD15    <3=> PLAO[15]
//   </h>
        GP4CON_Val      EQU     0x00000000

// </e>


// <e> External Memory Interface
        XM_SETUP        EQU     0
        XMBASE          EQU     0xFFFFF000

//   <e.0>  Enable Memory Region 0
//     <o.1>       Data Bus Width  <0=> 8-bit  <1=> 16-bit
//     <o1.11>     Byte Address Mode Forced
//     <o1.15>     Byte Enabled Write Strobe
//     <o1.10>     Disable extra Address Latch Hold Cycle
//     <o1.8>      Disable extra Write Address Hold Cycle
//     <o1.9>      Disable Read Bus Turn Cycle
//     <o1.12..14> Address Wait States <0-7>
//                 <i> Number of Wait States added for AE
//     <o1.0..3>   Read Wait States <0-15>
//                 <i> Number of Wait States added for RS
//     <o1.4..7>   Write Wait States <0-15>
//                 <i> Number of Wait States added for WS
//   </e>
        XM0CON_Val      EQU     0x00000000
        XM0PAR_Val      EQU     0x000070FF

//   <e.0>  Enable Memory Region 1
//     <o.1>       Data Bus Width  <0=> 8-bit  <1=> 16-bit
//     <o1.11>     Byte Address Mode Forced
//     <o1.15>     Byte Enabled Write Strobe
//     <o1.10>     Disable extra Address Latch Hold Cycle
//     <o1.8>      Disable extra Write Address Hold Cycle
//     <o1.9>      Disable Read Bus Turn Cycle
//     <o1.12..14> Address Wait States <0-7>
//                 <i> Number of Wait States added for AE
//     <o1.0..3>   Read Wait States <0-15>
//                 <i> Number of Wait States added for RS
//     <o1.4..7>   Write Wait States <0-15>
//                 <i> Number of Wait States added for WS
//   </e>
        XM1CON_Val      EQU     0x00000000
        XM1PAR_Val      EQU     0x000070FF

//   <e.0>  Enable Memory Region 2
//     <o.1>       Data Bus Width  <0=> 8-bit  <1=> 16-bit
//     <o1.11>     Byte Address Mode Forced
//     <o1.15>     Byte Enabled Write Strobe
//     <o1.10>     Disable extra Address Latch Hold Cycle
//     <o1.8>      Disable extra Write Address Hold Cycle
//     <o1.9>      Disable Read Bus Turn Cycle
//     <o1.12..14> Address Wait States <0-7>
//                 <i> Number of Wait States added for AE
//     <o1.0..3>   Read Wait States <0-15>
//                 <i> Number of Wait States added for RS
//     <o1.4..7>   Write Wait States <0-15>
//                 <i> Number of Wait States added for WS
//   </e>
        XM2CON_Val      EQU     0x00000000
        XM2PAR_Val      EQU     0x000070FF

//   <e.0>  Enable Memory Region 3
//     <o.1>       Data Bus Width  <0=> 8-bit  <1=> 16-bit
//     <o1.11>     Byte Address Mode Forced
//     <o1.15>     Byte Enabled Write Strobe
//     <o1.10>     Disable extra Address Latch Hold Cycle
//     <o1.8>      Disable extra Write Address Hold Cycle
//     <o1.9>      Disable Read Bus Turn Cycle
//     <o1.12..14> Address Wait States <0-7>
//                 <i> Number of Wait States added for AE
//     <o1.0..3>   Read Wait States <0-15>
//                 <i> Number of Wait States added for RS
//     <o1.4..7>   Write Wait States <0-15>
//                 <i> Number of Wait States added for WS
//   </e>
        XM3CON_Val      EQU     0x00000000
        XM3PAR_Val      EQU     0x000070FF

//   <e.0>         Memory Muxed Mode
        XMCFG_Val       EQU     0x00000001
//   </e>

// </e>


$IF (RAM_INTVEC)
// Exception Vector Area in RAM
AREA   VECTORS, DATA, AT 0x00010000
                DS      64
$ENDIF        
        

// Startup Code must be linked at address which it expects to run.
									
AREA   STARTUPCODE, CODE, AT 0x00080000
       PUBLIC  __startup

       EXTERN  CODE32 (?C?INIT)

__startup       PROC    CODE32

// Pre-defined interrupt handlers that may be directly 
// overwritten by C interrupt functions
EXTERN CODE32 (Undef_Handler?A)
EXTERN CODE32 (SWI_Handler?A)
EXTERN CODE32 (PAbt_Handler?A)
EXTERN CODE32 (DAbt_Handler?A)
EXTERN CODE32 (IRQ_Handler?A)
EXTERN CODE32 (FIQ_Handler?A)

// Exception Vectors
// Mapped to Address 0.
// Absolute addressing mode must be used.

Vectors:        LDR     PC,Reset_Addr         
                LDR     PC,Undef_Addr
                LDR     PC,SWI_Addr
                LDR     PC,PAbt_Addr
                LDR     PC,DAbt_Addr
                NOP                            /* Reserved Vector */
                LDR     PC,IRQ_Addr
                LDR     PC,FIQ_Addr

Reset_Addr:     DD      Reset_Handler
Undef_Addr:     DD      Undef_Handler?A
SWI_Addr:       DD      SWI_Handler?A
PAbt_Addr:      DD      PAbt_Handler?A
DAbt_Addr:      DD      DAbt_Handler?A
                DD      0                      /* Reserved Address */
IRQ_Addr:       DD      IRQ_Handler?A
FIQ_Addr:       DD      FIQ_Handler?A


// Reset Handler

Reset_Handler:  


// Setup PLL
IF (PLL_SETUP != 0)
                LDR     R0, =MMR_BASE
                MOV     R1, #0x01         
                STR     R1, [R0,#POWKEY1_OFFSET]          
                MOV     R1, #PLLCFG_Val      
                STR     R1, [R0,#POWCON_OFFSET]    
                MOV     R1, #0xF4
                STR     R1, [R0,#POWKEY2_OFFSET]
ENDIF   ; PLL_SETUP


// Setup Pins
IF (GPIO_SETUP != 0)

                ADR     R10, GPIO_CFG          /* Pointer to GPIO CFG */
                LDMIA   R10, {R0-R5}           /* Load GPIO Configuration */
                STMIA   R0, {R1-R5}            /* Store GPxCON */
                B       GPIO_END

GPIO_CFG:       DD      GPIOBASE
                DD      GP0CON_Val
                DD      GP1CON_Val
                DD      GP2CON_Val
                DD      GP3CON_Val
                DD      GP4CON_Val
GPIO_END:

ENDIF   ; GPIO_SETUP


// Setup External Memory Interface
IF (XM_SETUP != 0)

                ADR     R10, XM_CFG            /* Pointer to XM CFG */
                LDMIA   R10, {R0-R9}           /* Load XM Configuration */
                STR     R1, [R0],#0x10         /* Store XMCFG */
                STMIA   R0, {R2-R9}            /* Store XMxCON & XMxPAR */
                B       XM_END

XM_CFG:         DD      XMBASE
                DD      XMCFG_Val
                DD      XM0CON_Val
                DD      XM1CON_Val
                DD      XM2CON_Val
                DD      XM3CON_Val
                DD      XM0PAR_Val
                DD      XM1PAR_Val
                DD      XM2PAR_Val
                DD      XM3PAR_Val
XM_END:

ENDIF   ; XM_SETUP


// Copy Exception Vectors to Internal RAM and Remap Memory
//  (when Interrupt Vectors are in RAM)

$IF (RAM_INTVEC)
                ADR     R8, Vectors         ; Source
                LDR     R9, =0x00010000     ; Destination
                LDMIA   R8!, {R0-R7}        ; Load Vectors 
                STMIA   R9!, {R0-R7}        ; Store Vectors 
                LDMIA   R8!, {R0-R7}        ; Load Handler Addresses 
                STMIA   R9!, {R0-R7}        ; Store Handler Addresses 
                LDR     R0, =MMR_BASE
                MOV     R1, #1     
                STR     R1, [R0,#PREMAP_OFFSET]          
                STR     R1, [R0,#REMAP_OFFSET]          
$ENDIF


// Setup Stack for each mode
                LDR     R0, =Top_Stack

// Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

// Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

// Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

// Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

// Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC|I_Bit|F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

// Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0

// Enter the C code
                LDR     R0,=?C?INIT
                TST     R0,#1       ; Bit-0 set: main is Thumb
                LDREQ   LR,=exit?A  ; ARM Mode
                LDRNE   LR,=exit?T  ; Thumb Mode
                BX      R0
                ENDP

PUBLIC exit?A
exit?A          PROC    CODE32
                B       exit?A
                ENDP

PUBLIC exit?T
exit?T          PROC    CODE16
                B       exit?T
                ENDP

                END
