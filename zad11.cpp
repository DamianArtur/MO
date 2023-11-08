#include <iostream>
#include <fstream>
#include <cmath>

#define WEZLY 20
#define N 200
#define START -1.0d
#define KONIEC 1.0d

using namespace std;

double funkcja(double x) {
	return 1.0d / (1.0d + (10.0d * x * x * x * x * x * x));
}

void przygotuj_wielomiany(double wezly[][2]) {
	
	double krok = (KONIEC - START) / (WEZLY - 1);
	double x = START;
	for (int i = 0; x <= KONIEC; i++) {
		wezly[i][0] = x;
		wezly[i][1] = funkcja(x);
		x += krok;
	}
	
	for (int i = 1; i < WEZLY; i++) {
		for(int j = WEZLY-1; j >= i; j--) {
			wezly[j][1] = (wezly[j][1] - wezly[j-1][1]) / (wezly[j][0] - wezly[j-i][0]);
		}
	}
}

void przygotuj_wielomiany_Czebyszew(double wezly_Czebyszew[][2]) {
	
	for (int i = 0; i < WEZLY; i++) {
		wezly_Czebyszew[i][0] = cos(((2.0d * i + 1.0d) * M_PI) / (2.0d * WEZLY));
		wezly_Czebyszew[i][1] = funkcja(wezly_Czebyszew[i][0]);
	}
	
	for (int i = 1; i < WEZLY; i++) {
		for (int j = WEZLY-1; j >= i; j--) {
			wezly_Czebyszew[j][1] = (wezly_Czebyszew[j][1] - wezly_Czebyszew[j-1][1]) / (wezly_Czebyszew[j][0] - wezly_Czebyszew[j-i][0]);
		}
	}
}

double interpolacja(double wezly[][2], double x) {
	
	double res = wezly[WEZLY-1][1];
	
	for (int i = WEZLY - 2; i >= 0; i--) {
		res *= (x - wezly[i][0]);
		res += wezly[i][1];
	}
	
	return res;
}

double interpolacja_Czebyszew(double wezly_Czebyszew[][2], double x) {
	
	double res = wezly_Czebyszew[WEZLY-1][1];
	
	for (int i = WEZLY - 2; i >= 0; i--) {
		res *= (x - wezly_Czebyszew[i][0]);
		res += wezly_Czebyszew[i][1];
	}
	
	return res;
}

int main() {
	
	double wezly[WEZLY][2];
	double wezly_Czebyszew[WEZLY][2];
	double h = (KONIEC - START) / N;
	
	fstream wyniki;
	wyniki.open("zad12_wyniki.txt", ios::out);
	if (!wyniki.is_open()) {
		cout << "Nie mozna utworzyc pliku!" << endl;
		return 1;
	}
	
	przygotuj_wielomiany(wezly);
	przygotuj_wielomiany_Czebyszew(wezly_Czebyszew);
	
	for (double x = START; x < KONIEC; x += h) {
		wyniki << x << "\t" << funkcja(x) << "\t" << interpolacja(wezly, x) << "\t" << interpolacja_Czebyszew(wezly_Czebyszew, x) << endl;
	}
	
	wyniki.close();
	return 0;
}