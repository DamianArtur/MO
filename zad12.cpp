#include <iostream>
#include "calerf.h"
#include "calerf.cpp"

#define N 1000

using namespace std;

long double dokladna_wartosc(long double x) {
	return calerf::ERF_L(x);
}

double metoda_prostokatow_wariant_A(double x) {
	
	double krok = x / (double)N;
	double y = 0.0d;
	double suma = 0.0d;
	
	for (int i = 0; i < N; i++) {
		suma += exp(-1.0d * y * y);
		y += krok;
	}
	
	return suma * krok * 2 / sqrt(M_PI);
}

double metoda_prostokatow_wariant_B(double x) {
	
	double krok = x / (double)N;
	double y = krok / 2.0d;
	double suma = 0.0d;
	
	for (int i = 0; i < N; i++) {
		suma += exp(-1.0d * y * y);
		y += krok;
	}
	
	return suma * krok * 2 / sqrt(M_PI);
}

int main() {
	cout << dokladna_wartosc(1.0) << endl;
	cout << metoda_prostokatow_wariant_A(1.0) << endl;
	cout << metoda_prostokatow_wariant_B(1.0) << endl;
	cout << endl;
	cout << dokladna_wartosc(1.0) << endl;
	cout << metoda_prostokatow_wariant_A(2.0) << endl;
	cout << metoda_prostokatow_wariant_B(2.0) << endl;
	cout << endl;
	cout << dokladna_wartosc(1.0) << endl;
	cout << metoda_prostokatow_wariant_A(3.0) << endl;
	cout << metoda_prostokatow_wariant_B(3.0) << endl;
	cout << endl;

	return 0;
}