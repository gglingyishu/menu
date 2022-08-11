#ifndef __GG_MENU_H	
#define __GG_MENU_H	
#include "stm32f1xx.h"
//其他界面文件包含



#define BACKSTAGE_THREAD         1   //如果没有界面在隐藏时有特殊处理可以关闭
#define MENU_SUMPAGE             2   //总界面数 GG@



typedef enum
{
  Menu1,
  Menu2

} GG_MenuPageName;//界面名称对应每个界面的PAGE_ID  GG@

typedef struct
{
    void (*sendSign)();//传递界面信号
    void (*lastSignWork)();//界面运行
    void (*lastSign_ThreadWork)(GG_MenuPageName menu, int sign);//后台持续性事件，或者自身界面运行时给自己或者其他界面发送模拟信号

}GG_MENU_TypeDef;//界面运行总接口

typedef enum
{
  CLOSE = 0,
  NORMAR_ON,
  HIDE

} GG_MenuWorkSta;//界面当前状态

typedef struct
{
    uint8_t Menu_PowerSta;//界面上电标志(目前为预留标志)
    uint8_t KeyLastSignSta;//最新信号值
    uint8_t Menu_LastPage;//最新界面   
    
}GG_MENU_StateTypeDef;

typedef struct 
{
    uint8_t Menu_PowerSta;//界面状态标志 对应GG_MenuWorkSta//为什么不直接用枚举呢。。。。
    
    void (*keyupdate)();
    void (*show)();
    void (*hide)();
    void (*close)();

}GG_MENUPAGE_TypeDef;//界面操作

void GG_MENU_Init(GG_MENU_TypeDef  *MENUx);//初始化
void GG_MENU_SendKeySign(int  keysignsta);//信号接收
void GG_MENU_LastSignWork(void);//信号通知处理

void GG_MENU_BackThreadSignWork(GG_MenuPageName menu, int sign);//持续性后台信号通知处理(可以根据定时器时间放在对应处理函数里)
void GG_MENU_MenuStaUpdate(uint8_t menu, uint8_t worksta);//信号通知处理


#endif




