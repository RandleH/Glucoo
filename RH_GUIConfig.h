

#ifndef _RH_GUI_CONFIG_H
#define _RH_GUI_CONFIG_H

#define GUI_ASSERT                  1   // 0=Disable   1=Enable

#define GUI_DEMO                    1   // 0=Disable   1=Enable

#define GUI_DIALOG_DISPLAY          1   // 0=Disable   1=Enable

#define GUI_ICON_DISPLAY            1   // 0=Disable   1=Enable

#define GUI_TRACE_WATCH_DISPLAY     1   // 0=Disable   1=Enable

#define GUI_ANIMATION_DISPLAY       1   // 0=Disable   1=Enable

#define GUI_FONT_EXTENTION          1   // 0=Disable   1=Enable

#define GUI_TEST_EXTENTION          1   // 0=Disable   1=Enable

#define GUI_Y_WIDTH               480
#define GUI_X_WIDTH               800
#define GUI_PAGEs                 16
     
#define GUI_1BitPerPixel          (1)    //DO NOT MODIFY
#define GUI_8BitPerPixel          (1<<3) //DO NOT MODIFY
#define GUI_16BitPerPixel         (1<<4) //DO NOT MODIFY
#define GUI_32BitPerPixel         (1<<5) //DO NOT MODIFY
#define GUI_BPP                   GUI_16BitPerPixel            // < Choose one of above >


#define GUI_1Bit                  (0)    //DO NOT MODIFY
#define GUI_RGB256                (1<<0) //DO NOT MODIFY
#define GUI_RGB565                (1<<1) //DO NOT MODIFY
#define GUI_RGB888                (1<<2) //DO NOT MODIFY
#define GUI_COLOR_TYPE            GUI_RGB565                   // < Choose one of above >


#define GUI_OLED_PAGE_COLUMN      (0)    //DO NOT MODIFY
#define GUI_SINGLE_PIXEL          (1<<0) //DO NOT MODIFY
#define GUI_DISPLAY_MODE          GUI_SINGLE_PIXEL             // < Choose one of above >

#define GUI_EXTERNAL_GRAM         (0)    //DO NOT MODIFY
#define GUI_SOFTWARE_GRAM         (1)    //DO NOT MODIFY
#define GUI_GRAM_STORAGE_MODE     GUI_EXTERNAL_GRAM            // < Choose one of above >

#if   (GUI_GRAM_TYPE == GUI_EXTERNAL_GRAM)
  #define GUI_GRAM_ATTRIBUTE_ADDRESS  (0)
  #define GUI_GRAM_ATTRIBUTE_SECTION  (1)
  #define GUI_GRAM_STORAGE_TYPE     GUI_GRAM_ATTRIBUTE_ADDRESS   // < Choose one of above >

  #if   (GUI_GRAM_STORAGE_TYPE == GUI_GRAM_ATTRIBUTE_SECTION)
    #define GUI_GRAM_SECTION_NAME       "m_ncache_start"   // This should be a string.
  #elif (GUI_GRAM_STORAGE_TYPE == GUI_GRAM_ATTRIBUTE_ADDRESS)
    #define GUI_GRAM_ABUSOLUTE_ADDRESS  0x81C00000         // This should be a number.
  #endif
#endif

//Reserve
#define GUI_DEBUG_ENABLE



#endif


