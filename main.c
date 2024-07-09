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
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	  Serial2_Init();
	  yan_Init ();
	  FMQ_Init();
	
	while (1)
	{ 		 //Serial_RxFlag = 1;
//        enter();
         off();
		    out();//��������ͷ
		if(Serial_RxFlag==1&&a==0)//���������ͷʶ�������λa�ǿյ�
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_0);//����a0��arduino�˶�Ӧ�����Ž��յ��͵�ƽ�󣬿�������λa�ĵ�
			Delay_ms(5000);
			Serial_RxFlag=0;//����ͷ״̬����0����ʼ�µ�ʶ��
			a=1;//��λa��1����ʾa�г�
		}
		if(Serial_RxFlag==1&&a==1&&b==0)//b��λ
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_1);
			Delay_ms(5000);
			Serial_RxFlag=0;
			b=1;
		}
	if(Serial_RxFlag==1&&a==1&&b==1&&c==0)//c��λ
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_4);
			Delay_ms(5000);
			Serial_RxFlag=0;
			c=1;
		}
	if(Serial_RxFlag==1&&a==1&&b==1&&c==1&&d==0)//d��λ
		{
		  GPIO_SetBits(GPIOA,GPIO_Pin_5);
			Delay_ms(5000);
			Serial_RxFlag=0;
			d=1;
		}
		
		
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0)//��ȡ������������Ӧ�̵�ѹ����
		{

			GPIO_SetBits(GPIOA,GPIO_Pin_7);//����a7��arduion���յ��ߵ�ƽ�󣬽��Ż�λ�Ʊ��
			
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);//��Դ����������500ms���
			Delay_ms(500);
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
			Delay_ms(500);
			
		}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) != 0)//δ�Ż�
		{

			GPIO_ResetBits(GPIOA,GPIO_Pin_7);//����a7����λ���Ϩ��
			
		}
  }
}




// void TIM3_IRQHandler(void)//��ʱ�жϣ�������ʱ
//{
//  if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
//  {
//	
//	    t++;

//		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//   }

//}
