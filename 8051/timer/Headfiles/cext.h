/* Commons definitions */

#define  true           1
#define  false          0

#define  HIGH           1
#define  LOW          	0

#define  ON             1
#define  OFF            0

#define  ENABLED        1
#define  DISABLED       0

#define  uchar          unsigned char
#define  uint           unsigned int
#define  ulong          unsigned long

#define  forever        while(1)

#define  low_byte(int_num)  *((char*)&int_num + 1)
#define  high_byte(int_num) *(char*)&int_num

#define  NAN            (ulong)0xFFFFFFFF
#define  PINF           (ulong)0x7F800000
#define  MINF           (ulong)0XFF800000

#define  NULL           (void*)0 

#define  CR             0x0D
#define  LF             0x0A
#define  ESC            0x1B
