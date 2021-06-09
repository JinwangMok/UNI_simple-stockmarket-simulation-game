#pragma once
#define UP 72
#define DOWN 80
#define ENTER 13
#define _CRT_SECURE_NO_WARNINGS  //fopen �� ��������

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#pragma warning(disable:4996)  // fopen �� ��������

void setConsole();
void setTextColor(int colorNum);
void gotoxy(int x, int y);
void CursorView(char show);
void makeBox(int fromX, int fromY, int length, int height);
void makeTable(int fromX, int fromY, int length, int height, int col, int row);
void setDate(int* targetDay, int* targetMonth);

//�ֽ� ����ü
typedef struct {
   char name[20];//�̸�
   int count;//�����ֽļ� -> �÷��̾ ������ �ֽ���!
   int pricePerStock;//�ִ� ���簡
}Stock;