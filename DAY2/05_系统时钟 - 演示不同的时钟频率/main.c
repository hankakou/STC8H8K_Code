
#include "config.h"
#include "GPIO.h"
#include "delay.h"


void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
	
	
	GPIO_InitStructure.Pin  = GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
}

int main() {
	GPIO_config();
	
	while(1) {
		P53 = 1;
		NOP1();  // 24M :  20.5us   ----   12M : �� С��
		P53 = 0;
		//NOP1();
	}
}