#include "interrupt.h"
#include "stdint.h"
#include "global.h"
#include "io.h"
 
#define PIC_M_CTRL 0x20 //主片控制端口
#define PIC_M_DATA 0x21 //主片数据端口
#define PIC_S_CTRL 0xa0 //从片控制端口
#define PIC_S_DATA 0xa1 //从片数据端口 
#define IDT_DESC_CNT 0x21    //目前总共支持的中断数
 
// 中断门描述符结构体
struct gate_desc
{
	uint16_t func_offset_low_word;
	uint16_t selector;
   	uint8_t  dcount;
   	uint8_t  attribute;
   	uint16_t func_offset_high_word;
};
 
// 静态函数声明，非必须
static void make_idt_desc(struct gate_desc* p_gdesc, uint8_t attr, intr_handler function);
// 中断门描述符表的数组
static struct gate_desc idt[IDT_DESC_CNT];
// 用于保存异常名
char* intr_name[IDT_DESC_CNT];
// 定义中断处理程序数组，在kernel.asm中定义的intrXXentry。只是中断处理程序的入口，最终调用idt_table中的处理程序
intr_handler idt_table[IDT_DESC_CNT];
// 声明引用定义在kernel.asm中的中断处理函数入口数组
extern intr_handler intr_entry_table[IDT_DESC_CNT];
// 初始化可编程中断控制器 8259A
static void pic_init(void)
{
/*初始化主片 */
	outb (PIC_M_CTRL, 0x11); // ICW1: 边沿触发,级联8259, 需要ICW4
	outb (PIC_M_DATA, 0x20); // ICW2: 起始中断向量号为0x20, 也就是IR[0-7] 为 0x20 ～ 0x27
   	outb (PIC_M_DATA, 0x04); // ICW3: IR2 接从片
   	outb (PIC_M_DATA, 0x01); // ICW4: 8086 模式, 正常EOI
     
/*初始化从片 */
   	outb (PIC_S_CTRL, 0x11); // ICW1: 边沿触发,级联8259, 需要ICW4
   	outb (PIC_S_DATA, 0x28); // ICW2: 起始中断向量号为0x28, 也就是IR[8-15]为0x28 ～ 0x2F
   	outb (PIC_S_DATA, 0x02); // ICW3: 设置从片连接到主片的IR2 引脚
   	outb (PIC_S_DATA, 0x01); // ICW4: 8086 模式, 正常EOI
/*打开主片上IR0,也就是目前只接受时钟产生的中断 */
   	outb (PIC_M_DATA, 0xfe);
   	outb (PIC_S_DATA, 0xff);
     
   	put_str("   pic_init done\n");
}

//创建中断门描述符
static void make_idt_desc(struct gate_desc* p_gdesc, uint8_t attr, intr_handler function)
{
    	p_gdesc->func_offset_low_word = (uint32_t)function & 0x0000FFFF;
    	p_gdesc->selector = SELECTOR_K_CODE;
    	p_gdesc->dcount = 0;
    	p_gdesc->attribute = attr;
    	p_gdesc->func_offset_high_word = ((uint32_t)function & 0xFFFF0000) >> 16;
}
  
// 初始化中断描述符表
static void idt_desc_init(void)
{
	int i;
	for(i=0;i<IDT_DESC_CNT;i++)
	{
		make_idt_desc(&idt[i],IDT_DESC_ATTR_DPL0,intr_entry_table[i]);
	}
	put_str("   idt_desc_init done\n");
}

//通过的中断处理函数，一般用在异常出现时的处理
static void general_intr_handler(uint8_t vec_nr)
{
//IRQ7和IRQ15会产生伪中断(spurious interrupt),无需处理0x2f是从片8259A上的最后一个IRQ引脚，保留项
	if(vec_nr == 0x27 || vec_nr == 0x2f)
	{
		return;
	}
	put_str("int vector : 0x");
	put_int(vec_nr);
	put_char('\n');
}

//完成一般中断处理函数注册及异常名称注册
static void exception_init(void)
{
	int i;
	for(i=0;i<IDT_DESC_CNT;i++)
	{
		//idt_table数组中的函数是在进入中断后根据中断向量号调用的，见kernel.S的call[idt_table + %1*4]
		idt_table[i] = general_intr_handler;	//这里的idt_table[i]在interrupt.h中定义了是的viod*类型，general_intr_handler是void类型函数，这里直接引用同样为void*类型
		intr_name[i] = "unknown";
	}
	intr_name[0] = "#DE Divide Error";
	intr_name[1] = "#DB Debug Exception";
	intr_name[2] = "NMI Interrupt";
	intr_name[3] = "#BP Breakpoint Exception";
	intr_name[4] = "#OF Overflow Exception";
	intr_name[5] = "#BR BOUND Range Exceeded Exception"; 
	intr_name[6] = "#UD Invalid Opcode Exception";
	intr_name[7] = "#NM Device Not Available Exception";
	intr_name[8] = "#DF Double Fault Exception";
	intr_name[9] = "Coprocessor Segment Overrun";
	intr_name[10] = "#TS Invalid TSS Exception";
	intr_name[11] = "#NP Segment Not Present"; 
	intr_name[12] = "#SS Stack Fault Exception";
	intr_name[13] = "#GP General Protection Exception";
	intr_name[14] = "#PF Page-Fault Exception";
	// intr_name[15] 第 15 项是 intel 保留项,未使用
	intr_name[16] = "#MF x87 FPU Floating-Point Error"; 
	intr_name[17] = "#AC Alignment Check Exception";
	intr_name[18] = "#MC Machine-Check Exception";
	intr_name[19] = "#XF SIMD Floating-Point Exception";
}

//完成有关中断到所有初始化工作
void idt_init()
{
	put_str("idt_init start\n");
	idt_desc_init();			//初始化中断描述符
	exception_init();			//初始化通用中断处理函数
	pic_init();				//初始化8259A

	//加载idt
	uint64_t idt_operand = ((sizeof(idt)-1)|((uint64_t)((uint32_t)idt<<16)));
	asm volatile("lidt %0"::"m"(idt_operand));
	put_str("idt_init done\n");
}
