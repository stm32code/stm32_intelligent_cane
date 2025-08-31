#ifndef __RC_1602_H
#define __RC_1602_H
#include "sys.h"

#define T_GPIO_PORT GPIOB               /* GPIO端口 */
#define T_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO端口时钟 */
#define T_GPIO_PIN GPIO_Pin_12

#define E_GPIO_PORT GPIOB               /* GPIO端口 */
#define E_GPIO_CLK RCC_APB2Periph_GPIOB /* GPIO端口时钟 */
#define E_GPIO_PIN GPIO_Pin_13

#define RC06_Trlg2 PBout(12)
#define RC06_Echo2 PBin(13)  
// 引脚配置
void RC_1602_Init(void);
// 测量
u16 Get_RC06_Distance(void);
void TIM3_Init(u16 arr, u16 psc);

#endif

