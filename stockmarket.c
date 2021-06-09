#include "function.h"
#include "stockmarket.h"

void intro(int* targetDate, double* targetMoney) { 
	gotoxy(25, 9);
	printf("            #########           #########          ########    #  #          ########");
	gotoxy(25, 10);
	printf("                #                   #                     #    #  #          #");
	gotoxy(25, 11);
	printf("               ##                  ##                     #    #  #          #");
	gotoxy(25, 12);
	printf("              #  #                #  #             ########    ####          ########");
	gotoxy(25, 13);
	printf("             #    #              #    #            #           #  #");
	gotoxy(25, 14);
	printf("          ############        ############         #           #  #         ###########");
	gotoxy(25, 15);
	printf("               #                   #               ########    #  #");
	gotoxy(25, 16);
	printf("               #                   #");
	gotoxy(25, 17);
	printf("               #                   #                    ##");
	gotoxy(25, 18);
	printf("                                                        ##");
	gotoxy(25, 19);
	printf("                                                        #############");
	gotoxy(56, 26);
	printf("☆★주린이들의 안전한 놀이터☆★");
	Sleep(3000);
	system("cls");

	CursorView(1);
	gotoxy(57, 4);
	printf("주주랜드에 오신 것을 환영합니다><");

	gotoxy(50, 15);
	printf("목표 수익을 입력해주세요 :            원\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s("%lf", targetMoney);//&*targetMoney
	gotoxy(50, 20);
	printf("목표 기간 입력해주세요 :     일\b\b\b\b\b\b");
	scanf_s("%d", targetDate);
	CursorView(0);
}

void setDashboard(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double* targetMoney, double* money, double* totalPL) {
	//각 포인터로 받은 변수들을 사용하면되고, (target)month랑 (target)day는 '1~12월', '1~31'일 형식이야!
	//예) printf("%d", day); 이런식으로 쓰고 싶으면, printf("%d", *day); 이렇게 쓰면됨!
	system("cls");
	makeBox(20, 2, 110, 35);
	gotoxy(65, 5);
	printf("D A S H   B O A R D");

	makeBox(30, 8, 90, 14);
	gotoxy(32, 9);
	printf("[2021년 %02d월 %02d일]", *month, *day);
	gotoxy(92, 9);
	printf("목표 날짜 : 2021년 %02d월 %02d일", *targetMonth, *targetDay);
	gotoxy(92, 10);
	printf("목표 금액 : %.lf원", *targetMoney);
	gotoxy(32, 11);
	printf("[보유주식]");
	int temp = 0;
	double totalStock = 0;
	for (int i = 0; i < 10; i++) {
		if (temp < 5) {
			if ((ps + i)->count > 0) {
				gotoxy(36, 13 + temp);
				printf("%8s %d주 전일종가 %d원", (ps + i)->name, (ps + i)->count, (ps + i)->pricePerStock);
				temp++;
			}
		}
		else {
			if ((ps + i)->count > 0) {
				gotoxy(70, 13 + temp);
				printf("%8s %d주 전일종가 %d원", (ps + i)->name, (ps + i)->count, (ps + i)->pricePerStock);
				temp++;
			}
		}
		totalStock += (double)(ps + i)->pricePerStock * (ps + i)->count;
	}
	if (temp == 0) {
		gotoxy(65, 14);
		printf("- 보유 주식 없음 -");
	}

	gotoxy(92, 19);
	printf("★보유 자산 : %.lf원", totalStock + *money);
	gotoxy(92, 20);
	printf("▷보유 현금 : %.lf원", *money);
	gotoxy(92, 21);
	printf("▷보유 주식 : %.lf원", totalStock);

	gotoxy(32, 21);
	printf("현재까지 총 손익 : %.lf원", *totalPL);

	gotoxy(64, 27);
	printf("$주식시장 입장하기$");

	gotoxy(68, 33);
	printf("$종료하기$");
}

int choiceAction(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double* targetMoney, double* money, double* totalPL) {//메인메뉴 커서제어
	int choice = 1;
	int loop = 1;
	char key;
	gotoxy(62, 27);
	printf(">");

	while (1) {
		key = _getch();
		if (key == UP) {
			setDashboard(ps, targetMonth, targetDay, month, day, targetMoney, money, totalPL);
			gotoxy(62, 27);
			printf(">");
			choice = 1;
		}
		else if (key == DOWN) {
			setDashboard(ps, targetMonth, targetDay, month, day, targetMoney, money, totalPL);
			gotoxy(66, 33);
			printf(">");
			choice = 2;
		}
		else if (key == ENTER) {
			return choice;
		}
		else {
			continue;
		}
	}
}

//console size = 150 x 40
void setBoard(Stock* ps) {
	//캘린더
	makeBox(0, 0, 20, 7);
	//보유 주식 및 자산란
	makeBox(90, 0, 58, 7);
	gotoxy(120, 0);
	printf("┳");
	gotoxy(120, 7);
	printf("┻");
	for (int i = 1; i < 7; i++) {
		gotoxy(120, i);
		printf("┃");
	}
	//전체 주식 현황표
	makeTable(10, 8, 110, 22, 11, 10);
	//주식이름
	for (int i = 0; i < 10; i++) {
		gotoxy(21 + (i * 10), 10);
		printf(" %-8s", (ps + i)->name);
	}
	//현재가 열
	for (int i = 0; i < 9; i++) {
		gotoxy(13, 13 + (i * 2));
		if (i == 4) {
			setTextColor(12);
			printf("현재가");
			setTextColor(0);
		}
		else if (i < 4) {
			printf("  %d", 400 + (-100 * i));
		}
		else {
			printf(" %d", 400 + (-100 * i));
		}
	}
	//타이틀
	gotoxy(30,1);
	printf("//////////  ///   /////////////     /////     ///");
	gotoxy(30, 2);
	printf("      ///  ///        ////       ///    ///  ///");
	gotoxy(30, 3);
	printf("     ///  //////  ////   ////   ///    ///  //////");
	gotoxy(30, 4);
	printf("    ///  ///                   ///   ///   ///");
	gotoxy(30, 5);
	printf("   ///  ///    //////////////   /////     ///");
	//광고 박스
	makeBox(30, 32, 90, 5);
	//매수
	makeBox(124, 13, 19, 4);
	gotoxy(129, 15);
	setTextColor(12);
	printf("%10s", "  매  수  ");
	setTextColor(0);

	//매도
	makeBox(124, 20, 19, 4);
	gotoxy(129, 22);
	setTextColor(9);
	printf("%10s", "  매  도  ");
	setTextColor(0);
	//커서
	gotoxy(129, 15);
	printf(">");
}

void repeatStockmarket(Stock* ps, int* month, int* day, int* time, double* money, double* todayAS, int* eventVar) {//ps->name으로 접근
	setStock(ps);//주식정보표시
	setCalendar(month, day, time);//날짜, 시간정보표시
	setStockStat(ps);//보유주식표시
	setAssetStat(ps, money, todayAS);//보유자산표시
	checkAd(ps, eventVar, time);//찌라시 이벤트
}

void setStock(Stock* ps) {
	srand(time(NULL));//시드
	//주식 변동. 33.3%확률로 상승/하락 33.3%로 유지
	for (int i = 0; i < 10; i++) {
		int temp = rand();
		if (temp % 3 == 0) {
			if (temp % 5 == 3) {//떡락
				(ps + i)->pricePerStock -= 700;
			}
			else {
				(ps + i)->pricePerStock -= 100;
			}
			gotoxy(25 + (i * 10), 11);
			setTextColor(9);
			printf("▼");
			setTextColor(0);
		}
		else if (temp % 3 == 2) {
			if (temp % 5 == 1) {//떡상
				(ps + i)->pricePerStock += 700;
			}
			else {
				(ps + i)->pricePerStock += 100;
			}
			gotoxy(25 + (i * 10), 11);
			setTextColor(12);
			printf("▲");
			setTextColor(0);
		}
		else {
			gotoxy(25 + (i * 10), 11);
			printf("  ");
		}
	}
	
	//게임성 변동조작
	if (rand() % 2 == 1) {
		(ps + ((rand() % 10) + 1))->pricePerStock += ((rand() % 10) + 1) * ((rand() % 10) + 1) * 100;
	}
	else {
		(ps + ((rand() % 10) + 1))->pricePerStock -= ((rand() % 10) + 1) * ((rand() % 10) + 1) * 100;
	}

	//주식별 정보 표시
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			gotoxy(22 + (j * 10), 13 + i * 2);
			if (i == 4) {
				setTextColor(12);//현재가 붉은 색
				printf("%8d", (ps + j)->pricePerStock + (400 - (i * 100)));
				setTextColor(0);
			}
			else {
				printf("%8d", (ps + j)->pricePerStock + (400 - (i * 100)));
			}
		}
	}
}

//게임 찌라시
void setAd(Stock* ps, int* eventVar) {
	int temp;
	temp = (*eventVar) % 10;
	if (*eventVar != 0) {
		gotoxy(40, 33);
		printf("      가즈아 경제에 따르면 잠시후 ");
		setTextColor(12);
		printf("%8s", (ps + temp)->name);
		setTextColor(0);
		printf(" 주가가 급등할 것이라고 합니다.");
		gotoxy(55, 36);
		printf("※위 정보에 따른 책임은 본인에게 있습니다.");
	}
}

void checkAd(Stock* ps, int* eventVar, int* _time) {
	int stockNum;
	stockNum = (*eventVar) % 10;
	srand(time(NULL));//시드
	if (*eventVar != 0 && *_time % 10 != 5) {
		if (rand() % 17 == stockNum) { //약 60%확률
			gotoxy(40, 33);
			setTextColor(12);
			printf("☆★가즈아 경제의 예상이 적중해 %8s 주가가 급등했습니다!!!☆★      ", (ps + stockNum)->name);
			setTextColor(0);
			gotoxy(55, 36);
			printf("※위 정보에 따른 책임은 본인에게 있습니다.");

			(ps + stockNum)->pricePerStock += (rand() % 10 + 10) * (rand() % 10 + 10) * 100;

			*eventVar = 0;
		}
	}
}

void setCalendar(int* month, int* day, int* time) {
	int temp = 540 + *time;
	int hour, min;
	hour = temp / 60;
	min = temp % 60;
	gotoxy(2, 1);
	printf("[오늘 날짜]");
	gotoxy(6, 2);
	printf("21.%02d.%02d", *month, *day);//날짜 변수 가져와야함
	gotoxy(2, 4);
	printf("[현재 시간]");
	gotoxy(6, 5);
	printf("%02d :%02d", hour, min);//시간 변수 만들어야함 게임시간동안
}

void setStockStat(Stock* ps) {
	gotoxy(99,1);
	printf("[보유주식목록]");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			gotoxy(92+(i*15),2+j);
			printf("@%8s %d주", (ps + j + (i * 5))->name, (ps + j + (i * 5))->count);
		}
	}
}

void setAssetStat(Stock* ps, double* money, double* todayPL) {
	//보유현금, 보유주식, 당일손익, 시작자산 = todayPL
	double totalStock = 0;

	for (int i = 0; i < 10; i++) {
		totalStock += (double)((ps + i)->count) * ((ps + i)->pricePerStock);
	}

	gotoxy(123, 1);
	printf("보유 현금 : %10.lf원", *money);
	gotoxy(123, 3);
	printf("보유 주식 : %10.lf원", totalStock);
	gotoxy(123, 5);
	printf("당일 손익 : %10.lf원", (*money + totalStock) - *todayPL);
}

//매수 매도 기능 관련************************
int choiceOrder() {
	int order = 1;
	char key;

	while (1) {
		key = _getch();
		if (key == UP) {
			gotoxy(129, 22);
			printf(" ");
			gotoxy(129, 15);
			printf(">");
			order = 1;
		}
		else if (key == DOWN) {
			gotoxy(129, 15);
			printf(" ");
			gotoxy(129, 22);
			printf(">");
			order = 2;
		}
		else if (key == ENTER) {
			return order;
		}
		else {
			continue;
		}
	}
}

void buyingStock(Stock* ps, double* money) {
	int num;
	double requestMoney;
	int success = 0;
	int count = 0;

	while (success == 0) {
		system("cls");
		CursorView(1);
		makeBox(20, 2, 110, 28);//큰 박스
		makeBox(95, 4, 30, 24);//작은 박스95-125

		gotoxy(69, 4);
		setTextColor(12);
		printf("[매수 주문서]");
		setTextColor(0);

		gotoxy(98, 6);
		printf("<<종목번호>>");
		gotoxy(111, 6);
		printf("<<현 재 가>>");
		for (int i = 0; i < 10; i++) {
			gotoxy(97, 8 + (i * 2));
			printf("%d) %8s", i + 1, (ps + i)->name);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(112, 8 + (i * 2));
			printf("%10d원", (ps + i)->pricePerStock);
		}

		while (count == 0) {
			gotoxy(35, 11);
			setTextColor(8);
			printf("(종료하시려면 0을 입력하세요.)");
			setTextColor(0);
			gotoxy(35, 10);
			printf("매수할 종목의 종목번호를 입력하세요. : \t__번\b\b\b\b ");
			scanf_s("%d", &num);
			if (num == 0) break;

			gotoxy(35, 21);
			setTextColor(8);
			printf("(종목을 다시 선택하시려면 0을 입력하세요.)");
			setTextColor(0);
			gotoxy(35, 20);
			printf("주문할 수량을 입력하세요. : \t\t\t__주\b\b\b\b");
			scanf_s("%d", &count);
		}
		if (num == 0) {
			success = 1;
			continue;
		}
		requestMoney = (double)(ps + (num - 1))->pricePerStock * (double)count; //주문에 해당하는 현금
		if ((ps + num - 1)->pricePerStock < 0) {
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(58, 17);
			printf("머리는 잘 쓰셨지만 막아놨어요^^");
			gotoxy(66, 24);
			printf("다시 입력하세요!");
			Sleep(1500);
			count = 0;
		}
		else if (*money < requestMoney) {
			system("cls");
			makeBox(49,10,50,20);
			gotoxy(59, 17);
			printf("보유 현금으로 살 수 없습니다.");
			gotoxy(66, 24);
			printf("다시 입력하세요!");
			Sleep(1500);
			count = 0;
		}
		else {
			*money -= requestMoney;//보유 현금 - 주문 금액
			(ps + (num - 1))->count += count;//주문 주식 보유 수 += 주문량
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(55, 12);
			printf("매수 주문이 정상적으로 처리되었습니다.");
			gotoxy(66, 17);
			printf("주문 종목 : %10s", (ps + (num - 1))->name);
			gotoxy(66, 20);
			printf("매수 개수 : %10d", count);
			gotoxy(66, 23);
			printf("매수 금액 : %10.lf", requestMoney);
			Sleep(1500);
			success = 1;
		}
	}
}

void sellingStock(Stock* ps, double* money) {
	int num;
	double requestMoney;
	int success = 0;
	int count = 0;

	while (success == 0) {
		system("cls");
		CursorView(1);
		makeBox(20, 2, 110, 28);//큰 박스
		makeBox(85, 4, 42, 24);//작은 박스

		gotoxy(69, 4);
		setTextColor(9);
		printf("[매도 주문서]");
		setTextColor(0);

		gotoxy(88, 6);
		printf("<<종목번호>>");
		gotoxy(101, 6);
		printf("<<현 재 가>>");
		gotoxy(114, 6);
		printf("<<보 유 량>>");
		for (int i = 0; i < 10; i++) {
			gotoxy(87, 8 + (i * 2));
			printf("%d) %8s", i + 1, (ps + i)->name);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(102, 8 + (i * 2));
			printf("%10d원", (ps + i)->pricePerStock);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(117, 8 + (i * 2));
			printf("%4d주", (ps + i)->count);
		}

		while (count == 0) {
			gotoxy(35, 11);
			setTextColor(8);
			printf("(종료하시려면 0을 입력하세요.)");
			setTextColor(0);
			gotoxy(35, 10);
			printf("매도할 종목의 종목번호를 입력하세요. : \t__번\b\b\b\b ");
			scanf_s("%d", &num);
			if (num == 0) break;

			gotoxy(35, 21);
			setTextColor(8);
			printf("(종목을 다시 선택하시려면 0을 입력하세요.)");
			setTextColor(0);
			gotoxy(35, 20);
			printf("주문할 수량을 입력하세요. : \t\t\t__주\b\b\b\b");
			scanf_s("%d", &count);
		}
		if (num == 0) {
			success = 1;
			continue;
		}
		requestMoney = (double)(ps + (num - 1))->pricePerStock * (double)count; //주문에 해당하는 현금 = 현재가 * 주문량
		if ((ps + (num - 1))->count < count) {
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(58, 17);
			printf("보유량보다 많이 주문하셨습니다.");
			gotoxy(66, 24);
			printf("다시 입력하세요!");
			Sleep(1500);
			count = 0;
		}
		else {
			*money += requestMoney;//보유 현금 - 주문 금액
			(ps + (num - 1))->count -= count;//주문 주식 보유 수 -= 주문량
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(55, 12);
			printf("매도 주문이 정상적으로 처리되었습니다.");
			gotoxy(66, 17);
			printf("주문 종목 : %10s", (ps + (num - 1))->name);
			gotoxy(66, 20);
			printf("매도 개수 : %10d", count);
			gotoxy(66, 23);
			printf("매도 금액 : %10.lf", requestMoney);
			Sleep(1500);
			success = 1;
		}
	}
	
}

//결과창************************
int Result(Stock* ps, double* money, double* todayPL, double* targetMoney) {
	double total;
	double stocks = 0;
	int loop;
	for (int i = 0; i < 10; i++) {
		if (((ps + i)->count) > 0) {
			stocks += (double)((ps + i)->count) * ((ps + i)->pricePerStock);
		}
	}
	total = *money + stocks;

	system("cls");
	makeBox(20, 2, 110, 28);

	gotoxy(61, 4);
	printf("[금일 거래가 마감되었습니다.]");

	gotoxy(51, 12);
	printf("금일 거래로 인한 손익은 %.lf원 입니다.", *todayPL);

	gotoxy(51, 17);
	printf("보유 자산은 현금 %.lf원, 주식 %.lf원으로 총 %.lf원 입니다.", *money, stocks, total);

	gotoxy(58, 25);
	printf("5초 후 종료 화면으로 이동합니다.");

	if (total > *targetMoney) {
		gotoxy(51, 23);
		printf("☆★목표로 하신 수익에 도달하셨습니다!! 축하합니다☆★");
		loop = 0;
		Sleep(5000);
		system("cls");
	}
	else {
		Sleep(5000);
		system("cls");
		loop = 1;
	}

	return loop;
}