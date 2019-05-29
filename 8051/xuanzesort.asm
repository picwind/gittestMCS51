;选择排序算法
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
    LOOP1:
        MOV     R2,#0;      //第一个循环的控制量
        MOV     R3,#0;      //temp
        MOV     A,R2;
        MOV     R1,A;       //index
        ADD     A,#1;
        MOV     R4,A;
        LOOP2:
            MOV     A,#30H;
            ADD     A,R2;
            MOV     R0,A;
            MOV     A,@R0;
            MOV     R5,A;
            MOV     A,#30;
            ADD     A,R4;
            MOV     R0,A;
            MOV     A,@R0;
            CLR     C;
            SUBB    A,R5;
            JNC     LOOP2;
            MOV     A,R4;
            MOV     R1,A;
            INC     R4;
            CJNE    R4,#9,LOOP2;
        MOV     A,R1;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,@R0;
        MOV     R3,A;
        MOV     A,R2;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,@R0;
        MOV     R6,A;       //第i个数
        MOV     A,R1;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,R6;
        MOV     @R0,R6;
        MOV     A,R2;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,R3;
        MOV     @R0,A;
        INC     R2;
        CJNE    R2,#8,LOOP1;
HERE:   SJMP    HERE