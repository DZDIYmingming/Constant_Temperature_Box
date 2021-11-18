#include <STC15F2K60S2.h>
#include "ST7567.h"
#include "picture.h"
#include "18b20.h"
#include <stdio.h>
#include "delay.h"

/*
sbit    LCD_DAT= P2^0;  //串行数据
sbit    LCD_CLK= P2^1;  //串行时钟
sbit    LCD_RS=  P2^2;  //数据指令
sbit    LCD_RST= P2^3;  //复位
sbit    LCD_CS=  P2^4;  //片选


*/
  sbit  LCD_LED=P1^1;	//屏幕背光
  sbit  LED=P1^0;//板载指示灯
  sbit  KEY1=P1^2;
  sbit  KEY2=P1^3;
  sbit  KEY3=P1^4;
  sbit  KEY4=P1^5;	
  
  sbit  HOT=P3^6;  
	
  unsigned char Max=26;
  unsigned char Min=23;

  unsigned char Temp=0;

  unsigned char page=0;  //0没有  1上限   2下限


  unsigned char Led_flag=0;//0亮  1灭

 


void show2num(unsigned char x,unsigned char y,unsigned char num) //显示2位数字
{
  switch(num/10)
  {
  	case 0:Lcd_P8x16Str(x,y," ",0);break;
	case 1:Lcd_P8x16Str(x,y,"1",0);break;
	case 2:Lcd_P8x16Str(x,y,"2",0);break;
	case 3:Lcd_P8x16Str(x,y,"3",0);break;
	case 4:Lcd_P8x16Str(x,y,"4",0);break;
	case 5:Lcd_P8x16Str(x,y,"5",0);break;
	case 6:Lcd_P8x16Str(x,y,"6",0);break;
	case 7:Lcd_P8x16Str(x,y,"7",0);break;
	case 8:Lcd_P8x16Str(x,y,"8",0);break;
	case 9:Lcd_P8x16Str(x,y,"9",0);break;
  }
   switch(num%10)
  {
  	case 0:Lcd_P8x16Str(x+8,y,"0",0);break;
	case 1:Lcd_P8x16Str(x+8,y,"1",0);break;
	case 2:Lcd_P8x16Str(x+8,y,"2",0);break;
	case 3:Lcd_P8x16Str(x+8,y,"3",0);break;
	case 4:Lcd_P8x16Str(x+8,y,"4",0);break;
	case 5:Lcd_P8x16Str(x+8,y,"5",0);break;
	case 6:Lcd_P8x16Str(x+8,y,"6",0);break;
	case 7:Lcd_P8x16Str(x+8,y,"7",0);break;
	case 8:Lcd_P8x16Str(x+8,y,"8",0);break;
	case 9:Lcd_P8x16Str(x+8,y,"9",0);break;
  }

}


void showUI()	//显示框架
{
   Lcd_P16x16Ch(24,0,"恒温控制板",0);
		Lcd_P16x16Ch(0,2,"当前温度:",0);
		switch(page)
		{
		 	case 0:Lcd_P16x16Ch(0,4,"上限温度:",0);
				   Lcd_P16x16Ch(0,6,"下限温度:",0);break;
			case 1:Lcd_P16x16Ch(0,4,"上限温度:",1);
				   Lcd_P16x16Ch(0,6,"下限温度:",0);break;
			case 2:Lcd_P16x16Ch(0,4,"上限温度:",0);
				   Lcd_P16x16Ch(0,6,"下限温度:",1);break;
		}
		Lcd_P16x16Ch(88,2,"℃",0);
		Lcd_P16x16Ch(88,4,"℃",0);
		Lcd_P16x16Ch(88,6,"℃",0);
			if(Led_flag==0)
		{
		    LCD_LED=0;
			Lcd_pic(112,0,16,2,light_key_on,0);
		}
		else
		{
		    LCD_LED=1;
			Lcd_pic(112,0,16,2,light_key_off,0);
		}
		
		Lcd_pic(112,2,16,4,up_key,0);
		Lcd_pic(112,4,16,6,down_key,0);
		Lcd_pic(112,6,16,8,enter_key,0);
		Temp=read_temp();
		show2num(72,2,Temp);
		show2num(72,4,Max);
		show2num(72,6,Min);	
}

void ReadKey()
{
   if(KEY1==0)
		{
		 while(KEY1==0)
		 {
		  ;
		 }
		 Led_flag=!Led_flag;
		}
		if(KEY2==0)
		{
		 while(KEY2==0)
		 {
		  ;
		 }
		 if(page==1)
		 {
		  Max++;
		 }
		 if(page==2)
		 {
		  Min++;
		 }
		 
		}
		if(KEY3==0)
		{
		 while(KEY3==0)
		 {
		  ;
		 }
		if(page==1)
		 {
		  Max--;
		 }
		 if(page==2)
		 {
		  Min--;
		 }
		}
		if(KEY4==0)
		{
		 while(KEY4==0)
		 {
		  ;
		 }
		 page++;
		 if(page>=3)
		 {
		  page=0;
		 }
		}
		
		   

}
void Heating()
{	 if(Temp>10&&Temp<35)	 //温度在正常范围内
	{
		if(Temp<Min)
		{
			HOT=0;
			LED=0;
		}
		if(Temp>Max)
		{
			HOT=1;
			LED=1;
		}	
	
	}
	else
	{
		HOT=1;
		LED=1;
	}
	  
}


void main()
{

	Lcd_init();
	LCD_LED=0;

	 while(1)
	 {
	     showUI();//显示框架界面
		 ReadKey();//读取按键						   
		 Heating();//加热
	 	 delayms(100);
	 }			 


			   
}