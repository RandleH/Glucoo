


#include "fsl_iomuxc.h"
#include "fsl_gpio.h"  
#include "fsl_elcdif.h" 
#include "fsl_clock.h"
#include "fsl_pxp.h"

    
#include "pad_config.h"  
#include "./lcd/bsp_lcd.h" 


LCD_TypeDef cur_lcd = INCH_5;
/* 帧中断标志 */
volatile bool s_frameDone = false;

/* 帧数计数器，使能帧中断才有效 */
__IO uint32_t s_frame_count = 0;

/* ÏÔ´æ */
AT_NONCACHEABLE_SECTION_ALIGN( pixel_t s_psBufferLcd[1][LCD_PIXEL_HEIGHT][LCD_PIXEL_WIDTH], FRAME_BUFFER_ALIGN);

static pixel_t CurrentTextColor   = CL_RED;
static pixel_t CurrentBackColor   = CL_BLACK;

static uint32_t CurrentFrameBuffer = (uint32_t)s_psBufferLcd[0];

#define LCD_PAD_CONFIG_DATA            ( SRE_1_FAST_SLEW_RATE      | \
                                         DSE_6_R0_6                | \
                                         SPEED_3_MAX_200MHz        | \
                                         ODE_0_OPEN_DRAIN_DISABLED | \
                                         PKE_1_PULL_KEEPER_ENABLED | \
                                         PUE_0_KEEPER_SELECTED     | \
                                         PUS_0_100K_OHM_PULL_DOWN  | \
                                         HYS_0_HYSTERESIS_DISABLED )   
/* 转换速率: 转换速率快
 * 驱动强度: R0/6 
 * 带宽配置: max(200MHz)
 * 开漏配置: 关闭 
 * 拉/保持器配置: 使能
 * 拉/保持器选择: 保持器
 * 上拉/下拉选择: 100K欧姆下拉(选择了保持器此配置无效)
 * 滞回器配置: 禁止 */
        

static void LCD_IOMUXC_MUX_Config ( void );
static void LCD_IOMUXC_PAD_Config ( void );
static void LCD_ELCDIF_Config     ( void );


static void LCD_IOMUXC_MUX_Config( void ){
    /* 所有引脚均不开启SION功能 */
    /* 时序控制信号线          */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LCD_CLK, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LCD_ENABLE, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LCD_HSYNC, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LCD_VSYNC, 0U);
  
    /* RGB565数据信号线，
     DATA[ 0: 4] B3~B7
     DATA[ 5:10] G2~G7
     DATA[11:15] R3~R7 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LCD_DATA00, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LCD_DATA01, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_LCD_DATA02, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_LCD_DATA03, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LCD_DATA04, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LCD_DATA05, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_LCD_DATA06, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_LCD_DATA07, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_LCD_DATA08, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_LCD_DATA09, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_LCD_DATA10, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_LCD_DATA11, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LCD_DATA12, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LCD_DATA13, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LCD_DATA14, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LCD_DATA15, 0U); 

    /* 若使用24位数据信号线需要初始化其余数据信号线 */
#if LCD_BUS_24_BIT
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_LCD_DATA16, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_LCD_DATA17, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_LCD_DATA18, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_LCD_DATA19, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_LCD_DATA20, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_LCD_DATA21, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_LCD_DATA22, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_LCD_DATA23, 0U);                                    
#endif 
        
    /* LCD_BL背光控制信号线 */
    IOMUXC_SetPinMux(LCD_BL_IOMUXC, 0U); 
}

static void LCD_IOMUXC_PAD_Config( void ){  
    /* 所有引脚均使用同样的PAD配置 */
    /* 时序控制信号线            */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_00_LCD_CLK   , LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_LCD_ENABLE, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_02_LCD_HSYNC , LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_LCD_VSYNC , LCD_PAD_CONFIG_DATA); 

    /* RGB565数据信号线，
     DATA[ 0: 4] B3~B7
     DATA[ 5:10] G2~G7
     DATA[11:15] R3~R7 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_04_LCD_DATA00, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_05_LCD_DATA01, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_06_LCD_DATA02, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_07_LCD_DATA03, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LCD_DATA04, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LCD_DATA05, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_10_LCD_DATA06, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_11_LCD_DATA07, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_12_LCD_DATA08, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_13_LCD_DATA09, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_14_LCD_DATA10, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_15_LCD_DATA11, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_00_LCD_DATA12, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_LCD_DATA13, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_LCD_DATA14, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_03_LCD_DATA15, LCD_PAD_CONFIG_DATA); 
        
    /* 若使用24位数据信号线需要初始化其余数据信号线 */
#if LCD_BUS_24_BIT
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_04_LCD_DATA16, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_LCD_DATA17, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_LCD_DATA18, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_LCD_DATA19, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_08_LCD_DATA20, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_LCD_DATA21, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_LCD_DATA22, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_LCD_DATA23, LCD_PAD_CONFIG_DATA);                                    
#endif     
    /* LCD_BL背光控制信号线 */
    IOMUXC_SetPinConfig(LCD_BL_IOMUXC, LCD_PAD_CONFIG_DATA);
}

static void LCD_ELCDIF_Config( void ){    
    const elcdif_rgb_mode_config_t config = {
        .panelWidth  = LCD_PIXEL_WIDTH,
        .panelHeight = LCD_PIXEL_HEIGHT,
        .hsw = LCD_HSW,
        .hfp = LCD_HFP,
        .hbp = LCD_HBP,
        .vsw = LCD_VSW,
        .vfp = LCD_VFP,
        .vbp = LCD_VBP,
        .polarityFlags =  LCD_POLARITY_FLAGS        ,                                                    
        .bufferAddr    = (uint32_t)s_psBufferLcd[0] ,
        .pixelFormat   = ELCDIF_PIXEL_FORMAT        ,
        .dataBus       = LCD_DATA_BUS_WIDTH         ,
    };
 
    ELCDIF_RgbModeInit  ( LCDIF , &config);
    ELCDIF_RgbModeStart ( LCDIF );
}

void LCD_InitClock( void ){
    /*
     * 要把帧率设置成60Hz，所以像素时钟频率为:
     * 水平像素时钟个数：(LCD_IMG_WIDTH + LCD_HSW + LCD_HFP + LCD_HBP ) 
     * 垂直行数：(LCD_IMG_HEIGHT + LCD_VSW + LCD_VFP + LCD_VBP)
     * 
     * 像素时钟频率：(800 + 1 + 22 + 46) * (480 + 1 + 22 + 23) * 60 = 27.4M.
     * 本例子设置 LCDIF 像素时钟频率为 27M.
     *   LCD的帧率以实测的为准。
     */

    /*
     * 初始化 Video PLL，即PLL5
     * Video PLL 输出频率为 
     * OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 108MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 36, .postDivider = 8, .numerator = 0, .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */


    /* 选择为vedio PLL，即PLL5 */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    /* 设置预分频 */  
    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 1);

    /* 设置分频 */ 
    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

void LCD_BackLight_ON( void ){    
    gpio_pin_config_t config = {
      kGPIO_DigitalOutput, 
      1,
      kGPIO_NoIntmode
    };

    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}


void LCD_Init(bool enableInterrupt){
#if LCD_RGB_888    

    *((uint32_t *)0x41044100) = 0x0000000f;
    *((uint32_t *)0x41044104) = 0x0000000f;
#endif
    
    LCD_IOMUXC_MUX_Config();
    LCD_IOMUXC_PAD_Config();
    LCD_InitClock();
    LCD_ELCDIF_Config();
    LCD_BackLight_ON();
  
    if(enableInterrupt){
        LCD_InterruptConfig();
    }
}

void LCD_InterruptConfig(void){
    EnableIRQ(LCDIF_IRQn);
    ELCDIF_EnableInterrupts(LCDIF, kELCDIF_CurFrameDoneInterruptEnable);
}

void LCDIF_IRQHandler(void){
    uint32_t intStatus = ELCDIF_GetInterruptStatus(LCDIF);

    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);

   if (intStatus & kELCDIF_CurFrameDone ){
        /* 当前帧处理完成标志 */
        s_frameDone = true;
        /* 帧计数器 */
        s_frame_count++;
    }

#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}



/***************************ÏÔÊ¾Í¼ÐÎÏà¹Ø******************************/
/**
  * @brief Ñ¡Ôñµ±Ç°Òª²Ù×÷µÄÏÔ´æÇøÓò
  * @param  index: 0»ò1
  * @retval None
  */
void LCD_SetFrameBuffer(uint8_t index){
  CurrentFrameBuffer = (uint32_t)s_psBufferLcd[index];
}


void LCD_SetDisplayBuffer(uint8_t index){

  ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)s_psBufferLcd[index]);

}

/**
  * @brief Ê¹ÓÃµ±Ç°ÑÕÉ«ÔÚÖ¸¶¨µÄÎ»ÖÃ»æÖÆÒ»¸öÏñËØµã
  * @param  Xpos: x×ø±ê
  * @param  Ypos: y×ø±ê
  * @note ¿ÉÊ¹ÓÃLCD_SetBackColor¡¢LCD_SetTextColor¡¢LCD_SetColorsº¯ÊýÉèÖÃÑÕÉ«
  * @retval None
  */
void PutPixel(uint16_t Xpos, uint16_t Ypos){   
    if ( ( Xpos < LCD_PIXEL_WIDTH ) && ( Ypos < LCD_PIXEL_HEIGHT ) ){
        *(pixel_t *)(CurrentFrameBuffer + LCD_BPP*(Xpos + (LCD_PIXEL_WIDTH*Ypos))) = CurrentTextColor;
    }
}

/**
  * @brief  ÒÔµ±Ç°±³¾°ÑÕÉ«Çå³ýÕû¸öÆÁÄ»
  * @param  ÎÞ
  * @note ¿ÉÊ¹ÓÃLCD_SetBackColor¡¢LCD_SetTextColor¡¢LCD_SetColorsº¯ÊýÉèÖÃÑÕÉ«
  * @retval ÎÞ
  */
void LCD_Clear(uint32_t Color){
    /* Çå³ý»º³åÇøÄÚÈÝ */
    uint16_t page, column;  
  
    /* Ö¸Ïò¾ØÐÎµÚÒ»¸öÏñËØµãµÄÏÔ´æÎ»ÖÃ */
    pixel_t *pRectImage = (pixel_t*)CurrentFrameBuffer ;
  
    /* ±éÀúÃ¿Ò»ÐÐ */
    for ( page = 0; page < LCD_PIXEL_HEIGHT; page++ ){    
        /* ±éÀúÃ¿Ò»ÁÐ */
        for ( column = 0; column < LCD_PIXEL_WIDTH; column++ ){    
          *pRectImage = Color;
          
          /* Ö¸ÏòÏÂÒ»¸öÏñËØµãµÄÏÔ´æÎ»ÖÃ */
          pRectImage++;
        }      
    }
}



/**
 * @brief  ÔÚÒº¾§ÆÁÉÏÊ¹ÓÃ Bresenham Ëã·¨»­Ïß¶Î£¨»ùÓÚÁ½µã£© 
 * @param  Xpos1 £ºÏß¶ÎµÄÒ»¸ö¶ËµãX×ø±ê
 * @param  Ypos1 £ºÏß¶ÎµÄÒ»¸ö¶ËµãY×ø±ê
 * @param  Xpos2 £ºÏß¶ÎµÄÁíÒ»¸ö¶ËµãX×ø±ê
 * @param  Ypos2 £ºÏß¶ÎµÄÁíÒ»¸ö¶ËµãY×ø±ê
 * @note ¿ÉÊ¹ÓÃLCD_SetBackColor¡¢LCD_SetTextColor¡¢LCD_SetColorsº¯ÊýÉèÖÃÑÕÉ«
 * @retval ÎÞ
 */
void LCD_DrawUniLine ( uint16_t Xpos1, uint16_t Ypos1, uint16_t Xpos2, uint16_t Ypos2 )
{
    uint16_t us; 
    uint16_t usX_Current, usY_Current;
    
    int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
    int32_t lIncrease_X, lIncrease_Y;     
    
    
    lDelta_X = Xpos2 - Xpos1; //¼ÆËã×ø±êÔöÁ¿ 
    lDelta_Y = Ypos2 - Ypos1; 
    
    usX_Current = Xpos1; 
    usY_Current = Ypos1; 
    
    
    if ( lDelta_X > 0 ) 
        lIncrease_X = 1; //ÉèÖÃµ¥²½·½Ïò 
    
    else if ( lDelta_X == 0 ) 
        lIncrease_X = 0;//´¹Ö±Ïß 
    
    else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

    
    if ( lDelta_Y > 0 )
        lIncrease_Y = 1; 
    
    else if ( lDelta_Y == 0 )
        lIncrease_Y = 0;//Ë®Æ½Ïß 
    
    else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

    
    if (  lDelta_X > lDelta_Y )
        lDistance = lDelta_X; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá 
    
    else 
        lDistance = lDelta_Y; 

    
    for ( us = 0; us <= lDistance + 1; us ++ )//»­ÏßÊä³ö 
    {  
        PutPixel ( usX_Current, usY_Current );//»­µã 
        
        lError_X += lDelta_X ; 
        lError_Y += lDelta_Y ; 
        
        if ( lError_X > lDistance ) 
        { 
            lError_X -= lDistance; 
            usX_Current += lIncrease_X; 
        }  
        
        if ( lError_Y > lDistance ) 
        { 
            lError_Y -= lDistance; 
            usY_Current += lIncrease_Y; 
        } 
        
    }      
    
}   



