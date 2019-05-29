;冒泡排序算法
ORG         2000H
DATA: DB    85,38,15,35,77,99,19,55,25
DUQU:
    MOV     DPTR,#DATA;
    MOV     R2,#9;
    MOV     R0,#0;
    MOV     R1,#30H;
    MOVC    A,#@DPTR+R0;
    MOV     @R1,A;
    INC     R0;
    INC     R1;
    DJNZ    R2,DUQU;


ORG 3000H
SORT:
    MOV     R0,#30H
    MOV     R7,#08H
    CLR     TR0
LOOP:
     MOVB   A,@R0
     MOV    2BH,A
     INC    R0
     MOV    2AH,@R0
     CLR    C
     SUBB   A,@R0
     JC     NEXT
     MOV    @R0,2BH
     DEC    R0
     MOVB   @R0,2AH
     INC    R0
     SETB   TR0
NEXT:
    DJNZ    R7,LOOP
    JB      TR0,SORT
HERE: SJMP  HERE
