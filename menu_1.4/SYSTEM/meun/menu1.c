#include "gg_menu.h"
#include "menu1.h"

#define PAGE_ID        Menu1//����ź�GG_MenuPageName��Ӧ GG@
#define PAGE_SUMSIGN   4//���ź�����ͳ��һ�£��������������һ��Ԥ����NULL��

//���ؿ�ܽṹ��
extern GG_MENU_StateTypeDef g_MENU_MainSta;
//�û����ýӿ�
static void GG_MENU_Show(GG_MENUPAGE_TypeDef  *MENUx);
static void GG_MENU_Close(GG_MENUPAGE_TypeDef  *MENUx);
static void GG_MENU_Hide(GG_MENUPAGE_TypeDef  *MENUx);

static void GG_MENU_KeyUpdate(GG_MENUPAGE_TypeDef  *MENUx);
//�û��޸���ӻص��ʹ�����
static void GG_MenuDefShowCallback(void);//�򿪽���ӿ�   GG@
static void GG_MenuDefCloseCallback(void);//�رս���ӿ�
static void GG_MenuDefHideCallback(void);//���ؽ��棬�λ������ݲɼ������ݴ���ȹ���
static void GG_MenuSignChangeCallback(void);//�ź�ת�������ӽ�������źŲ������������ת��

static void Menu1Action(void);
static void Menu2Action(void);
static void Menu3Action(void);

typedef enum
{
  KEY_DOWN = 1,
  KEY_UP,
  RUN_THREAD = 103//������̨��Ч��+100������
} GG_KeySignSta;//��ǰ�������ź��¼� GG@

typedef struct
{
    uint8_t sign;//�ź�
    void (*action)(void);//�ź���Ϊ
    
} GG_MenuBobyHandle;

static const GG_MenuBobyHandle s_menuBobyHandleMap[] = 
{
    {NULL,NULL},
    {KEY_DOWN,Menu1Action},
    {KEY_UP,Menu2Action},
    {RUN_THREAD,Menu3Action},

};

static void GG_MenuDefShowCallback(void)//����Ĭ�ϴ���
{

    
}

static void GG_MenuDefCloseCallback(void)//����Ĭ�ϴ���
{

    
}

static void GG_MenuDefHideCallback(void)
{


}

static void GG_MenuSignChangeCallback(void)
{
    if(g_MENU_MainSta.KeyLastSignSta > 100)//��̨�ź�
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



