#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gg_menu.h"
#include "menu1.h"
#include "gg_key.h"


void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}
void Key_Init(void);
    



GG_MENU_TypeDef  MENUMAIN;
GG_MENUPAGE_TypeDef MENU1;
GG_MENUPAGE_TypeDef MENU2;
GG_KEYBROAD_TypeDef KEY1;
extern GG_MENU_StateTypeDef g_MENU_MainSta;

int main(void)
{
    int i;
    HAL_Init();                    	 			//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
    uart_init(115200);
    Key_Init();
    GG_KEYBOARD_INIT(&KEY1,0xff);
    
    GG_MENU_Init(&MENUMAIN);
    GG_MENU1_Init(&MENU1); 
    GG_MENU2_Init(&MENU2);     
    
    MENU1.show(&MENU1);
	//TIM3_Init(5000-1,7200-1); 
	while(1)
	{
       
        i=KEY1.getkeyvalue(&KEY1);
        if(i>0)
            printf("%d",i);
      
    
            
            GG_MENU_LastSignWork();
       

	}
    
}


void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2;			//PA9
    GPIO_Initure.Mode=GPIO_MODE_INPUT;		//复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9
    
    
    

}







