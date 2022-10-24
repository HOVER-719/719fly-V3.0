//#include "main.h"
////#include "tfmini.h"

///**使用串口1进行通信**/
//uint16_t TFminiStrength;
////uint8_t TFminiMode,TFminiCheckSum;
//uint8_t TFminiDATA[10],TFminiDistance;
////unsigned char TFminiDATA[Max_BUFF_Len];
////unsigned int RXTime=0;
//uint8_t RXTime=0;//次数


///**模拟串口，用来进行数据监测   仅发送   TX PA9**/

//void MUSART1_SendData(uint8_t data)
//{
//	uint8_t i = 0;
//	

//	//Delay_us(104);
//	
//	GPIOB->BRR  = GPIO_Pin_13;		//!<起始位
//	Delay_us(8);
//	for(i = 0; i < 8; i++)
//	{
//		if(data & 0x01)
//			GPIOB->BSRR = GPIO_Pin_13;
//		else
//			GPIOB->BRR  = GPIO_Pin_13;
//		Delay_us(8);
//		data >>= 1;
//	}
//	GPIOB->BSRR = GPIO_Pin_13;		//!<停止位
//	Delay_us(8);
//}



//void USART1_IRQHandler(void)//接收TFmini数据
//{
//	 
//		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET) //中断产生 
//	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //清除中断标志
//		TFminiDATA[RXTime] = USART_ReceiveData(USART1);
//		RXTime++;
//		if(TFminiDATA[0]!=0x59)	 
//			{
//			RXTime=0;
//			}
//			
//		if(TFminiDATA[1]==0x59&&RXTime>=8)
//			{
//		//MUSART1_SendData(TFminiDATA[2]);//dd【记得删除】测试用
//		//		MUSART1_SendData(TFminiDATA[2]);//【记得删除】测试用
//				TFminiDistance=TFminiDATA[2];
//			
//				//	MUSART1_SendData(RXTime);
//			RXTime=0;
//			}
//		
//		
//	}
//}

//			






//void TFmini_Init(void)
//{
//	//全部使用默认配置   如果测量精度不够再改成 固定档位模式+短距离档位
//}
