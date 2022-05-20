# Glucoo 

Graph Library for embedded software system. 

<p align="center">
<img src="https://raw.githubusercontent.com/RandleH/Glucoo/master/img/glucoo_leopard.bmp" width="400" height="240" border="10">
 </p>






## Object, Window, Menu, UIbase







## Member Functions & Variables

| Name                      | Description                                    |
| ------------------------- | ---------------------------------------------- |
| **GUI**                   | **Include `GUI::` as the prefix term.**        |
| [.init](#GLU_GUI_00)      | Initialize the UI system                       |
| [.setPenSize](#GLU_GUI_01) | Given a pixelwise size of pen, set pen size    |
| [.setPenColor](#GLU_GUI_02)          | Given a RGB color, set it as the pen color     |
| [.autoDisplay](#GLU_GUI_03)          | Refresh the screen automatically               |
| [.refreashScreen](#GLU_GUI_04)       | Refresh the screen from the cache memory       |
| [.refreashEntireScreen](#GLU_GUI_05) | Refresh the screen and empity the cache memory |
| [.isAutoDisplay](#GLU_GUI_06)        | Return the configuration flag                  |
| [.isInternalGRAM](#GLU_GUI_07)       | Return the configuration flag                  |
| [.isCacheEmpty](#GLU_GUI_08)         | Return the configuration flag                  |
| **Graph**                 | **Include `GUI::` as the prefix term.**        |
| [.rect_raw]               |                                                |
| [.rect_edged]             |                                                |
| [.rect_fill]              |                                                |
| [.rect_round_fill]        |                                                |
| [.EX_rect_raw]            |                                                |
| [.EX_rect_edged]          |                                                |
| [.EX_rect_fill]           |                                                |
| [.circle_raw]             |                                                |
| [.circle_edged]           |                                                |
| [.circle_fill]            |                                                |
| [.circle_qrt1_fill]       |                                                |
| [.circle_qrt2_fill]       |                                                |
| [.circle_qrt3_fill]       |                                                |
| [.circle_qrt4_fill]       |                                                |
| [.circle_qrt1_raw]        |                                                |
| [.circle_qrt2_raw]        |                                                |
| [.circle_qrt3_raw]        |                                                |
| [.circle_qrt4_raw]        |                                                |
| [.capsule_raw]            |                                                |
| [.line_raw]               |                                                |
| [.quad_raw]               |                                                |
| [.screen_fill]            |                                                |
| [.yield_GRAM]             |                                                |




### `GUI::init` 
---
<div id="GLU_GUI_00"></div>

```c++
void GLU_GUI_init( void );
```







### `GUI::setPenSize` 

---
<div id="GLU_GUI_01"></div>

```c++
void GLU_GUI_setPenSize( size_t penSize );
```







### `GUI::setPenColor` 

---
<div id="GLU_GUI_02"></div>

```c++
void GLU_GUI_setPenColor( GLU_TYPE(Color)  penColor );
```







### `GUI::autoDisplay` 
---
<div id="GLU_GUI_03"></div>

```c++
void GLU_GUI_autoDisplay( bool cmd );
```







### `GUI::refreashScreen` 

---
<div id="GLU_GUI_04"></div>

```c++
void GLU_GUI_refreashScreen( void );
```







### `GUI::refreashEntireScreen` 

---
<div id="GLU_GUI_05"></div>

```c++
void GLU_GUI_refreashEntireScreen( void );
```









### `GUI::refreashEntireScreen` 

---
<div id="GLU_GUI_05"></div>

```c++
void GLU_GUI_refreashEntireScreen( void );
```







### `GUI::isAutoDisplay` 

---
<div id="GLU_GUI_06"></div>

```c++
bool GLU_GUI_isAutoDisplay( void );
```







### `GUI::isInternalGRAM` 

---
<div id="GLU_GUI_07"></div>

```c++
bool GLU_GUI_isInternalGRAM( void );
```









### `GUI::isCacheEmpty` 

---
<div id="GLU_GUI_08"></div>

```c++
bool GLU_GUI_isCacheEmpty( void );
```






