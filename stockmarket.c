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
	printf("�١��ָ��̵��� ������ �����͡١�");
	Sleep(3000);
	system("cls");

	CursorView(1);
	gotoxy(57, 4);
	printf("���ַ��忡 ���� ���� ȯ���մϴ�><");

	gotoxy(50, 15);
	printf("��ǥ ������ �Է����ּ��� :            ��\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s("%lf", targetMoney);//&*targetMoney
	gotoxy(50, 20);
	printf("��ǥ �Ⱓ �Է����ּ��� :     ��\b\b\b\b\b\b");
	scanf_s("%d", targetDate);
	CursorView(0);
}

void setDashboard(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double* targetMoney, double* money, double* totalPL) {
	//�� �����ͷ� ���� �������� ����ϸ�ǰ�, (target)month�� (target)day�� '1~12��', '1~31'�� �����̾�!
	//��) printf("%d", day); �̷������� ���� ������, printf("%d", *day); �̷��� �����!
	system("cls");
	makeBox(20, 2, 110, 35);
	gotoxy(65, 5);
	printf("D A S H   B O A R D");

	makeBox(30, 8, 90, 14);
	gotoxy(32, 9);
	printf("[2021�� %02d�� %02d��]", *month, *day);
	gotoxy(92, 9);
	printf("��ǥ ��¥ : 2021�� %02d�� %02d��", *targetMonth, *targetDay);
	gotoxy(92, 10);
	printf("��ǥ �ݾ� : %.lf��", *targetMoney);
	gotoxy(32, 11);
	printf("[�����ֽ�]");
	int temp = 0;
	double totalStock = 0;
	for (int i = 0; i < 10; i++) {
		if (temp < 5) {
			if ((ps + i)->count > 0) {
				gotoxy(36, 13 + temp);
				printf("%8s %d�� �������� %d��", (ps + i)->name, (ps + i)->count, (ps + i)->pricePerStock);
				temp++;
			}
		}
		else {
			if ((ps + i)->count > 0) {
				gotoxy(70, 13 + temp);
				printf("%8s %d�� �������� %d��", (ps + i)->name, (ps + i)->count, (ps + i)->pricePerStock);
				temp++;
			}
		}
		totalStock += (double)(ps + i)->pricePerStock * (ps + i)->count;
	}
	if (temp == 0) {
		gotoxy(65, 14);
		printf("- ���� �ֽ� ���� -");
	}

	gotoxy(92, 19);
	printf("�ں��� �ڻ� : %.lf��", totalStock + *money);
	gotoxy(92, 20);
	printf("������ ���� : %.lf��", *money);
	gotoxy(92, 21);
	printf("������ �ֽ� : %.lf��", totalStock);

	gotoxy(32, 21);
	printf("������� �� ���� : %.lf��", *totalPL);

	gotoxy(64, 27);
	printf("$�ֽĽ��� �����ϱ�$");

	gotoxy(68, 33);
	printf("$�����ϱ�$");
}

int choiceAction(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double* targetMoney, double* money, double* totalPL) {//���θ޴� Ŀ������
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
	//Ķ����
	makeBox(0, 0, 20, 7);
	//���� �ֽ� �� �ڻ��
	makeBox(90, 0, 58, 7);
	gotoxy(120, 0);
	printf("��");
	gotoxy(120, 7);
	printf("��");
	for (int i = 1; i < 7; i++) {
		gotoxy(120, i);
		printf("��");
	}
	//��ü �ֽ� ��Ȳǥ
	makeTable(10, 8, 110, 22, 11, 10);
	//�ֽ��̸�
	for (int i = 0; i < 10; i++) {
		gotoxy(21 + (i * 10), 10);
		printf(" %-8s", (ps + i)->name);
	}
	//���簡 ��
	for (int i = 0; i < 9; i++) {
		gotoxy(13, 13 + (i * 2));
		if (i == 4) {
			setTextColor(12);
			printf("���簡");
			setTextColor(0);
		}
		else if (i < 4) {
			printf("  %d", 400 + (-100 * i));
		}
		else {
			printf(" %d", 400 + (-100 * i));
		}
	}
	//Ÿ��Ʋ
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
	//���� �ڽ�
	makeBox(30, 32, 90, 5);
	//�ż�
	makeBox(124, 13, 19, 4);
	gotoxy(129, 15);
	setTextColor(12);
	printf("%10s", "  ��  ��  ");
	setTextColor(0);

	//�ŵ�
	makeBox(124, 20, 19, 4);
	gotoxy(129, 22);
	setTextColor(9);
	printf("%10s", "  ��  ��  ");
	setTextColor(0);
	//Ŀ��
	gotoxy(129, 15);
	printf(">");
}

void repeatStockmarket(Stock* ps, int* month, int* day, int* time, double* money, double* todayAS, int* eventVar) {//ps->name���� ����
	setStock(ps);//�ֽ�����ǥ��
	setCalendar(month, day, time);//��¥, �ð�����ǥ��
	setStockStat(ps);//�����ֽ�ǥ��
	setAssetStat(ps, money, todayAS);//�����ڻ�ǥ��
	checkAd(ps, eventVar, time);//���� �̺�Ʈ
}

void setStock(Stock* ps) {
	srand(time(NULL));//�õ�
	//�ֽ� ����. 33.3%Ȯ���� ���/�϶� 33.3%�� ����
	for (int i = 0; i < 10; i++) {
		int temp = rand();
		if (temp % 3 == 0) {
			if (temp % 5 == 3) {//����
				(ps + i)->pricePerStock -= 700;
			}
			else {
				(ps + i)->pricePerStock -= 100;
			}
			gotoxy(25 + (i * 10), 11);
			setTextColor(9);
			printf("��");
			setTextColor(0);
		}
		else if (temp % 3 == 2) {
			if (temp % 5 == 1) {//����
				(ps + i)->pricePerStock += 700;
			}
			else {
				(ps + i)->pricePerStock += 100;
			}
			gotoxy(25 + (i * 10), 11);
			setTextColor(12);
			printf("��");
			setTextColor(0);
		}
		else {
			gotoxy(25 + (i * 10), 11);
			printf("  ");
		}
	}
	
	//���Ӽ� ��������
	if (rand() % 2 == 1) {
		(ps + ((rand() % 10) + 1))->pricePerStock += ((rand() % 10) + 1) * ((rand() % 10) + 1) * 100;
	}
	else {
		(ps + ((rand() % 10) + 1))->pricePerStock -= ((rand() % 10) + 1) * ((rand() % 10) + 1) * 100;
	}

	//�ֽĺ� ���� ǥ��
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			gotoxy(22 + (j * 10), 13 + i * 2);
			if (i == 4) {
				setTextColor(12);//���簡 ���� ��
				printf("%8d", (ps + j)->pricePerStock + (400 - (i * 100)));
				setTextColor(0);
			}
			else {
				printf("%8d", (ps + j)->pricePerStock + (400 - (i * 100)));
			}
		}
	}
}

//���� ����
void setAd(Stock* ps, int* eventVar) {
	int temp;
	temp = (*eventVar) % 10;
	if (*eventVar != 0) {
		gotoxy(40, 33);
		printf("      ����� ������ ������ ����� ");
		setTextColor(12);
		printf("%8s", (ps + temp)->name);
		setTextColor(0);
		printf(" �ְ��� �޵��� ���̶�� �մϴ�.");
		gotoxy(55, 36);
		printf("���� ������ ���� å���� ���ο��� �ֽ��ϴ�.");
	}
}

void checkAd(Stock* ps, int* eventVar, int* _time) {
	int stockNum;
	stockNum = (*eventVar) % 10;
	srand(time(NULL));//�õ�
	if (*eventVar != 0 && *_time % 10 != 5) {
		if (rand() % 17 == stockNum) { //�� 60%Ȯ��
			gotoxy(40, 33);
			setTextColor(12);
			printf("�١ڰ���� ������ ������ ������ %8s �ְ��� �޵��߽��ϴ�!!!�١�      ", (ps + stockNum)->name);
			setTextColor(0);
			gotoxy(55, 36);
			printf("���� ������ ���� å���� ���ο��� �ֽ��ϴ�.");

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
	printf("[���� ��¥]");
	gotoxy(6, 2);
	printf("21.%02d.%02d", *month, *day);//��¥ ���� �����;���
	gotoxy(2, 4);
	printf("[���� �ð�]");
	gotoxy(6, 5);
	printf("%02d :%02d", hour, min);//�ð� ���� �������� ���ӽð�����
}

void setStockStat(Stock* ps) {
	gotoxy(99,1);
	printf("[�����ֽĸ��]");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			gotoxy(92+(i*15),2+j);
			printf("@%8s %d��", (ps + j + (i * 5))->name, (ps + j + (i * 5))->count);
		}
	}
}

void setAssetStat(Stock* ps, double* money, double* todayPL) {
	//��������, �����ֽ�, ���ϼ���, �����ڻ� = todayPL
	double totalStock = 0;

	for (int i = 0; i < 10; i++) {
		totalStock += (double)((ps + i)->count) * ((ps + i)->pricePerStock);
	}

	gotoxy(123, 1);
	printf("���� ���� : %10.lf��", *money);
	gotoxy(123, 3);
	printf("���� �ֽ� : %10.lf��", totalStock);
	gotoxy(123, 5);
	printf("���� ���� : %10.lf��", (*money + totalStock) - *todayPL);
}

//�ż� �ŵ� ��� ����************************
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
		makeBox(20, 2, 110, 28);//ū �ڽ�
		makeBox(95, 4, 30, 24);//���� �ڽ�95-125

		gotoxy(69, 4);
		setTextColor(12);
		printf("[�ż� �ֹ���]");
		setTextColor(0);

		gotoxy(98, 6);
		printf("<<�����ȣ>>");
		gotoxy(111, 6);
		printf("<<�� �� ��>>");
		for (int i = 0; i < 10; i++) {
			gotoxy(97, 8 + (i * 2));
			printf("%d) %8s", i + 1, (ps + i)->name);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(112, 8 + (i * 2));
			printf("%10d��", (ps + i)->pricePerStock);
		}

		while (count == 0) {
			gotoxy(35, 11);
			setTextColor(8);
			printf("(�����Ͻ÷��� 0�� �Է��ϼ���.)");
			setTextColor(0);
			gotoxy(35, 10);
			printf("�ż��� ������ �����ȣ�� �Է��ϼ���. : \t__��\b\b\b\b ");
			scanf_s("%d", &num);
			if (num == 0) break;

			gotoxy(35, 21);
			setTextColor(8);
			printf("(������ �ٽ� �����Ͻ÷��� 0�� �Է��ϼ���.)");
			setTextColor(0);
			gotoxy(35, 20);
			printf("�ֹ��� ������ �Է��ϼ���. : \t\t\t__��\b\b\b\b");
			scanf_s("%d", &count);
		}
		if (num == 0) {
			success = 1;
			continue;
		}
		requestMoney = (double)(ps + (num - 1))->pricePerStock * (double)count; //�ֹ��� �ش��ϴ� ����
		if ((ps + num - 1)->pricePerStock < 0) {
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(58, 17);
			printf("�Ӹ��� �� �������� ���Ƴ����^^");
			gotoxy(66, 24);
			printf("�ٽ� �Է��ϼ���!");
			Sleep(1500);
			count = 0;
		}
		else if (*money < requestMoney) {
			system("cls");
			makeBox(49,10,50,20);
			gotoxy(59, 17);
			printf("���� �������� �� �� �����ϴ�.");
			gotoxy(66, 24);
			printf("�ٽ� �Է��ϼ���!");
			Sleep(1500);
			count = 0;
		}
		else {
			*money -= requestMoney;//���� ���� - �ֹ� �ݾ�
			(ps + (num - 1))->count += count;//�ֹ� �ֽ� ���� �� += �ֹ���
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(55, 12);
			printf("�ż� �ֹ��� ���������� ó���Ǿ����ϴ�.");
			gotoxy(66, 17);
			printf("�ֹ� ���� : %10s", (ps + (num - 1))->name);
			gotoxy(66, 20);
			printf("�ż� ���� : %10d", count);
			gotoxy(66, 23);
			printf("�ż� �ݾ� : %10.lf", requestMoney);
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
		makeBox(20, 2, 110, 28);//ū �ڽ�
		makeBox(85, 4, 42, 24);//���� �ڽ�

		gotoxy(69, 4);
		setTextColor(9);
		printf("[�ŵ� �ֹ���]");
		setTextColor(0);

		gotoxy(88, 6);
		printf("<<�����ȣ>>");
		gotoxy(101, 6);
		printf("<<�� �� ��>>");
		gotoxy(114, 6);
		printf("<<�� �� ��>>");
		for (int i = 0; i < 10; i++) {
			gotoxy(87, 8 + (i * 2));
			printf("%d) %8s", i + 1, (ps + i)->name);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(102, 8 + (i * 2));
			printf("%10d��", (ps + i)->pricePerStock);
		}
		for (int i = 0; i < 10; i++) {
			gotoxy(117, 8 + (i * 2));
			printf("%4d��", (ps + i)->count);
		}

		while (count == 0) {
			gotoxy(35, 11);
			setTextColor(8);
			printf("(�����Ͻ÷��� 0�� �Է��ϼ���.)");
			setTextColor(0);
			gotoxy(35, 10);
			printf("�ŵ��� ������ �����ȣ�� �Է��ϼ���. : \t__��\b\b\b\b ");
			scanf_s("%d", &num);
			if (num == 0) break;

			gotoxy(35, 21);
			setTextColor(8);
			printf("(������ �ٽ� �����Ͻ÷��� 0�� �Է��ϼ���.)");
			setTextColor(0);
			gotoxy(35, 20);
			printf("�ֹ��� ������ �Է��ϼ���. : \t\t\t__��\b\b\b\b");
			scanf_s("%d", &count);
		}
		if (num == 0) {
			success = 1;
			continue;
		}
		requestMoney = (double)(ps + (num - 1))->pricePerStock * (double)count; //�ֹ��� �ش��ϴ� ���� = ���簡 * �ֹ���
		if ((ps + (num - 1))->count < count) {
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(58, 17);
			printf("���������� ���� �ֹ��ϼ̽��ϴ�.");
			gotoxy(66, 24);
			printf("�ٽ� �Է��ϼ���!");
			Sleep(1500);
			count = 0;
		}
		else {
			*money += requestMoney;//���� ���� - �ֹ� �ݾ�
			(ps + (num - 1))->count -= count;//�ֹ� �ֽ� ���� �� -= �ֹ���
			system("cls");
			makeBox(49, 10, 50, 20);
			gotoxy(55, 12);
			printf("�ŵ� �ֹ��� ���������� ó���Ǿ����ϴ�.");
			gotoxy(66, 17);
			printf("�ֹ� ���� : %10s", (ps + (num - 1))->name);
			gotoxy(66, 20);
			printf("�ŵ� ���� : %10d", count);
			gotoxy(66, 23);
			printf("�ŵ� �ݾ� : %10.lf", requestMoney);
			Sleep(1500);
			success = 1;
		}
	}
	
}

//���â************************
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
	printf("[���� �ŷ��� �����Ǿ����ϴ�.]");

	gotoxy(51, 12);
	printf("���� �ŷ��� ���� ������ %.lf�� �Դϴ�.", *todayPL);

	gotoxy(51, 17);
	printf("���� �ڻ��� ���� %.lf��, �ֽ� %.lf������ �� %.lf�� �Դϴ�.", *money, stocks, total);

	gotoxy(58, 25);
	printf("5�� �� ���� ȭ������ �̵��մϴ�.");

	if (total > *targetMoney) {
		gotoxy(51, 23);
		printf("�١ڸ�ǥ�� �Ͻ� ���Ϳ� �����ϼ̽��ϴ�!! �����մϴ١١�");
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