#include "GPIO.h"
#include "NVIC.h"
#include "Timer.h"

void GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
}


void Timer_Config(){
	TIM_InitTypeDef init;
	
	init.TIM_Mode = TIM_16BitAutoReload;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	init.TIM_ClkSource = TIM_CLOCK_1T;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	init.TIM_ClkOut = DISABLE;		//可编程时钟输出,	ENABLE,DISABLE
	
	//定时器是什么时候回触发中断？ 溢出的时候才会触发。 
	// 16位 。0 ~ 65535    使用 65536 去 减 24000， 这样的意思就是： 还要数24000个数，就够65536就能够触发中断了！
	init.TIM_Value = 65536 - ( MAIN_Fosc / 1000 );		//装载初值
	init.TIM_Run = ENABLE;		//是否运行		ENABLE,DISABLE
	
	//初始化
	Timer_Inilize(Timer0 , &init);
	
	NVIC_Timer0_Init(ENABLE , Priority_1);
}



int count = 0 ;
//处理定时器0的中断
void handle_timer0_interrupt(){
	//希望 1s 间隔实现LED灯的亮灭效果
	count++;
	if(count == 500){
		P53 = ~P53;
		count = 0 ;
	}
}


//void My_Timer0_ISR_Handler (void) interrupt TMR0_VECTOR	{
//	handle_timer0_interrupt();
//}



void main(){
	
	//配置GPIO
	GPIO_Config();
	
	//配置Timer
	Timer_Config();
	
	//全局中断
	EA = 1;
	
	while(1){
	
	}

}