;====================================================================
; Main.asm file generated by New Project wizard
;
; Created:   周三 6月 12 2019
; Processor: 80C51
; Compiler:  ASEM-51 (Proteus)
;====================================================================

$NOMOD51
$INCLUDE (8051.MCU)
;====================================================================

      ; Reset Vector
      org   0000h
      jmp   Start

;====================================================================
; CODE SEGMENT
;====================================================================

      org   0100h
Start:	
      MOV	SP,#60      ;初始化堆栈
      MOV 	DPTR,#TAB   ;赋予段码表地址
      MOV 	R0,#0F0H    ;初始化R0
      MOV 	R1,#0FH     ;初始化R1
LOOP1:
      MOV 	P2,R0       ;输出行为高电平，列为低电平
      MOV	A,P2        ;从P2口读取数
      ANL	A,#0F0H     ;与11110000相与，看是否有键按下
      JNB	Acc.4,PK
      JNB	Acc.5,PK
      JNB	Acc.6,PK
      JNB	Acc.7,PK    ;有键被按下
PK:
      ACALL	DL10        ;延迟10ms去抖动
      MOV 	P2,R0       ;输出行为高电平，列为低电平
      MOV	A,P2        ;从P2口读取数
      ANL	A,#0F0H     ;与11110000相与，看是第几行键被按下
      JNB	Acc.4,L1
      JNB	Acc.5,L2
      JNB	Acc.6,L3
      JNB	Acc.7,L4    ;看是第几行按键被按下
      LJMP	LOOP1
LOOP2:  
      SUBB	A,#0F0H
      JZ	LOOP1
      MOV	P2,R1       ;行为低电平，列为高电平
      MOV	A,P2        ;从P2口读数
      ANL	A,#0FH      ;与00001111相与，看列线中是否有低电平
      JNB	Acc.0,C1
      JNB	Acc.1,C2
      JNB	Acc.2,C3
      JNB	Acc.3,C4    ;看第几列被按下
LOOP3:
      MOV	A,R2;
      DEC	A
      MOV	B,#4;
      MUL	AB
      ADD	A,R3
      DEC	A;          ;计算(R2-1)*4+(R3-1),即对应按键的段码表偏移量
      MOVC	A,@A+DPTR   ;取出段码
      MOV	P0,A        ;将段码输出到7端显像管
      LJMP	LOOP1
    
L1:
      MOV	R2,#1;
      LJMP	LOOP2
L2:
      MOV	R2,#2;
      LJMP	LOOP2 
L3:
      MOV	R2,#3;
      LJMP	LOOP2
L4:
      MOV	R2,#4;
      LJMP	LOOP2       ;记录行值
C1:
      MOV	R3,#1;
      LJMP	LOOP3
C2:
      MOV	R3,#2;
      LJMP	LOOP3
C3:
      MOV	R3,#3;
      LJMP	LOOP3
C4:
      MOV	R3,#4;
      LJMP	LOOP3       ;记录列值
DL10:                   ;延迟10ms去抖动子程序
      MOV	R7,#14H     ;循环20次
DL:      
      MOV	R6,#0FAH    ;循环250次
DL6:
      DJNZ	R6,DL6
      DJNZ	R7,DL       ;共循环5000次，10000个机器周期，大约10ms
      RET
TAB:  DB  0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,88H,83H,0C6H,0A1H,86H,8EH
                        ;共阳极七段LED的从0 - F的段码
;====================================================================
      END
