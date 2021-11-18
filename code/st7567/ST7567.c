/*****************************************
ģ�����ƣ�ST7567����
���ߣ�SocialSisterYi
����ʱ�䣺2017.2
˵����ST7567������ST7565��UC1701�ȵȡ�������Ϊ��ɫSTN���������ӿڣ�SPI/8-bit���ڣ��ֱ���132*64+1ICON,ȡģ��ʽ��8λ���ú����¸�λ
��ע��
*****************************************/
#include <STC15F2K60S2.h>
#include <intrins.h>
#include "delay.h"
#include "ST7567.h"
#if (LCD_INTERFACE==LCD_INTERFACE_SPI_HW)
#include "SPIHW.h"
#endif

bit lcd_seg_reverse=  LCD_SEG_REVERSE,
    lcd_com_reverse=  LCD_COM_REVERSE,
	lcd_black_reverse=LCD_BLACK_REVERSE;
unsigned char lcd_contrast=LCD_CONTRAST;

/*********************************
�������ƣ�Lcd_write_byte
���ܣ�LCDͨ�����SPI����һ���ֽ�
���룺д������
�������
��ע���������
*********************************/
#if (LCD_INTERFACE==LCD_INTERFACE_SPI_SW)
void Lcd_write_byte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		LCD_CLK=0;
		LCD_DAT=(Byte&0x80);
		Byte<<=1;
		LCD_CLK=1;
	}
}
#endif

/*********************************
�������ƣ�Lcd_write_cmd
���ܣ�LCDдָ��
���룺д��ָ��
�������
��ע��
*********************************/
void Lcd_write_cmd(unsigned char cmd)
{
	EA=0;
	LCD_CS=0;
	LCD_RS=0;
#if (LCD_INTERFACE==LCD_INTERFACE_6800PARALLEL)
//	LCD_RW=0;
	LCD_DATA=cmd;
	LCD_E=0;
	_nop_();
	LCD_E=1;
#elif (LCD_INTERFACE==LCD_INTERFACE_8080PARALLEL)
//	LCD_RD=1;
	LCD_DATA=cmd;
	LCD_WR=0;
	_nop_();
	LCD_WR=1;
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_SW)
	Lcd_write_byte(cmd);
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_HW)
	SPIHW_Write(cmd);
#endif
	LCD_CS=1;
	EA=1;
}

/*********************************
�������ƣ�Lcd_write_dat
���ܣ�LCDд����
���룺д������
�������
��ע��
*********************************/
void Lcd_write_dat(unsigned char dat)
{
	EA=0;
	LCD_CS=0;
	LCD_RS=1;
#if (LCD_INTERFACE==LCD_INTERFACE_6800PARALLEL)
//	LCD_RW=0;
	LCD_DATA=dat;
	LCD_E=0;
	_nop_();
	LCD_E=1;
#elif (LCD_INTERFACE==LCD_INTERFACE_8080PARALLEL)
//	LCD_RD=1;
	LCD_DATA=dat;
	LCD_WR=0;
	_nop_();
	LCD_WR=1;
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_SW)
	Lcd_write_byte(dat);
#elif (LCD_INTERFACE==LCD_INTERFACE_SPI_HW)
	SPIHW_Write(dat);
#endif
	LCD_CS=1;
	EA=1;
}

/*********************************
�������ƣ�Lcd_set_pos
���ܣ�LCD��������
���룺x���꣬y����
�������
��ע��x<=131��y<=7
*********************************/
void Lcd_set_pos(unsigned char x,unsigned char y)
{
	if(lcd_seg_reverse)
		x+=(132-LCD_WEIGHT);
	Lcd_write_cmd(LCD_Set_Page_Address+y);//ҳ��ַ
	Lcd_write_cmd(LCD_Set_Column_Address_lower_bit|x&0x0f);//�͵�ַ
	Lcd_write_cmd(LCD_Set_Column_Address_upper_bit|((x&0xf0)>>4));//�ߵ�ַ
}

/*********************************
�������ƣ�Lcd_fill
���ܣ�LCD���
���룺x��ʼ���꣬y��ʼ���꣬���ȣ���ȣ����ֵ
�������
��ע��
*********************************/
void Lcd_fill(unsigned char x0,unsigned char y0,unsigned char h,unsigned char w,unsigned char dat)
{
	unsigned char x;
	if(x0>131||h>132||y0>7||w>8)
		return;
	h=h+x0-1;//��������������ֵֹ
	w=w+y0-1;
	for(;y0<=w;y0++)
	{
		Lcd_set_pos(x0,y0);
		for(x=x0;x<=h;x++)
			Lcd_write_dat(dat);
	}
}

/*********************************
�������ƣ�Lcd_cls
���ܣ�LCD����
���룺��
�������
��ע��
*********************************/
void Lcd_cls()
{
	Lcd_fill(0,0,132,8,0x00);
}

/*********************************
�������ƣ�Lcd_on
���ܣ�LCD������ʾ
���룺��
�������
��ע��
*********************************/
void Lcd_on()
{
	Lcd_write_cmd(LCD_Set_Display_ON_OFF|LCD_Display_ON);
}

/*********************************
�������ƣ�Lcd_off
���ܣ�LCD�ر���ʾ
���룺��
�������
��ע��
*********************************/
void Lcd_off()
{
	Lcd_write_cmd(LCD_Set_Display_ON_OFF|LCD_Display_OFF);
}

/*********************************
�������ƣ�Lcd_set_seg_reverse
���ܣ�LCD���ô�ֱ����
���룺0������1��ת
�������
��ע��ֻ�ı����뷽�򣬲��ı�ɨ�跽��
*********************************/
void Lcd_set_seg_reverse(bit on)
{
	lcd_seg_reverse=on;
	Lcd_write_cmd(LCD_Set_SEG_Direction|(on ? LCD_SEG_Direction_reverse:LCD_SEG_Direction_normal));
}

/*********************************
�������ƣ�Lcd_set_com_reverse
���ܣ�LCD����ˮƽ����
���룺0������1��ת
�������
��ע��
*********************************/
void Lcd_set_com_reverse(bit on)
{
	lcd_com_reverse=on;
	Lcd_write_cmd(LCD_Set_COM_Direction|(on ? LCD_COM_Direction_reverse:LCD_COM_Direction_normal));
}

/*********************************
�������ƣ�Lcd_set_com_reverse
���ܣ�LCD���÷�ɫ��ʾ
���룺0������1��ת
�������
��ע��
*********************************/
void Lcd_set_black_reverse(bit on)
{
	lcd_black_reverse=on;
	Lcd_write_cmd(LCD_Inverse_Display|(on ? LCD_Inverse_Display_inverse:LCD_Inverse_Display_normal));
}

/*********************************
�������ƣ�Lcd_set_contrast
���ܣ�LCD���öԱȶ�
���룺�Աȶ�
�������
��ע��
*********************************/
void Lcd_set_contrast(unsigned char contrast)
{
	if(contrast>63)
		return;
	lcd_contrast=contrast;
	Lcd_write_cmd(LCD_Set_EV);
	Lcd_write_cmd(contrast);
}

/*********************************
�������ƣ�Lcd_write_icon
���ܣ�LCDдͼ��RAM����9PAGE��
���룺ͼ����ţ���ʾ/�ر�
�������
��ע��
*********************************/
#if LCD_ICON
void Lcd_write_icon(unsigned char num,bit value)
{
	if(num>131)
		return;
	Lcd_set_pos(num,8);
	Lcd_write_dat(value);
}

/*********************************
�������ƣ�Lcd_clear_icon
���ܣ�LCD�������ͼ��
���룺��
�������
��ע��
*********************************/
void Lcd_clear_icon()
{
	unsigned char i;
	for(i=0;i<131;i++)
		Lcd_write_icon(i,0);
}
#endif

/*********************************
�������ƣ�Lcd_init
���ܣ�LCD��ʼ��
���룺��
�������
��ע��
*********************************/
void Lcd_init()
{
	LCD_RST=0;//Ӳ��λ
	delayms(10);
	LCD_RST=1;
	delayms(10);
	
	Lcd_write_cmd(LCD_Reset);//��λ
	delayms(100); 
	Lcd_off();
	Lcd_write_cmd(LCD_Bias_Select|LCD_Bias_Select_1_9_bias);//ƫѹ��
	Lcd_write_cmd(LCD_Regulation_Ratio|LCD_Rv0_RATIO);//����V0�������
	Lcd_set_seg_reverse(lcd_seg_reverse);//��ֱ����
	Lcd_set_com_reverse(lcd_com_reverse);//ˮƽ����
	Lcd_set_black_reverse(lcd_black_reverse);//����
	Lcd_set_contrast(lcd_contrast);//Һ��������ѹ�������Աȶȣ�
	Lcd_write_cmd(LCD_Set_All_Pixel_ON|LCD_All_Pixel_ON_Disable);//��ȫ����ʾ
	Lcd_write_cmd(LCD_Set_Booster);Lcd_write_cmd(LCD_Set_Booster_2x_3x_4x);//��ѹ��
	Lcd_write_cmd(LCD_Power_Control|LCD_Power_Control_Booster);//����ѹ��
	delayms(10);
	Lcd_write_cmd(LCD_Power_Control|LCD_Power_Control_Booster|LCD_Power_Control_Vadj);//����ѹ������
	delayms(10);
	Lcd_write_cmd(LCD_Power_Control|LCD_Power_Control_Booster|LCD_Power_Control_Vadj|LCD_Power_Control_Follow);//����ѹ������
	delayms(2);
	Lcd_write_cmd(LCD_Set_Start_Line|LCD_START_LINE);//����0ҳ��ʼ��
	Lcd_cls();//����
#if LCD_ICON
	Lcd_clear_icon();
#endif
	Lcd_set_pos(0,0);//�����λ
	Lcd_on();//����ʾ
}

/*********************************
�������ƣ�Lcd_pic
���ܣ�LCD��ʾͼƬ
���룺x��ʼ���꣬y��ʼ���꣬���ȣ���ȣ�ͼƬ���ݣ�����
�������
��ע��
*********************************/
void Lcd_pic(unsigned char x0,unsigned char y0,unsigned char h,unsigned char w,unsigned char *pic,bit b)
{
	unsigned char x;
	if(x0>131||h>132||y0>7||w>8)
		return;
	h=h+x0-1;//��������������ֵֹ
	w=w+y0-1;
	for(;y0<=w;y0++)
	{
		Lcd_set_pos(x0,y0);
		for(x=x0;x<=h;x++)
			Lcd_write_dat(b ? ~*pic++:*pic++);
	}
}

/*********************************
�������ƣ�Lcd_P8x16char
���ܣ�LCD��ʾһ��8x16�ַ�
���룺x���꣬y���꣬�ַ�������
�������
��ע��
*********************************/
#if (LCD_ASCLL8X16||LCD_CH16X16)
#include "ASC8X16.h"
void Lcd_P8x16char(unsigned char x,unsigned char y,unsigned char chr,bit b)
{
	if(x>131||y>7||chr>127)
		return;
	Lcd_pic(x,y,8,2,&ASC8X16[(chr-32)*16],b);
}

/*********************************
�������ƣ�Lcd_P8x16Str
���ܣ�LCD��ʾ8x16�ַ���
���룺x���꣬y���꣬�ַ���������
�������
��ע��
*********************************/
void Lcd_P8x16Str(unsigned char x,unsigned char y,unsigned char *str,bit b)
{
	while(*str!='\0')
	{
		Lcd_P8x16char(x,y,*str++,b);
		x+=8;
	}
}
#endif

/*********************************
�������ƣ�Lcd_P5x7char
���ܣ�LCD��ʾһ��5x7�ַ�
���룺x���꣬y���꣬�ַ�������
�������
��ע��
*********************************/
#if LCD_ASCLL5X7
#include "ASC5X7.h"
void Lcd_P5x7char(unsigned char x,unsigned char y,unsigned char chr,bit b)
{
	if(x>131||y>7||chr>127)
		return;
	Lcd_pic(x,y,5,1,&ASC5X7[(chr-32)*5],b);
}

/*********************************
�������ƣ�Lcd_P5x7Str
���ܣ�LCD��ʾ5x7�ַ���
���룺x���꣬y���꣬�ַ���������
�������
��ע��
*********************************/
void Lcd_P5x7Str(unsigned char x,unsigned char y,unsigned char *str,bit b)
{
	while(*str!='\0')
	{
		Lcd_P5x7char(x,y,*str++,b);
		x+=6;
	}
}
#endif

/*********************************
�������ƣ�Lcd_P16x16Ch
���ܣ�LCD��ʾ���ĺ�8x16�ַ���
���룺x���꣬y���꣬�ַ���������
�������
��ע��
*********************************/
#if LCD_CH16X16
#include "CH16X16.h"
const unsigned int CH_NUM=(sizeof GB_16)/34;//�����ֿ�����

void Lcd_P16x16Ch(unsigned char x,unsigned char y,unsigned char *cnstr,bit b)
{
	unsigned int word;
	if(x>131||y>7)
		return;
	while(*cnstr!='\0')
	{
		if(*cnstr>=0x81)//����Ϊ����
		{
			for(word=0;word<=CH_NUM;word++)//�����ֿ�
				if((GB_16[word].Index[0]==*cnstr)&&(GB_16[word].Index[1]==*(cnstr+1)))
					Lcd_pic(x,y,16,2,GB_16[word].Msk,b);
			x+=16;
			cnstr+=2;
		}
		else//����ΪASCLL�ַ�
		{
			Lcd_P8x16char(x,y,*cnstr,b);
			cnstr++;
			x+=8;
		}
	}
}
#endif