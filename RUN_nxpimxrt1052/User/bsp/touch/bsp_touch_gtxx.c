
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "./touch/bsp_touch_gtxx.h"
#include "./touch/bsp_i2c_touch.h"
#include "./lcd/bsp_lcd.h"
// #include "./touch/palette.h"
#include "./delay/core_delay.h"   

__TouchData_t TouchData = {0};

const uint8_t CTP_CFG_GT9157[] = {
  0x00,0x20,0x03,0xE0,0x01,0x05,0x3C,0x00,0x01,0x08,
  0x28,0x0C,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x17,0x19,0x1E,0x14,0x8B,0x2B,0x0D,
  0x33,0x35,0x0C,0x08,0x00,0x00,0x00,0x9A,0x03,0x11,
  0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x32,0x00,0x00,
  0x00,0x20,0x58,0x94,0xC5,0x02,0x00,0x00,0x00,0x04,
  0xB0,0x23,0x00,0x93,0x2B,0x00,0x7B,0x35,0x00,0x69,
  0x41,0x00,0x5B,0x4F,0x00,0x5B,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,
  0x12,0x14,0x16,0x18,0x1A,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0F,
  0x10,0x12,0x13,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,
  0x21,0x22,0x24,0x26,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x48,0x01
};


const uint8_t CTP_CFG_GT911[]  = {
  0x00,0x20,0x03,0xE0,0x01,0x05,0x0D,0x00,0x01,0x08,
  0x28,0x0F,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x2A,0x0C,
  0x45,0x47,0x0C,0x08,0x00,0x00,0x00,0x02,0x02,0x2D,
  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
  0x00,0x28,0x64,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0x9C,0x2C,0x00,0x8F,0x34,0x00,0x84,0x3F,0x00,0x7C,
  0x4C,0x00,0x77,0x5B,0x00,0x77,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,0x21,
  0x22,0x24,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x24,0x01    
};


const uint8_t CTP_CFG_GT5688[] = {
  0x97,0xE0,0x01,0x10,0x01,0x05,0x0D,0x00,0x01,0x00,
  0x00,0x05,0x5A,0x46,0x53,0x11,0x00,0x00,0x11,0x11,
  0x14,0x14,0x14,0x22,0x0A,0x04,0x00,0x00,0x00,0x00,
  0x00,0x00,0x53,0x00,0x14,0x00,0x00,0x84,0x00,0x00,
  0x3C,0x00,0x00,0x64,0x1E,0x28,0x87,0x27,0x08,0x32,
  0x34,0x05,0x0D,0x20,0x33,0x60,0x11,0x02,0x24,0x00,
  0x00,0x64,0x80,0x80,0x14,0x02,0x00,0x00,0x54,0x89,
  0x68,0x85,0x6D,0x82,0x72,0x80,0x76,0x7D,0x7B,0x7B,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x50,0x3C,
  0xFF,0xFF,0x07,0x00,0x00,0x00,0x02,0x14,0x14,0x03,
  0x04,0x00,0x21,0x64,0x0A,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x32,0x20,0x50,0x3C,0x3C,0x00,0x00,0x00,0x00,0x00,
  0x0D,0x06,0x0C,0x05,0x0B,0x04,0x0A,0x03,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,
  0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x3C,0x00,0x05,0x1E,0x00,0x02,
  0x2A,0x1E,0x19,0x14,0x02,0x00,0x03,0x0A,0x05,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x86,
  0x22,0x03,0x00,0x00,0x33,0x00,0x0F,0x00,0x00,0x00,
  0x50,0x3C,0x50,0x00,0x00,0x00,0x00,0x2A,0x01
};


const uint8_t CTP_CFG_GT917S[] = {
  0x97,0x20,0x03,0xE0,0x01,0x0A,0x35,0x04,0x00,0x69,
  0x09,0x0F,0x50,0x32,0x33,0x11,0x00,0x32,0x11,0x11,
  0x28,0x8C,0xAA,0xDC,0x58,0x04,0x00,0x00,0x1E,0x3C,
  0x00,0x00,0x00,0x31,0x00,0x00,0x00,0x00,0x00,0x40,
  0x32,0x00,0x00,0x50,0x38,0x00,0x8D,0x20,0x16,0x4E,
  0x4C,0x7C,0x05,0x28,0x3E,0x28,0x0D,0x43,0x24,0x00,
  0x01,0x39,0x6B,0xC0,0x94,0x84,0x2D,0x00,0x54,0xB0,
  0x41,0x9D,0x49,0x8D,0x52,0x7F,0x5A,0x75,0x62,0x6C,
  0x42,0x50,0x14,0x00,0x00,0x00,0x00,0xF0,0x50,0x3C,
  0x88,0x88,0x27,0x50,0x3C,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x02,0x78,
  0x0A,0x50,0xFF,0xE4,0x04,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x3C,0xB0,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x56,0xA2,0x07,0x50,0x1E,
  0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
  0x0F,0x10,0x12,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,
  0x1D,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,
  0x17,0x15,0x14,0x13,0x12,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x00,0x30,0x7F,0x7F,0x7F,0xFF,
  0x54,0x64,0x00,0x80,0x46,0x07,0x50,0x3C,0x32,0x14,
  0x0A,0x64,0x32,0x00,0x00,0x00,0x00,0x11,0x02,0x62,
  0x32,0x03,0x14,0x50,0x0C,0xE2,0x14,0x50,0x00,0x54,
  0x10,0x00,0x32,0xA2,0x07,0x64,0xA4,0xB6,0x01
};

typedef struct{
    /*根据触摸屏类型配置*/
    uint16_t max_width;        // 触点最大值,高
    uint16_t max_height;       // 触点最大值,宽

    uint16_t config_reg_addr;  // 不同类型的触摸ic配置寄存器地址不同

}TOUCH_PARAM_TypeDef;


typedef enum{
    GT9157 = 0,
    GT911  = 1,
    GT5688 = 2,
    GT917S = 3,
}TOUCH_IC;

TOUCH_IC touchIC = GT911;        

const TOUCH_PARAM_TypeDef touch_param[4] = 
{
    /* GT9157,5´  */
    {
    .max_width       = 800,
    .max_height      = 480,
    .config_reg_addr = 0x8047,
    },
    /* GT911,7´  */
    {
    .max_width       = 800,
    .max_height      = 480,
    .config_reg_addr = 0x8047,
    },
    /* GT5688,4.3´ */
    {
    .max_width       = 480,
    .max_height      = 272,
    .config_reg_addr = 0x8050,
    },
    /* GT917,5´ */
    {
    .max_width       = 800,
    .max_height      = 480,
    .config_reg_addr = 0x8050,
    }
};

static void __touchinfo_Init(void){
    memset( TouchData.track, -1, GTP_MAX_TOUCH*sizeof(TouchData.track[0]) );
}

static int I2C_Transfer( struct i2c_msg *msgs,int num){
    int im = 0;
    int ret = 0;

    GTP_DEBUG_FUNC();
  
    for (im = 0; ret == 0 && im != num; im++){
        if ( msgs[im].flags == I2C_M_RD )    
          ret = I2C_ReadBytes(msgs[im].addr, msgs[im].buf, msgs[im].len);     
        else
          ret = I2C_WriteBytes(msgs[im].addr,  msgs[im].buf, msgs[im].len);   

    }
  
    if(ret)
        return ret;
  
    return im; 
}

static int32_t GTP_I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len){
    struct i2c_msg msgs[2];
    int32_t ret=-1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();

    msgs[0].flags = I2C_M_WR;        
    msgs[0].addr  = client_addr;        
    msgs[0].len   = GTP_ADDR_LENGTH;
    msgs[0].buf   = &buf[0];

    msgs[1].flags = I2C_M_RD;
    msgs[1].addr  = client_addr;
    msgs[1].len   = len - GTP_ADDR_LENGTH;
    msgs[1].buf   = &buf[GTP_ADDR_LENGTH];
  
    while(retries < 5){
        ret = I2C_Transfer( msgs, 2);    
        if(ret == 2)
            return ret;
        retries++;
    }

    GTP_ERROR("I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);

    return ret;
}

static int32_t GTP_I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len){
    struct i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();

    msg.flags = I2C_M_WR;
    msg.addr  = client_addr;    
    msg.len   = len;
    msg.buf   = buf;
  
    while(retries < 5){
        ret = I2C_Transfer(&msg, 1);
        if (ret == 1){
            return ret;
        }

        retries++;
    }

    GTP_ERROR("I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
    
  return ret;
}

static int8_t GTP_I2C_Test( void ){

    uint8_t test[3] = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
    uint8_t retry   = 0;
    int8_t  ret     = -1;

    GTP_DEBUG_FUNC();
  
    while(retry++ < 5){
        ret = GTP_I2C_Read(GTP_ADDRESS, test, 3);
        if (ret <= 0){
          GTP_ERROR("GTP i2c test failed time %d.",retry);
        }

    }
    return ret;
}


int32_t GTP_I2C_Read_dbl_check(uint8_t client_addr, uint16_t addr, uint8_t *rxbuf, int len){
    uint8_t buf[16] = {0};
    uint8_t confirm_buf[16] = {0};
    uint8_t retry = 0;
  
    GTP_DEBUG_FUNC();
  
    while (retry++ < 3){
        memset(buf, 0xAA, 16);
        buf[0] = (uint8_t)(addr >> 8);
        buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, buf, len + 2);

        memset(confirm_buf, 0xAB, 16);
        confirm_buf[0] = (uint8_t)(addr >> 8);
        confirm_buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, confirm_buf, len + 2);


        if (!memcmp(buf, confirm_buf, len+2)){
          memcpy(rxbuf, confirm_buf+2, len);
          return SUCCESS;
        }
    }    
  GTP_ERROR("I2C read 0x%04X, %d bytes, double check failed!", addr, len);
  return FAIL;
}

void GTP_IRQ_Disable(void){
    GTP_IRQDisable();
}


void GTP_IRQ_Enable(void){
    GTP_IRQEnable();    
}


static void GTP_Touch_Down(int32_t id,int32_t x,int32_t y,int32_t w){

  
}

static void GTP_Touch_Up( int32_t id){
      
  
}

static void Goodix_TS_Work_Func(void)
{
  uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
  uint8_t  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
  uint8_t  touch_num = 0;
  uint8_t  finger = 0;
  static uint16_t pre_touch = 0;
  static uint8_t pre_id[GTP_MAX_TOUCH] = {0};
  
  uint8_t client_addr=GTP_ADDRESS;
  uint8_t* coor_data = NULL;
  int32_t input_x = 0;
  int32_t input_y = 0;
  int32_t input_w = 0;
  uint8_t id = 0;
  
  int32_t i  = 0;
  int32_t ret = -1;
  
  GTP_DEBUG_FUNC();
  
  ret = GTP_I2C_Read(client_addr, point_data, 12);//10×Ö½Ú¼Ä´æÆ÷¼Ó2×Ö½ÚµØÖ·
  if (ret < 0){
    GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
    
    return;
  }
  
  finger = point_data[GTP_ADDR_LENGTH];//×´Ì¬¼Ä´æÆ÷Êý¾Ý
  
  if (finger == 0x00)            // Ã»ÓÐÊý¾Ý£¬ÍË³ö
    return;
  
  if((finger & 0x80) == 0)  // ÅÐ¶Ïbuffer statusÎ»
    goto exit_work_func;    // ×ø±êÎ´¾ÍÐ÷£¬Êý¾ÝÎÞÐ§
  
  touch_num = finger & 0x0f;// ×ø±êµãÊý

  if (touch_num > GTP_MAX_TOUCH)
    goto exit_work_func;    // ´óÓÚ×î´óÖ§³ÖµãÊý£¬´íÎóÍË³ö
  
  if (touch_num > 1){       // ²»Ö¹Ò»¸öµã
    uint8_t buf[8 * GTP_MAX_TOUCH] = {(GTP_READ_COOR_ADDR + 10) >> 8, (GTP_READ_COOR_ADDR + 10) & 0xff};
    
    ret = GTP_I2C_Read(client_addr, buf, 2 + 8 * (touch_num - 1));
    memcpy(&point_data[12], &buf[2], 8 * (touch_num - 1));//¸´ÖÆÆäÓàµãÊýµÄÊý¾Ýµ½point_data
  }
  
  
  
  if (pre_touch>touch_num)         //pre_touch>touch_num,±íÊ¾ÓÐµÄµãÊÍ·ÅÁË
  {
    for (i = 0; i < pre_touch; i++)//Ò»¸öµãÒ»¸öµã´¦Àí
    {
      uint8_t j;
      for(j=0; j<touch_num; j++)
      {
        coor_data = &point_data[j * 8 + 3];
        id = coor_data[0] & 0x0F;//track id
        if(pre_id[i] == id)
          break;
        
        if(j >= touch_num-1)    //±éÀúµ±Ç°ËùÓÐid¶¼ÕÒ²»µ½pre_id[i]£¬±íÊ¾ÒÑÊÍ·Å
        {
          GTP_Touch_Up( pre_id[i]);
        }
      }
    }
  }
  
  
  if (touch_num)
  {
    for (i = 0; i < touch_num; i++)//Ò»¸öµãÒ»¸öµã´¦Àí
    {
      coor_data = &point_data[i * 8 + 3];
      
      id = coor_data[0] & 0x0F;    //track id
      pre_id[i] = id;
      
      input_x  = coor_data[1] | (coor_data[2] << 8);    //x×ø±ê
      input_y  = coor_data[3] | (coor_data[4] << 8);    //y×ø±ê
      input_w  = coor_data[5] | (coor_data[6] << 8);    //size
      
      {
        GTP_Touch_Down( id, input_x, input_y, input_w);//Êý¾Ý´¦Àí
      }
    }
  }
  else if (pre_touch)        //touch_ num=0 ÇÒpre_touch£¡=0
  {
    for(i=0;i<pre_touch;i++)
    {
      GTP_Touch_Up(pre_id[i]);
    }
  }
  
  
  pre_touch = touch_num;
  
  
exit_work_func:
  {
    ret = GTP_I2C_Write(client_addr, end_cmd, 3);
    if (ret < 0)
    {
      GTP_INFO("I2C write end_cmd error!");
    }
  }
  
}


#pragma anon_unions   
static void Goodix_TS_Work_Func1( void ){

static typeof( TouchData.num_Fingers ) cache_num_Fingers = 0;

#pragma pack(1)

// 适用于寄存器0x814E 至 0x819F 的数据结构, 详见GT911参考手册    
struct{
    uint8_t addrH;
    uint8_t addrL;
    struct{
        uint8_t num_of_touchpoint : 4; // 屏上的坐标点个数
        uint8_t have_key          : 1; // 1=有按键          ; 0=无按键(已经松键);
        uint8_t proximity_valid   : 1;
        uint8_t large_detect      : 1;
        uint8_t buffer_status     : 1; // 1=坐标(或按键)已就绪; 0=未就绪，数据无效;
    }REG_0x814E;
    
    struct{
        uint8_t trackID;
        uint8_t XL;
        uint8_t XH;
        uint8_t YL;
        uint8_t YH;
        uint8_t pointSizeH;
        uint8_t pointSizeL;
        uint8_t reserved;
    }CordInfo[10];
    
    uint8_t key_value;
}REG_Data = {0};

// 适用于结束指令的数据结构, 清空0x814E寄存器内容
#pragma pack(1)
struct{
    uint8_t addrH;
    uint8_t addrL;
    uint8_t data;
}ExitInfo = {0};    

    bool* trackRecord = NULL;

    REG_Data.addrH = (uint8_t)(GTP_READ_COOR_ADDR>>8  );
    REG_Data.addrL = (uint8_t)(GTP_READ_COOR_ADDR&0xff);

    ExitInfo.addrH  = (uint8_t)(GTP_READ_COOR_ADDR>>8  );
    ExitInfo.addrL  = (uint8_t)(GTP_READ_COOR_ADDR&0xff);
    ExitInfo.data   = 0;

    GTP_DEBUG_FUNC();
    
    // 先读取状态寄存器 和 第一个触点数据
    GTP_I2C_Read( GTP_ADDRESS, (uint8_t*)&REG_Data, sizeof(REG_Data.REG_0x814E)+sizeof(REG_Data.CordInfo[0])+2 );
    
    // 状态寄存器未就绪
    if( REG_Data.REG_0x814E.buffer_status == false )
        goto EXIT;
    
    // 收到触点数量大于最大值
    if( REG_Data.REG_0x814E.num_of_touchpoint > GTP_MAX_TOUCH )
        goto EXIT;
    
    // 多个触点接收到, 则读取全部数据
    if( REG_Data.REG_0x814E.num_of_touchpoint > 1 )
        GTP_I2C_Read( GTP_ADDRESS, (uint8_t*)&REG_Data, sizeof(REG_Data) );





    trackRecord = alloca( REG_Data.REG_0x814E.num_of_touchpoint*sizeof(bool) ); // false = 新轨迹; true = 老轨迹
    memset( trackRecord, false, REG_Data.REG_0x814E.num_of_touchpoint*sizeof(bool) );
    // 在记录的track轨迹中找现有仍然存在的轨迹
    for( int8_t i=0; i<TouchData.num_Fingers; i++ ){
        for( int8_t j=0; j<REG_Data.REG_0x814E.num_of_touchpoint; j++ ){

            if ( TouchData.track[i].ID == -1 ){
                continue;
            }

            if( TouchData.track[i].ID==REG_Data.CordInfo[j].trackID && trackRecord[j]==false ){
                // 寻找到之前记录的轨迹
                TouchData.track[i].pos_X = (int16_t)((REG_Data.CordInfo[j].XH<<8)|(REG_Data.CordInfo[j].XL));
                TouchData.track[i].pos_Y = (int16_t)((REG_Data.CordInfo[j].YH<<8)|(REG_Data.CordInfo[j].YL));
                TouchData.track[i].size  = (int16_t)((REG_Data.CordInfo[j].pointSizeH<<8)|(REG_Data.CordInfo[j].pointSizeL));
                trackRecord[j] = true;
                goto NEXT_SEARCH_IN_RECORD;
            }
        }
        
        // 未寻找到之前记录的轨迹, 说明这条轨迹已经结束
        TouchData.track[i].ID    = -1;
        TouchData.track[i].pos_X = -1;
        TouchData.track[i].pos_Y = -1;
        TouchData.track[i].size  = -1;

    NEXT_SEARCH_IN_RECORD:    
        continue;
    }
    // 至此 所有上一轮有记录但现在不存在了的轨迹都已被置-1, 所有上一轮有记录现在仍然存在的轨迹都已更新数据
    // 因此仅剩上一轮没有记录, 而现在却存在了的轨迹 即 新轨迹 需要被创建
    
    for( int8_t j=0, i=0; j<REG_Data.REG_0x814E.num_of_touchpoint; j++ ){

        if( trackRecord[j]==false ){
            // 发现一条新轨迹
            for( ;i<GTP_MAX_TOUCH; i++ ){
                if( TouchData.track[i].ID == -1 ){ 
                    // 找到未被使用的轨迹记录数组
                    TouchData.track[i].ID    = REG_Data.CordInfo[j].trackID;
                    TouchData.track[i].pos_X = (int16_t)((REG_Data.CordInfo[j].XH<<8)|(REG_Data.CordInfo[j].XL));
                    TouchData.track[i].pos_Y = (int16_t)((REG_Data.CordInfo[j].YH<<8)|(REG_Data.CordInfo[j].YL));
                    TouchData.track[i].size  = (int16_t)((REG_Data.CordInfo[j].pointSizeH<<8)|(REG_Data.CordInfo[j].pointSizeL));
                    break;
                }
            }
        }
    }


    if( cache_num_Fingers > 0 ){

    }

    if( TouchData.num_Fingers > 0 ){

    }
    
    //...//

    TouchData.num_Fingers = REG_Data.REG_0x814E.num_of_touchpoint;
EXIT:
    {
        GTP_I2C_Write( GTP_ADDRESS, (uint8_t*)&ExitInfo, sizeof(ExitInfo) );
    } 
}


int8_t GTP_Reset_Guitar(void){
    GTP_DEBUG_FUNC();

    GTP_ResetChip();
    return 0;
}



// int8_t GTP_Enter_Sleep(void)
// {
//    int8_t ret = -1;
//    int8_t retry = 0;
//    uint8_t reset_comment[3] = {(uint8_t)(GTP_REG_COMMENT >> 8), (uint8_t)GTP_REG_COMMENT&0xFF, 5};//5

//    GTP_DEBUG_FUNC();

//    while(retry++ < 5)
//    {
//        ret = GTP_I2C_Write(GTP_ADDRESS, reset_comment, 3);
//        if (ret > 0)
//        {
//            GTP_INFO("GTP enter sleep!");

//            return ret;
//        }

//    }
//    GTP_ERROR("GTP send sleep cmd failed.");
//    return ret;
// }


int8_t GTP_Send_Command(uint8_t command)
{
  int8_t ret = -1;
  int8_t retry = 0;
  uint8_t command_buf[3] = {(uint8_t)(GTP_REG_COMMAND >> 8), (uint8_t)GTP_REG_COMMAND&0xFF, GTP_COMMAND_READSTATUS};
  
  GTP_DEBUG_FUNC();
  
  while(retry++ < 5)
  {
    ret = GTP_I2C_Write(GTP_ADDRESS, command_buf, 3);
    if (ret > 0)
    {
      GTP_INFO("send command success!");
      
      return ret;
    }
    
  }
  GTP_ERROR("send command fail!");
  return ret;
}

int8_t GTP_WakeUp_Sleep(void)
{
  uint8_t retry = 0;
  int8_t ret = -1;
  
  GTP_DEBUG_FUNC();
  
  while(retry++ < 10)
  {
    ret = GTP_I2C_Test();
    if (ret > 0)
    {
      GTP_INFO("GTP wakeup sleep.");
      return ret;
    }
    GTP_Reset_Guitar();
  }
  
  GTP_ERROR("GTP wakeup sleep failed.");
  return ret;
}

static int32_t GTP_Get_Info(void)
{
  uint8_t opr_buf[10] = {0};
  int32_t ret = 0;
  
  uint16_t abs_x_max = GTP_MAX_WIDTH;
  uint16_t abs_y_max = GTP_MAX_HEIGHT;
  uint8_t int_trigger_type = GTP_INT_TRIGGER;
  
  opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+1) >> 8);
  opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+1) & 0xFF);
  
  ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 10);
  if (ret < 0)
  {
    return FAIL;
  }
  
  abs_x_max = (opr_buf[3] << 8) + opr_buf[2];
  abs_y_max = (opr_buf[5] << 8) + opr_buf[4];
  GTP_DEBUG("RES");   
  GTP_DEBUG_ARRAY(&opr_buf[0],10);
  
  opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+6) >> 8);
  opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+6) & 0xFF);
  
  ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 3);
  if (ret < 0)
  {
    return FAIL;
  }
  int_trigger_type = opr_buf[2] & 0x03;
  
  GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
           abs_x_max,abs_y_max,int_trigger_type);
  
  return SUCCESS;    
}

/*******************************************************
Function:
Initialize gtp.
Input:
ts: goodix private data
Output:
Executive outcomes.
0: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Init_Panel(void)
{
  int32_t ret = -1;
  
  int32_t i = 0;
  uint16_t check_sum = 0;
  int32_t retry = 0;
  
  const uint8_t* cfg_info;
  uint8_t cfg_info_len  ;
  uint8_t* config;
  
  uint8_t cfg_num =0 ;        //ÐèÒªÅäÖÃµÄ¼Ä´æÆ÷¸öÊý
  
  GTP_DEBUG_FUNC();
  
  I2C_Touch_Init();
  
  ret = GTP_I2C_Test();
  if (ret < 0)
  {
    GTP_ERROR("I2C communication ERROR!");
    return ret;
  } 
  
  //»ñÈ¡´¥ÃþICµÄÐÍºÅ
  GTP_Read_Version(); 
  
  config = (uint8_t *)malloc (GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH);
  
  config[0] = GTP_REG_CONFIG_DATA >> 8;//¸ß8Î»
  config[1] =  GTP_REG_CONFIG_DATA & 0xff;//µÍ8Î»
  
  //¸ù¾ÝICµÄÐÍºÅÖ¸Ïò²»Í¬µÄÅäÖÃ
  if(touchIC == GT9157)
  {
    cfg_info =  CTP_CFG_GT9157; //Ö¸Ïò¼Ä´æÆ÷ÅäÖÃ
    cfg_info_len = CFG_GROUP_LEN(CTP_CFG_GT9157);//¼ÆËãÅäÖÃ±íµÄ´óÐ¡
  }
  else if(touchIC == GT911)
  {
    cfg_info =  CTP_CFG_GT911;//Ö¸Ïò¼Ä´æÆ÷ÅäÖÃ
    cfg_info_len = CFG_GROUP_LEN(CTP_CFG_GT911) ;//¼ÆËãÅäÖÃ±íµÄ´óÐ¡
  }
  else if(touchIC == GT5688)            
  {
    cfg_info =  CTP_CFG_GT5688; //Ö¸Ïò¼Ä´æÆ÷ÅäÖÃ
    cfg_info_len = CFG_GROUP_LEN(CTP_CFG_GT5688);//¼ÆËãÅäÖÃ±íµÄ´óÐ¡
  }
  else if(touchIC == GT917S)
  {
    cfg_info =  CTP_CFG_GT917S; //Ö¸Ïò¼Ä´æÆ÷ÅäÖÃ
    cfg_info_len = CFG_GROUP_LEN(CTP_CFG_GT917S);//¼ÆËãÅäÖÃ±íµÄ´óÐ¡  
  }
  
  memset(&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
  memcpy(&config[GTP_ADDR_LENGTH], cfg_info, cfg_info_len);
  
  cfg_num = cfg_info_len;
  
  GTP_DEBUG("cfg_info_len = %d ",cfg_info_len);
  GTP_DEBUG("cfg_num = %d ",cfg_num);
  GTP_DEBUG_ARRAY(config,6);
  
  /*¸ù¾ÝLCDµÄÉ¨Ãè·½ÏòÉèÖÃ·Ö±æÂÊ*/
  config[GTP_ADDR_LENGTH+1] = LCD_PIXEL_WIDTH & 0xFF;
  config[GTP_ADDR_LENGTH+2] = LCD_PIXEL_WIDTH >> 8;
  config[GTP_ADDR_LENGTH+3] = LCD_PIXEL_HEIGHT & 0xFF;
  config[GTP_ADDR_LENGTH+4] = LCD_PIXEL_HEIGHT >> 8;
  
  /*¸ù¾ÝÄ£Ê½ÉèÖÃX2Y½»»»*/
  
  //²»½»»»
  //                config[GTP_ADDR_LENGTH+6] &= ~(X2Y_LOC);
  
  if(touchIC == GT911 || touchIC == GT9157 || touchIC == GT5688)
  {
    //½»»»
    config[GTP_ADDR_LENGTH+6] |= (X2Y_LOC);
  }
  
  //¼ÆËãÒªÐ´Èëchecksum¼Ä´æÆ÷µÄÖµ
  check_sum = 0;
  
  /* ¼ÆËãcheck sum Ð£ÑéÖµ */
  if(touchIC == GT911 || touchIC == GT9157)
  {
    for (i = GTP_ADDR_LENGTH; i < cfg_num+GTP_ADDR_LENGTH; i++)
    {
      check_sum += (config[i] & 0xFF);
    }
    config[ cfg_num+GTP_ADDR_LENGTH] = (~(check_sum & 0xFF)) + 1;     //checksum
    config[ cfg_num+GTP_ADDR_LENGTH+1] =  1;                         //refresh ÅäÖÃ¸üÐÂ±êÖ¾
  }
  else if(touchIC == GT5688 || touchIC == GT917S) 
  {
    for (i = GTP_ADDR_LENGTH; i < (cfg_num+GTP_ADDR_LENGTH -3); i += 2) 
    {
      check_sum += (config[i] << 8) + config[i + 1];
    }
    
    check_sum = 0 - check_sum;
    GTP_DEBUG("Config checksum: 0x%04X", check_sum);
    //¸üÐÂchecksum
    config[(cfg_num+GTP_ADDR_LENGTH -3)] = (check_sum >> 8) & 0xFF;
    config[(cfg_num+GTP_ADDR_LENGTH -2)] = check_sum & 0xFF;
    config[(cfg_num+GTP_ADDR_LENGTH -1)] = 0x01;
  }
  
  //Ð´ÈëÅäÖÃÐÅÏ¢
  for (retry = 0; retry < 5; retry++)
  {
    ret = GTP_I2C_Write(GTP_ADDRESS, config , cfg_num + GTP_ADDR_LENGTH+2);
    if (ret > 0)
    {
      break;
    }
  }
  CPU_TS_Tmr_Delay_MS(40);                //ÑÓ³ÙµÈ´ýÐ¾Æ¬¸üÐÂ
  
  
  
#if 1   
  {
    uint16_t i;
    uint8_t buf[250];
    buf[0] = config[0];
    buf[1] =config[1];    //¼Ä´æÆ÷µØÖ·
    
    GTP_DEBUG_FUNC();
    
    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
    
    GTP_DEBUG("read ");
    
    GTP_DEBUG_ARRAY(buf,cfg_num);
    
    GTP_DEBUG("write ");
    
    GTP_DEBUG_ARRAY(config,cfg_num);
    
    //²»¶Ô±È°æ±¾ºÅ
    for(i=3;i<cfg_num+GTP_ADDR_LENGTH-3;i++)
    {
      
      if(config[i] != buf[i])
      {
        GTP_ERROR("Config fail ! i = %d ",i);
        free(config);
        return -1;
      }
    }
    if(i==cfg_num+GTP_ADDR_LENGTH-3)
      GTP_DEBUG("Config success ! i = %d ",i);
  }
#endif
  
  
  /* emXGUIÊ¾ÀýÖÐ²»Ê¹ÄÜÖÐ¶Ï */
  GTP_IRQ_Enable();
  
  GTP_Get_Info();
  
  free(config);
  
  __touchinfo_Init();
  return 0;
}


/*******************************************************
Function:
Read chip version.
Input:
client:  i2c device
version: buffer to keep ic firmware version
Output:
read operation return.
2: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Read_Version(void)
{
  int32_t ret = -1;
  uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //¼Ä´æÆ÷µØÖ·
  
  GTP_DEBUG_FUNC();
  
  ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
  if (ret < 0)
  {
    GTP_ERROR("GTP read version failed");
    return ret;
  }
  
  if (buf[2] == '9')
  {                
    //GT911Ð¾Æ¬
    if(buf[2] == '9' && buf[3] == '1' && buf[4] == '1')
    {
      GTP_INFO("IC1 Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);
      
      touchIC = GT911;
      /* ÉèÖÃµ±Ç°µÄÒº¾§ÆÁÀàÐÍ */
      cur_lcd = INCH_7;
    }
    //GT9157Ð¾Æ¬
    else if( buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7')
    {
      GTP_INFO("IC2 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
      
      touchIC = GT9157;
      /* ÉèÖÃµ±Ç°µÄÒº¾§ÆÁÀàÐÍ */
      cur_lcd = INCH_5;
    }
    //GT91SÐ¾Æ¬
    else if( buf[2] == '9' && buf[3] == '1' && buf[4] == '7' && buf[5] == 'S')
    {
      GTP_INFO("IC2 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
      
      touchIC = GT917S;
      /* ÉèÖÃµ±Ç°µÄÒº¾§ÆÁÀàÐÍ */
      cur_lcd = INCH_5;
    }
    else
      GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    
  }    
  else if (buf[2] == '5')
  {    
    //GT5688Ð¾Æ¬
    if(buf[2] == '5' && buf[3] == '6' && buf[4] == '8' && buf[5] == '8')
    {
      GTP_INFO("IC3 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
      
      touchIC = GT5688;
      /* ÉèÖÃµ±Ç°µÄÒº¾§ÆÁÀàÐÍ */
      cur_lcd = INCH_4_3;
    }
    else
      GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    
  }
  else
    GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
  
  return ret;
}

void GTP_TouchProcess(void)
{
  GTP_DEBUG_FUNC();
  Goodix_TS_Work_Func1();
  
}

#if 0//Ã»ÓÐµ½µÄ²âÊÔº¯Êý
/*******************************************************
Function:
Request gpio(INT & RST) ports.
Input:
ts: private data.
Output:
Executive outcomes.
>= 0: succeed, < 0: failed
*******************************************************/
static int8_t GTP_Request_IO_Port(struct goodix_ts_data *ts)
{
}

/*******************************************************
Function:
Request interrupt.
Input:
ts: private data.
Output:
Executive outcomes.
0: succeed, -1: failed.
*******************************************************/
static int8_t GTP_Request_IRQ(struct goodix_ts_data *ts)
{
}

//Êä³öÒª³õÊ¼»¯µÄÊý¾Ý¼°Ð¾Æ¬ÖÐµÄÕæÊµÊý¾Ý
static void GT91xx_Config_Read_Proc(void)
{
  char temp_data[GTP_CONFIG_MAX_LENGTH + 2] = {0x80, 0x47};
  int i;
  
  GTP_INFO("==== GT9XX config init value====\n");
  
  for (i = 0 ; i < GTP_CONFIG_MAX_LENGTH ; i++)
  {
    printf("reg0x%x = 0x%02X ", i+0x8047, config[i + 2]);
    
    if (i % 10 == 9)
      printf("\n");
  }
  
  
  GTP_INFO("==== GT9XX config real value====\n");
  GTP_I2C_Read(GTP_ADDRESS, (uint8_t *)temp_data, GTP_CONFIG_MAX_LENGTH + 2);
  for (i = 0 ; i < GTP_CONFIG_MAX_LENGTH ; i++)
  {
    printf("reg0x%x = 0x%02X ", i+0x8047,temp_data[i+2]);
    
    if (i % 10 == 9)
      printf("\n");
  }
  
}

//ÏòÐ¾Æ¬Ð´ÈëÅäÖÃÊý¾Ý
static int32_t GT91xx_Config_Write_Proc(void)
{
  int32_t ret = -1;
  
  int32_t i = 0;
  uint8_t check_sum = 0;
  int32_t retry = 0;
  uint8_t cfg_num =0x80FE-0x8047+1 ;        //ÐèÒªÅäÖÃµÄ¼Ä´æÆ÷¸öÊý
  
  uint8_t cfg_info[] = CTP_CFG_GROUP1;
  uint8_t cfg_info_len =CFG_GROUP_LEN(cfg_info) ;
  
  GTP_INFO("==== GT9XX send config====\n");
  
  memset(&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
  memcpy(&config[GTP_ADDR_LENGTH], cfg_info,cfg_info_len);
  
  //¼ÆËãÒªÐ´Èëchecksum¼Ä´æÆ÷µÄÖµ
  check_sum = 0;
  for (i = GTP_ADDR_LENGTH; i < cfg_num+GTP_ADDR_LENGTH; i++)
  {
    check_sum += config[i];
  }
  config[ cfg_num+GTP_ADDR_LENGTH] = (~check_sum) + 1;     //checksum
  config[ cfg_num+GTP_ADDR_LENGTH+1] =  1;         //refresh ÅäÖÃ¸üÐÂ±êÖ¾
  
  //Ð´ÈëÅäÖÃÐÅÏ¢
  for (retry = 0; retry < 5; retry++)
  {
    ret = GTP_I2C_Write(GTP_ADDRESS, config , cfg_num + GTP_ADDR_LENGTH+2);
    if (ret > 0)
    {
      break;
    }
  }
  
  
  return ret;
}

#endif

/**
* @brief  ´¥ÆÁÖÐ¶Ï·þÎñº¯Êý£¬emXGUIÊ¾ÀýÖÐÃ»ÓÐÊ¹ÓÃÖÐ¶Ï
* @param ÎÞ
* @retval ÎÞ
*/
//void GTP_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //È·±£ÊÇ·ñ²úÉúÁËEXTI LineÖÐ¶Ï
//    {
//        //LED2_TOGGLE;
//        GTP_TouchProcess();    
//        EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //Çå³ýÖÐ¶Ï±êÖ¾Î»
//    }  
//}

/**
* @brief  ´¥ÆÁ¼ì²âº¯Êý£¬±¾º¯Êý×÷ÎªemXGUIµÄ¶¨ÖÆ¼ì²âº¯Êý£¬
*        ²Î¿¼Goodix_TS_Work_FuncÐÞ¸Ä¶øÀ´£¬ Ö»¶ÁÈ¡µ¥¸ö´¥Ãþµã×ø±ê
* @param x[out] y[out] ¶ÁÈ¡µ½µÄ×ø±ê
* @retval ×ø±êÓÐÐ§·µ»Ø1£¬·ñÔò·µ»Ø0
*/
int    GTP_Execu( int *x,int *y)
{
  uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
  //2-¼Ä´æÆ÷µØÖ· 1-×´Ì¬¼Ä´æÆ÷ 8*1-Ã¿¸ö´¥ÃþµãÊ¹ÓÃ8¸ö¼Ä´æÆ÷ 
  uint8_t  point_data[2 + 1 + 8 * 1 + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
  uint8_t  touch_num = 0;
  uint8_t  finger = 0;
  
  uint8_t client_addr=GTP_ADDRESS;
  int32_t input_x = 0;
  int32_t input_y = 0;
  
  int32_t ret = -1;
  
  GTP_DEBUG_FUNC();
  
  ret = GTP_I2C_Read(client_addr, point_data, 12);//10×Ö½Ú¼Ä´æÆ÷¼Ó2×Ö½ÚµØÖ·
  if (ret < 0)
  {
    GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
    return 0;
  }
  
  finger = point_data[GTP_ADDR_LENGTH];//×´Ì¬¼Ä´æÆ÷Êý¾Ý
  
  if (finger == 0x00)        //Ã»ÓÐÊý¾Ý£¬ÍË³ö
  {
    return 0;
  }
  
  if((finger & 0x80) == 0)//ÅÐ¶Ïbuffer statusÎ»
  {
    goto exit_work_func;//×ø±êÎ´¾ÍÐ÷£¬Êý¾ÝÎÞÐ§
  }
  
  touch_num = finger & 0x0f;//×ø±êµãÊý
  if (touch_num > GTP_MAX_TOUCH)
  {
    goto exit_work_func;//´óÓÚ×î´óÖ§³ÖµãÊý£¬´íÎóÍË³ö
  }    
  
  if (touch_num)
  {
    //      id = point_data[0] & 0x0F;                //track id
    
    input_x  = point_data[3+1] | (point_data[3+2] << 8);    //x×ø±ê
    input_y  = point_data[3+3] | (point_data[3+4] << 8);    //y×ø±ê
    //      input_w  = coor_data[5] | (coor_data[6] << 8);    //size
    
    if(input_x < GTP_MAX_WIDTH && input_y < GTP_MAX_HEIGHT)  
    {
      *x = input_x;
      *y = input_y;
    }
    else
    {
      //³¬³ö·¶Î§£¬´íÎóÍË³ö
      goto exit_work_func;
    }
  }
  
exit_work_func:
  {
    //Çå¿Õ±êÖ¾
    ret = GTP_I2C_Write(client_addr, end_cmd, 3);
    if (ret < 0)
    {
      GTP_INFO("I2C write end_cmd error!");
      return 0;
    }
  }
  
  return touch_num;
}

































