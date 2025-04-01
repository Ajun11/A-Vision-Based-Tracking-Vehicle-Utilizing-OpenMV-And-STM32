#include "sys.h"		    
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#define UART2_BUFFER_SIZE 256 
volatile uint8_t rx2Buffer[UART2_BUFFER_SIZE]; //��������256���ֽڵĻ�������
volatile uint8_t rxBufferNum  = 0;
volatile uint8_t h_u32RecCnt = 0; 
static volatile uint8_t rx2BufferRTail  = 0;
//u8 str1[8];
u8 str_get[7];
short  x_axis=0;
short  y_axis=0;
int blob_flag=-1;
//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void USART2_Init(u32 bound)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ�� 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//Tx
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������Rx
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ
 
	 
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
   
}

//����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���
void USART2_Send_Data(u8 *buf,u8 len)
{
	u8 t; 
  for(t=0;t<len;t++)		//ѭ����������
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,buf[t]);
	}	 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);  
}
  



void TR_Receive(void)
{
	unsigned char BufC; 
	if(uart2Available())//�ж��Ƿ񴥷����ն�
	{
		BufC = uart2Read(); //��һ���ֽ�
		if((BufC==0xFF))//�ж��Ƿ�Ϊ֡ ͷ
		{ 
			BufC = uart2Read(); //��һ���ֽ�
			if((BufC==0xF1))//�Ƿ�Ϊ�ڶ���֡ͷ����Ϊopenmvһ�㴫����λ
			{
				str_get[2]=uart2Read();
				str_get[3]=uart2Read();
				str_get[4]=uart2Read();
				str_get[5]=uart2Read();
				str_get[6]=uart2Read();
				blob_flag=str_get[2];
				x_axis=(short)(str_get[3]+(str_get[4]<<8));//openmv�洢���ݵķ�ʽ��С��ģʽ�������ݵĸ��ֽڴ洢���͵�ַ�����ֽڴ洢���ߵ�ַ
				y_axis=(short)(str_get[5]+(str_get[6]<<8));//���紮�ڽ�������0xff01,��ô�Ƚ��յ�����0x01,��ӵ�0xff������Ϊʲô���ֽ�����
				//��Ϊ���������Ǹ�int���͵����֣������Ǹ�������ô�ͶԸ��ֽ����ư�λ���ϵ��ֽڼ��ɡ�
			}
			 
		}
	} 
}



/**
* @brief      UartRead
* @param[out]  Ret 1 Byte Data.
* @param[in]  void.
*/
uint8_t uart2Read(void)
{
    uint8_t ch ;
    while  (!h_u32RecCnt);//��0ʱִ��������䣬����˵��h_u32RecCnt=1ʱִ�ж�ȡ�����

    ch = rx2Buffer[rx2BufferRTail];
    rx2BufferRTail++;
    if (rx2BufferRTail>=UART2_BUFFER_SIZE)
    {
        rx2BufferRTail  = 0;
    } 
    h_u32RecCnt--;//����ͱ����0��ֻ�е��ٴδ����жϲŻ���1
    return ch;
}

uint16_t uart2Available(void)
{
    return h_u32RecCnt;
}

void USART2_IRQHandler(void)
{ //ǧ������USART_GetITStatus
	if(USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
	{
		rx2Buffer[rxBufferNum] = USART_ReceiveData(USART2); //����8 Bit���� ����һ�ֽ�����,����0x03
		rxBufferNum++;
		if (rxBufferNum >= UART2_BUFFER_SIZE ) rxBufferNum = 0;//������жϽ��������ô洢�����ƶ��ѣ������������һ���洢256�ֽ�����
		h_u32RecCnt++;//��־�����ݵı�־λ
  } 
} 
//���Ӧ������д��
uint8_t usart_read_byte(void)
{
	uint8_t values;
	if(h_u32RecCnt!=0)//˵���ж����ɶ�
	{
		values=rx2Buffer[rx2BufferRTail];
		rx2BufferRTail++;
	}
	if(rx2BufferRTail==256)
		rx2BufferRTail=0;
  h_u32RecCnt=0;
	return values;
}









