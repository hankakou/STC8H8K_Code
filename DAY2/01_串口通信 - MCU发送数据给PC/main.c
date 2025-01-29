
#include "Delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"



/*typedef struct
{
	u8	Mode;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	u8	Pin;		//Ҫ���õĶ˿�	
} GPIO_InitTypeDef;

u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx); */

// IOģʽ������
void GPIO_Config(){
    GPIO_InitTypeDef init;
    init.Mode=GPIO_PullUp;
    init.Pin=GPIO_Pin_0 | GPIO_Pin_1;

    GPIO_Inilize(GPIO_P3 , &init);
    
}

/*
typedef struct
{ 
	u8	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	u32	UART_BaudRate;		//������, 	   һ�� 110 ~ 115200
	u8	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	u8	UART_RxEnable;		//�������,   ENABLE,DISABLE
	u8	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
} COMx_InitDefine;

*/
// ���ڵ�����
void UART_Config(){
    //1.�����ṹ�����
    COMx_InitDefine init;
    
    //2.����Ա��ֵ1s��9600������λ
    init.UART_Mode=UART_8bit_BRTx;
    // �������ʱ������ʱ�䣬������֮�󣬾͸��ߴ���Ҫ��һ��������λ��ȥ�ˣ�
    init.UART_BRT_Use = BRT_Timer1;
    init.UART_BaudRate=115200;
    init.UART_RxEnable=ENABLE;
    init.BaudRateDouble=DISABLE;
    
    //3.��ʼ������
    // u8	UART_Configuration(u8 UARTx, COMx_InitDefine *COMx);
    UART_Configuration( UART1, &init);
    
    //4.���ж� NVIC
    NVIC_UART1_Init(ENABLE, Priority_1);
    
    //�л�����
    UART1_SW(UART1_SW_P30_P31);
}


void main(){
    int age=18;
    char name[]="abcdefg123";
    
    //1.����IO��
     GPIO_Config();
    
    //2.���ô���
    UART_Config();
    
    //3.��ȫ���ж�
    EA=1;
    
    TX1_write2buff('A');
    PrintString1("start....\n");
    
while(1)
    {
      //PrintString1("���...\n");
//		printf("age=%d\n"  , age);
//		printf("name=%s\n" , name);
//		
//		
         TX1_write2buff('A');
       PrintString1("���....\n");
       printf("age=%d\n",age);
       printf("name=%s\n",name);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250); 
        



}



} 
 
