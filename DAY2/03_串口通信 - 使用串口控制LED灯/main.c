#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Delay.h"


//1. IO����
void GPIO_Config(){

	//���ڵ�����
	GPIO_InitTypeDef init;
	
	init.Mode = GPIO_PullUp;		//IOģʽ,  		 GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 | GPIO_Pin_1;		//Ҫ���õĶ˿�	
	GPIO_Inilize(GPIO_P3 , &init);
	
	
	//LED������
	init.Mode = GPIO_OUT_PP;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_3;		//Ҫ���õĶ˿�	
	GPIO_Inilize(GPIO_P5 , &init);
}

//2. ��������
void UART_Config(){
	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//������, 	   һ�� 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//�������,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//�����ʼӱ�, ENABLE,DISABLE
	
	//��ʼ������
	UART_Configuration(UART1 , &init);
	
	//�ж�ʹ��  NVIC
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	
	//�л����� Switch
	UART1_SW(UART1_SW_P30_P31);
}


void main(){
	
	//1. IO
	 GPIO_Config();
	
	
	//2. ����
	UART_Config();
	
	
	//3. ���ж��ܿ���
	EA = 1;

	
	while(1){
	
		//4. ���մ������ݣ��ж�LED��Ҫ��������
		if(COM1.RX_Cnt > 0 ){
			
			//5. ��������ϣ������LED��������Ϩ������ֻ��Ҫ����һ���ֽڵ����ݹ������ɡ�����Ͳ���ѭ��ȥ����128�����ȵ������ˡ�
			if(RX1_Buffer[0] == 0x01){ // ����
				P53 = 1;
			}else{ //Ϩ��
 				P53 = 0;
			}
			
			//6. ��ձ�־λ
			COM1.RX_Cnt = 0;
		}
		
		
		
		delay_ms(20); // ÿ���20ms ��ȥ��ȡһ�δ��ڵ�����
	}
}