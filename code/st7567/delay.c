#include "delay.h"
#include <intrins.h>

void delayms(unsigned int ms)
{
    unsigned char a,b,c;
	while(ms--)
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=12;a>0;a--);
}

void delayus(unsigned int us)
{
    unsigned char a;
	while(us--)
	{
		for(a=1;a>0;a--);
		_nop_();  //if Keil,require use intrins.h
		_nop_();  //if Keil,require use intrins.h
	}
}