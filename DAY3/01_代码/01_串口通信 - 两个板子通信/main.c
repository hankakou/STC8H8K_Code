
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"

void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode = GPIO_PullUp;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 |  GPIO_Pin_1;		//Ҫ���õĶ˿�	
	GPIO_Inilize(GPIO_P3 , &init);
	
	//����52 �� 53
	
	init.Mode = GPIO_PullUp;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_2 |  GPIO_Pin_3;		//Ҫ���õĶ˿�	
	GPIO_Inilize(GPIO_P5 , &init);
}

void UART_Config(){

	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//������, 	   һ�� 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//�������,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//�����ʼӱ�, ENABLE,DISABLE
	
	//��ʼ�� ����1
	UART_Configuration(UART1 , &init);
	
	//�ж�ʹ�� ����1
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	//�л�����  ����1
	UART1_SW(UART1_SW_P30_P31);
	
	
	//���ô���4
	init.UART_Mode = UART_8bit_BRTx;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer4;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//������, 	   һ�� 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//�������,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//�����ʼӱ�, ENABLE,DISABLE
	
	//��ʼ�� ����4
	UART_Configuration(UART4 , &init);
	
	//�ж�ʹ�� ����4
	NVIC_UART4_Init(ENABLE , Priority_1);
	
	//�л����� ����4
	UART4_SW(UART4_SW_P52_P53);
	
	
}

void main(){
	int i;
	
	//1. IO����
	GPIO_Config();
	
	//2. ��������
	UART_Config();
	
	//3. ��ȫ���ж�
	EA = 1;

	while(1){
		
		//========================������1������ ������1�յ�����֮��ʹ�ô���4д��ȥ��=================
		//1. ��ȡPC���͹��������ݡ�PC���͹�����������ͨ������1���͹����ġ���
		if(COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0){
				
			//Ҫ�������ݿ����кܶ�����������Ҫʹ��forѭ��
			for(i = 0  ; i < COM1.RX_Cnt ; i++){
				
					// �ȱ�æ�ŷ�������İ��ӣ��Ȱ�������ݻ�д��PC��֤�����Ǵ��ڵ�ͨ����û������ģ�
					//TX1_write2buff(RX1_Buffer[i]);
				
				
					// ������ͨ������4��д������İ���
					TX4_write2buff(RX1_Buffer[i]);
			}
			
			//���ó���
			COM1.RX_Cnt = 0 ;
		}
	
		
		//======================������4�����ݡ�����4�յ�����֮��ʹ�ô���1д��ȥ�� ======================
		if(COM4.RX_Cnt > 0 && --COM4.RX_TimeOut == 0){
			 for(i = 0 ; i < COM4.RX_Cnt ; i++){
				 
				 //ʹ�ô���1�Ѵ���4�Ļ���������д��ȥ����������д��PC���ˡ�
					TX1_write2buff(RX4_Buffer[i]);
			 }
			 
			 COM4.RX_Cnt = 0 ;
		}
		
		delay_ms(20);
	}
}