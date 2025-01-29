#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"


//1. IO配置
void GPIO_Config(){

	//串口的配置
	GPIO_InitTypeDef init;
	
	init.Mode = GPIO_PullUp;		//IO模式,  		 GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 | GPIO_Pin_1;		//要设置的端口	
	GPIO_Inilize(GPIO_P3 , &init);
	
	
	//LED的配置
	init.Mode = GPIO_OUT_PP;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_3;		//要设置的端口	
	GPIO_Inilize(GPIO_P5 , &init);
}

//2. 串口配置
void UART_Config(){
	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//波特率, 	   一般 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//允许接收,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//波特率加倍, ENABLE,DISABLE
	
	//初始化串口
	UART_Configuration(UART1 , &init);
	
	//中断使能  NVIC
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	
	//切换引脚 Switch
	UART1_SW(UART1_SW_P30_P31);
}


void main(){
	
	//1. IO
	 GPIO_Config();
	
	
	//2. 串口
	UART_Config();
	
	
	//3. 打开中断总开关
	EA = 1;

	
	while(1){
	
		//4. 接收串口数据，判断LED灯要亮还是灭
		if(COM1.RX_Cnt > 0 ){
			
			//5. 由于我们希望控制LED灯亮或者熄灭，所以只需要发送一个字节的数据过来即可。这里就不用循环去遍历128个长度的数组了。
			if(RX1_Buffer[0] == 0x01){ // 亮灯
				P53 = 1;
			}else{ //熄灯
 				P53 = 0;
			}
			
			//6. 清空标志位
			COM1.RX_Cnt = 0;
		}
		
		
		
		delay_ms(20); // 每间隔20ms 就去获取一次串口的数据
	}
}