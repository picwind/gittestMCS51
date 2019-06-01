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
    DJNZ    R2,DUQU;        //读取数据


ORG 3000H
SORT:
    LOOP1:
        MOV     R2,#0;      //第一个循环的控制量，位置
        MOV     R3,#0;      //temp
        MOV     A,R2;
        MOV     R1,A;       //index 记录最小数的位置
        ADD     A,#1;
        MOV     R4,A;
        LOOP2:
            MOV     A,#30H;
            ADD     A,R2;
            MOV     R0,A;
            MOV     A,@R0;      
            MOV     R5,A;       //第R2趟排序，序列中第R2个数送入R5
            MOV     A,#30;
            ADD     A,R4;
            MOV     R0,A;
            MOV     A,@R0;      //序列中第R2个数之后的第R4个数送入A
            CLR     C;          //进位标志位清零
            SUBB    A,R5;       //第R2个数和其后的数比较大小
            JNC     LOOP2;      //若R5中数较小，不交换，继续循环，否则交换
            MOV     A,R4;
            MOV     R1,A;       //更新最小数位置
            INC     R4;         //进行下一循环
            CJNE    R4,#9,LOOP2;
        MOV     A,R1;       //记录最小数的位置
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,@R0;
        MOV     R3,A;       //第R2趟排序中最小的数
        MOV     A,R2;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,@R0;
        MOV     R6,A;       //第R2个数
        MOV     A,R1;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,R6;
        MOV     @R0,R6;
        MOV     A,R2;
        ADD     A,#30H;
        MOV     R0,A;
        MOV     A,R3;
        MOV     @R0,A;      //交换位置，最小数放在前面
        INC     R2;         //进行下一交换
        CJNE    R2,#9,LOOP1;//
HERE:   SJMP    HERE;       //排序结束