#include "function.h"//���� ������� �Լ���
#include "stockmarket.h"//���Ӱ� ���õ� �Լ���

int main() {
	PlaySound(TEXT("gameBgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	CursorView(0);//Ŀ�� ����

	Stock s[10] = {
		{.name = "�缺����", .count = 0, .pricePerStock = 80000},
		{.name = "�� �� ��", .count = 0, .pricePerStock = 120000},
		{.name = "�� �� ��", .count = 0, .pricePerStock = 400000},
		{.name = "�� �� ��", .count = 0, .pricePerStock = 270000},
		{.name = "��Ʈ����", .count = 0, .pricePerStock = 240000},
		{.name = "�� �� Ʈ", .count = 0, .pricePerStock = 300000},
		{.name = "�� �� ��", .count = 0, .pricePerStock = 900000},
		{.name = " ��  �� ", .count = 0, .pricePerStock = 150000},
		{.name = " ��  �� ", .count = 0, .pricePerStock = 45000},
		{.name = "������ž", .count = 0, .pricePerStock = 30000}
	};//���� ����ü �迭. ������ function.h�� ����Ǿ�����.

	//**********���� ����**********
	//�ʱ� ������ ���Ǵ� ����
	double targetMoney = 0;//��ǥ�ݾ�
	int	targetDate = 0;//��ǥ�Ⱓ

	//�ڻ� ���� ����
	double money = 500000;//��������
	double totalPL = 0;//�� ����_total(PL : profit & Loss, ����)
	double todayAS;//���� �ڻ�_today(AS : asset, �ڻ�)
	double totalMoney = 0;

	//��¥ ���� ����
	int targetMonth = 1;//��ǥ ��
	int targetDay = 1;//��ǥ ��
	int month = 1;//���� ��
	int day = 1;//���� ��

	//���� ���� ���� ����
	int eventVar = 0;
	int loop = 1;
	FILE* fp;

	//*********���� ����*********
	setConsole();//�ܼ�â�� ũ��, ����, Ÿ��Ʋ�� �����ϴ� �Լ�. function.c�� ����Ǿ�����.
	intro(&targetDate, &targetMoney);//��Ʈ�� �ִϸ��̼ǰ� �Ѱܹ��� ��ǥ �Ⱓ, ��ǥ �ݾ� ������ ������ �Է°� �����ϴ� �Լ�. ������ stockmarket.c�� ����Ǿ�����.
	targetMoney += 500000;

	//**********��ǥ ��¥ ����**********
	targetDay += targetDate;
	setDate(&targetDay, &targetMonth);//'��'�� '��'�� �ѱ��, '��'�� 28,30,31�� ��쿡 '��'�� ������Ű�� �Լ�. ������ function.c�� ����Ǿ�����

	//*********������ ���� ���*********
	while (loop == 1) {
		setDashboard(s,&targetMonth, &targetDay, &month, &day, &targetMoney, &money, &totalPL);//�뽬 ���忡 ���� ����ϴ� �Լ�. ������ stockmarket.c�� ����Ǿ�����.
		todayAS = 0;//���� ���� �ʱ�ȭ
		int i = choiceAction(s, &targetMonth, &targetDay, &month, &day, &targetMoney, &money, &totalPL);//�뽬 ������ '>'��� Ŀ���� �����̰� �Է��� �޾� ������ �����ϴ� �Լ�. ������ stockmarket.c�� ����Ǿ�����.

		switch (i) {
		case 1://*********�ֽ� ���� ����*********
			//*********���� ���� �� ����*********
			for (int k = 0; k < 10; k++) {
				todayAS += (double)(s[k].count) * (s[k].pricePerStock);
			}
			todayAS += money;
			//todayPL ������ (���� �ֽ��� ���簡�� + ���� ����)����. -> ������ �����ϴ� ������ �����ϰ� �ִ� �ڻ�

			system("cls");//ȭ�� �ʱ�ȭ
			setBoard(s);//�ֽ� ������ ��ü���� ����� �����ϴ� �Լ�. ������ stockmarket.c�� ����Ǿ�����.
			//���带 �ݺ��� �ۿ��� �� ���� ȣ���ϹǷν� ȭ���� �����̴� ���� �ذ�!!
			int time = 0;//������ �÷��̽ð� ���� 0���� �ʱ�ȭ.
			eventVar = 0;//���� ���� ���� 0���� �ʱ�ȭ.
			//*********���� �÷��� �ð� ���� �ݺ�*********
			for (int j = 0; j < 390; j++) {
				int order = 0;//�ż�, �ŵ��� ������ ��� ���� 0���� �ʱ�ȭ.
				time++;//���� �ð� 1����. 389�� �Ǹ� ���� ����.
				if (time % 10 == 5) {
					srand(time);//�õ�
					eventVar = rand();//10�ʿ� �ѹ��� �ٲ�
				}
				repeatStockmarket(s, &month, &day, &time, &money, &todayAS, &eventVar);//�ֽ� ����, ��¥ �� �÷��� �ð�, ���� �ֽ�, ���� �ڻ� ǥ��
				setAd(s, &eventVar);
				Sleep(500);//ƽ �� �ð�
				if (_kbhit()) { //if Ű�� �����ٸ�
					order = choiceOrder();//choiceAction()ó�� �ż��� �ŵ��� ������ �޾� ������ �����ϴ� �Լ�. ������ stockmarket.c�� ����Ǿ�����.
				}
				if (order == 1) { //�ż�
					buyingStock(s, &money);//�ż� ȭ��
					system("cls");
					setBoard(s); //�ż� ���� ȭ��
					CursorView(0);
				}
				else if (order == 2) { //�ŵ�
					sellingStock(s, &money); //�ŵ� ȭ��
					system("cls");
					setBoard(s); //�ŵ� ���� ȭ��
					CursorView(0);
				}
				else continue;// �ȴ��ȴٸ� ����
			}
			//*********���� ���� �� ����*********
			//��¥ ����
			day++;
			if (day > 31) setDate(&day, &month);//��¥ �˻� �� ��¥ ����
			
			//���� �ְ� ����
			double todayPL = 0;
			for (int k = 0; k < 10; k++) {
				todayPL += (double)(s[k].count) * (s[k].pricePerStock);
			}
			todayPL += money;//todayPL = ���� + ���� ���� �ְ�(�ֽĺ� ������ * ���� ���� ����)
			totalMoney = todayPL;
			todayPL -= todayAS;
			//�� ���� ����
			totalPL += todayPL;//�� ���� = �� ���� + ���� ���� -> [���� ���� �ڻ� - ���� �ڻ�]
			//*********���� ���â*********
			loop = Result(s, &money, &todayPL, &targetMoney);//�ٷ� ����Ǵ� �� ��ġ���� loop������ Ȱ���ؾ���
			break;

		case 2://*********���� ����*********      *****�������*****
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*��ǥ�� �޼����� �� �Ͽ����ϴ�.*\n");
			fprintf(fp, "��ǥ �ݾ� : %.lf��\n", targetMoney);
			fprintf(fp, "��ǥ ��¥ : 2021�� %d�� %d��\n", targetMonth, targetDay);
			fprintf(fp, "���� �ڻ� : %.lf��\n", totalMoney);
			fprintf(fp, "���� ��¥ : 2021�� %d�� %d��\n", month, day);
			fclose(fp);
			loop = 0;
			break;
		default:
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*��ǥ�� �޼����� �� �Ͽ����ϴ�.*\n");
			fprintf(fp, "��ǥ �ݾ� : %.lf��\n", targetMoney);
			fprintf(fp, "��ǥ ��¥ : 2021�� %d�� %d��\n", targetMonth, targetDay);
			fprintf(fp, "���� �ڻ� : %.lf��\n", totalMoney);
			fprintf(fp, "���� ��¥ : 2021�� %d�� %d��\n", month, day);
			fclose(fp);
			loop = 0;
			break;
		}
		//��ǥ�Ⱓ�� �����ٸ� ����(����)
		if ((month == targetMonth) && (day > targetDay)) {
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*��ǥ�� �޼����� �� �Ͽ����ϴ�.*\n");
			fprintf(fp, "��ǥ �ݾ� : %.lf��\n", targetMoney);
			fprintf(fp, "��ǥ ��¥ : 2021�� %d�� %d��\n", targetMonth, targetDay);
			fprintf(fp, "���� �ڻ� : %.lf��\n", totalMoney);
			fprintf(fp, "���� ��¥ : 2021�� %d�� %d��\n", month, day);
			fclose(fp);
			loop = 0;
		}
		//��ǥ �ݾ� �޼��̸� ����(����)
		if (money >= targetMoney && loop == 0) {
			fp = fopen("result.txt", "w+");
			fprintf(fp, "\t\t*��ǥ�� �޼��Ͽ����ϴ�.*\n");
			fprintf(fp, "��ǥ �ݾ� : %.lf��\n", targetMoney);
			fprintf(fp, "��ǥ ��¥ : 2021�� %d�� %d��\n", targetMonth, targetDay);
			fprintf(fp, "���� �ڻ� : %.lf��\n", totalMoney);
			fprintf(fp, "���� ��¥ : 2021�� %d�� %d��\n", month, day);
			fclose(fp);
			loop = 0;
		}
	}
	system(".\\result.txt");
	return 0;
}