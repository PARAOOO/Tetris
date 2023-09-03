# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <conio.h> 
# include <time.h> 
# include <process.h>
# include <Windows.h>
CRITICAL_SECTION cs;

void create_I();
void create_T();
void create_O();
void create_S();
void create_Z();
void create_L();
void create_J();
void down();
void move_left();
void move_right();
void spin_I();
void spin_S();
void spin_T();
void spin_O();
void spin_Z();
void spin_L();
void spin_J();
void print_board();
void next_queue();

int endcount = 0;

int board[22][12] = { 0, };
int queue;
int q_count = 0;

int random_board[7] = { 1,2,3,4,5,6,7 };
int r_next;
int r_count = 0;

int end = 0;
int spin = 0;
int h = 0;
int h_count = 0;
int h_d_count = 0;

int end_c = 0;

int restart_count = 0;

int stage = 0;

void setFontSize(int X, int Y)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = X;
	cfi.dwFontSize.Y = Y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void setWindowConsole(int cols, int lines)
{
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, WS_CAPTION | WS_SYSMENU);
	SetWindowPos(GetConsoleWindow(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_SHOWWINDOW);
	char cmd[100];
	sprintf(cmd, "mode con:cols=%d lines=%d", cols, lines);
	system(cmd);
	system("color 0f");


}

void cursorHide() {

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

unsigned _stdcall Thread_down(void* arg)
{
	while (1)
	{   

		int delay_count = 0;

		int con = 0;

		if (endcount > 0) {
			endcount = 0;
			_endthreadex(0);
		}

		for (int i = 1; i < 21; i++) {
			for (int j = 1; j < 11; j++) {
				if (board[i][j] == 1) {
					con = 1;
				}
				else if (board[i][j] == 2) {
					con = 2;
				}
				else if (board[i][j] == 3) {
					con = 3;
				}
				else if (board[i][j] == 4) {
					con = 4;
				}
				else if (board[i][j] == 5) {
					con = 5;
				}
				else if (board[i][j] == 6) {
					con = 6;
				}
				else if (board[i][j] == 7) {
					con = 7;
				}
			}
		}
		
			down(con);
			print_board();
			Sleep(1000-stage*10);
		
	}
}

void hard_drop(int h_d) {

	h_d_count = 0;

	while (h_d_count == 0) down(h_d);


}

void random_create() {

	int i = 1;
	while (i == 1) {

		srand(clock());
		int r;
		r = rand() % 7;

		if (random_board[r] != 0) {
			r_next = random_board[r];

			random_board[r] = 0;
			r_count++;
			i++;

			if (r_count == 7)
			{
				random_board[0] = 1;
				random_board[1] = 2;
				random_board[2] = 3;
				random_board[3] = 4;
				random_board[4] = 5;
				random_board[5] = 6;
				random_board[6] = 7;
				r_count = 0;

			}
		}
	}
}

void next_queue() {

	if (q_count == 0) {
		random_create();
		if (r_next == 1) create_I();
		else if (r_next == 2) create_T();
		else if (r_next == 3) create_O();
		else if (r_next == 4) create_S();
		else if (r_next == 5) create_Z();
		else if (r_next == 6) create_L();
		else if (r_next == 7) create_J();
	}
	else {
		if (queue == 1) create_I();
		else if (queue == 2) create_T();
		else if (queue == 3) create_O();
		else if (queue == 4) create_S();
		else if (queue == 5) create_Z();
		else if (queue == 6) create_L();
		else if (queue == 7) create_J();
	}

	random_create();
	queue = r_next;
	q_count++;



}

void line_clear() {

	int sum = 0;
	

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (board[i][j] == 11) {
				sum++;
			}
		}
		if (sum == 10) {
			for (int k = i; k > 1; k--) {
				for (int l = 1; l < 11; l++) {
					board[k][l] = board[k - 1][l];
					board[k - 1][l] = 0;
				}
				
			}
			stage++;
		}
		
		sum = 0;
	}
}

void hold(int hold) {


	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 21; j++) {
			for (int k = 1; k < 11; k++) {
				if (board[j][k] == hold) {
					board[j][k] = 0;
				}
			}
		}
	}

	if (h_count == 0) {

		next_queue();
	}
	else {

		if (h == 1) create_I();
		else if (h == 2) create_T();
		else if (h == 3) create_O();
		else if (h == 4) create_S();
		else if (h == 5) create_Z();
		else if (h == 6) create_L();
		else if (h == 7) create_J();
	}

	h = hold;
	h_count++;

}

void control() {

	int con = 0;
	char control;

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (board[i][j] == 1) {
				con = 1;
			}
			else if (board[i][j] == 2) {
				con = 2;
			}
			else if (board[i][j] == 3) {
				con = 3;
			}
			else if (board[i][j] == 4) {
				con = 4;
			}
			else if (board[i][j] == 5) {
				con = 5;
			}
			else if (board[i][j] == 6) {
				con = 6;
			}
			else if (board[i][j] == 7) {
				con = 7;
			}
		}
	}
		while (1) {
			control = _getch();
			if (control == -32) {
				control = _getch();
				if (control == 75) {
					move_left(con);
					return;
				}
				else if (control == 77) {
					move_right(con);
					return;
				}
				else if (control == 80) {
					down(con);
					return;
				}
			}
			else if (control == 122) {
				if (con == 1) spin_I();
				else if (con == 2) spin_T();
				else if (con == 3) spin_O();
				else if (con == 4) spin_S();
				else if (con == 5) spin_Z();
				else if (con == 6) spin_L();
				else if (con == 7) spin_J();
				return;
			}
			else if (control == 120) {
				hold(con);
				return;
			}
			else if (control == 32) {
				hard_drop(con);
				return;
			}
			else if (control == 114 ) {
				restart_count++;
				return;
			}
		}
}

void print_board() {

	EnterCriticalSection(&cs);

	system("CLS");

	printf("\n\n");
	for (int i = 1; i < 21; i++) {
		printf("       ");
		for (int j = 1; j < 11; j++) {
			if (board[i][j] == 0) {
				printf("¡à");
			}
			else if (board[i][j] == 1) {
				printf("¢Ç");
			}
			else if (board[i][j] == 2) {
				printf("¢Ã");
			}
			else if (board[i][j] == 3) {
				printf("¢È");
			}
			else if (board[i][j] == 4) {
				printf("¢Ë");
			}
			else if (board[i][j] == 5) {
				printf("¢Ê");
			}
			else if (board[i][j] == 6) {
				printf("¢É");
			}
			else if (board[i][j] == 7) {
				printf("¢Ì");
			}
			else if (board[i][j] == 11) {
				printf("¡á");
			}
			
			if (i == 2 && j == 10) printf("       hold");
			if (i == 4 && j == 10) {
				if (h == 1) printf("	¢Ç¢Ç¢Ç¢Ç");
				else if (h == 2) printf("      ¢Ã¢Ã¢Ã");
				else if (h == 3) printf("	  ¢È¢È");
				else if (h == 4) printf(" 	   ¢Ë¢Ë");
				else if (h == 5) printf("      ¢Ê¢Ê");
				else if (h == 6) printf("      ¢É¢É¢É");
				else if (h == 7) printf("      ¢Ì¢Ì¢Ì");
			}
			if (i == 5 && j == 10) {
				if (h == 2) printf(" 	   ¢Ã");
				else if (h == 3) printf("	  ¢È¢È");
				else if (h == 4) printf("      ¢Ë¢Ë");
				else if (h == 5) printf("        ¢Ê¢Ê");
				else if (h == 6) printf("      ¢É");
				else if (h == 7) printf("          ¢Ì");
			}
			if (i == 8 && j == 10) printf("       next");
			if (i == 10 && j == 10) {
				if (queue == 1) printf("	¢Ç¢Ç¢Ç¢Ç");
				else if (queue == 2) printf("      ¢Ã¢Ã¢Ã");
				else if (queue == 3) printf("	  ¢È¢È");
				else if (queue == 4) printf(" 	   ¢Ë¢Ë");
				else if (queue == 5) printf("      ¢Ê¢Ê");
				else if (queue == 6) printf("      ¢É¢É¢É");
				else if (queue == 7) printf("      ¢Ì¢Ì¢Ì");
			}
			if (i == 11 && j == 10) {
				if (queue == 2) printf(" 	   ¢Ã");
				else if (queue == 3) printf("	  ¢È¢È");
				else if (queue == 4) printf("      ¢Ë¢Ë");
				else if (queue == 5) printf(" 	   ¢Ê¢Ê");
				else if (queue == 6) printf("      ¢É");
				else if (queue == 7) printf("          ¢Ì");
			}
			if (i == 14 && j == 10) {
				printf("     line : %d", stage);
			}
		}
		printf("\n");

	}
	LeaveCriticalSection(&cs);
}

void create_I() {

	spin = 0;
	end = 0; 
	board[1][4] = 1;
	board[1][5] = 1;
	board[1][6] = 1;
	board[1][7] = 1;

}

void create_T() {

	spin = 0;
	end = 0;
	board[1][4] = 2;
	board[1][5] = 2;
	board[1][6] = 2;
	board[2][5] = 2;

}

void create_O() {

	spin = 0;
	end = 0;
	board[1][4] = 3;
	board[1][5] = 3;
	board[2][4] = 3;
	board[2][5] = 3;

}

void create_S() {

	spin = 0;
	end = 0;
	board[1][5] = 4;
	board[1][6] = 4;
	board[2][4] = 4;
	board[2][5] = 4;

}

void create_Z() {

	spin = 0;
	end = 0;
	board[1][5] = 5;
	board[1][6] = 5;
	board[2][6] = 5;
	board[2][7] = 5;

}

void create_L() {

	spin = 0;
	end = 0;
	board[1][5] = 6;
	board[1][6] = 6;
	board[1][7] = 6;
	board[2][5] = 6;

}

void create_J() {

	spin = 0;
	end = 0;
	board[1][5] = 7;
	board[1][6] = 7;
	board[1][7] = 7;
	board[2][7] = 7;

}

void down(int d) {

	int count = 0;
	int c = 0;
	int a1 = 0;
	int b1 = 0;
	int a2 = 0;
	int b2 = 0;
	int a3 = 0;
	int b3 = 0;
	int a4 = 0;
	int b4 = 0;
	int i, j;
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == d) {
				board[i][j] = 0;
				a1 = i + 1;
				b1 = j;

				count++;
				c++;
				break;
			}
		}
		if (c == 1) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == d) {
				board[i][j] = 0;
				a2 = i + 1;
				b2 = j;

				count++;
				c++;
				break;
			}
		}
		if (c == 2) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == d) {
				board[i][j] = 0;
				a3 = i + 1;
				b3 = j;

				count++;
				c++;
				break;
			}
		}
		if (c == 3) break;
	}
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == d) {
				board[i][j] = 0;
				a4 = i + 1;
				b4 = j;
				count++;
				c++;
				break;
			}
		}
		if (c == 4) break;
	}

	if (board[a1][b1] == 0 && board[a2][b2] == 0 && board[a3][b3] == 0 && board[a4][b4] == 0 && count == 4) {

		board[a1][b1] = d;
		board[a2][b2] = d;
		board[a3][b3] = d;
		board[a4][b4] = d;

	}
	else {

		board[a1 - 1][b1] = 11;
		board[a2 - 1][b2] = 11;
		board[a3 - 1][b3] = 11;
		board[a4 - 1][b4] = 11;
		h_d_count++;
		line_clear();
		for (int i = 4; i < 8; i++) {
			if (board[1][i] == 11) {
				end_c++;
				return;
			}
		}
		next_queue();
	}

}

void spin_I() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (spin % 4 == 0) {
				if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1) {
					if (board[i][j + 3] == 1 && board[i + 1][j + 3] == 0 && board[i + 2][j + 3] == 0 && board[i + 3][j + 3] == 0) {
						printf("Dd");
						board[i][j] = 0;
						board[i][j + 1] = 0;
						board[i][j + 2] = 0;
						board[i][j + 3] = 0;
						board[i][j + 3] = 1;
						board[i + 1][j + 3] = 1;
						board[i + 2][j + 3] = 1;
						board[i + 3][j + 3] = 1;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 1) {
				if (board[i][j + 3] == 1 && board[i + 1][j + 3] == 1 && board[i + 2][j + 3] == 1 && board[i + 3][j + 3] == 1) {
					if (board[i + 3][j] == 0 && board[i + 3][j + 1] == 0 && board[i + 3][j + 2] == 0 && board[i + 3][j + 3] == 1) {
						board[i][j + 3] = 0;
						board[i + 1][j + 3] = 0;
						board[i + 2][j + 3] = 0;
						board[i + 3][j + 3] = 0;
						board[i + 3][j] = 1;
						board[i + 3][j + 1] = 1;
						board[i + 3][j + 2] = 1;
						board[i + 3][j + 3] = 1;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 2) {
				if (board[i + 3][j] == 1 && board[i + 3][j + 1] == 1 && board[i + 3][j + 2] == 1 && board[i + 3][j + 3] == 1) {
					if (board[i][j] == 0 && board[i + 1][j] == 0 && board[i + 2][j] == 0 && board[i + 3][j] == 1) {
						board[i + 3][j] = 0;
						board[i + 3][j + 1] = 0;
						board[i + 3][j + 2] = 0;
						board[i + 3][j + 3] = 0;
						board[i][j] = 1;
						board[i + 1][j] = 1;
						board[i + 2][j] = 1;
						board[i + 3][j] = 1;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 3) {
				if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1) {
					if (board[i][j] == 1 && board[i][j + 1] == 0 && board[i][j + 2] == 0 && board[i][j + 3] == 0) {
						board[i][j] = 0;
						board[i + 1][j] = 0;
						board[i + 2][j] = 0;
						board[i + 3][j] = 0;
						board[i][j] = 1;
						board[i][j + 1] = 1;
						board[i][j + 2] = 1;
						board[i][j + 3] = 1;
						spin++;
						return;
					}
				}
			}
			if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j - 2] == 1 && board[i][j - 1] == 1) {
				if (board[i][j] == 1 && board[i + 1][j] == 0 && board[i + 2][j] == 0 && board[i - 1][j] == 0) {
					board[i][j + 1] = 0;
					board[i][j - 2] = 0;
					board[i][j - 1] = 0;
					board[i][j] = 1;
					board[i + 1][j] = 1;
					board[i + 2][j] = 1;
					board[i - 1][j] = 1;
					spin++;
					return;
				}
			}
			if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i - 1][j] == 1) {
				if (board[i][j] == 1 && board[i][j + 1] == 0 && board[i][j - 2] == 0 && board[i][j - 1] == 0) {
					board[i + 1][j] = 0;
					board[i + 2][j ] = 0;
					board[i  - 1][j] = 0;
					board[i][j] = 1;
					board[i][j + 1] = 1;
					board[i ][j- 2] = 1;
					board[i  ][j- 1 ] = 1;
					spin++;
					return;
				}
			} 
		}
	}
}

void spin_T() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {

			if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j - 1] == 2 && board[i + 1][j] == 2) {
				if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i - 1][j] == 0 && board[i + 1][j] == 2) {
					board[i][j - 1] = 0;
					board[i][j] = 2;
					board[i][j + 1] = 2;
					board[i - 1][j] = 2;
					board[i + 1][j] = 2;
					spin++;

				}
			}


			else if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i - 1][j] == 2 && board[i + 1][j] == 2) {
				if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i - 1][j] == 2 && board[i][j - 1] == 0) {
					board[i + 1][j] = 0;
					board[i][j] = 2;
					board[i][j + 1] = 2;
					board[i][j - 1] = 2;
					board[i - 1][j] = 2;
					spin++;

				}
			}


			else if (board[i][j] == 2 && board[i - 1][j] == 2 && board[i][j + 1] == 2 && board[i][j - 1] == 2) {
				if (board[i][j] == 2 && board[i + 1][j] == 0 && board[i][j - 1] == 2 && board[i - 1][j] == 2) {
					board[i][j + 1] = 0;
					board[i][j] = 2;
					board[i + 1][j] = 2;
					board[i - 1][j] = 2;
					board[i][j - 1] = 2;
					spin++;

				}
			}


			else if (board[i][j] == 2 && board[i + 1][j] == 2 && board[i - 1][j] == 2 && board[i][j - 1] == 2) {
				if (board[i][j] == 2 && board[i + 1][j] == 2 && board[i][j + 1] == 0 && board[i][j - 1] == 2) {
					board[i - 1][j] = 0;
					board[i][j] = 2;
					board[i + 1][j] = 2;
					board[i][j + 1] = 2;
					board[i][j - 1] = 2;
					spin++;

				}
			}

		}
	}
}

void spin_Z() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (spin % 4 == 0) {
				if (board[i][j] == 5 && board[i][j - 1] == 5 && board[i + 1][j] == 5 && board[i + 1][j + 1] == 5) {
					if (board[i][j] == 5 && board[i ][j - 1] == 5 && board[i-1][j] == 0 && board[i + 1][j - 1] == 0) {
						board[i + 1][j] = 0;
						board[i + 1][j + 1] = 0;
						board[i][j] = 5;
						board[i ][j - 1] = 5;
						board[i-1][j] = 5;
						board[i + 1][j - 1] = 5;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 1) {
				if (board[i][j] == 5 && board[i][j - 1] == 5 && board[i - 1][j] == 5 && board[i + 1][j - 1] == 5) {
					if (board[i][j] == 5 && board[i - 1][j ] == 5 && board[i ][j + 1] == 0 && board[i - 1][j - 1] == 0) {
						board[i ][j- 1] = 0;
						board[i + 1][j - 1] = 0;
						board[i][j] = 5;
						board[i- 1][j ] = 5;
						board[i ][j+ 1] = 5;
						board[i - 1][j - 1] = 5;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 2) {
				if (board[i][j] == 5 && board[i - 1][j] == 5 && board[i][j + 1] == 5 && board[i - 1][j - 1] == 5) {
					if (board[i][j] == 5 && board[i -1][j] == 5 && board[i-1][j + 1] == 0 && board[i + 1][j] == 0) {
						board[i-1][j] = 0;
						board[i - 1][j - 1] = 0;
						board[i][j] = 5;
						board[i + 1][j] = 5;
						board[i-1][j + 1] = 5;
						board[i + 1][j] = 5;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 3) {
				if (board[i][j] == 5 && board[i ][j+1] == 5 && board[i - 1][j + 1] == 5 && board[i + 1][j] == 5) {
					if (board[i][j] == 5 && board[i][j - 1] == 0 && board[i + 1][j] == 5 && board[i + 1][j +1] == 0) {
						board[i][j+1] = 0;
						board[i -1][j+1] = 0;
						board[i][j] = 5;
						board[i + 1][j] = 5;
						board[i+1][j + 1] = 5;
						board[i][j - 1] = 5;
						spin++;
						return;
					}
				}
			}
		}
	}
}

void spin_O() {

	return;
}

void spin_S() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (spin % 4 == 0) {
				if (board[i][j] == 4 && board[i][j + 1] == 4 && board[i + 1][j] == 4 && board[i + 1][j - 1] == 4) {
					if (board[i][j] == 4 && board[i + 1][j] == 4 && board[i][j - 1] == 0 && board[i - 1][j - 1] == 0) {
						board[i][j + 1] = 0;
						board[i + 1][j - 1] = 0;
						board[i][j] = 4;
						board[i + 1][j] = 4;
						board[i][j - 1] = 4;
						board[i - 1][j - 1] = 4;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 1) {
				if (board[i][j] == 4 && board[i + 1][j] == 4 && board[i][j - 1] == 4 && board[i - 1][j - 1] == 4) {
					if (board[i][j] == 4 && board[i][j - 1] == 4 && board[i - 1][j] == 0 && board[i - 1][j + 1] == 0) {
						board[i + 1][j] = 0;
						board[i - 1][j - 1] = 0;
						board[i][j] = 4;
						board[i][j - 1] = 4;
						board[i - 1][j] = 4;
						board[i - 1][j + 1] = 4;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 2) {
				if (board[i][j] == 4 && board[i][j - 1] == 4 && board[i - 1][j] == 4 && board[i - 1][j + 1] == 4) {
					if (board[i][j] == 4 && board[i - 1][j] == 4 && board[i][j + 1] == 0 && board[i + 1][j + 1] == 0) {
						board[i][j - 1] = 0;
						board[i - 1][j + 1] = 0;
						board[i][j] = 4;
						board[i - 1][j] = 4;
						board[i][j + 1] = 4;
						board[i + 1][j + 1] = 4;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 3) {
				if (board[i][j] == 4 && board[i - 1][j] == 4 && board[i][j + 1] == 4 && board[i + 1][j + 1] == 4) {
					if (board[i][j] == 4 && board[i + 1][j] == 0 && board[i][j + 1] == 4 && board[i + 1][j - 1] == 0) {
						board[i + 1][j + 1] = 0;
						board[i - 1][j] = 0;
						board[i][j] = 4;
						board[i + 1][j] = 4;
						board[i][j + 1] = 4;
						board[i + 1][j - 1] = 4;
						spin++;
						return;
					}
				}
			}
		}
	}
}

void spin_L() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (spin % 4 == 0) {
				if (board[i][j] == 6 && board[i][j + 1] == 6 && board[i][j - 1] == 6 && board[i + 1][j - 1] == 6) {
					if (board[i][j] == 6 && board[i + 1][j] == 0 && board[i- 1][j ] == 0 && board[i - 1][j - 1] == 0) {
						board[i][j + 1] = 0;
						board[i][j - 1] = 0;
						board[i + 1][j - 1] = 0;
						board[i][j] = 6;
						board[i + 1][j] = 6;
						board[i- 1][j ] = 6;
						board[i - 1][j - 1] = 6;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 1) {
				if (board[i][j] == 6 && board[i + 1][j] == 6 && board[i - 1][j] == 6 && board[i - 1][j - 1] == 6) {
					if (board[i][j] == 6 && board[i][j - 1] == 0 && board[i ][j+1] == 0 && board[i - 1][j + 1] == 0) {
						board[i + 1][j] = 0;
						board[i - 1][j] = 0;
						board[i - 1][j - 1] = 0;
						board[i][j] = 6;
						board[i][j - 1] = 6;
						board[i ][j+ 1] = 6;
						board[i - 1][j + 1] = 6;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 2) {
				if (board[i][j] == 6 && board[i][j - 1] == 6 && board[i][j + 1] == 6 && board[i - 1][j + 1] == 6) {
					if (board[i][j] == 6 && board[i - 1][j] == 0 && board[i+ 1][j ] == 0 && board[i + 1][j + 1] == 0) {
						board[i][j - 1] = 0;
						board[i][j + 1] = 0;
						board[i - 1][j + 1] = 0;
						board[i][j] = 6;
						board[i - 1][j] = 6;
						board[i + 1][j] = 6;
						board[i + 1][j + 1] = 6;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 3) {
				if (board[i][j] == 6 && board[i - 1][j] == 6 && board[i + 1][j] == 6 && board[i + 1][j + 1] == 6) {
					if (board[i][j] == 6 && board[i ][j+ 1] == 0 && board[i][j - 1] == 0 && board[i + 1][j - 1] == 0) {
						board[i + 1][j] = 0;
						board[i - 1][j] = 0;
						board[i + 1][j+1] = 0;
						board[i][j] = 6;
						board[i ][j+ 1] = 6;
						board[i][j - 1] = 6;
						board[i + 1][j - 1] = 6;
						spin++;
						return;
					}
				}
			}
		}
	}
}

void spin_J() {

	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 11; j++) {
			if (spin % 4 == 0) {
				if (board[i][j] == 7 && board[i][j + 1] == 7 && board[i][j - 1] == 7 && board[i + 1][j + 1] == 7) {
					if (board[i][j] == 7 && board[i + 1][j] == 0 && board[i - 1][j] == 0 && board[i + 1][j -  1] == 0) {
						board[i][j + 1] = 0;
						board[i][j - 1] = 0;
						board[i + 1][j + 1] = 0;
						board[i][j] = 7;
						board[i + 1][j] = 7;
						board[i - 1][j] = 7;
						board[i + 1][j - 1] = 7;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 1) {
				if (board[i][j] == 7 && board[i + 1][j] == 7 && board[i - 1][j] == 7 && board[i + 1][j - 1] == 7) {
					if (board[i][j] == 7 && board[i][j - 1] == 0 && board[i][j + 1] == 0 && board[i - 1][j - 1] == 0) {
						board[i + 1][j] = 0;
						board[i - 1][j] = 0;
						board[i + 1][j - 1] = 0;
						board[i][j] = 7;
						board[i][j - 1] = 7;
						board[i][j + 1] = 7;
						board[i - 1][j - 1] = 7;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 2) {
				if (board[i][j] == 7 && board[i][j - 1] == 7 && board[i][j + 1] == 7 && board[i - 1][j - 1] == 7) {
					if (board[i][j] == 7 && board[i - 1][j] == 0 && board[i + 1][j] == 0 && board[i - 1][j + 1] == 0) {
						board[i][j - 1] = 0;
						board[i][j + 1] = 0;
						board[i - 1][j - 1] = 0;
						board[i][j] = 7;
						board[i - 1][j] = 7;
						board[i + 1][j] = 7;
						board[i - 1][j + 1] = 7;
						spin++;
						return;
					}
				}
			}
			else if (spin % 4 == 3) {
				if (board[i][j] == 7 && board[i - 1][j] == 7 && board[i + 1][j] == 7 && board[i - 1][j + 1] == 7) {
					if (board[i][j] == 7 && board[i][j + 1] == 0 && board[i][j - 1] == 0 && board[i + 1][j + 1] == 0) {
						board[i + 1][j] = 0;
						board[i - 1][j] = 0;
						board[i - 1][j + 1] = 0;
						board[i][j] = 7;
						board[i][j + 1] = 7;
						board[i][j - 1] = 7;
						board[i + 1][j + 1] = 7;
						spin++;
						return;
					}
				}
			}
		}
	}
}

void move_right(int m_r) {


	int count = 0;
	int c = 0;
	int a1 = 0;
	int b1 = 0;
	int a2 = 0;
	int b2 = 0;
	int a3 = 0;
	int b3 = 0;
	int a4 = 0;
	int b4 = 0;
	int i, j;
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_r) {
				board[i][j] = 0;
				a1 = i;
				b1 = j + 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 1) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_r) {
				board[i][j] = 0;
				a2 = i;
				b2 = j + 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 2) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_r) {
				board[i][j] = 0;
				a3 = i;
				b3 = j + 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 3) break;
	}
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_r) {
				board[i][j] = 0;
				a4 = i;
				b4 = j + 1;
				count++;
				c++;
				break;
			}
		}
		if (c == 4) break;
	}

	if (board[a1][b1] == 0 && board[a2][b2] == 0 && board[a3][b3] == 0 && board[a4][b4] == 0 && count == 4) {

		board[a1][b1] = m_r;
		board[a2][b2] = m_r;
		board[a3][b3] = m_r;
		board[a4][b4] = m_r;

	}
	else {

		board[a1][b1 - 1] = m_r;
		board[a2][b2 - 1] = m_r;
		board[a3][b3 - 1] = m_r;
		board[a4][b4 - 1] = m_r;

	}

}

void move_left(int m_l) {

	int count = 0;
	int c = 0;
	int a1 = 0;
	int b1 = 0;
	int a2 = 0;
	int b2 = 0;
	int a3 = 0;
	int b3 = 0;
	int a4 = 0;
	int b4 = 0;
	int i, j;
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_l) {
				board[i][j] = 0;
				a1 = i;
				b1 = j - 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 1) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_l) {
				board[i][j] = 0;
				a2 = i;
				b2 = j - 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 2) break;
	}

	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_l) {
				board[i][j] = 0;
				a3 = i;
				b3 = j - 1;

				count++;
				c++;
				break;
			}
		}
		if (c == 3) break;
	}
	for (i = 1; i < 21; i++) {
		for (j = 1; j < 11; j++) {
			if (board[i][j] == m_l) {
				board[i][j] = 0;
				a4 = i;
				b4 = j - 1;
				count++;
				c++;
				break;
			}
		}
		if (c == 4) break;
	}

	if (board[a1][b1] == 0 && board[a2][b2] == 0 && board[a3][b3] == 0 && board[a4][b4] == 0 && count == 4) {

		board[a1][b1] = m_l;
		board[a2][b2] = m_l;
		board[a3][b3] = m_l;
		board[a4][b4] = m_l;
	}
	else {

		board[a1][b1 + 1] = m_l;
		board[a2][b2 + 1] = m_l;
		board[a3][b3 + 1] = m_l;
		board[a4][b4 + 1] = m_l;

	}

}

int main(){
	
	while (1) {

		SetConsoleTitle(TEXT("[TETRIS]"));
		
		setWindowConsole(50, 29);
		setFontSize(15, 30);
		cursorHide();
		
		for (int i = 0; i < 22; i++) {
			for (int j = 0; j < 12; j++) {
				board[i][j] = 0;
			}
		}
		queue = 0;
		q_count = 0;

		random_board[0] = 1;
		random_board[1] = 2;
		random_board[2] = 3;
		random_board[3] = 4;
		random_board[4] = 5;
		random_board[5] = 6;
		random_board[6] = 7;

		r_next = 0;
		r_count = 0;

		end = 0;
		spin = 0;
		h = 0;
		h_count = 0;
		h_d_count = 0;

		end_c = 0;

		restart_count = 0;

		stage = 0;

		InitializeCriticalSection(&cs);

		for (int i = 0; i < 12; i++) {
			board[0][i] = 20;
		}
		for (int i = 0; i < 12; i++) {
			board[20][i] = 20;
		}
		for (int i = 0; i < 21; i++) {
			board[i][0] = 20;
		}
		for (int i = 0; i < 21; i++) {
			board[i][11] = 20;
		}

		next_queue();

		_beginthreadex(NULL, 0, Thread_down, 0, 0, NULL);

		print_board();

		while (1) {

			endcount = 0;

			control();

			print_board();

			if (restart_count == 1) {
				endcount++;
				break;
			}

			else if (end_c > 0) {
				printf("             The End");

				endcount++;

				while (1) {
					int end = _getch();

					if (end == 114) {

						break;
					}
				}

				break;

			}
		}


		DeleteCriticalSection(&cs);
	}
}

