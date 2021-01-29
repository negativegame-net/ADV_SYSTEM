#include "advsys.h"
#include "advsys_data.h"
#include "draw_sjis.h"

//-----------------------------------------------------------------------------
// Declaration
//-----------------------------------------------------------------------------

void setMessageAdv(const char *str);
void updateMessageAdv();
void drawMessageAdv(const char *str);
void hideMessageAdv();
void updateJoyAdv();
void drawAdvDebug();

static ADV_WORK         adv_work_data;
static ADV_JOY_WORK    AdvJoyData;
static ADV_MSG_WORK    AdvMsgData;

//*****************************************************************************
// Program
//*****************************************************************************

// *** アドベンチャーシステム初期化
void init_adv_system()
{
    adv_work_data.sceneIdx = adv_work_data.cmdIdx = adv_work_data.inputWaitType
        = adv_work_data.vramIdx = adv_work_data.vramLastIdx = 0;
    adv_work_data.currentImgIdx = ADV_SYS_NULL;
    adv_work_data.startFlg = FALSE;

    AdvJoyData.old = AdvJoyData.now = AdvJoyData.on = 0x0000;
    AdvMsgData.startflg = AdvMsgData.endflg = 0;
    AdvMsgData.msgcount = AdvMsgData.msglength = AdvMsgData.msgpointer = 0x0000;
}

// *** アドベンチャーシステム開始
// sceneIdx:開始するシーンのインデックス
// vramIdx:これで指定された番地以降のVRAMを利用する
void start_adv_system(u16 sceneIdx, u16 vramIdx)
{
    adv_work_data.sceneIdx = sceneIdx;
    adv_work_data.cmdIdx = adv_scene_idx_data[sceneIdx];
    adv_work_data.vramIdx = vramIdx;
    if(vramIdx < TILE_USERINDEX) adv_work_data.vramIdx = TILE_USERINDEX;
    adv_work_data.startFlg = TRUE;
}

// *** アドベンチャーシステム更新
// （毎フレーム呼び出す必要あり）
u16 update_adv_system()
{
    u16 returnVal = ADV_SYS_NULL;

    updateJoyAdv();
    updateMessageAdv();
    //drawAdvDebug();
    //joyTestAdv();

    if(!adv_work_data.startFlg)return returnVal;

    // 入力待ち状態の場合
    if(adv_work_data.inputWaitType != 0)
    {

        if(AdvMsgData.endflg)
        {
            if(adv_work_data.inputWaitType == ADV_SYS_WAIT_TYPE_STR
               &&AdvJoyData.on & SHOT_A){
                adv_work_data.inputWaitType = 0;
                adv_work_data.cmdIdx++;
            }

            if(adv_work_data.inputWaitType == ADV_SYS_WAIT_TYPE_DIR)
            {
                if((AdvJoyData.on & (UP|DOWN|LEFT|RIGHT))>0){
                    adv_work_data.inputWaitType = 0;
                    adv_work_data.cmdIdx++;
                }
            }
        }
    }

    // コマンドの実行
    while(adv_work_data.startFlg && adv_work_data.inputWaitType == 0)
    {
        //drawAdvDebug();
        // デフォルトでは1コマンド解析後にコマンドデータのインデックスをインクリメントする
        // ジャンプコマンド後などでは無効にする
        adv_work_data.cmdIdxAddFlg = TRUE;

        ADV_CMD *data = &adv_cmd_data[adv_work_data.cmdIdx];

        u8 isTrue = FALSE;

        switch (data->cmd)
        {
            case ADV_CMD_STR:   // 文字表示
                setMessageAdv(adv_str_data[data->val1]);
                adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_STR;
                adv_work_data.cmdIdxAddFlg = FALSE;
                break;

            case ADV_CMD_IPTWAIT:   // コマンド入力待ち
                setMessageAdv(adv_str_data[data->val1]);
                adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_DIR;
                adv_work_data.cmdIdxAddFlg = FALSE;
                break;

            case ADV_CMD_IPTJMP:    // コマンド入力後ジャンプ
                if(AdvMsgData.endflg)
                {
                    if(AdvJoyData.on & UP)
                    {
                        if(data->val1 != ADV_SYS_NULL){
                            adv_work_data.cmdIdx = adv_scene_idx_data[data->val1];
                        }else{
                            adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_DIR;
                        }
                    }
                    if(AdvJoyData.on & LEFT)
                    {
                        if(data->val2 != ADV_SYS_NULL){
                            adv_work_data.cmdIdx = adv_scene_idx_data[data->val2];
                        }else{
                            adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_DIR;
                        }
                    }
                    if(AdvJoyData.on & DOWN)
                    {
                        if(data->val3 != ADV_SYS_NULL){
                            adv_work_data.cmdIdx = adv_scene_idx_data[data->val3];
                        }else{
                            adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_DIR;
                        }
                    }
                    if(AdvJoyData.on & RIGHT)
                    {
                        if(data->val4 != ADV_SYS_NULL){
                            adv_work_data.cmdIdx = adv_scene_idx_data[data->val4];
                        }else{
                            adv_work_data.inputWaitType = ADV_SYS_WAIT_TYPE_DIR;
                        }
                    }

                }
                adv_work_data.cmdIdxAddFlg = FALSE;
                break;

            case ADV_CMD_IF:    // 条件分岐
                isTrue = FALSE;
                switch(data->val2)
                {
                    case ADV_OPR_EQUAL:
                        if(adv_val_data[data->val1] == data->val3) isTrue = TRUE;
                        break;
                    case ADV_OPR_MORE_THAN:
                        if(adv_val_data[data->val1] > data->val3) isTrue = TRUE;
                        break;
                    case ADV_OPR_LESS_THAN:
                        if(adv_val_data[data->val1] < data->val3) isTrue = TRUE;
                        break;
                    case ADV_OPR_E_MORE_THAN:
                        if(adv_val_data[data->val1] >= data->val3) isTrue = TRUE;
                        break;
                    case ADV_OPR_E_LESS_THAN:
                        if(adv_val_data[data->val1] <= data->val3) isTrue = TRUE;
                        break;
                    case ADV_OPR_N_EQUAL:
                        if(adv_val_data[data->val1] != data->val3) isTrue = TRUE;
                        break;
                }
                // 条件を満たした場合変数4のシーンにジャンプ
                if(isTrue == TRUE){
                    adv_work_data.cmdIdx = adv_scene_idx_data[data->val4];
                    adv_work_data.cmdIdxAddFlg = FALSE;
                }
                break;

            case ADV_CMD_IMG:   // グラフィック表示
                if(data->val1 != adv_work_data.currentImgIdx){
                    // 現在表示されているイメージとコマンドで指定されたイメージが違う場合のみ更新
                    VDP_clearPlane(BG_A,0);
                    VDP_drawImageEx(BG_A, adv_img_data[data->val1],TILE_ATTR_FULL(PAL1,0,0,0,adv_work_data.vramIdx + ADV_VRAM_ADR_GRAPH),0,0,0,1);
                    VDP_setPalette(1, adv_img_data[data->val1]->palette->data);
                    adv_work_data.currentImgIdx = data->val1;
                }
                break;

            case ADV_CMD_SETVAL:    // 変数設定
                adv_val_data[data->val1] = data->val2;
                break;

            case ADV_CMD_ADDVAL:    // 変数加算
                adv_val_data[data->val1] += data->val2;
                break;

            case ADV_CMD_SUBVAL:    // 変数減算
                adv_val_data[data->val1] -= data->val2;
                break;

            case ADV_CMD_JMP:   // ジャンプ
                adv_work_data.cmdIdx = adv_scene_idx_data[data->val1];
                adv_work_data.cmdIdxAddFlg = FALSE;
                break;

            case ADV_CMD_END:   // 終了
                adv_work_data.startFlg = FALSE;
                adv_work_data.cmdIdxAddFlg = FALSE;
                returnVal = data->val1;
                break;
        }

        if(adv_work_data.cmdIdxAddFlg == TRUE) adv_work_data.cmdIdx++;
    }

    return returnVal;
}


void updateJoyAdv()
{
    AdvJoyData.old  = AdvJoyData.now;
    AdvJoyData.now  = JOY_readJoypad(JOY_ALL);

    // trg
    AdvJoyData.on = AdvJoyData.now ^ AdvJoyData.old;
    AdvJoyData.on &= AdvJoyData.now;
}

// ***メッセージ一文字ずつ描画するためのセット
void setMessageAdv(const char *str)
{
    hideMessageAdv();
    AdvMsgData.str = str;
    AdvMsgData.msglength = strlen(str);
    AdvMsgData.msgcount = AdvMsgData.msgpointer = 0;
    AdvMsgData.endflg = 0;
    AdvMsgData.startflg = 1;
}

// *** Mssage Update
void updateMessageAdv()
{
    if(AdvMsgData.startflg & (~AdvMsgData.endflg))
    {

        if(AdvMsgData.msgcount == ADV_MSG_SPD)
        {

            char buff[73];
            strncpy(buff, AdvMsgData.str, AdvMsgData.msgpointer);
            buff[72]='\0';

            drawMessageAdv(buff);

            if( AdvMsgData.msgpointer < AdvMsgData.msglength ){
                AdvMsgData.msgpointer += 2;
            }else{
                AdvMsgData.endflg = 1;
            }
            AdvMsgData.msgcount = 0;
        }else{
            AdvMsgData.msgcount ++;
        }
    }
}

void hideMessageAdv()
{

    draw_sjis_text(BG_A, "　　　　　　　　　　　　　　　　　　", TILE_ATTR_FULL(PAL0, 0, 0, 0, adv_work_data.vramIdx), ADV_MESSAGE_X, ADV_MESSAGE_Y, 0);
    draw_sjis_text(BG_A, "　　　　　　　　　　　　　　　　　　", TILE_ATTR_FULL(PAL0, 0, 0, 0, 72+adv_work_data.vramIdx), ADV_MESSAGE_X, ADV_MESSAGE_Y+2, 0);
}

// ***メッセージ領域に文字列表示
void drawMessageAdv(const char *str)
{
    char buff[37];
    strncpy(buff, str, 36);
    buff[36]='\0';

    draw_sjis_text(BG_A, buff, TILE_ATTR_FULL(PAL0, 0, 0, 0, adv_work_data.vramIdx), ADV_MESSAGE_X, ADV_MESSAGE_Y, 0);

    strncpy(buff, str+36, 72);
    buff[36]='\0';
    draw_sjis_text(BG_A, buff, TILE_ATTR_FULL(PAL0, 0, 0, 0, 72+adv_work_data.vramIdx), ADV_MESSAGE_X, ADV_MESSAGE_Y+2, 0);
}

void drawAdvDebug()
{
    static char *strNum[]=
    {
        "0"
        ,"1"
        ,"2"
        ,"3"
        ,"4"
        ,"5"
        ,"6"
        ,"7"
        ,"8"
        ,"9"
    };
    VDP_drawText("CommandIndex:",0,0);
    VDP_drawText(strNum[(adv_work_data.cmdIdx%1000)/100],1,1);
    VDP_drawText(strNum[(adv_work_data.cmdIdx%100)/10],2,1);
    VDP_drawText(strNum[(adv_work_data.cmdIdx%10)],3,1);

    VDP_drawText("CommandNumber:",0,2);
    VDP_drawText(strNum[(adv_cmd_data[adv_work_data.cmdIdx].cmd%1000)/100],1,3);
    VDP_drawText(strNum[(adv_cmd_data[adv_work_data.cmdIdx].cmd%100)/10],2,3);
    VDP_drawText(strNum[(adv_cmd_data[adv_work_data.cmdIdx].cmd%10)],3,3);

    VDP_drawText("inputWaitType:",0,4);
    VDP_drawText(strNum[adv_work_data.inputWaitType%10],1,5);

    VDP_drawText("AdvMsgData.endflg:",0,6);
    VDP_drawText(strNum[AdvMsgData.endflg],1,7);

    VDP_drawText("AdvMsgData.startflg:",0,8);
    VDP_drawText(strNum[AdvMsgData.startflg],1,9);


    VDP_drawText("adv_work_data.startflg:",0,10);
    VDP_drawText(strNum[adv_work_data.startFlg],1,11);

    VDP_drawText("MsgString:",0,12);
    //VDP_drawText(AdvMsgData.str,1,13);
    draw_sjis_text(BG_B, AdvMsgData.str, TILE_ATTR_FULL(PAL0, 0, 0, 0, ADV_VRAM_ADR_GRAPH), 0, 13, 0);

    VDP_drawText("vram:",0,15);
    VDP_drawText(strNum[(adv_work_data.vramIdx%1000)/100],1,16);
    VDP_drawText(strNum[(adv_work_data.vramIdx%100)/10],2,16);
    VDP_drawText(strNum[(adv_work_data.vramIdx%10)],3,16);

}

// *** for Input debug
void joyTestAdv()
{
    VDP_drawText("  UP:",0,0);
    if(AdvJoyData.now & UP)
    {
        VDP_drawText("Enable",6,0);
    }else
    {
       VDP_drawText("      ",6,0);
    }

    if(AdvJoyData.on & UP)
    {
        VDP_drawText("on",13,0);
    }else
    {
       VDP_drawText("  ",13,0);
    }

    VDP_drawText("DOWN:",0,1);
    if(AdvJoyData.now & DOWN)
    {
        VDP_drawText("Enable",6,1);
    }else
    {
       VDP_drawText("      ",6,1);
    }

    if(AdvJoyData.on & DOWN)
    {
        VDP_drawText("on",13,1);
    }else
    {
       VDP_drawText("  ",13,1);
    }

    VDP_drawText("LEFT:",0,2);
    if(AdvJoyData.now & LEFT)
    {
        VDP_drawText("Enable",6,2);
    }else
    {
       VDP_drawText("      ",6,2);
    }

    if(AdvJoyData.on & LEFT)
    {
        VDP_drawText("on",13,2);
    }else
    {
       VDP_drawText("  ",13,2);
    }

    VDP_drawText("RIGH:",0,3);
    if(AdvJoyData.now & RIGHT)
    {
        VDP_drawText("Enable",6,3);
    }else
    {
       VDP_drawText("      ",6,3);
    }

    if(AdvJoyData.on & RIGHT)
    {
        VDP_drawText("on",13,3);
    }else
    {
       VDP_drawText("  ",13,3);
    }

    VDP_drawText("   A:",0,4);
    if(AdvJoyData.now & SHOT_A)
    {
        VDP_drawText("Enable",6,4);
    }else
    {
       VDP_drawText("      ",6,4);
    }

    if(AdvJoyData.on & SHOT_A)
    {
        VDP_drawText("on",13,4);
    }else
    {
       VDP_drawText("  ",13,4);
    }

}
