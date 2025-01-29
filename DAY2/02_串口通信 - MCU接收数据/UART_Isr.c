/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include "UART.h"

//========================================================================
// 函数: UART1_ISR_Handler
// 描述: UART1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART1
void UART1_ISR_Handler (void) interrupt UART1_VECTOR
{
	
	// 如果发生接收中断，那么就会执行这段if的代码 :: 接收完一次数据帧【8位数据】，就会触发一次中断
	if(RI)
	{
		// 把中断的标记给重置了。
		RI = 0; 

				//1. 判断现在已经接收到的数据长度已经超过了一个固定的值，那么就把已经接收到的数据长度重置为 0 
        if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
		
				/*
					2. 
						2.1 SBUF 就是串口接收到的一个数据帧【8位数据】之后，就把这个数据放在SBUF里面存着。  SBUF只有一个自己的长度的！
						2.2 我们自己要定义一个数组 RX1_Buffer，用来不断地把SBUF的数据拿走，否则下一个数据过来，就会把SBUF原来的数据给顶替|覆盖了！
						2.3 我们的代码定义了一个 128个长度的数组 RX1_Buffer 用来临时存储 SBUF的数据。
						2.4 为了把所有发过来的数据都装到数组里面去，定义了一个在变化的长度 | 下标 变量 COM1.RX_Cnt ， 它默认值是 0 
				*/
        RX1_Buffer[COM1.RX_Cnt++] = SBUF;
		
		
				//3. 每次接收到一个数据帧【8位数据】，它就让这个变量重置为一个值

        COM1.RX_TimeOut = TimeOutSet1;  // 5
	} 

	// 如果发生发送中断，那么就会执行这段if的代码
	if(TI)
	{
		TI = 0;
		
        #if(UART_QUEUE_MODE == 1)   //判断是否使用队列模式
		if(COM1.TX_send != COM1.TX_write)
		{
		 	SBUF = TX1_Buffer[COM1.TX_send];
			if(++COM1.TX_send >= COM_TX1_Lenth)		COM1.TX_send = 0;
		}
		else	COM1.B_TX_busy = 0;
        #else
        COM1.B_TX_busy = 0;     //使用阻塞方式发送直接清除繁忙标志
        #endif
	}
}
#endif

//========================================================================
// 函数: UART2_ISR_Handler
// 描述: UART2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART2
void UART2_ISR_Handler (void) interrupt UART2_VECTOR
{
	if(RI2)
	{
		CLR_RI2();

		
        if(COM2.RX_Cnt >= COM_RX2_Lenth)	COM2.RX_Cnt = 0;
        RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
        COM2.RX_TimeOut = TimeOutSet2;
	}

	if(TI2)
	{
		CLR_TI2();
		
        #if(UART_QUEUE_MODE == 1)   //判断是否使用队列模式
		if(COM2.TX_send != COM2.TX_write)
		{
		 	S2BUF = TX2_Buffer[COM2.TX_send];
			if(++COM2.TX_send >= COM_TX2_Lenth)		COM2.TX_send = 0;
		}
		else	COM2.B_TX_busy = 0;
        #else
        COM2.B_TX_busy = 0;     //使用阻塞方式发送直接清除繁忙标志
        #endif
	}
}
#endif

//========================================================================
// 函数: UART3_ISR_Handler
// 描述: UART3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART3
void UART3_ISR_Handler (void) interrupt UART3_VECTOR
{
	if(RI3)
	{
		CLR_RI3();

        if(COM3.RX_Cnt >= COM_RX3_Lenth)	COM3.RX_Cnt = 0;
        RX3_Buffer[COM3.RX_Cnt++] = S3BUF;
        COM3.RX_TimeOut = TimeOutSet3;
	}

	if(TI3)
	{
		CLR_TI3();
		
        #if(UART_QUEUE_MODE == 1)   //判断是否使用队列模式
		if(COM3.TX_send != COM3.TX_write)
		{
		 	S3BUF = TX3_Buffer[COM3.TX_send];
			if(++COM3.TX_send >= COM_TX3_Lenth)		COM3.TX_send = 0;
		}
		else	COM3.B_TX_busy = 0;
        #else
        COM3.B_TX_busy = 0;     //使用阻塞方式发送直接清除繁忙标志
        #endif
	}
}
#endif

//========================================================================
// 函数: UART4_ISR_Handler
// 描述: UART4中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-23
//========================================================================
#ifdef UART4
void UART4_ISR_Handler (void) interrupt UART4_VECTOR
{
	if(RI4)
	{
		CLR_RI4();

        if(COM4.RX_Cnt >= COM_RX4_Lenth)	COM4.RX_Cnt = 0;
        RX4_Buffer[COM4.RX_Cnt++] = S4BUF;
        COM4.RX_TimeOut = TimeOutSet4;
	}

	if(TI4)
	{
		CLR_TI4();
		
        #if(UART_QUEUE_MODE == 1)   //判断是否使用队列模式
		if(COM4.TX_send != COM4.TX_write)
		{
		 	S4BUF = TX4_Buffer[COM4.TX_send];
			if(++COM4.TX_send >= COM_TX4_Lenth)		COM4.TX_send = 0;
		}
		else	COM4.B_TX_busy = 0;
        #else
        COM4.B_TX_busy = 0;     //使用阻塞方式发送直接清除繁忙标志
        #endif
	}
}
#endif
