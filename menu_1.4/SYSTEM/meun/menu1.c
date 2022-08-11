#include "gg_menu.h"
#include "menu1.h"

#define PAGE_ID        Menu1//界面号和GG_MenuPageName对应 GG@
#define PAGE_SUMSIGN   4//总信号数，统计一下，怕溢出（包含第一个预留的NULL）

//主控框架结构体
extern GG_MENU_StateTypeDef g_MENU_MainSta;
//用户调用接口
static void GG_MENU_Show(GG_MENUPAGE_TypeDef  *MENUx);
static void GG_MENU_Close(GG_MENUPAGE_TypeDef  *MENUx);
static void GG_MENU_Hide(GG_MENUPAGE_TypeDef  *MENUx);

static void GG_MENU_KeyUpdate(GG_MENUPAGE_TypeDef  *MENUx);
//用户修改添加回调和处理函数
static void GG_MenuDefShowCallback(void);//打开界面接口   GG@
static void GG_MenuDefCloseCallback(void);//关闭界面接口
static void GG_MenuDefHideCallback(void);//隐藏界面，任会做数据采集，数据处理等工作
static void GG_MenuSignChangeCallback(void);//信号转换，复杂界面如果信号差异量大可以做转换

static void Menu1Action(void);
static void Menu2Action(void);
static void Menu3Action(void);

typedef enum
{
  KEY_DOWN = 1,
  KEY_UP,
  RUN_THREAD = 103//动画后台等效果+100后排序
} GG_KeySignSta;//当前界面总信号事件 GG@

typedef struct
{
    uint8_t sign;//信号
    void (*action)(void);//信号行为
    
} GG_MenuBobyHandle;

static const GG_MenuBobyHandle s_menuBobyHandleMap[] = 
{
    {NULL,NULL},
    {KEY_DOWN,Menu1Action},
    {KEY_UP,Menu2Action},
    {RUN_THREAD,Menu3Action},

};

static void GG_MenuDefShowCallback(void)//界面默认窗口
{

    
}

static void GG_MenuDefCloseCallback(void)//界面默认窗口
{

    
}

static void GG_MenuDefHideCallback(void)
{


}

static void GG_MenuSignChangeCallback(void)
{
    if(g_MENU_MainSta.KeyLastSignSta > 100)//后台信号
        g_MENU_MainSta.KeyLastSignSta = g_MENU_MainSta.KeyLastSignSta % 100;
        
    
}

void GG_MENU1_Init(GG_MENUPAGE_TypeDef  *MENUx)
{
    MENUx->close = GG_MENU_Close;
    MENUx->keyupdate = GG_MENU_KeyUpdate;
    MENUx->show = GG_MENU_Show;
    MENUx->hide = GG_MENU_Hide;

}

static void GG_MENU_Show(GG_MENUPAGE_TypeDef  *MENUx)
{
    g_MENU_MainSta.Menu_LastPage = PAGE_ID;
    MENUx->Menu_PowerSta = NORMAR_ON;
    GG_MenuDefShowCallback();     
#ifdef BACKSTAGE_THREAD    
    GG_MENU_MenuStaUpdate(PAGE_ID, NORMAR_ON);
#endif

}

static void GG_MENU_Hide(GG_MENUPAGE_TypeDef  *MENUx)
{
    MENUx->Menu_PowerSta = HIDE;
    GG_MenuDefHideCallback();
#ifdef BACKSTAGE_THREAD    
    GG_MENU_MenuStaUpdate(PAGE_ID, HIDE);
#endif

}

static void GG_MENU_Close(GG_MENUPAGE_TypeDef  *MENUx)
{
    if(PAGE_ID == g_MENU_MainSta.Menu_LastPage)
        g_MENU_MainSta.Menu_LastPage = 0;
    MENUx->Menu_PowerSta = CLOSE;
    GG_MenuDefCloseCallback();
#ifdef BACKSTAGE_THREAD    
    GG_MENU_MenuStaUpdate(PAGE_ID, CLOSE);
#endif
}

static void GG_MENU_KeyUpdate(GG_MENUPAGE_TypeDef  *MENUx)
{
    if((MENUx->Menu_PowerSta != CLOSE)&&(g_MENU_MainSta.KeyLastSignSta % 100 < PAGE_SUMSIGN))
    {
        if((NORMAR_ON == MENUx->Menu_PowerSta)||(g_MENU_MainSta.KeyLastSignSta > 100))
        {
            GG_MenuSignChangeCallback();
            s_menuBobyHandleMap[g_MENU_MainSta.KeyLastSignSta].action();   
        }
    }
    g_MENU_MainSta.KeyLastSignSta = 0;
  
}


static void Menu1Action(void)
{
    printf("1-111\r\n");
    MENU1.close(&MENU1);
    MENU2.show(&MENU2);
    
}

static void Menu2Action(void)
{
    printf("1-222\r\n");   
    MENU1.hide(&MENU1);
} 

static void Menu3Action(void)
{
    printf("1-333\r\n");   
    
} 



