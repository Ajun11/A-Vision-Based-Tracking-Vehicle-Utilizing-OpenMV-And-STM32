#include "bsp_motor.h"
static void wheel_GPIO_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd(left_front_wheel_clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  left_front_wheel_pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(left_front_wheel_port, &GPIO_InitStructure);
		
		RCC_APB2PeriphClockCmd(right_front_wheel_clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  right_front_wheel_pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(right_front_wheel_port, &GPIO_InitStructure);
		
		RCC_APB2PeriphClockCmd(left_back_wheel_clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  left_back_wheel_pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(left_back_wheel_port, &GPIO_InitStructure);
		
		RCC_APB2PeriphClockCmd(right_back_wheel_clk, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  right_back_wheel_pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(right_back_wheel_port, &GPIO_InitStructure);
		//�����Ǽ���
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure_1;
		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( left_front_wheel_control_1_clk, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure_1.GPIO_Pin = left_front_wheel_control_1_pin;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(left_front_wheel_control_1_port, &GPIO_InitStructure_1);	
	
	//**************************����B��
		GPIO_InitTypeDef GPIO_InitStructure_1_1;

		RCC_APB2PeriphClockCmd( left_front_wheel_control_2_clk, ENABLE);

		GPIO_InitStructure_1_1.GPIO_Pin = left_front_wheel_control_2_pin|right_front_wheel_control_1_pin|right_front_wheel_control_2_pin|
		                                left_back_wheel_control_1_pin|left_back_wheel_control_2_pin|right_back_wheel_control_1_pin|
																		right_back_wheel_control_2_pin;	

		GPIO_InitStructure_1_1.GPIO_Mode = GPIO_Mode_Out_PP;   


		GPIO_InitStructure_1_1.GPIO_Speed = GPIO_Speed_50MHz; 

	
		GPIO_Init(left_front_wheel_control_2_port, &GPIO_InitStructure_1_1);	
		left_front_wheel_control_1_low;
		left_front_wheel_control_2_low;
		right_front_wheel_control_1_low;
		right_front_wheel_control_2_low;
		left_back_wheel_control_1_low;
		left_back_wheel_control_2_low;
		right_back_wheel_control_1_low;
		right_back_wheel_control_2_low;
}



//��ʹ�õ������֮ǰ�������������г�ʼ��
/*****************pwm******************/
void  TIM_INIT(void)
{

			ADVANCE_TIM_APBxClock_FUN_1(ADVANCE_TIM_CLK_1,ENABLE);
		/*--------------------ʱ���ṹ���ʼ��-------------------------*/
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
			TIM_TimeBaseStructure.TIM_Period=TIM_PERIOD;	
			// ����CNT��������ʱ�� = Fck_int/(psc+1)
			TIM_TimeBaseStructure.TIM_Prescaler= TIM_PSC;		
			// ����������ģʽ������Ϊ���ϼ���
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
			// �ظ���������ֵ��û�õ����ù�
			TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
			// ��ʼ����ʱ��
			TIM_TimeBaseInit(ADVANCE_TIM_1, &TIM_TimeBaseStructure);
	
			// ռ�ձ����ó�ʼ
			uint16_t CCR1_Val = 100;
			uint16_t CCR2_Val = 100;
			uint16_t CCR3_Val = 100;
			uint16_t CCR4_Val = 100;
			
			TIM_OCInitTypeDef  TIM_OCInitStructure;
			// ����ΪPWMģʽ1
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			// ���ʹ��
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			// ����ռ�ձȴ�С
			//TIM_OCInitStructure_1.TIM_Pulse = 7;
			// ���ͨ����ƽ��������
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			// ���ͨ�����е�ƽ��������
			//TIM_OCInitStructure_1.TIM_OCIdleState = TIM_OCIdleState_Set;
			//ͨ��1
			TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
			TIM_OC1Init(ADVANCE_TIM_1, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(ADVANCE_TIM_1, TIM_OCPreload_Enable);
			//ͨ��2
			TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
			TIM_OC2Init(ADVANCE_TIM_1, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(ADVANCE_TIM_1, TIM_OCPreload_Enable);
			//ͨ��3
			TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
			TIM_OC3Init(ADVANCE_TIM_1, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(ADVANCE_TIM_1, TIM_OCPreload_Enable);
			//ͨ��4
			TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
			TIM_OC4Init(ADVANCE_TIM_1, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(ADVANCE_TIM_1, TIM_OCPreload_Enable);
			// ʹ�ܼ�����
			TIM_Cmd(ADVANCE_TIM_1, ENABLE);	
			// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
			TIM_CtrlPWMOutputs(ADVANCE_TIM_1, ENABLE);	
}
/***************��ʼ������*************/
void MOTOR_INIT(void)
{
	wheel_GPIO_init();
	TIM_INIT();
}

//��ǰ��ǰת��ת�Լ��ٶ�
void  front_left_wheel_control(int judge_value,unsigned int Space)
{
	if(judge_value==0)//�����ת
	{
		left_front_wheel_control_1_low;
		left_front_wheel_control_2_high;
	}
	else if(judge_value==1) //�����ת
	{
		left_front_wheel_control_1_high;
		left_front_wheel_control_2_low;
	}
	TIM_SetCompare1(TIM1 ,Space);
}

//��ǰ��ǰת��ת�Լ��ٶ�
void  front_right_wheel_control(int judge_value,unsigned int Space)
{
	if(judge_value==0)//�����ת
	{
		right_front_wheel_control_1_low;
		right_front_wheel_control_2_high;
	}
	else if(judge_value==1) //�����ת
	{
		right_front_wheel_control_1_high;
		right_front_wheel_control_2_low;
	}
	
	TIM_SetCompare2(TIM1 ,Space);
}
//�����ǰת��ת�Լ��ٶ�
void  back_left_wheel_control(int judge_value,unsigned int Space)
{
	if(judge_value==0)//�����ת
	{
		left_back_wheel_control_1_low;
		left_back_wheel_control_2_high;
	}
	else  if(judge_value==1) //�����ת
	{
		left_back_wheel_control_1_high;
		left_back_wheel_control_2_low;
	}
	TIM_SetCompare3(TIM1 ,Space);
}
//�Һ���ǰת��ת�Լ��ٶ�
void  back_right_wheel_control(int judge_value,unsigned int Space)
{
	if(judge_value==0)//�����ת
	{
		right_back_wheel_control_1_low;
		right_back_wheel_control_2_high;
	}
	else  if(judge_value==1) //�����ת
	{
		right_back_wheel_control_1_high;
		right_back_wheel_control_2_low;
	}
	TIM_SetCompare4(TIM1 ,Space);
}
////ǰ��
//void  straight_move(unsigned int space)
//{
//	front_left_wheel_control(1,space);
//	front_right_wheel_control(1,space);
//	back_left_wheel_control(1,space);
//	back_right_wheel_control(1,space);
//}
////����
//void  straight_reverse(unsigned int space)
//{
//	front_left_wheel_control(0,space);
//	front_right_wheel_control(0,space);
//	back_left_wheel_control(0,space);
//  back_right_wheel_control(0,space);
//}
////��ƽ��
//void  right_move(unsigned  int space)
//{
//	front_left_wheel_control(1,space);
//	front_right_wheel_control(0,space);
//	back_left_wheel_control(0,space);
//  back_right_wheel_control(1,space);
//}
////��ƽ��
//void  left_move(unsigned int space)
//{
//	front_left_wheel_control(0,space);
//	front_right_wheel_control(1,space);
//	back_left_wheel_control(1,space);
//  back_right_wheel_control(0,space);
//}
//void  ce_move( int space_x , int space_y)
//{
//  if(space_x<0)
//	{
//	front_left_wheel_control(0,space_x*-1);
//	front_right_wheel_control(1,space_x*-1);
//	}
//	if(space_x>0)
//	{
//		front_left_wheel_control(1,space_x);
//		front_right_wheel_control(0,space_x);
//	} 
//	if(space_y<0)
//	{
//	back_left_wheel_control(0,space_y*-1);
//  back_right_wheel_control(0,space_y*-1);
//	}
//	if(space_y>0)
//	{
//	back_left_wheel_control(1,space_y);
//  back_right_wheel_control(1,space_y);
//	}
//}
