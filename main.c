#include "itcfunc.h"

// 盤上のOとXの数
int O;
int X;
int dir[8][2] = {
		{-2, -1}, {0, -1}, {2, -1},
		{-2, 0},         {2, 0},
		{-2, 1}, {0, 1}, {2, 1}
};
int End_flag=0;
char *board[10] = {
	"*----------------*",   
	"|. . . . . . . . |1", //1,1
	"|. . . . . . . . |2",
	"|. . . o . . . . |3",
	"|. . . x o x . . |4",
	"|. . x o x . . . |5",
	"|. . . . o . . . |6",
	"|. . . . . . . . |7",
	"|. . . . . . . . |8", //8,15
	"*----------------*"
};


int isOut(int x, int y){
	if(x<1 || y<1 || x>15 || y>8) return 1;
	else return 0;
}

int canReverse(int x, int y){
	return 0;
}

int countDisc(){
	int i,j;
	O=0;X=0;
	for(i=0;i<9;i++){
		for(j=1;j<16;j+=2){
			switch(board[i][j]){
				case 'o': O++; break;
				case 'x': X++; break;
				default: continue;
			}
		}
	}
	return 0;
}

int canPut(int x, int y, char p){
	int i=0,j;
	int x0, y0, x2, y2;
	for(;i<8;i++){
		x0=x+dir[i][0];
		y0=y+dir[i][1];
		if(isOut(x0, y0)) continue;
		else if(board[y0][x0]=='.') continue;
		else if(board[y0][x0]==p) continue;
		else{ 
			for(j=1;j<16;j++){
				x2=x0+dir[i][0]*j;
				y2=y0+dir[i][1]*j;
				if(isOut(x2, y2)) continue;
				else if(board[y2][x2] == '.') continue;
				else if(board[y2][x2] == p) return 1;
				else continue;
			}
		}
	}
	return 0;
}



int output(int counter_val, int color, int cursol_x, int cursol_y) {
	if(counter_val > 5000000){
		if(End_flag) return 0;
		lcd_setcolor(0xff);
		countDisc();
		lcd_locate(0,0);
		lcd_printf("o: %d", O);
		lcd_locate(0,1);
		lcd_printf("x: %d", X);
		lcd_locate(0,2);
		if(O>X) lcd_printf("YOU WIN!!");
		else if(O==X) lcd_printf("DRAW GAME");
		else lcd_printf("YOU LOSE!!");
		End_flag=1;
	}else{
		lcd_locate(20,12);
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
		lcd_locate(0,12);
		lcd_printf("x, y = %d, %d", cursol_x, cursol_y);

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
		}else if( key_val & 0x10){   //s
			cursol_x-=2;
		}else if( key_val & 0x08){   //a
			if(canPut(cursol_x-1, cursol_y, 'o')) board[cursol_y][cursol_x-1] = 'o';
			else{
				lcd_locate(0,0);
				lcd_printf("Can't Put!!");
			}
		}else if( key_val & 0x04){   //d
				lcd_locate(0,0);
				lcd_printf("!!");
			cursol_x+=2;
		}else if( key_val & 0x02){   //j
				lcd_locate(0,0);
				lcd_printf("!!");
			cursol_y++;
		}else if( key_val & 0x01){   //k
				lcd_locate(0,0);
				lcd_printf("!!");
			cursol_y--;
		}
		output(counter_val, color, cursol_x, cursol_y);
	}
	lcd_ttyclose();
	// while (1);
	return 0;
}



