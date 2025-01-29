
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

// �жϺ��� ???  
void uart_hello(void) interrupt 4 {
	if(RI) {
        // ������ռĴ���RI�������жϣ��򿪵�
		RI = 0;
		P53 = 1;//��
	} 
	
	if(TI) {
        // ������ͼĴ���TI�������жϣ��ص���
		TI = 0;
		P53 = 0;//��
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
	P5M1 &= ~0x08,	P5M0 |=  0x08; //�������
	
	SCON = 0x50;
	T2L = 0xe8; //65536-11059200/115200/4=0FFE8H
	T2H = 0xff;
	AUXR = 0x15;//������ʱ��
	
	EA = 1;  // ȫ���ж�
	ES = 1;  // �ж�ʹ�� 
	
	P53 = 0;  // �ȹص�
	
	while(1) {
    // ����1000ms
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		
    // ����һ������0x11
		SBUF = 0x11;
		
    // ��TIλ�Ĵ�����Ϊ1 (������Բ�����, ֻҪ��SBUF��ֵ��, TIҲ���Զ���Ϊ1) :: �ᷢ�������ж�
		TI = 1;
	}
}