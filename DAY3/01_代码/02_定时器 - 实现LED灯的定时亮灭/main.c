#include "GPIO.h"
#include "NVIC.h"
#include "Delay.h"
#include "Timer.h"


//配置IO
void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
}

//定时器配置
void Timer_Config(){
	
	//创建结构体变量
	TIM_InitTypeDef init;
	
	
	//给成员赋值
	init.TIM_Mode =TIM_16BitAutoReload;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	init.TIM_ClkSource =TIM_CLOCK_1T;	//时钟源		TIM_CLOCK_1T (41.67ns),TIM_CLOCK_12T(12*41.67),TIM_CLOCK_Ext
	init.TIM_ClkOut =DISABLE;		//可编程时钟输出,	ENABLE,DISABLE  会在P35引脚输出高低电平信号！
	
	/*
		1. 初值就是这个16位里面一开始|默认 就有的值。
			1.1 如果设置初值是0，就要从0 开始数数，数65535个数就满了。 再数一个数就溢出，此时就会触发中断。
			1.2 如果设置初值是10000，就是要从10000开始数数，数 （65535 - 1000 ）个数就数满了，此时就会从触发中断
		2. 为了方便未来能够精准的使用这个定时器，就希望把这个定时器触发的中断【定的时间，设置在 1ms之间】
			2.1 如果希望设置定时器是定时 1ms 就触发中断，那么这里应该写什么数字（初值应该设置成什么？）
			2.2 现在的芯片时钟频率是24M （1s钟可以数 24 000 000个数），1ms可以数 24000个数
						1s = 24M  1000ms = 24M  
			2.3 为什么一定要纠结于1ms 呢？ 10ms , 65535 最大就是2ms 多一点..  主要是为了以后计算时间更好计算。
	*/
	init.TIM_Value = 65535 - ( MAIN_Fosc / 1000 );		//装载初值  0 ~ 65535
	init.TIM_Run =ENABLE;		//是否运行		ENABLE,DISABLE  初始化好了之后，是否立即开始计数 启动定时器
	
	//初始化定时器
	Timer_Inilize(Timer0, &init);
	
	//中断使能
	NVIC_Timer0_Init(ENABLE , Priority_1);
	
}





void main(){
	
	
	//1. 配置P53的IO模式
	GPIO_config();
	
	//2. 定时器配置
	Timer_Config();
	
	//3. 打开全局中断
	EA = 1;

	while(1);
}