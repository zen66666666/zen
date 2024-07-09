#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "Serial.h"
#include "Serial2.h"
#include "LED.h"
#include "TIME.h"
#include "ENTER.h"
#include "KEY.h"
#include "yan.h"
#include "FMQ.h"


 uint8_t Serial_RxFlag;
uint16_t t=0,m;
uint8_t a=0,b=0,c=0,d=0;
int main (void)
{
	  LED_Init();
	  Key_Init();
	uart_init(115200);	 //串口初始化为115200
	  Serial2_Init();
	  yan_Init ();
	  FMQ_Init();
	
	while (1)
	{ 		 //Serial_RxFlag = 1;
//        enter();
         off();
		    out();//出口摄像头
		if(Serial_RxFlag==1&&a==0)//当入口摄像头识别后，若车位a是空的
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_0);//拉高a0，arduino端对应的引脚接收到低电平后，开启到车位a的灯
			Delay_ms(5000);
			Serial_RxFlag=0;//摄像头状态量至0，开始新的识别
			a=1;//车位a至1，表示a有车
		}
		if(Serial_RxFlag==1&&a==1&&b==0)//b车位
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_1);
			Delay_ms(5000);
			Serial_RxFlag=0;
			b=1;
		}
	if(Serial_RxFlag==1&&a==1&&b==1&&c==0)//c车位
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_4);
			Delay_ms(5000);
			Serial_RxFlag=0;
			c=1;
		}
	if(Serial_RxFlag==1&&a==1&&b==1&&c==1&&d==0)//d车位
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			Delay_ms(5000);
			Serial_RxFlag=0;
			d=1;
		}
		
		
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0)//读取烟雾传感器，感应烟电压至低
		{

			GPIO_SetBits(GPIOA,GPIO_Pin_7);//拉高a7，arduion端收到高电平后，将着火车位灯变红
			
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);//有源蜂鸣器发声500ms间断
			Delay_ms(500);
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
			Delay_ms(500);
			
		}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) != 0)//未着火
		{

			GPIO_ResetBits(GPIOA,GPIO_Pin_7);//拉低a7，车位红灯熄灭
			
		}
  }
}




// void TIM3_IRQHandler(void)//定时中断，用来计时
//{
//  if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
//  {
//	
//	    t++;

//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//   }

//}
