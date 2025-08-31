#include "rc_1605.h"
#include "delay.h"

// 引脚配置
void RC_1602_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(E_GPIO_CLK, ENABLE); // 使能PB端口时钟
	
	GPIO_InitStructure.GPIO_Pin = T_GPIO_PIN ;			  // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  // IO口速度为50MHz
	GPIO_Init(T_GPIO_PORT, &GPIO_InitStructure);				  // 根据设定参数初始化GPIOB3
	
	GPIO_InitStructure.GPIO_Pin = E_GPIO_PIN;			  // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO口速度为50MHz
	GPIO_Init(E_GPIO_PORT, &GPIO_InitStructure);			  // 根据设定参数初始化GPIOB4

}
// 测量
u16 DATA = 0;
u32 temp1 = 0;
u16 Get_RC06_Distance(void)
{

	RC06_Trlg2 = 1; // 触发信号是高电平脉冲，宽度大于10us
	delay_us(20);
	RC06_Trlg2 = 0;
	while (!RC06_Echo2)
		;					 // 等待高电平
	TIM_SetCounter(TIM3, 0); // 重填计数器值
	DATA = 0;		 // 溢出次数清零
	while (RC06_Echo2)
		;																			 // 等待低电平
	TIM_Cmd(TIM3, DISABLE);															 // 暂时关闭定时器，保证数据正确性
	temp1 = (int)(((double)(TIM_GetCounter(TIM3) + (7200 * DATA))) / 72 / 2); // 得到高电平总时间，单位us（定时器的计数值加上溢出的值才是高电平的时间），除以2是计算单程的时间
	// （7200* TIM2_UPDATA这里为溢出的时间us，可以转换为100* TIM2_UPDATA,因为在公式后面除以了72。可最终理解为TIM2_UPDATA个100us）
	TIM_Cmd(TIM3, ENABLE);
	return temp1;
}
void TIM3_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 使能TIM2时钟

	// 初始化定时器3
	TIM_TimeBaseStructure.TIM_Period = arr;						// 设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					// 预分频器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	// 中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			  // TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // 先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // 从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);							  // 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 允许更新中断 ,

	TIM_Cmd(TIM3, ENABLE); // 使能定时器2
}
// 定时器3中断服务程序
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) // 检查指定的TIM中断发生与否:TIM 中断源
	{
		DATA++;								// 当回响信号很长时，记录溢出次数，每加一次代表加100us
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除中断标志位
	}
}
