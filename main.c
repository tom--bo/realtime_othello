#include "itcfunc.h"

int output(int counter_val, int color) {
	lcd_locate(0,0);
	if(counter_val > 5000000){
		lcd_setcolor(0xff);
		lcd_printf("END!!");
	}else{
		lcd_locate(20,12);
		switch(color){
			case 0: lcd_setcolor(0xff); break; //  white
			case 1: lcd_setcolor(0xff); break; //w white
			case 2: lcd_setcolor(0x80); break; //s red
			case 3: lcd_setcolor(0x70); break; //a green
			case 4: lcd_setcolor(0x80); break; //d red
			case 5: lcd_setcolor(0x90); break; //j yellow
			case 6: lcd_setcolor(0xa0); break; //k red
		}
		lcd_printf("%d",counter_val);
		if(color == 5){
			lcd_locate(1,1);
			lcd_printf("----------");
			lcd_locate(2,2);
			lcd_printf("oooooooo");
			lcd_locate(2,3);
			lcd_printf("xxxxxxxx");
			lcd_locate(2,4);
			lcd_printf("ooxxxooo");
			lcd_locate(2,5);
			lcd_printf("xxxooooo");
		}else if(color == 6){
			lcd_locate(2,2);
			lcd_printf("xxxxxxxx");
			lcd_locate(2,3);
			lcd_printf("oooooooo");
			lcd_locate(2,4);
			lcd_printf("xxxooooo");
			lcd_locate(2,5);
			lcd_printf("ooxxxooo");
		}
	}
	return 1;
}

int main() {
	int *counter_reg=(int *)0x010c;
	char *key_reg=(char *)0x0110;
	int color=0;
	lcd_ttyopen(1);
	while(1){
	// キーとカウンタ取得
		int counter_val=*counter_reg;
		char key_val=*key_reg;
		// キー入力条件(WSADJK)
		if( key_val & 0x20){         //w
			color = 1; 
		}else if( key_val & 0x10){   //s
			color = 2;
		}else if( key_val & 0x08){   //a
			color = 3;
		}else if( key_val & 0x04){   //d
			color = 4;
		}else if( key_val & 0x02){   //j
			color = 5;
		}else if( key_val & 0x01){   //k
			color = 6;
		}
		output(counter_val,color);
	}
	lcd_ttyclose();
	while (1);
	return 0;
}



