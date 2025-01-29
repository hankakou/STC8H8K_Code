#include "GPIO.h"
#include "Delay.h"
#include "UART.h"
#include "NVIC.h"
#include "Switch.h"


#define LED_SW P45

#define LED1 P27
#define LED2 P26
#define LED3 P15
#define LED4 P14
#define LED5 P23
#define LED6 P22
#define LED7 P21
#define LED8 P20




void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	
	
	//LED_SW P45
	GPIO_InitStructure.Pin  = GPIO_Pin_5;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
	
	
	
	// 8个LED灯
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);//初始化
	
	
		
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//初始化
	
}

void UART_config(void) {
	// >>> 记得添加 NVIC.c, UART.c, UART_Isr.c <<<
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);		// 引脚选择, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}


void right2left(){
	int i ;
	//实现走马灯效果： 从右到左
		for(i = 1; i <=9 ;i++){
			
			LED1 = i == 1 ? 0 : 1;
			LED2 = i == 2 ? 0 : 1;
			LED3 = i == 3 ? 0 : 1;
			LED4 = i == 4 ? 0 : 1;
			LED5 = i == 5 ? 0 : 1;
			LED6 = i == 6 ? 0 : 1;
			LED7 = i == 7 ? 0 : 1;
			LED8 = i == 8 ? 0 : 1;
			
			delay_ms(100);
		}
	
}

void left2right(){
	int i ;
	//实现走马灯效果： 从左到右
		for(i = 1; i <=9 ;i++){
			
			LED1 = i == 8 ? 0 : 1;
			LED2 = i == 7 ? 0 : 1;
			LED3 = i == 6 ? 0 : 1;
			LED4 = i == 5 ? 0 : 1;
			LED5 = i == 4 ? 0 : 1;
			LED6 = i == 3 ? 0 : 1;
			LED7 = i == 2 ? 0 : 1;
			LED8 = i == 1 ? 0 : 1;
			
			delay_ms(100);

		}
}



void main(){
	
	// 配置IO模式
	GPIO_config();
	
	
	//配置串口
	UART_config();
	
	//中断总开关
	EA = 1;
	
	// 开启总开关
	LED_SW = 0;

	while(1){
		
		if(COM1.RX_Cnt > 0 && --COM1.RX_TimeOut ==0){
			
			if(RX1_Buffer[0] == 0x00){ // 从左到右
				 left2right();
			}else{   // 从右到左
				 right2left();
			}
			COM1.RX_Cnt = 0;
		}
		
		delay_ms(20);
		
	}
}