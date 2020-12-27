# Glucoo 
<p align="center">
<img src="https://raw.githubusercontent.com/RandleH/GUI-for-OLED-SSD1306/main/Img/OLED.png" width="270" height="225" border="10">
 </p>

---

## 项目文件结构
| Name | Description |
| ---- | --- |
| RH_GUI.c.           | 用于界面显示的源码文件   |
| RH_GUI.h            | 用于界面显示的声明头文件 |
| RH_GUI_Config.h     | 用于用户选配显示参数宏的配置头文件 |
| RH_GUI_ConfigCheck.h| 用于检查及确认相关配置信息的头文件 |
| RH_Utility.c        | 用于数学几何及内存管理相关工具的源码文件，后续将不以源码形式提供|
| RH_Utility.h        | 常用工具的对外声明头文件|

## 如何配置显示屏参数?
__【第一步】打开用户配置的头文件:  RH_GUIConfig.h__

__【第二步】配置宏参数__

+ 以下为用于配置项目信息的宏汇总

|        宏             |   是否缺省  |           相关描述            |
| --------------------- | ---------- | --------------------------    |
| GUI_ASSERT            |      √     | 置1启用断言功能，默认开启       |
| GUI_DEMO              |      √     | 置1启用示例程序，默认开启       |
| GUI_DIALOG_DISPLAY    |      √     | 置1启用对话框功能，默认关闭     |
| GUI_ICON_DISPLAY      |      √     | 置1启用图标功能，默认开启       |
| GUI_ANIMATION_DISPLAY |      √     | 置1启用动画插件功能，默认开启   |
| GUI_FONT_EXTENTION    |      √     | 置1可使用扩展字体，默认关闭     |
| GUI_TEST_EXTENTION    |      √     | 置1启用屏幕彩虹测试功能，默认关闭|
| GUI_Y_WIDTH           |      ×     | 屏幕高度，单位为像素点个数       |
| GUI_X_WIDTH           |      ×     | 屏幕长度，单位为像素点个数       |
| GUI_GRAM_STORAGE_MODE |      ×     | 显存存储方式                    |
| GUI_DISPLAY_MODE     |       ×     | 显示模式，1=像素点

+ 以下为选配宏，根据相关配置宏进行衍生


+ 以下为只读宏，请勿更改




## 数据结构定义
+ Pixel_t

+ uint
+ BYTE
+ WORD
+ DWORD

## 接口层(API)
| Function | Synopsis  |
| -------- | --------- |
| GUI_API_DrawArea  | void(\*)(uint x1,uint y1,uint x2,uint y2,const Pixel_t* pixData)  |
| GUI_API_DrawPixel | void(\*)(uint x,uint y,const Pixel_t pixData) |
| GUI_API_DelayMs   | void(\*)(unsigned long ms) |
|GUI_API_AssertParam|void(\*)(bool expression,const char* WHAT_IS_WRONG )|

## Target System 
__下列芯片被用于实验环境:__
+ STM32F103C8T6
+ STM32F407VET6
+ NXP.iMX.RT1052

Glucoo是一个可被移植的项目且不依赖于指定芯片特性或寄存器的项目，因此除上述芯片外，同样可适用于其他的嵌入式芯片。

## 基础显示功能
### 文本字符显示
|    Function    |    Description    |
| -------------- | ----------------- |
| void GUI_Axxxx |   |
| void GUI_Bxxxx |   |
| void GUI_Cxxxx |   |

另请参阅[字符显示]()


### 数字显示

另请参阅[数字显示]()

## 扩展显示功能

## Example and Demos
| Function | Description |
| ---- | --- |
| void GUI_DEMO_Axxxx |   |
| void GUI_DEMO_Bxxxx |   |
| void GUI_DEMO_Cxxxx |   |

## FreeRTOS 支持
暂不支持 :-(

## Purpose of this project

Fun  :-)

If you like it, send pizza,beer,cloth or dollar to RandleH@163.com .
