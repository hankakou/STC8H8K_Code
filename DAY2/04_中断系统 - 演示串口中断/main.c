
sfr		P5M1 	= 0xC9;
sfr		P5M0 	= 0xCA;
sfr		P5 		= 0xC8;
sbit	P53		= P5^3;

sfr     T2L     =   0xd7;
sfr     T2H     =   0xd6;
sfr     AUXR    =   0x8e;

sfr		IE		= 0xA8;
sbit	EA		= IE^7;
sbit	ES		= IE^4;

sfr		SCON	= 0x98;
sfr		SBUF	= 0x99;
sbit	RI		= SCON^0;
sbit	TI		= SCON^1;

// 中断函数 ???  
void uart_hello(void) interrupt 4 {
	if(RI) {
        // 如果接收寄存器RI触发了中断，打开灯
		RI = 0;
		P53 = 1;//开
	} 
	
	if(TI) {
        // 如果发送寄存器TI触发了中断，关掉灯
		TI = 0;
		P53 = 0;//关
	}
}

void Delay1000ms(void)	//@24.000MHz
{
	unsigned char data i, j, k;


	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


int main() {
	P5M1 &= ~0x08,	P5M0 |=  0x08; //推挽输出
	
	SCON = 0x50;
	T2L = 0xe8; //65536-11059200/115200/4=0FFE8H
	T2H = 0xff;
	AUXR = 0x15;//启动定时器
	
	EA = 1;  // 全局中断
	ES = 1;  // 中断使能 
	
	P53 = 0;  // 先关灯
	
	while(1) {
    // 休眠1000ms
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		
    // 发送一个数据0x11
		SBUF = 0x11;
		
    // 将TI位寄存器置为1 (这里可以不设置, 只要给SBUF赋值了, TI也会自动变为1) :: 会发生发送中断
		TI = 1;
	}
}