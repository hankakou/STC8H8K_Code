#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UARTy.h"
#include "Switch.h"

// IOģʽ������
void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode=GPIO_Pullup;
	init.Pin=GPIO_Pin_1|GPIO_pin_0;

	GPIO_Inilize(GPIO_P3,&init);
}
// ���ڵ�����
void UART_Config(){
	COMx_InitDefine init;

	init.UART_Mode=UART_8bit_BRTX;
	init.UART_BRT_Use=BRT_Timer1;
	init.UART_BaudRate =115200;		//������, 	   һ�� 110 ~ 115200
	init.UART_RxEnable = ENABLE ;		//�������,   ENABLE,DISABLE
	init.BaudRateDouble =DISABLE ;	

	//3.��ʼ������
	UART_Configuration(UART1,&init);

	//4.���жϣ�NVIC
	NVIC_UART1_Init(ENABLE,Priority_1);

	//�л�����
	UART1_SW(UART1_SW_P30_P31);

}
void main(){
int age=18;
//1.����IOģʽ
GPIO_Config();
//2.���ô���
UART_Config();
//3.��ȫ���ж�
EA=1;
//3. ʹ�ô��ڷ������ݸ�PC
// TX1_write2buff(0x10);  //a
// PrintString1("start.....\n");

while(1){
	//PrintString1("��á�������\n");
	printf("age=%d\n",age);
	printf("name=%s\n",name);

	delay_ms(250);
	delay_ms(250);
	delay_ms(250);
	delay_ms(250);
}

}