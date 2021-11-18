/*ST7567������ͷ�ļ���*/
#ifndef __ST7567_H
#define __ST7567_H

#include <STC15F2K60S2.h>

#define LCD_INTERFACE_6800PARALLEL                            0
#define LCD_INTERFACE_8080PARALLEL                            1
#define LCD_INTERFACE_SPI_SW                                  2
#define LCD_INTERFACE_SPI_HW                                  3

/********************��������********************/
/*�ӿ�ѡ��*/
#define LCD_INTERFACE        LCD_INTERFACE_SPI_SW
/*
�ӿ�ģʽ��
	1.LCD_INTERFACE_6800PARALLEL//6800 8-bit����
	2.LCD_INTERFACE_8080PARALLEL//8080 8-bit����
	3.LCD_INTERFACE_SPI_SW      //���SPI
	4.LCD_INTERFACE_SPI_HW      //Ӳ��SPI
*/

/*��ʼ������*/
//��ʼ�Աȶ����ã��Աȶ�ϸ����  ��Χ(0,63)
#define LCD_CONTRAST          50

//V0����������ã��Աȶȴֵ���  ��Χ(0,7)
#define LCD_Rv0_RATIO         6

//0ҳ��ʼ��       ��Χ(0,63)
#define LCD_START_LINE        0
//#define LCD_START_LINE        32

//��ֱ��ת  0�ر�,1����
#define LCD_SEG_REVERSE       0

//ˮƽ��ת  0�ر�,1����
#define LCD_COM_REVERSE       0

//��ɫ��ʾ  0�ر�,1����
#define LCD_BLACK_REVERSE     0

//��ʾ����  ��Χ(1,132)
//#define LCD_WEIGHT            96
#define LCD_WEIGHT            128
//#define LCD_WEIGHT            132

/*���ܿ���*/
//����ͼ����ʾ���ܣ���9PAGE��  0�ر�,1����
#define LCD_ICON              1

//��ʾ8X16ascll�ַ�����       0�ر�,1����
#define LCD_ASCLL8X16         1

//��ʾ5X7ascll�ַ�����        0�ر�,1����
#define LCD_ASCLL5X7          1

//��ʾ16X16���ֹ���           0�ر�,1����
#define LCD_CH16X16           1

/********************���Ŷ�����********************/
/*6800 8-bit����ģʽ*/
#if (LCD_INTERFACE==LCD_INTERFACE_6800PARALLEL)
#define LCD_DATA P0     //��������
sbit    LCD_E=   P1^1;  //���ڲ���ʹ��
//sbit    LCD_RW=  P2^4;  //��/дѡ��
sbit    LCD_RS=  P1^0;  //����/ָ��ѡ��
sbit    LCD_RST= P1^3;  //��λ
sbit    LCD_CS=  P1^2;  //Ƭѡ

/*8080 8-bit����ģʽ*/
#elif (LCD_INTERFACE==LCD_INTERFACE_8080PARALLEL)
#define LCD_DATA P0     //��������
sbit    LCD_WR=  P1^1;  //����д��ʹ��
//sbit    LCD_RD=  P2^4;  //���ڶ�ȡʹ��
sbit    LCD_RS=  P1^0;  //����/ָ��ѡ��
sbit    LCD_RST= P1^3;  //��λ
sbit    LCD_CS=  P1^2;  //Ƭѡ

/*���SPIģʽ*/
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_SW)
sbit    LCD_DAT= P2^0;  //��������
sbit    LCD_CLK= P2^1;  //����ʱ��
sbit    LCD_RS=  P2^2;  //����ָ��
sbit    LCD_RST= P2^3;  //��λ
sbit    LCD_CS=  P2^4;  //Ƭѡ

/*Ӳ��SPIģʽ*/
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_HW)
sbit    LCD_RS=  P0^4;  //����ָ��
sbit    LCD_RST= P0^3;  //��λ
sbit    LCD_CS=  P0^2;  //Ƭѡ
#endif

/********************��������********************/
/*ָ�*/
#define LCD_Set_Display_ON_OFF                                0xae//��ʾ����
	#define LCD_Display_OFF                                   0x00
	#define LCD_Display_ON                                    0x01
#define LCD_Set_Start_Line                                    0x40//��ʾ��ʼ�е�ַ
#define LCD_Set_Page_Address                                  0xb0//ҳ��ַ
#define LCD_Set_Column_Address_upper_bit                      0x10//�е�ַ��λ
#define LCD_Set_Column_Address_lower_bit                      0x00//�е�ַ��λ
#define LCD_Set_SEG_Direction                                 0xa0//�����뷽�򣨴�ֱ���񣩣����ı�ɨ�跽��
	#define LCD_SEG_Direction_normal                          0x00
	#define LCD_SEG_Direction_reverse                         0x01
#define LCD_Inverse_Display                                   0xa6//��ɫ��ʾ
	#define LCD_Inverse_Display_normal                        0x00
	#define LCD_Inverse_Display_inverse                       0x01
#define LCD_Set_All_Pixel_ON                                  0xa4//ȫ��������ʾ
	#define LCD_All_Pixel_ON_Disable                          0x00
	#define LCD_All_Pixel_ON_Enable                           0x01
#define LCD_Bias_Select                                       0xa2//ƫѹ������
	#define LCD_Bias_Select_1_9_bias                          0x00
	#define LCD_Bias_Select_1_7_bias                          0x01
#define LCD_Read_modify_write                                 0xe0
#define LCD_End                                               0xee
#define LCD_Reset                                             0xe2//�����λ
#define LCD_Set_COM_Direction                                 0xc0//��ɨ��˳��ˮƽ����
	#define LCD_COM_Direction_normal                          0x08
	#define LCD_COM_Direction_reverse                         0x00
#define LCD_Power_Control                                     0x28//��Դ����
	#define LCD_Power_Control_Booster                         0x04//��ѹ��
	#define LCD_Power_Control_Vadj                            0x02//��ѹ������
	#define LCD_Power_Control_Follow                          0x01//��ѹ������
#define LCD_Regulation_Ratio                                  0x20//�����������
#define LCD_Set_EV                                            0x81//Һ��������ѹ�������Աȶȣ���˫�ֽڣ�
#define LCD_Set_Booster                                       0xf8//��ѹ�������ã�˫�ֽڣ�
	#define LCD_Set_Booster_2x_3x_4x                          0x00
	#define LCD_Set_Booster_5x                                0x01
	#define LCD_Set_Booster_6x                                0x11
#define LCD_NOP                                               0xe3//��ָ��
#define LCD_Test                                              0xf0//����ָ��

/********************����������********************/
extern bit lcd_seg_reverse,lcd_com_reverse,lcd_black_reverse;
extern unsigned char lcd_contrast;

/********************����ԭ��������********************/
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