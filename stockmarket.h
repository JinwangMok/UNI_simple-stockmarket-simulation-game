#pragma once
void intro(int* targetDate, double* targetMoney);
void setDashboard(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double *targetMoney, double* money, double* totalPL);
int choiceAction(Stock* ps, int* targetMonth, int* targetDay, int* month, int* day, double* targetMoney, double* money, double* totalPL);
void setBoard(Stock* ps);
void repeatStockmarket(Stock* ps, int* month, int* day, int* time, double* money, double* todayAS, int* eventVar);
void setStock(Stock* ps);
void setAd(Stock* ps, int* eventVar);
void checkAd(Stock* ps, int* eventVar, int* _time);
void setCalendar(int* month, int* day, int* time);
void setStockStat(Stock* ps);
void setAssetStat(Stock* ps, double* money, double* todayPL);
int choiceOrder();
void buyingStock(Stock* ps, double* money);
void sellingStock(Stock* ps, double* money);
int Result(Stock* ps, double* money, double* todayPL, double* targetMoney);