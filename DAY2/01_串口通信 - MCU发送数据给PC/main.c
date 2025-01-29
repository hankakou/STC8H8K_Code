
#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"



/*typedef struct
{
	u8	Mode;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	u8	Pin;		//要设置的端口	
} GPIO_InitTypeDef;

u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx); */

// IO模式的配置
void GPIO_Config(){
    GPIO_InitTypeDef init;
    init.Mode=GPIO_PullUp;
    init.Pin=GPIO_Pin_0 | GPIO_Pin_1;

    GPIO_Inilize(GPIO_P3 , &init);
    
}

/*
typedef struct
{ 
	u8	UART_Mode;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	u32	UART_BaudRate;		//波特率, 	   一般 110 ~ 115200
	u8	Morecommunicate;	//多机通讯允许, ENABLE,DISABLE
	u8	UART_RxEnable;		//允许接收,   ENABLE,DISABLE
	u8	BaudRateDouble;		//波特率加倍, ENABLE,DISABLE
} COMx_InitDefine;

*/
// 串口的配置
void UART_Config(){
    //1.创建结构体变量
    COMx_InitDefine init;
    
    //2.给成员赋值1s发9600二进制位
    init.UART_Mode=UART_8bit_BRTx;
    // 由这个定时器来定时间，到点了之后，就告诉串口要发一个二进制位出去了！
    init.UART_BRT_Use = BRT_Timer1;
    init.UART_BaudRate=115200;
    init.UART_RxEnable=ENABLE;
    init.BaudRateDouble=DISABLE;
    
    //3.初始化串口
    // u8	UART_Configuration(u8 UARTx, COMx_InitDefine *COMx);
    UART_Configuration( UART1, &init);
    
    //4.打开中断 NVIC
    NVIC_UART1_Init(ENABLE, Priority_1);
    
    //切换引脚
    UART1_SW(UART1_SW_P30_P31);
}


void main(){
    int age=18;
    char name[]="abcdefg123";
    
    //1.配置IO口
     GPIO_Config();
    
    //2.配置串口
    UART_Config();
    
    //3.打开全局中断
    EA=1;
    
    TX1_write2buff('A');
    PrintString1("start....\n");
    
while(1)
    {
      //PrintString1("你好...\n");
//		printf("age=%d\n"  , age);
//		printf("name=%s\n" , name);
//		
//		
         TX1_write2buff('A');
       PrintString1("你好....\n");
       printf("age=%d\n",age);
       printf("name=%s\n",name);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250); 
        



}



} 
 
