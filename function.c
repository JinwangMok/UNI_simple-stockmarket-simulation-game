#include "function.h"
#include "stockmarket.h"

void setConsole() {//콘솔창 제어
	system("mode con:cols=150lines=40");//col:110 + margin 20*2
	system("color f0");
	SetConsoleTitle(TEXT("주 주 랜 드:☆★주린이들의 안전한 놀이터☆★"));
}

void setTextColor(int colorNum) {//텍스트 색상설정
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240 + colorNum);//240:white+black
	//검정:0, 파랑(d):1, 초록(d):2, 하늘(d):3, 빨강(d):4, 보라(d):5, 노랑(d):6, 회색:7
	//회색(d):8, 파랑:9, 초록:10, 하늘:11, 빨강:12, 보라:13, 노랑:14, 하양:15
}

void gotoxy(int x, int y) {//커서 이동 제어 함수
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void makeBox(int fromX, int fromY, int length, int height) {//박스만들기
	int toX = fromX + length;
	int toY = fromY + height;
	gotoxy(fromX, fromY);
	printf("┏");
	gotoxy(fromX, toY);
	printf("┗");
	gotoxy(toX, fromY);
	printf("┓");
	gotoxy(toX, toY);
	printf("┛");
	for (int i = 1; i < length; i++) {
		gotoxy(fromX + i, fromY);
		printf("━");
		gotoxy(fromX + i, toY);
		printf("━");
	}
	for (int j = 1; j < height; j++) {
		gotoxy(fromX, fromY + j);
		printf("┃");
		gotoxy(toX, fromY + j);
		printf("┃");
	}
}

void makeTable(int fromX, int fromY, int length, int height, int col, int row) {//(시작x좌표, 시작y좌표, 전체 길이, 전체 높이, 열의 개수, 행의 개수)
	int toX = fromX + length;
	int toY = fromY + height;
	int colSize = length / col;//colSize = 셀의 가로
	int rowSize = height / row;//rowSize = 셀의 세로
	//외곽
	gotoxy(fromX, fromY);
	printf("┏");
	gotoxy(fromX, toY);
	printf("┗");
	gotoxy(toX, fromY);
	printf("┓");
	gotoxy(toX, toY);
	printf("┛");
	gotoxy(fromX, fromY + (3 * rowSize));
	printf("┣");
	gotoxy(toX, fromY + (3 * rowSize));
	printf("┫");
	for (int i = 1; i < length; i++) {//가로선
		if (i % colSize != 0) {
			gotoxy(fromX + i, fromY);//상단
			printf("━");
			gotoxy(fromX + i, toY);//하단
			printf("━");
			gotoxy(fromX + i, fromY + (2 * rowSize));//헤더
			printf("━");
		}
		else if (i % colSize == 0) {
			gotoxy(fromX + i, fromY);//상단
			printf("┳");
			gotoxy(fromX + i, toY);//하단
			printf("┷");
			gotoxy(fromX + i, fromY + (2 * rowSize));//헤더
			printf("╇");
		}
		for (int j = 1; j < row - 1; j++) {
			gotoxy(fromX + i, fromY + (2 * rowSize) + (j * rowSize));
			printf("─");
		}
	}
	for (int j = 1; j < height; j++) {//세로선
		if (j % rowSize != 0) {
			gotoxy(fromX, fromY + j);
			printf("┃");
			gotoxy(toX, fromY + j);
			printf("┃");
		}
		else if (j >= (2 * rowSize) && j % rowSize == 0) {
			gotoxy(fromX, fromY + j);
			printf("┠");
			gotoxy(toX, fromY + j);
			printf("┨");
		}
		else {
			gotoxy(fromX, fromY + j);
			printf("┃");
			gotoxy(toX, fromY + j);
			printf("┃");
		}
		for (int k = 1; k < col; k++) {
			if (j < (2 * rowSize)) {
				gotoxy(fromX + (k * colSize), fromY + j);
				printf("┃");
			}
			else if (j > (2 * rowSize)) {
				gotoxy(fromX + (k * colSize), fromY + j);
				printf("│");
			}
		}
	}
}

void setDate(int* targetDay, int* targetMonth) {
	while (*targetDay > 31) {
		switch (*targetMonth) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (*targetDay > 31) {
				*targetMonth += 1;
				*targetDay -= 31;
			}
			break;
		case 4: case 6: case 9: case 11:
			if (*targetDay > 30) {
				*targetMonth += 1;
				*targetDay -=  30 + 1;
			}
			break;
		case 2:
			if (*targetDay > 28) {
				*targetMonth += 1;
				*targetDay -= 28 + 1;
			}
			break;
		default:
			break;
		}
	}
}