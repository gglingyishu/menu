#ifndef __MENU1_H	
#define __MENU1_H	
#include "stm32f1xx.h"
#include "gg_menu.h"

#include "menu1.h"
#include "menu2.h"
//typedef struct
//{
//    uint8_t Menu_PowerSta;
//    
//    void (*keyupdate)();
//    void (*show)();
//    void (*hide)();
//    void (*close)();

//}GG_MENUPAGE_TypeDef;

//调用子界面 GG@
extern GG_MENUPAGE_TypeDef MENU1;
extern GG_MENUPAGE_TypeDef MENU2;

void GG_MENU1_Init(GG_MENUPAGE_TypeDef  *MENUx);



#endif
