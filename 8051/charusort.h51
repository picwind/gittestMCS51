;插入排序算法
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
        MOV     R3,#30H;    //数据内存地址起始
        MOV     R2,#8;      //输入数据个数
        MOV     R4,#1;      //排序位置 循环控制量      
        MOV     A,R4;
        ADD     A,R3;
        MOV     R1,A;       //存储30H+R4地址
        MOV     A,@R1;
        MOV     R5,A;       //R5作temp存储
        DEC     R1;
        MOV     A,R1;
        MOV     R7,A;       //LOOP2循环控制量
        LOOP2:
            MOV     A,R7;
            MOV     R0,A;
            MOV     A,@R0;
            CLR     C;
            SUBB    A,R5;
            JC      BREAK;
            MOV     A,@R0;
            MOV     R6,A;
            MOV     A,R7;
            ADD     A,#1;
            MOV     R0,A;
            MOV     A,R6;
            MOV     @R0,A;
            DEC     R7;
            CJNE    R7,#29H,LOOP2;
    BREAK:      
        MOV     A,R7;
        ADD     A,#1;
        MOV     A,R5;
        MOV    @R1,A;
        INC     R4;
        DJNZ    R2,LOOP1;
HERE:   SJMP    HERE