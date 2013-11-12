#include "itcfunc.h"

char *board[10] = {
	"*----------------*",
	"|. . . . . . . . |1",
	"|. . . . . . . . |2",
	"|. . . o . . . . |3",
	"|. . . x o x . . |4",
	"|. . x o x . . . |5",
	"|. . . . o . . . |6",
	"|. . . . . . . . |7",
	"|. . . . . . . . |8",
	"*----------------*"
};

int output(int counter_val, int color, int cursol_x, int cursol_y) {
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

		board[cursol_y][cursol_x] = '@';

		lcd_locate(1,1);
		lcd_printf(board[0]);
		lcd_locate(1,2);
		lcd_printf(board[1]);
		lcd_locate(1,3);
		lcd_printf(board[2]);
		lcd_locate(1,4);
		lcd_printf(board[3]);
		lcd_locate(1,5);
		lcd_printf(board[4]);
		lcd_locate(1,6);
		lcd_printf(board[5]);
		lcd_locate(1,7);
		lcd_printf(board[6]);
		lcd_locate(1,8);
		lcd_printf(board[7]);
		lcd_locate(1,9);
		lcd_printf(board[8]);
		lcd_locate(1,10);
		lcd_printf(board[9]);

		board[cursol_y][cursol_x] = ' ';
	}
	return 1;
}

int main() {
	int *counter_reg=(int *)0x010c;
	char *key_reg=(char *)0x0110;
	int cursol_x=8, cursol_y=4;
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
			cursol_x-=2;
		}else if( key_val & 0x08){   //a
			color = 3;
		}else if( key_val & 0x04){   //d
			color = 4;
			cursol_x+=2;
		}else if( key_val & 0x02){   //j
			color = 5;
			cursol_y++;
		}else if( key_val & 0x01){   //k
			color = 6;
			cursol_y--;
		}
		output(counter_val, color, cursol_x, cursol_y);
	}
	lcd_ttyclose();
	while (1);
	return 0;
}



