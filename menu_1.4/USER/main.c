#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gg_menu.h"
#include "menu1.h"
#include "menu2.h"
#include "gg_key.h"

/*  
*    历程为实例，用串口模拟按键，进行两个界面的切换
*    使用串口将信号通过该语句赋值GG_MENU_SendKeySign(USART1->DR - 48);
*    达到切换menu1和menu2两个界面的效果   
*    在各个界面按下时会调用Menu1Action这样的对应按键框架的功能函数（由界面系统自己切换）
*
*    ps:界面是移植在正点原子的历程，做了一个简单的实例，主要代码量体现在gg——menu.c和menu.1c的框架逻辑   
*    框架推广中，后续有小项目被人使用在编写者同意的情况下会慢慢开源上来。
*/
GG_MENU_TypeDef  MENUMAIN;
GG_MENUPAGE_TypeDef MENU1;
GG_MENUPAGE_TypeDef MENU2;

int main(void)
{
    HAL_Init();                    	 			//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
    uart_init(115200);
    
    GG_MENU_Init(&MENUMAIN);
    GG_MENU1_Init(&MENU1); 
    GG_MENU2_Init(&MENU2);     
    
    MENU1.show(&MENU1);
	//TIM3_Init(5000-1,7200-1); 
	while(1)
    {
        GG_MENU_LastSignWork();
       
	}
    
}


