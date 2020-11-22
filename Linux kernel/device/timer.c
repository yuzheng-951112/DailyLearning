#include "time.h"
#include "io.h"
#include "print.h"

#define IRQ0_FREQUENCY		100				//始终中断频率
#define INPUT_FREQUENCY		1193180				//计数器0的工作脉冲信号频率
#define COUNTER0_VALUE		INPUT_FREQUENCY/IRQ0_FREQUENCY	//计数器0的计数初值
#define CONTRER0_PORT		0x40				//计数器0的端口号0x40
#define COUNTER0_NO		0				//控制字中选择计数器的号码，0计数器
#define COUNTER_MODE		2				//工作模式:比率发生器
#define READ_WRITE_LATCH	3				//读写方式
#define PIT_CONTROL_PORT	0x43				//控制字寄存器端口

/*把操作的计数器counter_no、读写锁属性rwl、计数器模式counter_mode写入模式控制寄存器并赋予初始值counter_value*/
static void frequency_set(uint8_t counter_port,uint8_t counter_no,uint8_t rwl,uint8_t counter_mode,uint16_t counter_value)
{
/*counter_value用来设置计数器的计数初值，由于此位是16位，所以	
counter_port计数器的端口号，用来指定初值counter_value的目的端口
counter_no用来控制字中指定所使用的计数器号码，对应于控制字中的SC1和SC2位
counter_mode用来设置计数器的工作方式，对应控制字中的M2~M0位
rwl用来设置计数器的读/写/锁存方式，对应于控制字中的RW1和RW2*/
	
/*往控制字寄存器端口0x43中写入控制字*/
	outb(PIC_CONTROL_PORT,(uint8_t)(counter_no<<6|rwl<<4|counter_mode<<1));
/*先写入counter_value的低8位*/
	outb(counter_port,(uint8_t)counter_value);
/*再写入counter_value的高8位*/
	outb(counter_port,(uint8_t)counter_value>>8);
}

/*初始化PIT8253*/
void timer_init()
{
	put_str("timer_init start\n");
	/*设置8253的定时周期，也就是发中断的周期*/
	frequency_set(CONTRER0_PORT,COUNTER0_NO,READ_WRITE_LATCH,COUNTER_MODE,COUNTER0_VALUE);
	put_str("timer_init done\n");
}
