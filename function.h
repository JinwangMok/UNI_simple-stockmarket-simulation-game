#pragma once
#define UP 72
#define DOWN 80
#define ENTER 13
#define _CRT_SECURE_NO_WARNINGS  //fopen 을 쓰기위함

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#pragma warning(disable:4996)  // fopen 을 쓰기위함

void setConsole();
void setTextColor(int colorNum);
void gotoxy(int x, int y);
void CursorView(char show);
void makeBox(int fromX, int fromY, int length, int height);
void makeTable(int fromX, int fromY, int length, int height, int col, int row);
void setDate(int* targetDay, int* targetMonth);

//주식 구조체
typedef struct {
   char name[20];//이름
   int count;//보유주식수 -> 플레이어가 보유한 주식임!
   int pricePerStock;//주당 현재가
}Stock;