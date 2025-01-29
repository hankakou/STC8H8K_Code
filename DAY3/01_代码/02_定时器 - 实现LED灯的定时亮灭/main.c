#include "GPIO.h"
#include "NVIC.h"
#include "Delay.h"
#include "Timer.h"


//����IO
void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}

//��ʱ������
void Timer_Config(){
	
	//�����ṹ�����
	TIM_InitTypeDef init;
	
	
	//����Ա��ֵ
	init.TIM_Mode =TIM_16BitAutoReload;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	init.TIM_ClkSource =TIM_CLOCK_1T;	//ʱ��Դ		TIM_CLOCK_1T (41.67ns),TIM_CLOCK_12T(12*41.67),TIM_CLOCK_Ext
	init.TIM_ClkOut =DISABLE;		//�ɱ��ʱ�����,	ENABLE,DISABLE  ����P35��������ߵ͵�ƽ�źţ�
	
	/*
		1. ��ֵ�������16λ����һ��ʼ|Ĭ�� ���е�ֵ��
			1.1 ������ó�ֵ��0����Ҫ��0 ��ʼ��������65535���������ˡ� ����һ�������������ʱ�ͻᴥ���жϡ�
			1.2 ������ó�ֵ��10000������Ҫ��10000��ʼ�������� ��65535 - 1000 �������������ˣ���ʱ�ͻ�Ӵ����ж�
		2. Ϊ�˷���δ���ܹ���׼��ʹ�������ʱ������ϣ���������ʱ���������жϡ�����ʱ�䣬������ 1ms֮�䡿
			2.1 ���ϣ�����ö�ʱ���Ƕ�ʱ 1ms �ʹ����жϣ���ô����Ӧ��дʲô���֣���ֵӦ�����ó�ʲô����
			2.2 ���ڵ�оƬʱ��Ƶ����24M ��1s�ӿ����� 24 000 000��������1ms������ 24000����
						1s = 24M  1000ms = 24M  
			2.3 Ϊʲôһ��Ҫ������1ms �أ� 10ms , 65535 ������2ms ��һ��..  ��Ҫ��Ϊ���Ժ����ʱ����ü��㡣
	*/
	init.TIM_Value = 65535 - ( MAIN_Fosc / 1000 );		//װ�س�ֵ  0 ~ 65535
	init.TIM_Run =ENABLE;		//�Ƿ�����		ENABLE,DISABLE  ��ʼ������֮���Ƿ�������ʼ���� ������ʱ��
	
	//��ʼ����ʱ��
	Timer_Inilize(Timer0, &init);
	
	//�ж�ʹ��
	NVIC_Timer0_Init(ENABLE , Priority_1);
	
}





void main(){
	
	
	//1. ����P53��IOģʽ
	GPIO_config();
	
	//2. ��ʱ������
	Timer_Config();
	
	//3. ��ȫ���ж�
	EA = 1;

	while(1);
}