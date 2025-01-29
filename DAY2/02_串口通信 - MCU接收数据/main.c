#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"

void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode = GPIO_PullUp;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 | GPIO_Pin_1;		//要设置的端口	
	GPIO_Inilize(GPIO_P3 , &init);
}


void UART_Config(){
	
	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//波特率, 	   一般 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//允许接收,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//波特率加倍, ENABLE,DISABLE
	
	//初始化串口：参数一 配置串口 几
	UART_Configuration(UART1, &init);
	
	//打开中断使能 NVIC
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	//切换引脚
	UART1_SW(UART1_SW_P30_P31);
}


void main(){
	
	int i;
	
	//1. 配置IO
	GPIO_Config();
	
	//2. 配置UART
	UART_Config();
	
	//3. 打开全局中断
	EA = 1;
    TX1_write2buff('D');
	
    while(1){
    // 4.接收PC发过来的数据
        
        //4.1 判断串口是否有数据过来
        if(COM1.RX_Cnt >0 && --COM1.RX_TimeOut ==0){
            //4.2  获取数据，遍历数组
            for(i=0;i<COM1.RX_Cnt;i++){
            
                //4.3 取出数组中的每一个元素，在写回去，PC就知道计算机受到什么数据了
                TX1_write2buff(RX1_Buffer[i]);
        }
        COM1.RX_Cnt = 0;
    }
	
    delay_ms(20);
	}
}