#ifndef ADVSYS_H_INCLUDED
#define ADVSYS_H_INCLUDED
#include <genesis.h>


extern const TileSet sjis_font;

//*****************************************************************************
// Defeine
//*****************************************************************************

// System Define
#define ADV_SYS_NULL (MAX_U16)
#define ADV_SYS_WAIT_TYPE_STR (0b0001)
#define ADV_SYS_WAIT_TYPE_DIR (0b0010)

#define UP      (BUTTON_UP)
#define DOWN    (BUTTON_DOWN)
#define LEFT    (BUTTON_LEFT)
#define RIGHT   (BUTTON_RIGHT)
#define SHOT_A  (BUTTON_A)
#define SHOT_B  (BUTTON_B)
#define SHOT_C  (BUTTON_C)
#define START   (BUTTON_START)
#define SHOT_X  (BUTTON_X)
#define SHOT_Y  (BUTTON_Y)
#define SHOT_Z  (BUTTON_Z)
#define MODE    (BUTTON_MODE)

#define ADV_MSG_SPD (1)
#define ADV_VRAM_ADR_GRAPH (144)
#define ADV_MESSAGE_Y (23)
#define ADV_MESSAGE_X (2)

//*****************************************************************************
// Struct
//*****************************************************************************

// コマンド構造体
typedef struct{
    u16 cmd;
    u16 val1;
    u16 val2;
    u16 val3;
    u16 val4;
}ADV_CMD;

// アドベンチャーシステムワーク
typedef struct{
    u16 sceneIdx;
    u16 cmdIdx;
    u8 startFlg;
    u8 inputWaitType;
    u8 cmdIdxAddFlg;
    u16 vramIdx;
    u16 vramLastIdx;
    u16 currentImgIdx;
}ADV_WORK;

// JoyPad データワーク
typedef struct{
    u16 joytype;
    u16 porttype;
    u16 old;
    u16 now;
    u16 on;
}ADV_JOY_WORK;

// メッセージ表示データワーク
typedef struct{
    const char *str;
    u16 msglength;
    u16 msgpointer;
    u16 msgcount;
    u16 startflg;
    u16 endflg;
}ADV_MSG_WORK;

//*****************************************************************************
// Extern
//*****************************************************************************

extern void init_adv_system();
extern void start_adv_system(u16 sceneIdx, u16 vramIdx);
extern u16 update_adv_system();

#endif // ADVSYS_H_INCLUDED
