#ifndef BSP_MOTOR_H
#define BSP_MOTOR_H
#include "stm32f10x.h"
/************�߼���ʱ��TIM�������壬СС���İ�ֻ��TIM1************/
//�ɲ���ͷ�ļ�199��
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ��߼���ʱ�����ڸ�������APB1�ϣ����Ǳ�Ĳ��ǣ����Ҫע��
// ��������ʹ�ø߼����ƶ�ʱ��TIM1
#define            ADVANCE_TIM_APBxClock_FUN_1     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_1                   TIM1
#define            ADVANCE_TIM_CLK_1               RCC_APB2Periph_TIM1
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            TIM_PERIOD                      799
#define            TIM_PSC                         8
/**************************��������********************************/

/*���Ӷ˿ڶ���*/
//������������ǰ��L298N������󣬷�����ʵ�����˵���ñ������pwm��Ȼ�����𵽿��Ƶ����ã�ֻ��˵���ĸ�����Ҫ�иߵ͵���������֮��ߵͲ���������˶�����
//�ڴ˶Դ�ͷ�ļ������޸�
//�����ĸ�����������ʱ��1���ĸ�ͨ������˿ڣ������·pwm
#define           left_front_wheel_port     		 GPIOA
#define           left_front_wheel_pin        	 GPIO_Pin_8
#define           left_front_wheel_clk           RCC_APB2Periph_GPIOA
  
#define           right_front_wheel_port         GPIOA
#define           right_front_wheel_pin       	 GPIO_Pin_9
#define           right_front_wheel_clk          RCC_APB2Periph_GPIOA

#define           left_back_wheel_port     		   GPIOA
#define           left_back_wheel_pin        	   GPIO_Pin_10
#define           left_back_wheel_clk            RCC_APB2Periph_GPIOA
  
#define           right_back_wheel_port          GPIOA
#define           right_back_wheel_pin           GPIO_Pin_11
#define           right_back_wheel_clk           RCC_APB2Periph_GPIOA
//����˸��ǿ������Ÿߵ͵�ƽ����ͨ���š�
//��ǰ�ֵ��������ƿ�******************////
///Reset����͵�ƽ��Set����ߵ�ƽ////////
///L298N������In 1 2 3 4 1�����������ת///
#define           left_front_wheel_control_1_port    GPIOB  //298N  in1
#define           left_front_wheel_control_1_pin     GPIO_Pin_11
#define           left_front_wheel_control_1_clk     RCC_APB2Periph_GPIOB
#define           left_front_wheel_control_1_low     GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define           left_front_wheel_control_1_high    GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define           left_front_wheel_control_2_port    GPIOB  //2
#define           left_front_wheel_control_2_pin     GPIO_Pin_10
#define           left_front_wheel_control_2_clk     RCC_APB2Periph_GPIOB
#define           left_front_wheel_control_2_low     GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define           left_front_wheel_control_2_high    GPIO_SetBits(GPIOB,GPIO_Pin_10)

//��ǰ�ֵ��������ƿ�******************///////
#define           right_front_wheel_control_1_port   GPIOB  //3
#define           right_front_wheel_control_1_pin    GPIO_Pin_1
#define           right_front_wheel_control_1_clk    RCC_APB2Periph_GPIOB
#define           right_front_wheel_control_1_low    GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define           right_front_wheel_control_1_high   GPIO_SetBits(GPIOB,GPIO_Pin_1)

#define           right_front_wheel_control_2_port   GPIOB //4
#define           right_front_wheel_control_2_pin    GPIO_Pin_0
#define           right_front_wheel_control_2_clk    RCC_APB2Periph_GPIOB
#define           right_front_wheel_control_2_low    GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define           right_front_wheel_control_2_high   GPIO_SetBits(GPIOB,GPIO_Pin_0)
//����ֵ��������ƿ�
#define           left_back_wheel_control_1_port     GPIOB
#define           left_back_wheel_control_1_pin      GPIO_Pin_6
#define           left_back_wheel_control_1_clk      RCC_APB2Periph_GPIOB
#define           left_back_wheel_control_1_low      GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define           left_back_wheel_control_1_high     GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define           left_back_wheel_control_2_port     GPIOB
#define           left_back_wheel_control_2_pin      GPIO_Pin_7
#define           left_back_wheel_control_2_clk      RCC_APB2Periph_GPIOB
#define           left_back_wheel_control_2_low      GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define           left_back_wheel_control_2_high     GPIO_SetBits(GPIOB,GPIO_Pin_7)

//�Һ��ֵ��������ƿ�
#define           right_back_wheel_control_1_port    GPIOB
#define           right_back_wheel_control_1_pin     GPIO_Pin_8
#define           right_back_wheel_control_1_clk     RCC_APB2Periph_GPIOB
#define           right_back_wheel_control_1_low     GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define           right_back_wheel_control_1_high    GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define           right_back_wheel_control_2_port    GPIOB
#define           right_back_wheel_control_2_pin     GPIO_Pin_9
#define           right_back_wheel_control_2_clk     RCC_APB2Periph_GPIOB
#define           right_back_wheel_control_2_low     GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define           right_back_wheel_control_2_high    GPIO_SetBits(GPIOB,GPIO_Pin_9)
/**************************��������********************************/
//judge_value�ж�ǰ��SpaceΪCRRֵ Ҫ��CRR<800
//��ǰ��ǰת��ת�Լ��ٶ�
void  front_left_wheel_control(int judge_value,unsigned int Space);
void  front_right_wheel_control(int judge_value,unsigned int Space);
void  back_left_wheel_control(int judge_value,unsigned int Space);
void  back_right_wheel_control(int judge_value,unsigned int Space);
void  MOTOR_INIT(void);
#endif
