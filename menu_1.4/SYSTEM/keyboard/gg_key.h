#ifndef __GG_KEY_H	
#define __GG_KEY_H	
#include "stm32f1xx.h"

#define CLICK_THRESHOLD_MINTIME          0
#define CLICK_THRESHOLD_MAXTIME          2

#define PRESS_FUNCTION                1
#define DOUBLE_FUNCTION               1
#define LONG_PRESSLAST_FUNCTION       1
#define LONG_PRESS_FUNCTION           0//�������ܹ���



typedef enum
{
  PRESS = 1,
  DOUBLE,
  LONG_PRESSLAST,
  LONG_PRESS

} GG_KeySignValue;//���浱ǰ״̬

typedef enum
{
  KEY_CLOSE = 0,
  KEY_RUN
  
} GG_KeySta;//������ǰ״̬

typedef struct 
{
    GG_KeySta Key_PowerSta;//����״̬��־ 
    
    GG_KeySignValue keyvalue;
    uint8_t keyfuntion;
    uint8_t keyruntime;
    uint8_t keytimeoutloop;

    void (*keyrun)();
    void (*keyclear)();
    uint8_t (*getkeyvalue)();
    void (*use)();
    void (*pend)();

}GG_KEYBROAD_TypeDef;//

void GG_KEYBOARD_INIT(GG_KEYBROAD_TypeDef *keyboard, uint8_t key);



#endif

















