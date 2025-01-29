#include "GPIO.h"
#include "Delay.h"


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
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	
	
	
	//LED_SW P45
	GPIO_InitStructure.Pin  = GPIO_Pin_5;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//��ʼ��
	
	
	
	// 8��LED��
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);//��ʼ��
	
	
		
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//��ʼ��
	
}

void main(){
	
	// ����IOģʽ
	GPIO_config();
	
	// �����ܿ���
	LED_SW = 0;

	while(1){
		
		
		//����
		LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = LED7 =LED8 = 0;
		
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);

		//Ϩ��
		LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = LED7 =LED8 = 1;
		
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		
		
	}
}