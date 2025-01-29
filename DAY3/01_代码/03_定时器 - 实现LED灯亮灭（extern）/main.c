#include "GPIO.h"
#include "NVIC.h"
#include "Timer.h"

void GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}


void Timer_Config(){
	TIM_InitTypeDef init;
	
	init.TIM_Mode = TIM_16BitAutoReload;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	init.TIM_ClkSource = TIM_CLOCK_1T;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	init.TIM_ClkOut = DISABLE;		//�ɱ��ʱ�����,	ENABLE,DISABLE
	
	//��ʱ����ʲôʱ��ش����жϣ� �����ʱ��Żᴥ���� 
	// 16λ ��0 ~ 65535    ʹ�� 65536 ȥ �� 24000�� ��������˼���ǣ� ��Ҫ��24000�������͹�65536���ܹ������ж��ˣ�
	init.TIM_Value = 65536 - ( MAIN_Fosc / 1000 );		//װ�س�ֵ
	init.TIM_Run = ENABLE;		//�Ƿ�����		ENABLE,DISABLE
	
	//��ʼ��
	Timer_Inilize(Timer0 , &init);
	
	NVIC_Timer0_Init(ENABLE , Priority_1);
}



int count = 0 ;
//����ʱ��0���ж�
void handle_timer0_interrupt(){
	//ϣ�� 1s ���ʵ��LED�Ƶ�����Ч��
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
	
	//����GPIO
	GPIO_Config();
	
	//����Timer
	Timer_Config();
	
	//ȫ���ж�
	EA = 1;
	
	while(1){
	
	}

}