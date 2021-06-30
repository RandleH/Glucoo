

# Font

<p align="center">
<img src="https://raw.githubusercontent.com/RandleH/Glucoo/master/img/font_profile.png">
</p>

<p align="center">
Font 模块可以完成对字体文件的读取, 解析以及图像输出
</p>

---

## Data Structure

我们需要对数据进行封装整理. 以下的数据结构非常有用.


### <u>Align</u> 
`GLU_ENUM(Align)`

Glucoo所支持的Align对齐方式有:


|  成员 <div style="width: 70pt">     | 类型<div style="width: 80pt">  |解释 <div style="width: 250pt">  |
| :----------------------- | ----- | ----------------------------------- |
| kGLU_Align_Right         | enum  | 向右对齐                             |
| kGLU_Align_Left          | enum  | 向左对齐                             |
| kGLU_Align_Middle        | enum  | 居中对齐                             |
| kGLU_Align_Justify       | enum  | 两端对齐                             |



### <u>Font</u> 
`GLU_ENUM(Font)`

Glucoo所支持的Font类型有:





### <u>Text</u> 
`GLU_SRCT(Text)`


在Glucoo中, 完整的Text需要包含以下信息: <br>

|  成员 <div style="width: 50pt">   | 类型<div style="width: 130pt">  | 解释 <div style="width: 350pt">  |
| :----: | ------------------ | :----------------   |
| font   |   GLU_ENUM(Font)   | 该文本使用的字体类型, 可在枚举列表中选择对应的字体    |
| size   |   uint8_t          | 该文本的字体大小       |
| color  |   GLU_TYPE(Pixel)  | 该文本使用的颜色, 颜色对应项目配置       |
| align  |   GLU_ENUM(Align)  | 该文本的对齐方式       |
| str    |   const char*      | 文本文字字符串         |

* 关于*color*的选型配置, 另请参阅...

### <u>Image</u>
`GLU_SRCT(FontImg)`

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
### <u>Initialization</u>
字体模块初始化.
```C
void GLU_FUNC(Font, init)  (void);
```
* 默认的初始配置如下:

* 该方法已嵌套在`GLU_FUNC(GUI, init)`中. 当然重复一次初始化也没什么后果.


### <u>Font Style</u>
设置字体类型
```C
void             GLU_FUNC(Font, set_style) ( GLU_ENUM(Font) font );
GLU_ENUM(Font)   GLU_FUNC(Font, get_style) ( void                );
```

* *font* 是你想要设置成的字体类型, 请在GLU_ENUM(Font)枚举列表中查找.



### <u>Font Size</u>
设置字体大小
```C
void    GLU_FUNC(Font, set_size) ( uint8_t size );
uint8_t GLU_FUNC(Font, get_size) ( void         );
```

* *size* 是你想要设置成的字体大小, 请设置合适的大小, 过大的字体可能会被报错.



### <u>Cache</u>
保存当前的字体设置. 恢复上一次保存的配置.
```C
void    GLU_FUNC(Font, backupCache ) ( void );
void    GLU_FUNC(Font, restoreCache) ( void );
```
* 有些情况下, 你可能在之后还会使用到当前的配置, 因此可以保存,在之后被还原.
* 如果连续多次调用backupCache, 则之前的未被restore的缓存将会被覆盖.

### <u>Output Image</u>
输出单个字符的灰度图像.
```C
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC(Font, out_chr_Img) ( uint16_t    chr );
```
* *chr*是你想要打印的字符.
* 返回文字图像.
<br>

输出字符串的灰度图像.
```C
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC(Font, out_str_Img) ( const char* str );
```
* *str*是你想要打印的字符串.
* 返回文字图像.
<br>

输出整个文本的灰度图像
```C
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC(Font, out_txt_Img) ( const char* str, size_t width, GLU_ENUM(Align) align );
```
* *str*是你想要打印的文本.
* *width*是你想要指定的宽度.
* *align*是你想要的对齐方式.
* 返回文字图像.

### <u>Info</u>
查询输出字符变量 *c* 图像的长宽.
```C
void GLU_FUNC( Font, get_chr_ImgInfo) ( size_t RH_NULLABLE *width, size_t RH_NULLABLE *height, char        c   );
```
* *width*是获取到的宽度, 给NULL将被忽略.
* *height*是获取到的高度, 给NULL将被忽略.
* *c* 是你想要针对的字符.
<br>

```C
void GLU_FUNC( Font, get_str_ImgInfo) ( size_t RH_NULLABLE *width, size_t RH_NULLABLE *height, const char* str );
```
* *width*是获取到的宽度, 给NULL将被忽略.
* *height*是获取到的高度, 给NULL将被忽略.
* *str* 是你想要针对的字符串.
<br>

## Examples




