#include "gg_key.h"


#define SET_BIT(x,y)    (x |= (1 << y))
#define RESET_BIT(x,y)  (x &= ~(1 << y))
#define GET_BIT(x,y)    ((x >> y) & 1)



static void GG_KeyRun(GG_KEYBROAD_TypeDef *keyboard, uint8_t keyio);
static uint8_t GG_GetKeyValue(GG_KEYBROAD_TypeDef *keyboard);
static void GG_KeyUseOpen(GG_KEYBROAD_TypeDef *keyboard);
static void GG_KeyPend(GG_KEYBROAD_TypeDef *keyboard);
static void GG_KeyClear(GG_KEYBROAD_TypeDef *keyboard);


void GG_KEYBOARD_INIT(GG_KEYBROAD_TypeDef *keyboard, uint8_t key)
{
    keyboard->getkeyvalue = GG_GetKeyValue;
    keyboard->use = GG_KeyUseOpen;
    keyboard->pend = GG_KeyPend;
    keyboard->keyrun = GG_KeyRun;
    keyboard->keyclear = GG_KeyClear;
    keyboard->Key_PowerSta = KEY_RUN;
    keyboard->keyruntime = 0;
    keyboard->keyfuntion = key;
//#ifdef PRESS_FUNCTION
//    SET_BIT(keyboard->keyfuntion,PRESS);
//#endif
//#ifdef DOUBLE_FUNCTION
//    SET_BIT(keyboard->keyfuntion,DOUBLE);
//#endif    
//#ifdef LONG_PRESSLAST_FUNCTION
//    SET_BIT(keyboard->keyfuntion,LONG_PRESSLAST);
//#endif   
//#ifdef LONG_PRESS_FUNCTION
//    SET_BIT(keyboard->keyfuntion,LONG_PRESS);
//#endif    
    
}

static void GG_KeyRun(GG_KEYBROAD_TypeDef *keyboard, uint8_t keyio)
{
    if(1 == keyio)
    {
        keyboard->keyruntime++;
        if(keyboard->keyruntime > CLICK_THRESHOLD_MAXTIME)
          keyboard->keytimeoutloop++; 
            
    }
    if(0 == keyio)
    {
        if((keyboard->keyruntime > CLICK_THRESHOLD_MINTIME)||(keyboard->keytimeoutloop > 0))
        {     
          if(keyboard->keytimeoutloop < 0)
            keyboard->keyvalue = PRESS;
           else if(1 == GET_BIT(keyboard->keyfuntion,LONG_PRESS))
            keyboard->keyvalue = LONG_PRESS;
           keyboard->keyruntime = 0;
           keyboard->keytimeoutloop = 0;   
        }  
    }    
    
}

static uint8_t  GG_GetKeyValue(GG_KEYBROAD_TypeDef *keyboard)
{
    uint8_t key;
    key = keyboard->keyvalue;

    if(1 == GET_BIT(keyboard->keyfuntion,LONG_PRESSLAST))
    {
       
        return key;
        
    }
    else
    {
        return key;
        
    }
            keyboard->keyvalue = 0;

    return key;
          
}

static void GG_KeyUseOpen(GG_KEYBROAD_TypeDef *keyboard)
{
    keyboard->Key_PowerSta = KEY_RUN;
    
}

static void GG_KeyPend(GG_KEYBROAD_TypeDef *keyboard)
{
    keyboard->Key_PowerSta = KEY_CLOSE;
    keyboard->keyruntime = 0;
    keyboard->keyclear(keyboard);
    
}

static void GG_KeyClear(GG_KEYBROAD_TypeDef *keyboard)
{
    keyboard->keyvalue = 0;
    keyboard->keyruntime = 0;
    keyboard->keytimeoutloop = 0;
    
}

















































