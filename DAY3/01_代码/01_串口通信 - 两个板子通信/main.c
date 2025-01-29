
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"

void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode = GPIO_PullUp;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 |  GPIO_Pin_1;		//要设置的端口	
	GPIO_Inilize(GPIO_P3 , &init);
	
	//配置52 和 53
	
	init.Mode = GPIO_PullUp;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_2 |  GPIO_Pin_3;		//要设置的端口	
	GPIO_Inilize(GPIO_P5 , &init);
}

void UART_Config(){

	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//波特率, 	   一般 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//允许接收,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//波特率加倍, ENABLE,DISABLE
	
	//初始化 串口1
	UART_Configuration(UART1 , &init);
	
	//中断使能 串口1
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	//切换引脚  串口1
	UART1_SW(UART1_SW_P30_P31);
	
	
	//配置串口4
	init.UART_Mode = UART_8bit_BRTx;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer4;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//波特率, 	   一般 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//允许接收,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//波特率加倍, ENABLE,DISABLE
	
	//初始化 串口4
	UART_Configuration(UART4 , &init);
	
	//中断使能 串口4
	NVIC_UART4_Init(ENABLE , Priority_1);
	
	//切换引脚 串口4
	UART4_SW(UART4_SW_P52_P53);
	
	
}

void main(){
	int i;
	
	//1. IO配置
	GPIO_Config();
	
	//2. 串口配置
	UART_Config();
	
	//3. 打开全局中断
	EA = 1;

	while(1){
		
		//========================处理串口1的数据 【串口1收到数据之后，使用串口4写出去】=================
		//1. 获取PC发送过来的数据【PC发送过来的数据是通过串口1发送过来的。】
		if(COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0){
				
			//要考虑数据可能有很多的情况，所以要使用for循环
			for(i = 0  ; i < COM1.RX_Cnt ; i++){
				
					// 先别忙着发给对面的板子，先把这份数据回写给PC，证明我们串口的通信是没有问题的！
					//TX1_write2buff(RX1_Buffer[i]);
				
				
					// 把数据通过串口4，写给对面的板子
					TX4_write2buff(RX1_Buffer[i]);
			}
			
			//重置长度
			COM1.RX_Cnt = 0 ;
		}
	
		
		//======================处理串口4的数据【串口4收到数据之后，使用串口1写出去】 ======================
		if(COM4.RX_Cnt > 0 && --COM4.RX_TimeOut == 0){
			 for(i = 0 ; i < COM4.RX_Cnt ; i++){
				 
				 //使用串口1把串口4的缓冲区数据写出去，这样就能写到PC上了。
					TX1_write2buff(RX4_Buffer[i]);
			 }
			 
			 COM4.RX_Cnt = 0 ;
		}
		
		delay_ms(20);
	}
}