.origin 0
.entrypoint START

#define PRU0_PRU1_INTERRUPT 17
#define PRU1_PRU0_INTERRUPT 18
#define PRU0_ARM_INTERRUPT  19
#define PRU1_ARM_INTERRUPT  20
#define ARM_PRU0_INTERRUPT  21
#define ARM_PRU1_INTERRUPT  22

#define CTBIR    0x22020
#define CTPPR_0  0x22028
#define CTPPR_1  0x2202C

#define CONST_PRUCFG        C4
#define CONST_PRUDRAM       C24
#define CONST_PRUSHAREDRAM  C28
#define CONST_DDR           C31

#define VALUE 0

START:
LBCO    r0, CONST_PRUCFG, 4, 4
CLR     r0, r0, 4
SBCO    r0, CONST_PRUCFG, 4, 4
MOV     r0, 0x00000120
MOV     r1, CTPPR_0
SBBO    r0, r1, 0, 4


MAINLOOP:

ZERO 4, 16
LBCO r2, CONST_PRUSHAREDRAM, 0, 16
QBEQ EXIT, r2, 255
QBNE REPLY, r2, 255
Return_REPLY:

JMP MAINLOOP

EXIT:
MOV R31.b0, PRU0_ARM_INTERRUPT+16
HALT

REPLY:
MOV  r2, VALUE
SBCO r2, CONST_PRUSHAREDRAM, 0, 16
JMP Return_REPLY