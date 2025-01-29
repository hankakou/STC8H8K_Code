#include "GPIO.h"
#include "NVIC.h"
#include "Timer.h"
#include "Switch.h"
#include "UART.h"


void GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//��ʼ��
}


void UART_Config(void) {
	// >>> �ǵ���� NVIC.c, UART.c, UART_Isr.c <<<
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

  	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);		// ����ѡ��, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

void Timer_Config(){
	TIM_InitTypeDef init;
	
	init.TIM_Mode = TIM_16BitAutoReload;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	init.TIM_ClkSource = TIM_CLOCK_1T;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	init.TIM_ClkOut = DISABLE;		//�ɱ��ʱ�����,	ENABLE,DISABLE
	init.TIM_Value = 65535 - (MAIN_Fosc / 1000);		//װ�س�ֵ
	init.TIM_Run = ENABLE;		//�Ƿ�����		ENABLE,DISABLE
	
	Timer_Inilize(Timer0 , &init);
	
	//�ж�ʹ��
	NVIC_Timer0_Init(ENABLE , Priority_1)

}

void main(){

	while(1){
	
	}
}