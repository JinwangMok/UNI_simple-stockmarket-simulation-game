#include "function.h"//각종 기능적인 함수들
#include "stockmarket.h"//게임과 관련된 함수들

int main() {
	PlaySound(TEXT("gameBgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	CursorView(0);//커서 숨김

	Stock s[10] = {
		{.name = "사성전자", .count = 0, .pricePerStock = 80000},
		{.name = "코 코 아", .count = 0, .pricePerStock = 120000},
		{.name = "내 이 버", .count = 0, .pricePerStock = 400000},
		{.name = "현 머 차", .count = 0, .pricePerStock = 270000},
		{.name = "젤트리온", .count = 0, .pricePerStock = 240000},
		{.name = "빅 하 트", .count = 0, .pricePerStock = 300000},
		{.name = "테 솔 라", .count = 0, .pricePerStock = 900000},
		{.name = " 사  과 ", .count = 0, .pricePerStock = 150000},
		{.name = " 코  팡 ", .count = 0, .pricePerStock = 45000},
		{.name = "과제스탑", .count = 0, .pricePerStock = 30000}
	};//메인 구조체 배열. 원형은 function.h에 선언되어있음.

	//**********변수 선언**********
	//초기 설정에 사용되는 변수
	double targetMoney = 0;//목표금액
	int	targetDate = 0;//목표기간

	//자산 관련 변수
	double money = 500000;//보유현금
	double totalPL = 0;//총 손익_total(PL : profit & Loss, 손익)
	double todayAS;//당일 자산_today(AS : asset, 자산)
	double totalMoney = 0;

	//날짜 관련 변수
	int targetMonth = 1;//목표 달
	int targetDay = 1;//목표 날
	int month = 1;//현재 달
	int day = 1;//현재 날

	//게임 진행 관련 변수
	int eventVar = 0;
	int loop = 1;
	FILE* fp;

	//*********게임 시작*********
	setConsole();//콘솔창의 크기, 색깔, 타이틀을 설정하는 함수. function.c에 선언되어있음.
	intro(&targetDate, &targetMoney);//인트로 애니메이션과 넘겨받은 목표 기간, 목표 금액 변수에 유저의 입력값 대입하는 함수. 원형은 stockmarket.c에 선언되어있음.
	targetMoney += 500000;

	//**********목표 날짜 설정**********
	targetDay += targetDate;
	setDate(&targetDay, &targetMonth);//'일'과 '월'을 넘기면, '일'이 28,30,31일 경우에 '월'을 증가시키는 함수. 원형은 function.c에 선언되어있음

	//*********게임의 메인 기능*********
	while (loop == 1) {
		setDashboard(s,&targetMonth, &targetDay, &month, &day, &targetMoney, &money, &totalPL);//대쉬 보드에 글자 출력하는 함수. 원형은 stockmarket.c에 선언되어있음.
		todayAS = 0;//당일 손익 초기화
		int i = choiceAction(s, &targetMonth, &targetDay, &month, &day, &targetMoney, &money, &totalPL);//대쉬 보드의 '>'모양 커서를 움직이고 입력을 받아 정수를 리턴하는 함수. 원형은 stockmarket.c에 선언되어있음.

		switch (i) {
		case 1://*********주식 시장 입장*********
			//*********게임 시작 전 설정*********
			for (int k = 0; k < 10; k++) {
				todayAS += (double)(s[k].count) * (s[k].pricePerStock);
			}
			todayAS += money;
			//todayPL 변수에 (보유 주식의 현재가격 + 보유 현금)대입. -> 게임을 시작하는 시점에 보유하고 있는 자산

			system("cls");//화면 초기화
			setBoard(s);//주식 시장의 전체적인 모양을 생성하는 함수. 원형은 stockmarket.c에 선언되어있음.
			//보드를 반복문 밖에서 한 번만 호출하므로써 화면이 깜빡이는 현상 해결!!
			int time = 0;//게임의 플레이시간 변수 0으로 초기화.
			eventVar = 0;//찌라시 랜덤 변수 0으로 초기화.
			//*********게임 플레이 시간 동안 반복*********
			for (int j = 0; j < 390; j++) {
				int order = 0;//매수, 매도의 선택을 담는 변수 0으로 초기화.
				time++;//게임 시간 1증가. 389가 되면 게임 종료.
				if (time % 10 == 5) {
					srand(time);//시드
					eventVar = rand();//10초에 한번씩 바뀜
				}
				repeatStockmarket(s, &month, &day, &time, &money, &todayAS, &eventVar);//주식 변동, 날짜 및 플레이 시간, 보유 주식, 보유 자산 표시
				setAd(s, &eventVar);
				Sleep(500);//틱 당 시간
				if (_kbhit()) { //if 키가 눌린다면
					order = choiceOrder();//choiceAction()처럼 매수와 매도의 선택을 받아 정수를 리턴하는 함수. 원형은 stockmarket.c에 선언되어있음.
				}
				if (order == 1) { //매수
					buyingStock(s, &money);//매수 화면
					system("cls");
					setBoard(s); //매수 성공 화면
					CursorView(0);
				}
				else if (order == 2) { //매도
					sellingStock(s, &money); //매도 화면
					system("cls");
					setBoard(s); //매도 성공 화면
					CursorView(0);
				}
				else continue;// 안눌렸다면 무시
			}
			//*********게임 종료 후 설정*********
			//날짜 설정
			day++;
			if (day > 31) setDate(&day, &month);//날짜 검사 후 날짜 수정
			
			//마감 주가 설정
			double todayPL = 0;
			for (int k = 0; k < 10; k++) {
				todayPL += (double)(s[k].count) * (s[k].pricePerStock);
			}
			todayPL += money;//todayPL = 현금 + 마감 시점 주가(주식별 보유량 * 마감 시점 가격)
			totalMoney = todayPL;
			todayPL -= todayAS;
			//총 손익 설정
			totalPL += todayPL;//총 손익 = 총 손익 + 당일 손익 -> [현재 보유 자산 - 시작 자산]
			//*********게임 결과창*********
			loop = Result(s, &money, &todayPL, &targetMoney);//바로 종료되는 걸 고치려면 loop변수를 활용해야함
			break;

		case 2://*********게임 종료*********      *****나영담당*****
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*목표를 달성하지 못 하였습니다.*\n");
			fprintf(fp, "목표 금액 : %.lf원\n", targetMoney);
			fprintf(fp, "목표 날짜 : 2021년 %d월 %d일\n", targetMonth, targetDay);
			fprintf(fp, "최종 자산 : %.lf원\n", totalMoney);
			fprintf(fp, "최종 날짜 : 2021년 %d월 %d일\n", month, day);
			fclose(fp);
			loop = 0;
			break;
		default:
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*목표를 달성하지 못 하였습니다.*\n");
			fprintf(fp, "목표 금액 : %.lf원\n", targetMoney);
			fprintf(fp, "목표 날짜 : 2021년 %d월 %d일\n", targetMonth, targetDay);
			fprintf(fp, "최종 자산 : %.lf원\n", totalMoney);
			fprintf(fp, "최종 날짜 : 2021년 %d월 %d일\n", month, day);
			fclose(fp);
			loop = 0;
			break;
		}
		//목표기간이 지났다면 종료(실패)
		if ((month == targetMonth) && (day > targetDay)) {
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*목표를 달성하지 못 하였습니다.*\n");
			fprintf(fp, "목표 금액 : %.lf원\n", targetMoney);
			fprintf(fp, "목표 날짜 : 2021년 %d월 %d일\n", targetMonth, targetDay);
			fprintf(fp, "최종 자산 : %.lf원\n", totalMoney);
			fprintf(fp, "최종 날짜 : 2021년 %d월 %d일\n", month, day);
			fclose(fp);
			loop = 0;
		}
		//목표 금액 달성이면 종료(성공)
		if (money >= targetMoney && loop == 0) {
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*목표를 달성하였습니다.*\n");
			fprintf(fp, "목표 금액 : %.lf원\n", targetMoney);
			fprintf(fp, "목표 날짜 : 2021년 %d월 %d일\n", targetMonth, targetDay);
			fprintf(fp, "최종 자산 : %.lf원\n", totalMoney);
			fprintf(fp, "최종 날짜 : 2021년 %d월 %d일\n", month, day);
			fclose(fp);
			loop = 0;
		}
	}
	system(".\\result.txt");
	return 0;
}