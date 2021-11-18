/*ST7567驱动（头文件）*/
#ifndef __ST7567_H
#define __ST7567_H

#include <STC15F2K60S2.h>

#define LCD_INTERFACE_6800PARALLEL                            0
#define LCD_INTERFACE_8080PARALLEL                            1
#define LCD_INTERFACE_SPI_SW                                  2
#define LCD_INTERFACE_SPI_HW                                  3

/********************参数设置********************/
/*接口选择*/
#define LCD_INTERFACE        LCD_INTERFACE_SPI_SW
/*
接口模式：
	1.LCD_INTERFACE_6800PARALLEL//6800 8-bit并口
	2.LCD_INTERFACE_8080PARALLEL//8080 8-bit并口
	3.LCD_INTERFACE_SPI_SW      //软件SPI
	4.LCD_INTERFACE_SPI_HW      //硬件SPI
*/

/*初始化设置*/
//初始对比度设置（对比度细调）  范围(0,63)
#define LCD_CONTRAST          50

//V0电阻比例设置（对比度粗调）  范围(0,7)
#define LCD_Rv0_RATIO         6

//0页起始行       范围(0,63)
#define LCD_START_LINE        0
//#define LCD_START_LINE        32

//垂直翻转  0关闭,1开启
#define LCD_SEG_REVERSE       0

//水平翻转  0关闭,1开启
#define LCD_COM_REVERSE       0

//反色显示  0关闭,1开启
#define LCD_BLACK_REVERSE     0

//显示屏宽  范围(1,132)
//#define LCD_WEIGHT            96
#define LCD_WEIGHT            128
//#define LCD_WEIGHT            132

/*功能开关*/
//启用图标显示功能（第9PAGE）  0关闭,1开启
#define LCD_ICON              1

//显示8X16ascll字符功能       0关闭,1开启
#define LCD_ASCLL8X16         1

//显示5X7ascll字符功能        0关闭,1开启
#define LCD_ASCLL5X7          1

//显示16X16汉字功能           0关闭,1开启
#define LCD_CH16X16           1

/********************引脚定义区********************/
/*6800 8-bit并口模式*/
#if (LCD_INTERFACE==LCD_INTERFACE_6800PARALLEL)
#define LCD_DATA P0     //并口数据
sbit    LCD_E=   P1^1;  //并口操作使能
//sbit    LCD_RW=  P2^4;  //读/写选择
sbit    LCD_RS=  P1^0;  //数据/指令选择
sbit    LCD_RST= P1^3;  //复位
sbit    LCD_CS=  P1^2;  //片选

/*8080 8-bit并口模式*/
#elif (LCD_INTERFACE==LCD_INTERFACE_8080PARALLEL)
#define LCD_DATA P0     //并口数据
sbit    LCD_WR=  P1^1;  //并口写入使能
//sbit    LCD_RD=  P2^4;  //并口读取使能
sbit    LCD_RS=  P1^0;  //数据/指令选择
sbit    LCD_RST= P1^3;  //复位
sbit    LCD_CS=  P1^2;  //片选

/*软件SPI模式*/
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_SW)
sbit    LCD_DAT= P2^0;  //串行数据
sbit    LCD_CLK= P2^1;  //串行时钟
sbit    LCD_RS=  P2^2;  //数据指令
sbit    LCD_RST= P2^3;  //复位
sbit    LCD_CS=  P2^4;  //片选

/*硬件SPI模式*/
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_HW)
sbit    LCD_RS=  P0^4;  //数据指令
sbit    LCD_RST= P0^3;  //复位
sbit    LCD_CS=  P0^2;  //片选
#endif

/********************程序定义区********************/
/*指令集*/
#define LCD_Set_Display_ON_OFF                                0xae//显示开关
	#define LCD_Display_OFF                                   0x00
	#define LCD_Display_ON                                    0x01
#define LCD_Set_Start_Line                                    0x40//显示初始行地址
#define LCD_Set_Page_Address                                  0xb0//页地址
#define LCD_Set_Column_Address_upper_bit                      0x10//列地址高位
#define LCD_Set_Column_Address_lower_bit                      0x00//列地址低位
#define LCD_Set_SEG_Direction                                 0xa0//列输入方向（垂直镜像）（不改变扫描方向）
	#define LCD_SEG_Direction_normal                          0x00
	#define LCD_SEG_Direction_reverse                         0x01
#define LCD_Inverse_Display                                   0xa6//反色显示
	#define LCD_Inverse_Display_normal                        0x00
	#define LCD_Inverse_Display_inverse                       0x01
#define LCD_Set_All_Pixel_ON                                  0xa4//全部点阵显示
	#define LCD_All_Pixel_ON_Disable                          0x00
	#define LCD_All_Pixel_ON_Enable                           0x01
#define LCD_Bias_Select                                       0xa2//偏压比设置
	#define LCD_Bias_Select_1_9_bias                          0x00
	#define LCD_Bias_Select_1_7_bias                          0x01
#define LCD_Read_modify_write                                 0xe0
#define LCD_End                                               0xee
#define LCD_Reset                                             0xe2//软件复位
#define LCD_Set_COM_Direction                                 0xc0//行扫描顺序（水平镜像）
	#define LCD_COM_Direction_normal                          0x08
	#define LCD_COM_Direction_reverse                         0x00
#define LCD_Power_Control                                     0x28//电源控制
	#define LCD_Power_Control_Booster                         0x04//升压器
	#define LCD_Power_Control_Vadj                            0x02//电压调整器
	#define LCD_Power_Control_Follow                          0x01//电压跟随器
#define LCD_Regulation_Ratio                                  0x20//电阻比例设置
#define LCD_Set_EV                                            0x81//液晶驱动电压调整（对比度）（双字节）
#define LCD_Set_Booster                                       0xf8//升压倍数设置（双字节）
	#define LCD_Set_Booster_2x_3x_4x                          0x00
	#define LCD_Set_Booster_5x                                0x01
	#define LCD_Set_Booster_6x                                0x11
#define LCD_NOP                                               0xe3//空指令
#define LCD_Test                                              0xf0//测试指令

/********************变量声明区********************/
extern bit lcd_seg_reverse,lcd_com_reverse,lcd_black_reverse;
extern unsigned char lcd_contrast;

/********************函数原型声明区********************/
void Lcd_init();
void Lcd_on();
void Lcd_off();
void Lcd_set_seg_reverse(bit on);
void Lcd_set_com_reverse(bit on);
void Lcd_set_black_reverse(bit on);
void Lcd_set_contrast(unsigned char contrast);
void Lcd_fill(unsigned char x0,unsigned char y0,unsigned char h,unsigned char w,unsigned char dat);
void Lcd_cls();
void Lcd_pic(unsigned char x0,unsigned char y0,unsigned char h,unsigned char w,unsigned char *pic,bit b);
#if (LCD_ASCLL8X16||LCD_CH16X16)
void Lcd_P8x16char(unsigned char x,unsigned char y,unsigned char chr,bit b);
void Lcd_P8x16Str(unsigned char x,unsigned char y,unsigned char *str,bit b);
#endif
#if LCD_ASCLL5X7
void Lcd_P5x7char(unsigned char x,unsigned char y,unsigned char chr,bit b);
void Lcd_P5x7Str(unsigned char x,unsigned char y,unsigned char *str,bit b);
#endif
#if LCD_CH16X16
void Lcd_P16x16Ch(unsigned char x,unsigned char y,unsigned char *cnstr,bit b);
#endif
#if LCD_ICON
void Lcd_write_icon(unsigned char num,bit value);
void Lcd_clear_icon();
#endif

#endif