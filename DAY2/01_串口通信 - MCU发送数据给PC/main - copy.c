#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UARTy.h"
#include "Switch.h"

// IO模式的配置
void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode=GPIO_Pullup;
	init.Pin=GPIO_Pin_1|GPIO_pin_0;

	GPIO_Inilize(GPIO_P3,&init);
}
// 串口的配置
void UART_Config(){
	COMx_InitDefine init;

	init.UART_Mode=UART_8bit_BRTX;
	init.UART_BRT_Use=BRT_Timer1;
	init.UART_BaudRate =115200;		//波特率, 	   一般 110 ~ 115200
	init.UART_RxEnable = ENABLE ;		//允许接收,   ENABLE,DISABLE
	init.BaudRateDouble =DISABLE ;	

	//3.初始化串口
	UART_Configuration(UART1,&init);

	//4.打开中断，NVIC
	NVIC_UART1_Init(ENABLE,Priority_1);

	//切换引脚
	UART1_SW(UART1_SW_P30_P31);

}
void main(){
int age=18;
//1.配置IO模式
GPIO_Config();
//2.配置串口
UART_Config();
//3.打开全局中断
EA=1;
//3. 使用串口发送数据给PC
// TX1_write2buff(0x10);  //a
// PrintString1("start.....\n");

while(1){
	//PrintString1("你好。。。。\n");
	printf("age=%d\n",age);
	printf("name=%s\n",name);

	delay_ms(250);
	delay_ms(250);
	delay_ms(250);
	delay_ms(250);
}

}