

#include <stdio.h>
#include "RH_common.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_font.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    
    GUI_Init();
    GUI_rect_raw( 30, 30, 50, 50 );
    GUI_RefreashScreen();

    return 0;
}
