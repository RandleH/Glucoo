

#ifndef _RH_GUI_CONFIG_H
#define _RH_GUI_CONFIG_H

#define GUI_ASSERT           1   // 0=Disable   1=Enable

#define GUI_DEMO             1   // 0=Disable   1=Enable

#define GUI_Y_WIDTH          128
#define GUI_X_WIDTH          128
#define GUI_PAGEs            16

#define GUI_1BitPerPixel     (1)    //DO NOT MODIFY
#define GUI_8BitPerPixel     (1<<3) //DO NOT MODIFY
#define GUI_16BitPerPixel    (1<<4) //DO NOT MODIFY
#define GUI_32BitPerPixel    (1<<5) //DO NOT MODIFY
#define GUI_BPP              GUI_16BitPerPixel  // Choose one of above


#define GUI_1Bit             (0)    //DO NOT MODIFY
#define GUI_RGB256           (1<<0) //DO NOT MODIFY
#define GUI_RGB565           (1<<1) //DO NOT MODIFY
#define GUI_RGB888           (1<<2) //DO NOT MODIFY
#define GUI_COLOR_TYPE       GUI_RGB565  // Choose one of above


#define GUI_OLED_PAGE_COLUMN (0)
#define GUI_SINGLE_PIXEL     (1<<0)
#define GUI_DISPLAY_MODE     GUI_SINGLE_PIXEL // Choose one of above

#define GUI_ENABLE_FONT_EXTENTION      0 // 0=Disable   1=Enable

#define GUI_GRAM_STORAGE_MODE            // 0=Internal  1=External 

//Reserve
#define GUI_DEBUG_ENABLE



#endif


