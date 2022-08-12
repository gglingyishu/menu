#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gg_menu.h"
#include "menu1.h"
#include "menu2.h"
#include "gg_key.h"

/*  
*    ����Ϊʵ�����ô���ģ�ⰴ������������������л�
*    ʹ�ô��ڽ��ź�ͨ������丳ֵGG_MENU_SendKeySign(USART1->DR - 48);
*    �ﵽ�л�menu1��menu2���������Ч��   
*    �ڸ������水��ʱ�����Menu1Action�����Ķ�Ӧ������ܵĹ��ܺ������ɽ���ϵͳ�Լ��л���
*
*    ps:��������ֲ������ԭ�ӵ����̣�����һ���򵥵�ʵ������Ҫ������������gg����menu.c��menu.1c�Ŀ���߼�   
*    ����ƹ��У�������С��Ŀ����ʹ���ڱ�д��ͬ�������»�������Դ������
*/
GG_MENU_TypeDef  MENUMAIN;
GG_MENUPAGE_TypeDef MENU1;
GG_MENUPAGE_TypeDef MENU2;

int main(void)
{
    HAL_Init();                    	 			//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//����ʱ��,72M
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


