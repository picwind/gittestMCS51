;催眠
DELAYTIME   EQU     31H
EXECHI      EQU     32H
EXECLO      EQU     33H
MAINHI      EQU     34H
MAINLO      EQU     35H
ORG         000H
    AJMP    MAIN 
ORG         003H
    AJMP    INT0 ;外部中断0
ORG         1BH
    AJMP    T1INT;定时器中断1
MAIN:
    MOV     DPTR,#wavestar;
    CLR     EX0;
    MOV     SP,#07;
    MOV     EXECHI,#00H;
    MOV     EXECLO,#60H;
    MOV     MAINHI,#00;
    MOV     MAINLO,#30H;
    MOV     TMOD,#10H;定时器1初始化
    MOV     TH1,#03CH;
    MOV     TL1,#0FFH;
    SETB    EA;
    SETB    ET1;
    SETB    TR1;
    MOV     R0,#03;脉冲波形及蜂鸣器初始化，R0是波形频率计数器
    MOV     R3,#00H;
    
ORG         0060H
EXECU:
FREQ1:
    CJNE    R0,#01,FREQ2;
    ACALL   DISP06;
    AJMP    FREQ1;
FREQ2:
    CJNE    R0,#02,FREQ3;
    ACALL   DISP08;
    AJMP    FREQ2;
FREQ3:
    CJNE    R0,#03,FREQ4;
    ACALL   DISP10;
    AJMP    FREQ3;
FREQ4:
    CJNE    R0,#04,FREQ5;
    ACALL   DISP12;
    AJMP    FREQ4;
FREQ5:
    CJNE    R0,#05,FREQ6;
    ACALL   DISP14;
    AJMP    FREQ5;
FREQ6:
    CJNE    R0,#06,NXTRND;
    ACALL   DISP16;
    AJMP    FREQ6;
NXTRND:
    CLR     ET1;
    CLR     IE0;
    SETB    EX0;
    SETB    IT0;
    SETB    PX0;
    SETB    P1.2;输出高电压
    SETB    P1.3;输出高电压
    SETB    P3.0;停止发出蜂鸣
    SJMP    $   ;等在这里，外部中断也起不了作用
    AJMP    EXECU;

;///////////////////////////////0.6Hz///////////////////////////////
DISP06:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD06:
    MOV     DELAYTIME,#30H;
DELAY06:
    MOV     R2,#66;
DELOOP06:
    DJNZ    R2,DELOOP06;
    DJNZ    DELAYTIME,DELAY06;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD06;A的第一个值设为1
    RET

;/////////////////////////////////0.8Hz//////////////////////////
DISP08:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD08:
    MOV     DELAYTIME,#30H;
DELAY08:
    MOV     R2,#49;
DELOOP08:
    DJNZ    R2,DELOOP08;
    DJNZ    DELAYTIME,DELAY08;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD08;A一个值设为1   
    RET

;///////////////////////////1Hz///////////////////////
DISP10:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD10:
    MOV     DELAYTIME,#030H;
DELAY10:
    MOV,    R2,#39;
DELOOP10:
    DJNZ    R2,DELOOP10;
    DJNZ    DELAYTIME,DELAY10;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD10;A一个值设为1
    RET

;/////////////////////////////1.2Hz////////////////////////
DISP12:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD12:
    MOV     DELAYTIME,#030H;
DELAY12:
    MOV,    R2,#32;
DELOOP12:
    DJNZ    R2,DELOOP12;
    DJNZ    DELAYTIME,DELAY12;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD12;A一个值设为1
    RET

;/////////////////////////////1.4Hz////////////////////////
DISP14:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD14:
    MOV     DELAYTIME,#030H;
DELAY14:
    MOV,    R2,#28;
DELOOP14:
    DJNZ    R2,DELOOP14;
    DJNZ    DELAYTIME,DELAY14;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD14;A一个值设为1
    RET

;/////////////////////////////1.6Hz////////////////////////
DISP16:
    MOV     A,#00H;下面这些决定了波形数据的时间沿
LOOPD16:
    MOV     DELAYTIME,#031H;
DELAY16:
    MOV,    R2,#23;
DELOOP16:
    DJNZ    R2,DELOOP16;
    DJNZ    DELAYTIME,DELAY16;
    MOV     R1,A;通过R1把A保存
    MOVC    A,@A+DPTR;DPTR通过主函数初始化，然后通过定时器0初始化设置
    RL      A;
    RL      A;
    MOV     P1,A;
    MOV     A,R1;
    INC     A;
    CJNE    A,#00H,LOOPD16;A一个值设为1
    RET

;////////////////////T1 INT/////////////////////
T1INT:
    INC     R3;每0.05s增加一次
    CJNE    R3,#24,LOAD;
    CPL     P3.0;
    INC     R4;每0.6(0.05×24=1.2)s增加一次
    CJNE    R4,#100,NEXT;
    MOV     R4,#00;
    MOV     R3,#00;
    INC     R0;每2.5(1.2×100=120)min增加一次
    PUSH    EXECLO;
    PUSH    EXECHI;
    RETI
NEXT:
    MOV     R3,#00;
LOAD:
    MOV     TH1,#03CH;
    MOV     TL1,#0FFH;
    RETI

;//////////////////////外部中断//////////////////
INT0:

REST:
    DELAY:
    MOV     R7,#00H;
LOOP:
    INC     R7;
    CJNE    R7,#0,LOOP;
    MOV     R0,#02;
    PUSH    MAINLO;
    PUSH    MAINHI;
    RETI;

;/////////////////////wave data///////////////////////
ORG         200H
wavestar:


RECT:
DB  252,252,252,252,252,252,252,252,252,252;

DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;
DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;
DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;
DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;
DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;
DB  253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253;//118个253

DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;
DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;
DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;
DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;
DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;
DB  254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254;//118个254
225
END
