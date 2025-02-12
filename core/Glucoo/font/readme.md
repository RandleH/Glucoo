

# Font

<p align="center">
<img src="https://raw.githubusercontent.com/RandleH/Glucoo/master/img/font_profile.png">
</p>

<p align="center">
Font 模块可以完成对字体文件的读取, 解析以及图像输出
</p>

---

## Data Structure

在Glucoo世界中, 必要的数据需要进行封装整理. 以下针对Font功能的数据结构非常有用.


### <u>Align</u> 
`tGluTextAlignEnum`

Glucoo所支持的Align对齐方式有:


|  枚举成员 <div style="width: 70pt">     | 类型<div style="width: 80pt">  |解释 <div style="width: 250pt">  |
| :----------------------- | ----- | ----------------------------------- |
| kGLU_Align_Right         | enum  | 向右对齐                             |
| kGLU_Align_Left          | enum  | 向左对齐                             |
| kGLU_Align_Middle        | enum  | 居中对齐                             |
| kGLU_Align_Justify       | enum  | 两端对齐                             |



### <u>Font</u> 
`tGluFontEnum`

Glucoo所支持的Font类型有:

|  枚举成员 <div style="width: 70pt">  | 等宽<div style="width: 40pt">  | 文件大小 <div style="width: 40pt">  |  样式 <div style="width: 170pt"> |
| :------------------------------ | :--: | :----------: | --------|
| kGLU_Font_Unscii                | Yes  | 293712 Byte  | <font face="Unscii_8" size="10" >Glucoo</font>       |
| kGLU_Font_ArialRounded_Bold     | No   | 49296  Byte  | <font face="Arial" size="10">**Glucoo**</font>       |
| kGLU_Font_CourierNew            | Yes  | 684624 Byte  | <font face="Courier New" size="10">Glucoo</font>     |
| kGLU_Font_CourierNew_Italic     | Yes  | 589900 Byte  | <font face="Courier New" size="10">*Glucoo*</font>   |
| kGLU_Font_CourierNew_Bold       | Yes  | 691796 Byte  | <font face="Courier New" size="10">**Glucoo**</font> |
| kGLU_Font_NewYork               | No   | 344120 Byte  | <font face="New York" size="10">Glucoo</font>        |
| kGLU_Font_NewYork_Italic        | No   | 361176 Byte  | <font face="New York" size="10">*Glucoo*</font>      |
| kGLU_Font_Optima                | No   | 263984 Byte  | <font face="Optima" size="10" >Glucoo</font>         |


### <u>Text</u> 
`tGluTextInfo`


在Glucoo中, 完整的Text需要包含以下信息: <br>

|  成员 <div style="width: 50pt">   | 类型<div style="width: 130pt">  | 解释 <div style="width: 350pt">  |
| :----: | ------------------ | :----------------   |
| font   |   tGluFontEnum   | 该文本使用的字体类型, 可在枚举列表中选择对应的字体    |
| size   |   uint8_t          | 该文本的字体大小       |
| color  |   GLU_TYPE(Pixel)  | 该文本使用的颜色, 颜色对应项目配置       |
| align  |   tGluTextAlignEnum  | 该文本的对齐方式       |
| str    |   const char*      | 文本文字字符串         |

* 关于*color*的选型配置, 另请参阅...

### <u>Image</u>
`tGluFontImg`

Glucoo的字体最终呈现形式是定长定宽的[0:255]级的灰度图像.

|  成员 <div style="width: 50pt">   | 类型<div style="width: 130pt">  | 解释 <div style="width: 350pt">  |
| :----:    | ------------------ | :----------------   |
| pBuffer   |   uint8_t*         | 数组数据流            |
| img_w     |   size_t           | 图片宽度             |
| img_h     |   size_t           | 图片高度             |

* 使用灰度图像可以有效地实现抗锯齿效果.
* 这样的灰度图像也可被理解为权重图像, 将权重划分为[0:255]个等级, 便于映射至其他图像中.
<br>
<br>

## Method



| 声明位置       | 方法 <div style="width: 350pt">    |
|:--------------|:----------------------------------|
| GLU_font.h    | [`glu_font_init`](#lk_init)                  |
| GLU_font.h    | [`glu_font_set_style`](#lk_set_style)        |
| GLU_font.h    | [`glu_font_get_style`](#lk_get_style)        |
| GLU_font.h    | [`glu_font_set_size`](#lk_set_size)          |
| GLU_font.h    | [`glu_font_get_size`](#lk_get_size)          |
| GLU_font.h    | [`glu_font_backup_cache`](#lk_backupCache)    |
| GLU_font.h    | [`glu_font_restore_cache`](#lk_restoreCache)  |
| GLU_font.h    | [`glu_font_out_chr_img`](#lk_out_chr_Img)    |
| GLU_font.h    | [`glu_font_out_str_img`](#lk_out_str_Img)    |
| GLU_font.h    | [`glu_font_out_txt_img`](#lk_out_txt_Img)    |
| GLU_font.h    | [`glu_font_get_chr_img_info`](#lk_get_chr_ImgInfo)    |
| GLU_font.h    | [`glu_font_get_str_img_info`](#lk_get_str_ImgInfo)    |
| GLU_font.h    | [`glu_font_get_str_word_cnt`](#lk_get_str_WordCnt)    |


### <u>Initialization</u> <div id="lk_init"></div>
字体模块初始化.
```C
void glu_font_init(void);
```
* 默认的初始配置如下:

* 该方法已嵌套在`glu_gui_init()`中. 当然重复一次初始化也没什么后果.


### <u>Font Style</u> <div id="lk_set_style"></div><div id="lk_get_style"></div>
设置字体类型
```C
void glu_font_set_style( tGluFontEnum font);
tGluFontEnum glu_font_get_style(void);
```

* *font* 是你想要设置成的字体类型, 请在GLU_ENUM(Font)枚举列表中查找.



### <u>Font Size</u>  <div id="lk_set_size"></div><div id="lk_get_size"></div>
设置字体大小
```C
void glu_font_set_size( uint16_t size);
uint8_t glu_font_get_size (void);
```

* *size* 是你想要设置成的字体大小, 请设置合适的大小, 过大的字体可能会被报错.



### <u>Cache</u> <div id="lk_backupCache"></div><div id="lk_restoreCache"></div>
保存当前的字体设置. 恢复上一次保存的配置.
```C
void glu_font_backup_cache(void);
void glu_font_restore_cache(void);
```
* 有些情况下, 你可能在之后还会使用到当前的配置, 因此可以保存,在之后被还原.
* 如果连续多次调用backupCache, 则之前的未被restore的缓存将会被覆盖.

### <u>Output Image</u> 
输出单个字符的灰度图像. <div id="lk_out_chr_Img"></div>
```C
tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_chr_img ( uint16_t    chr);
```
* *chr*是你想要打印的字符.
* 返回文字图像.
<br>

输出字符串的灰度图像. <div id="lk_out_str_Img"></div>
```C
tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_str_img ( const char* str);
```
* *str*是你想要打印的字符串.
* 返回文字图像.
<br>

输出整个文本的灰度图像. <div id="lk_out_txt_Img"></div>
```C
tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_txt_img ( const char* str, size_t width, tGluTextAlignEnum align);
```
* *str*是你想要打印的文本.
* *width*是你想要指定的宽度.
* *align*是你想要的对齐方式.
* 返回文字图像.

### <u>Info</u>
查询输出字符变量 *c* 图像的长宽. <div id="lk_get_chr_ImgInfo"></div>
```C
void glu_font_get_chr_img_info( var RH_NULLABLE *width, var RH_NULLABLE *height, char        c   );
```
* *width*是获取到的宽度, 给NULL将被忽略.
* *height*是获取到的高度, 给NULL将被忽略.
* *c* 是你想要针对的字符.
<br>

查询输出字符串 *str* 图像的长宽. <div id="lk_get_str_ImgInfo"></div>
```C
void glu_font_get_str_img_info( var RH_NULLABLE *width, var RH_NULLABLE *height, const char* str );
```
* *width*是获取到的宽度, 给NULL将被忽略.
* *height*是获取到的高度, 给NULL将被忽略.
* *str* 是你想要针对的字符串.
<br>

查询在限定宽度 *width* 的条件下, 可以输出字符串 *str* 中多少个字符. <div id="lk_get_str_WordCnt"></div>
```C
int glu_font_get_str_word_cnt( var width, const char* str );
```
* *width* 你所限定的宽度.
* *str* 是你想要针对的字符串.
* 返回可输出的字符个数.



## Examples



