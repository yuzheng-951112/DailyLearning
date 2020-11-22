[bits 32]
%define ERROR_CODE nop				;若在相关的异常中cpu已经自动压入了错误码，为保持栈中格式统一，这里不做操作
%define ZERO push 0				
 
extern idt_table				;声明外部函数
 
section .data
global intr_entry_table
intr_entry_table:
 
%macro VECTOR 2
section .text
	intr%1entry:				;每个中断处理程序都要压入中断类型一个中断处理程序，自己知道自己的中断向量号是多少
        %2
        push ds
        push es
	push fs
	push gs
	pushad					;PUSHAD指令压入32位寄存器，其入栈顺序是:EAX,ECX,EDX,EBX,ESP,ESI,EDI,EAX最先入栈        
		;如果是从片上进入到中断，除了往从片上发送EOI外，还要往主片上发送EOI
	mov al,0x20				;中断结束命令EOI
	out 0xa0,al				;向从片发送
	out 0x20,al				;向主片发送
         
	push %1					;不管idt_table中的目标程序是否需要参数，都一律压入中断向量号，调试起来是方便，在interrupt.c中有idt_table[i] = general_intr_handler 这里的general_intr_handler函数只调用了地址，但是没有传参数，而参数的的传到依靠栈，这里将%1压入栈其意义就在于传参
	call [idt_table + %1*4]			;调用idt_table中的C版本中断处理函数
	jmp intr_exit
         
section .data
	dd intr%1entry				;一个c源程序.c经过c预处理器cpp进行预处理后，变成.i-->c编译器cll将.i文件翻译成一个ASCII汇编语言文件.s-->汇编器as将.s翻译成一个可重定位目标文件.o(section本身的作用就是来自汇编中声明，.text,.bss,.data这些都是section,完成链接后所有中断处理程序的地址会作为数组intr_entry_table会紧凑的排在一起，)-->链接器ld将所有文件链接，最终生成一个可执行文件.p
%endmacro
 
section .text
global intr_exit
intr_exit:
	add esp,4				;跳过中断号
	popad
	pop gs
	pop fs
	pop es
	pop ds
	add esp,4				;跳过error_code
	iretd
 
VECTOR 0x00,ZERO
VECTOR 0x01,ZERO
VECTOR 0x02,ZERO
VECTOR 0x03,ZERO
VECTOR 0x04,ZERO
VECTOR 0x05,ZERO
VECTOR 0x06,ZERO
VECTOR 0x07,ZERO
VECTOR 0x08,ZERO
VECTOR 0x09,ZERO
VECTOR 0x0a,ZERO
VECTOR 0x0b,ZERO
VECTOR 0x0c,ZERO
VECTOR 0x0d,ZERO
VECTOR 0x0e,ZERO
VECTOR 0x0f,ZERO
VECTOR 0x10,ZERO
VECTOR 0x11,ZERO
VECTOR 0x12,ZERO
VECTOR 0x13,ZERO
VECTOR 0x14,ZERO
VECTOR 0x15,ZERO
VECTOR 0x16,ZERO
VECTOR 0x17,ZERO
VECTOR 0x18,ZERO
VECTOR 0x19,ZERO
VECTOR 0x1a,ZERO
VECTOR 0x1b,ZERO
VECTOR 0x1c,ZERO
VECTOR 0x1d,ZERO
VECTOR 0x1e,ERROR_CODE
VECTOR 0x1f,ZERO
VECTOR 0x20,ZERO
