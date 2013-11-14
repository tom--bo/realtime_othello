#include "itcfunc.h"
#define N 20
#define Limit 10000000

int ArrayEnqueue(int *queue, int data, int *head, int *tail, size_t n);
int ArrayDequeue(int *queue, int *head, int *tail, size_t n);
// 盤上のOとXの数
int O = 4;
int X = 4;
int Start_flag=0;
int Step_num=0;
int Com_strength = 300000;
int dir[8][2] = {
		{-2, -1}, {0, -1}, {2, -1},
		{-2, 0},         {2, 0},
		{-2, 1}, {0, 1}, {2, 1}
};
int End_flag=0;
char *board[10] = {
	"*----------------*",   
	"|. . . . . . . . |1   ___________", //1,1
	"|. . . . . . . . |2  |k -> Up    |",
	"|. . . o . . . . |3  |j -> Down  |",
	"|. . . x o x . . |4  |d -> Right |",
	"|. . x o x . . . |5  |s -> Left  |",
	"|. . . . o . . . |6  |a -> Put   |",
	"|. . . . . . . . |7  |w -> End   |",
	"|. . . . . . . . |8   -----------", //8,15
	"*----------------*"
};


int isOut(int x, int y){
	if(x<1 || y<1 || x>16 || y>8) return 1;
	else return 0;
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
	if(board[y][x] != '.') return 0;
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

int put(int x, int y, char p){
	int i=0,j,k;
	int x0, y0, x2, y2, x3, y3;
	if(board[y][x]!='.') return 0;
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
				else if(board[y2][x2] == p){
					for(k=-1;k<j;k++){
						x3=x0+dir[i][0]*k;
						y3=y0+dir[i][1]*k;
						board[y3][x3] = p;
					}
				}
				else continue;
			}
		}
	}
	countDisc();
	return 0;
}

int selectDifficulty(int Step_num) {
	lcd_setcolor(0xff);
	lcd_locate(6,1);
	lcd_printf("Select Computer strength!!");
	lcd_locate(11,3);
	lcd_printf("EASY");
	if(Step_num==0) lcd_printf("     <--");
	else lcd_printf("        ");
	lcd_locate(11,4);
	lcd_printf("NORMAL");
	if(Step_num==1) lcd_printf("   <--");
	else lcd_printf("        ");
	lcd_locate(11,5);
	lcd_printf("HARD");
	if(Step_num==2) lcd_printf("     <--");
	else lcd_printf("        ");

	lcd_locate(14,7);
	lcd_printf("_____________");
	lcd_locate(14,8);
	lcd_printf("|k -> Up    |");
	lcd_locate(14,9);
	lcd_printf("|j -> Down  |");
	lcd_locate(14,10);
	lcd_printf("|a -> Put   |");
	lcd_locate(14,11);
	lcd_printf(" ------------");


	return 0;
}

int startGame(int count){

	lcd_locate(10,1);
	lcd_printf("Start Game !!");
	lcd_locate(18,4);
	lcd_printf("%d", count);

	lcd_locate(14,6);
	lcd_printf("_____________");
	lcd_locate(14,7);
	lcd_printf("|k -> Up    |");
	lcd_locate(14,8);
	lcd_printf("|j -> Down  |");
	lcd_locate(14,9);
	lcd_printf("|d -> Right |");
	lcd_locate(14,10);
	lcd_printf("|s -> Left  |");
	lcd_locate(14,11);
	lcd_printf("|a -> Put   |");
	lcd_locate(14,12);
	lcd_printf("|w -> End   |");
	lcd_locate(14,13);
	lcd_printf(" ------------");

	return 0;
}


int output(int counter_val, int color, int cursol_x, int cursol_y) {
	if(counter_val > Limit){  //100sで終了
		if(End_flag) return 0;
		lcd_setcolor(0xff);
		countDisc();
		lcd_locate(2,12);
		lcd_printf("o: %d", O);
		lcd_locate(2,13);
		lcd_printf("x: %d", X);
		lcd_locate(4,14);
		if(O>X) lcd_printf("YOU WIN!!");
		else if(O==X) lcd_printf("DRAW GAME");
		else lcd_printf("YOU LOSE!!");
		End_flag=1;
		while(1){}
	}else{
		lcd_locate(20,12);
		lcd_printf("Left time: %d",(Limit-counter_val)/100000);
		board[cursol_y][cursol_x] = '<';
		lcd_locate(4,1); lcd_printf(board[0]);
		lcd_locate(4,2); lcd_printf(board[1]);
		lcd_locate(4,3); lcd_printf(board[2]);
		lcd_locate(4,4); lcd_printf(board[3]);
		lcd_locate(4,5); lcd_printf(board[4]);
		lcd_locate(4,6); lcd_printf(board[5]);
		lcd_locate(4,7); lcd_printf(board[6]);
		lcd_locate(4,8); lcd_printf(board[7]);
		lcd_locate(4,9); lcd_printf(board[8]);
		lcd_locate(4,10); lcd_printf(board[9]);

		lcd_locate(1,12);
		lcd_printf("o: %d", O);
		lcd_locate(1,13);
		lcd_printf("x: %d", X);
/*
		for(y=1;y<11;y++){
			for(x=1;x<11;x++){
				if(board[y-1][x-1] == 'x') lcd_setcolor(0x70);
				else if(board[y-1][x-1] == 'o') lcd_setcolor(0x80);
				else lcd_setcolor(0xff);
				lcd_locate(x,y);
				lcd_printf(&board[y-1][x-1]);
			}
		}
*/
		// lcd_locate(0,12); lcd_printf("x, y = %d, %d", cursol_x, cursol_y);

		board[cursol_y][cursol_x] = ' ';
	}
	return 1;
}

int turnComputer(){
	int i,j;
    int queue_x[N], queue_y[N];
    int head_x=0, tail_x=0, head_y=0, tail_y=0;
    int length, choice;
	// 置けるマスを検索
	for(i=1; i<9; i++){
		for(j=1; j<16; j+=2){
			if(canPut(j, i, 'x')){
				ArrayEnqueue(queue_x, j, &head_x, &tail_x, N);
				ArrayEnqueue(queue_y, i, &head_y, &tail_y, N);
			}
		}
	}
			// choice の選択を書く
	length = tail_x - head_x;
	if(length){
		choice = rand()%length;
		for(i=0;i<length;i++){
			if(i==choice) put(ArrayDequeue(queue_x, &head_x, &tail_x, N), ArrayDequeue(queue_y, &head_y, &tail_y, N), 'x');
			else{
				ArrayDequeue(queue_x, &head_x, &tail_x, N);
				ArrayDequeue(queue_y, &head_y, &tail_y, N);
			}
		}
	}
	return 0;
}



int main() {
	int *counter_reg=(int *)0x010c;
	char *key_reg=(char *)0x0110;
	int cursol_x=8, cursol_y=4;
	int counter_val=*counter_reg;
	int count=0;
	int color=0;
	lcd_ttyopen(1);

	while(1){
		char key_val=*key_reg;
		// キー入力条件(WSADJK)
		if( key_val & 0x20){         //w
		}else if( key_val & 0x10){   //s
		}else if( key_val & 0x08){   //a
			switch(Step_num){
				case 0: Com_strength=400000; break;
				case 1: Com_strength=300000; break;
				case 2: Com_strength=200000; break;
			}
			break;
		}else if( key_val & 0x04){   //d
		}else if( key_val & 0x02){   //j
			if(Step_num!=2) Step_num++;
		}else if( key_val & 0x01){   //k
			if(Step_num) Step_num--;
		}
		selectDifficulty(Step_num);
	}
	lcd_ttyopen(1);

	counter_val=*counter_reg;
	while(1){
		count=*counter_reg;
		if(count - counter_val > 400000) break;
		startGame(4-(count - counter_val)/100000);
	}
	lcd_ttyopen(1);

	counter_val=*counter_reg;
	count = counter_val;
	while(1){
	// キーとカウンタ取得
		char key_val=*key_reg;
		counter_val=*counter_reg;
		if(counter_val - count > Com_strength){
			turnComputer();
			count+=Com_strength;
		}
		// キー入力条件(WSADJK)
		if( key_val & 0x20){         //w
			//強制的に中断。（置くところがなくなった時)
			counter_val+=10000000;
		}else if( key_val & 0x10){   //s
			if(!isOut(cursol_x-2, cursol_y)) cursol_x-=2;
		}else if( key_val & 0x08){   //a
			put(cursol_x-1, cursol_y, 'o');
		}else if( key_val & 0x04){   //d
			if(!isOut(cursol_x+2, cursol_y)) cursol_x+=2;
		}else if( key_val & 0x02){   //j
			if(!isOut(cursol_x, cursol_y+1)) cursol_y++;
		}else if( key_val & 0x01){   //k
			if(!isOut(cursol_x, cursol_y-1)) cursol_y--;
		}
		output(counter_val, color, cursol_x, cursol_y);
	}
	lcd_ttyclose();
	// while (1);
	return 0;
}

//queueの実装
// 参考: http://www.c-tipsref.com/tips/array/queue.html

int ArrayEnqueue(int *queue, int data, int *head, int *tail, size_t n) {
    if (*head % n != (*tail + 1) % n) {
        queue[(*tail)++ % n] = data;
        return *tail - *head;
    } else {
        return 0;
    }
}

int ArrayDequeue(int *queue, int *head, int *tail, size_t n) {
    if (*head != *tail) {
        return queue[(*head)++ % n];
    } else {
        return 0;
    }
}

