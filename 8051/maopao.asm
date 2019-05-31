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
    DJNZ    R2,DUQU;读取数据


ORG 3000H
SORT:
    MOV     R0,#30H;   //数据存储区首单元地址
    MOV     R7,#08H;   //各次冒泡比较次数
    CLR     TR0;       //用户标志位清零
LOOP:
     MOVB   A,@R0;      //取前数
     MOV    2BH,A;      //存前数
     INC    R0;
     MOV    2AH,@R0;    //取后数
     CLR    C;          //进位标志位清零
     SUBB   A,@R0;      //前数减后数
     JC     NEXT;       //前数小于后数，不互换，大于后数，互换
     MOV    @R0,2BH;
     DEC    R0;
     MOV   @R0,2AH;     //两个数交换位置
     INC    R0;         //准备下一次比较
     SETB   TR0;        //置互换标志
NEXT:
    DJNZ    R7,LOOP;    //返回进行下一次比较
    JB      TR0,SORT;   //返回，进行下一轮冒泡
HERE: SJMP  HERE;       //排序结束
