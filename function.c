#include "function.h"
#include "stockmarket.h"

void setConsole() {//�ܼ�â ����
	system("mode con:cols=150lines=40");//col:110 + margin 20*2
	system("color f0");
	SetConsoleTitle(TEXT("�� �� �� ��:�١��ָ��̵��� ������ �����͡١�"));
}

void setTextColor(int colorNum) {//�ؽ�Ʈ ������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240 + colorNum);//240:white+black
	//����:0, �Ķ�(d):1, �ʷ�(d):2, �ϴ�(d):3, ����(d):4, ����(d):5, ���(d):6, ȸ��:7
	//ȸ��(d):8, �Ķ�:9, �ʷ�:10, �ϴ�:11, ����:12, ����:13, ���:14, �Ͼ�:15
}

void gotoxy(int x, int y) {//Ŀ�� �̵� ���� �Լ�
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show)//Ŀ�������
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void makeBox(int fromX, int fromY, int length, int height) {//�ڽ������
	int toX = fromX + length;
	int toY = fromY + height;
	gotoxy(fromX, fromY);
	printf("��");
	gotoxy(fromX, toY);
	printf("��");
	gotoxy(toX, fromY);
	printf("��");
	gotoxy(toX, toY);
	printf("��");
	for (int i = 1; i < length; i++) {
		gotoxy(fromX + i, fromY);
		printf("��");
		gotoxy(fromX + i, toY);
		printf("��");
	}
	for (int j = 1; j < height; j++) {
		gotoxy(fromX, fromY + j);
		printf("��");
		gotoxy(toX, fromY + j);
		printf("��");
	}
}

void makeTable(int fromX, int fromY, int length, int height, int col, int row) {//(����x��ǥ, ����y��ǥ, ��ü ����, ��ü ����, ���� ����, ���� ����)
	int toX = fromX + length;
	int toY = fromY + height;
	int colSize = length / col;//colSize = ���� ����
	int rowSize = height / row;//rowSize = ���� ����
	//�ܰ�
	gotoxy(fromX, fromY);
	printf("��");
	gotoxy(fromX, toY);
	printf("��");
	gotoxy(toX, fromY);
	printf("��");
	gotoxy(toX, toY);
	printf("��");
	gotoxy(fromX, fromY + (3 * rowSize));
	printf("��");
	gotoxy(toX, fromY + (3 * rowSize));
	printf("��");
	for (int i = 1; i < length; i++) {//���μ�
		if (i % colSize != 0) {
			gotoxy(fromX + i, fromY);//���
			printf("��");
			gotoxy(fromX + i, toY);//�ϴ�
			printf("��");
			gotoxy(fromX + i, fromY + (2 * rowSize));//���
			printf("��");
		}
		else if (i % colSize == 0) {
			gotoxy(fromX + i, fromY);//���
			printf("��");
			gotoxy(fromX + i, toY);//�ϴ�
			printf("��");
			gotoxy(fromX + i, fromY + (2 * rowSize));//���
			printf("��");
		}
		for (int j = 1; j < row - 1; j++) {
			gotoxy(fromX + i, fromY + (2 * rowSize) + (j * rowSize));
			printf("��");
		}
	}
	for (int j = 1; j < height; j++) {//���μ�
		if (j % rowSize != 0) {
			gotoxy(fromX, fromY + j);
			printf("��");
			gotoxy(toX, fromY + j);
			printf("��");
		}
		else if (j >= (2 * rowSize) && j % rowSize == 0) {
			gotoxy(fromX, fromY + j);
			printf("��");
			gotoxy(toX, fromY + j);
			printf("��");
		}
		else {
			gotoxy(fromX, fromY + j);
			printf("��");
			gotoxy(toX, fromY + j);
			printf("��");
		}
		for (int k = 1; k < col; k++) {
			if (j < (2 * rowSize)) {
				gotoxy(fromX + (k * colSize), fromY + j);
				printf("��");
			}
			else if (j > (2 * rowSize)) {
				gotoxy(fromX + (k * colSize), fromY + j);
				printf("��");
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