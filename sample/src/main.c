#include <genesis.h>
#include "advsys.h"
#include "main.h"

//-----------------------------------------------------------------------------
// Declaration
//-----------------------------------------------------------------------------
int main();


//*****************************************************************************
// Program
//*****************************************************************************

int main()
{
    init_adv_system();
    start_adv_system(0,TILE_USERINDEX);
    while(1)
    {
        update_adv_system();
        VDP_waitVSync();
    }
    return(0);
}