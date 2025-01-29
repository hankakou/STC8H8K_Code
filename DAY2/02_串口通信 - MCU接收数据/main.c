#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"

void GPIO_Config(){
	GPIO_InitTypeDef init;
	init.Mode = GPIO_PullUp;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	init.Pin = GPIO_Pin_0 | GPIO_Pin_1;		//Ҫ���õĶ˿�	
	GPIO_Inilize(GPIO_P3 , &init);
}


void UART_Config(){
	
	COMx_InitDefine init;
	
	init.UART_Mode = UART_8bit_BRTx;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	init.UART_BRT_Use = BRT_Timer1;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	init.UART_BaudRate = 115200;		//������, 	   һ�� 110 ~ 115200
	init.UART_RxEnable = ENABLE;		//�������,   ENABLE,DISABLE
	init.BaudRateDouble = DISABLE;		//�����ʼӱ�, ENABLE,DISABLE
	
	//��ʼ�����ڣ�����һ ���ô��� ��
	UART_Configuration(UART1, &init);
	
	//���ж�ʹ�� NVIC
	NVIC_UART1_Init(ENABLE , Priority_1);
	
	//�л�����
	UART1_SW(UART1_SW_P30_P31);
}


void main(){
	
	int i;
	
	//1. ����IO
	GPIO_Config();
	
	//2. ����UART
	UART_Config();
	
	//3. ��ȫ���ж�
	EA = 1;
    TX1_write2buff('D');
	
    while(1){
    // 4.����PC������������
        
        //4.1 �жϴ����Ƿ������ݹ���
        if(COM1.RX_Cnt >0 && --COM1.RX_TimeOut ==0){
            //4.2  ��ȡ���ݣ���������
            for(i=0;i<COM1.RX_Cnt;i++){
            
                //4.3 ȡ�������е�ÿһ��Ԫ�أ���д��ȥ��PC��֪��������ܵ�ʲô������
                TX1_write2buff(RX1_Buffer[i]);
        }
        COM1.RX_Cnt = 0;
    }
	
    delay_ms(20);
	}
}