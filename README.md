# Glucoo 

Graph Library for embedded software system. 

<p align="center">
<img src="https://raw.githubusercontent.com/RandleH/Glucoo/master/img/glucoo_leopard.bmp" width="400" height="240" border="10">
 </p>






## Object, Window, Menu, UIbase







## Member Functions & Variables

| Name                                    | Description                                    |
| --------------------------------------- | ---------------------------------------------- |
| **GUI**                                 | **Include `GUI::` as the prefix term.**        |
| [.init](#GLU_GUI_00)                    | Initialize the UI system                       |
| [.set_penSize](#GLU_GUI_01)             | Given a pixelwise size of pen, set pen size    |
| [.set_penColor](#GLU_GUI_02)            | Given a RGB color, set it as the pen color     |
| **DEV**                                 | **Include `DEV::` as the prefix term.** |
| [.auto_refreash](#GLU_GUI_03)           | Refresh the screen automatically               |
| [.refreash_screen](#GLU_GUI_04)         | Refresh the screen from the cache memory       |
| [.refreash_full_screen](#GLU_GUI_05)    | Refresh the screen and empity the cache memory |
| [glu_dev_is_auto_refreash](#GLU_GUI_06) | Return the configuration flag                  |
| [glu_dev_is_refreash_done](#GLU_GUI_07) | Return the configuration flag                  |
| **Graph**                               | **Include `GUI::` as the prefix term.**        |
| [`glu_draw_rectangle`]()                | Given the two corners coordinate of its diagnal edge, draw a rectangular with width `1` |
| [`glu_draw_rectangle_edged`]()          | Given the two corners coordinate of its diagnal edge, draw a rectangular with width of pen size |
| [`glu_draw_rectangle_filled`]()         | Given the two corners coordinate of its diagnal edge, fill a rectangular area |
| [`glu_draw_rectangle_rounded`]()        | Given the two corners coordinate of its diagnal edge, draw a rounded rectangular |
| [.EX_rect_raw]                          | Use the `gluArea_t` type instead of coordinate |
| [.EX_rect_edged]                        | (same) |
| [.EX_rect_fill]                         | (same) |
| [`glu_draw_circle`]()                   | Given the radius and (`X` ,`Y`), draw a circle with width `1` |
| [`glu_draw_circle_edged`]()             | Given the radius and (`X` ,`Y`), draw a circle with width of pen size. |
| [`glu_draw_circle_fill`]()              | Given the radius and (`X` ,`Y`), fill a circle |
| [`glu_draw_circle_qrt1_fill`]()         | Given the radius and (`X` ,`Y`), fill a quarter circle at 1st quadrant |
| [`glu_draw_circle_qrt2_fill`]()         | Given the radius and (`X` ,`Y`), fill a quarter circle at 2nd quadrant |
| [`glu_draw_circle_qrt3_fill`]()         | Given the radius and (`X` ,`Y`), fill a quarter circle at 3rd quadrant |
| [`glu_draw_circle_qrt4_fill`]()         | Given the radius and (`X` ,`Y`), fill a quarter circle at 4th quadrant |
| [`glu_draw_circle_qrt1`]()              | (same) |
| [`glu_draw_circle_qrt2`]()              | (same) |
| [`glu_draw_circle_qrt3`]()              | (same) |
| [`glu_draw_circle_qrt4`]()              | (same) |
| [`glu_draw_capsule`]()                  | Given 2 points, draw a line in the shape of capsule |
| [`glu_draw_line`]()                     | Given 2 points, draw a line |
| [`glu_draw_quad`]()                     | Given 4 corners coordinate, draw a quadrilateral |
| [`glu_dev_fill_full_screen`]()          | Fill the screen |
| [.yield_GRAM]                           | Export the address of Graph RAM |
| [`glu_gui_object_create`]()             |   |
| [`glu_gui_object_template`]()           |   |
| [`glu_gui_object_adjust`]()             |   |
| [`glu_gui_object_frame`]()              |   |                   
| [`glu_gui_object_insert`]()             |   |
| [`glu_gui_object_delete`]()             |   |
| [`glu_gui_object_default_area`]()       |   |
| **Window**                              | **?**        |
| [`glu_gui_window_create`]()             |   |
| [`glu_gui_window_template`]()           |   |
| [`glu_gui_window_insert`]()             |   |
| [`glu_gui_window_delete`]()             |   |
| **Menu**                                | **?**        |
| [`glu_gui_menu_create`]()               |   |
| [`glu_gui_menu_insert`]()               |   |
| [`glu_gui_menu_frame`]()                |   |
| [`glu_gui_menu_scroll`]()               |   |
| [`glu_gui_menu_delete`]()               |   |
| **Utility**                             | **?**        |
| [`glu_util_align_area`]()               |   |
| [`glu_util_align_screen`]()             |   |
| [`glu_util_is_pt_inside`]()             |   |
| [`glu_util_area_hdiv`]()                |   |
| [`glu_util_area_vdiv`]()                |   |
| [`glu_util_optimal_text`]()             |   |







### `GUI::init` 
---
<div id="GLU_GUI_00"></div>

```c++
void glu_gui_init( void) GLU_API;
```







### `GUI::setPenSize` 

---
<div id="GLU_GUI_01"></div>

```c++
void glu_gui_set_penSize(size_t penSize) GLU_API;
```







### `GUI::setPenColor` 

---
<div id="GLU_GUI_02"></div>

```c++
void glu_gui_set_penColor(gluColor_t penColor) GLU_API;
```







### `DEV::auto_refreash` 
---
<div id="GLU_GUI_03"></div>

```c++
void glu_dev_auto_refreash(cmnBoolean_t flag);
```



### `DEV::refreashScreen` 

---
<div id="GLU_GUI_04"></div>

```c++
void glu_dev_refreash_screen(void);
```

### `DEV::refreash_full_screen` 

---
<div id="GLU_GUI_05"></div>

```c++
void glu_dev_refreash_full_screen(void);
```






### `DEV::is_auto_refreash`

---
<div id="GLU_GUI_06"></div>

```c++
inline cmnBoolean_t glu_dev_is_auto_refreash(void)
```


### `DEV::is_refreash_done`

---
<div id="GLU_GUI_07"></div>

```c++
inline cmnBoolean_t glu_dev_is_refreash_done(void);
```





