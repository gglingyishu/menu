#include "gg_menu.h"
/*
*   作者: GG
*   邮箱: guotaoyuan1998@163.com
*   VX: qingya_1998
*   创建日期: 22/07/20
*   更新日期: 22/07/22
*   版本: V1.4
*           更新说明:
*           (BETA):新增了界面传递和信号传递防溢出的限制            
*           (BETA):修改了HIDE状态的处理方式   
*           (BETA):新增了界面传递和信号传递防溢出的限制 
*           (V1.4):新增了部分地方注释,将大部分要移植微调的部分加入标识 GG@
*           (V1.4):界面框架，（update）传递溢出后会重置信号缓存
*   ps: 计划下个版本内容：信号新增缓存区 GG_MenuBobyHandle类可以新添加一个当前界面状态值，或者光标选中值
*                         便于判断光标位置，更加快速实现下拉菜单等功能
*       使用方式:   调用系统初始化 -> 调用子界面初始化 -> 对应界面逻辑方面修改，尤其是标识部分
*/

//定义其他界面
extern GG_MENUPAGE_TypeDef MENU2;
extern GG_MENUPAGE_TypeDef MENU1;

static void Menu1Action(void);
static void Menu2Action(void);

GG_MENU_StateTypeDef g_MENU_MainSta={0};

typedef struct
{
    uint8_t page;//界面 GG@
    void (*action)(void);//界面对应功能处理
    uint8_t worksta;//界面当前工作状态
    
} GG_MenuBobyHandle;

static GG_MenuBobyHandle s_menuBobyHandleMap[] = 
{
    {Menu1,Menu1Action,CLOSE},
    {Menu2,Menu2Action,CLOSE},

};

void GG_MENU_Init(GG_MENU_TypeDef  *MENUx)
{
    MENUx->sendSign = GG_MENU_SendKeySign;  
    MENUx->lastSignWork = GG_MENU_LastSignWork; 
    MENUx->lastSign_ThreadWork = GG_MENU_BackThreadSignWork;   
    
}

static void Menu1Action(void)
{
    MENU1.keyupdate(&MENU1);
    
}

static void Menu2Action(void)
{   
    MENU2.keyupdate(&MENU2); 
    
} 

void GG_MENU_SendKeySign(int  keysignsta)
{
    if(g_MENU_MainSta.KeyLastSignSta > 0)
        g_MENU_MainSta.KeyLastSignSta = keysignsta;
      
}

void GG_MENU_LastSignWork(void)
{
//    uint8_t i;
#ifdef BACKSTAGE_THREAD
    if(g_MENU_MainSta.KeyLastSignSta > 0)
    {
//        if(s_menuBobyHandleMap[i].worksta != 0)
        s_menuBobyHandleMap[g_MENU_MainSta.Menu_LastPage].action();
//            
    }
    
#else    
    s_menuBobyHandleMap[g_MENU_MainSta.Menu_LastPage].action();
#endif

 
}

void GG_MENU_MenuStaUpdate(uint8_t menu, uint8_t worksta)
{
    if(menu < MENU_SUMPAGE)
        s_menuBobyHandleMap[menu].worksta = worksta;

}

void GG_MENU_BackThreadSignWork(GG_MenuPageName menu, int sign)
{
    if(s_menuBobyHandleMap[menu].worksta != CLOSE)
    {
        g_MENU_MainSta.KeyLastSignSta = sign;
        s_menuBobyHandleMap[menu].action();
    }

}













