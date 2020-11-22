#include "print.h"
void main(void) {
	put_str("\nI am kernel\n");
	init_all();
	asm volatile("sti");				//为演示中断处理，在此临时打开中断
	while(1);
}
