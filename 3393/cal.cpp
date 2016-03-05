#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

/*	day 0 Sun
		1 Mon
		2 Tue
		3 Wed
		4 Thur
		5 Fri
		6 Sat
*/

int getMonthsCount(int year, int month){
	return (year - 1) * 12 + month;
}

int getMonthDays(int year, int month){
	const int regular[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year == 1752 && month == 9)
		return 19;
	if (year == 1700 && month == 2)
		return 29;
	if (month == 2){
		if (year < 1582 && year % 4 == 0)
			return 29;
		else if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)
			return 29;
	}
	return regular[month];
}

void init(vector<int>& good, vector<int>& lucky){
	int month_count = 1, year = 1, month = 1, day = 6;
	while (month_count <= 140000){
		good[month_count] = good[month_count - 1];
		lucky[month_count] = lucky[month_count - 1];

		if (day == 6 || day <= 1)
			good[month_count]++;
		int days = getMonthDays(year, month);
		day = (day + days - 1) % 7;
		if (day >=5 || day == 0)
			lucky[month_count]++;

		day = (day + 1) % 7;
		month++;
		if (month == 13){
			year++;
			month = 1;
		}

		month_count++;
	}
}

int main(){
	vector<int> good(150000, 0), lucky(150000, 0);
	init(good, lucky);
	
	int w;
	scanf("%d", &w);
	while (w--){
		int Ys, Ms, Ye, Me;
		scanf("%d %d %d %d", &Ys, &Ms, &Ye, &Me);
		if (getMonthsCount(Ye, Me) < getMonthsCount(Ys, Ms))
			printf("0 0\n");
		else printf("%d %d\n", 	lucky[getMonthsCount(Ye, Me)] - lucky[getMonthsCount(Ys, Ms) - 1],
								good[getMonthsCount(Ye, Me)] - good[getMonthsCount(Ys, Ms) - 1]);
	}
	return 0;
}
