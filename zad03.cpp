#include <iostream>
#include <iomanip>
#include <cmath>

#define N 30 // ograniczenie na liczbe iteracji
#define TOLX 1e-12 // zadana tolerancja bledu
#define TOLF 1e-12 // zadana tolerancja residuum

using namespace std;

// funkcja sin^2(x/4) - x
double f_1(double x) {
	return sin(x / 4.0d) * sin(x / 4.0d) - x;
}

// funkcja pochodna z f_1: 1/4 * sin(x/2) - 1
double f_1_pochodna(double x) {
	return (1.0d / 4.0d) * sin(x / 2.0d) - 1.0d;
}

// funkcja tan(2x) - x - 1
double f_2(double x) {
	return tan(2.0d * x) - x - 1.0d;
}

// funckcja pochodna z f_2: 2.0d / (cos^2(2x)) - 1
double f_2_pochodna(double x) {
	return 2.0d / (cos(2.0d * x) * cos(2.0d * x)) - 1.0d;
}

// fukcja 1 dla metody Picarda: sin^2(x/4)
double f_1_Picard(double x) {
	return sin(x / 4.0d) * sin(x / 4.0d);
}

// funkcja 2 dla metody Picarda: tan(2x) - 1
double f_2_Picard(double x) {
	return tan(2.0d * x) - 1.0d;
}

// funkcja pochodna 1 dla metody Picarda: 1/4 * sin(x/2)
double f_1_Picard_pochodna(double x) {
	return (1.0d / 4.0d) * sin(x / 2.0d);
}

// funkcja pochodna 2 dla metody Picarda: 2 / cos^2(2x)
double f_2_Picard_pochodna(double x) {
	return 2.0d / (cos(2.0d * x) * cos(2.0d * x));
}

// implementacja metody Picarda
void metoda_Picarda(double (*f)(double), double (*f_Picard)(double), double (*f_Picard_pochodna)(double), double x0) {
	if(!(fabs(f_Picard_pochodna(x0)) < 1.0d)) {
		cout << "wartosc bezwzgledna z pochodnej funkcji phi(x) nie jest mniejsza od 1 -> metoda nie moze byc zastosowana" << endl << endl;
		return;
	}
	
	double x1;
	double est; // estymator bledu
	double res; // residuum
	
	for(int i = 1; i < N; i++) {
		x1 = f_Picard(x0);
		
		est = fabs(x1 - x0);
		res = fabs(f(x1));
		
		cout << i << ":\tx1 = " << x1 << "\t\test = " << est << "\tres = " << res << endl;
		
		if(est <= TOLX && res <= TOLF) {
			break;
		}
		
		x0 = x1;
	}
}

// implementacja metody bisekcji
void metoda_bisekcji(double (*f)(double), double a, double b) {	
	if((f(a) < 0.0d && f(b) < 0.0d) || (f(a) > 0.0d && f(b) > 0.0d)) {
		cout << "f(a) i f(b) nie sa roznego znaku -> metoda nie moze byc zastosowana" << endl << endl;
		return;
	}
	
	double x;
	double est; // estymator bledu
	double res; // residuum
	
	for(int i = 1; i <= N; i++) {
		x = (a + b) / 2.0d;
		est = fabs((b-a) / 2.0d);
		res = fabs(f(x));
		
		cout << i << ":\tx = " << x << "\t\test = " << est << "\tres = " << res << endl;
		
		if(est <= TOLX && res <= TOLF) {
			break;
		}
		
		if(f(x) > 0) {
			if(f(a) > 0) {
				a = x;
			} else {
				b = x;
			}
		} else {
			if(f(a) > 0) {
				b = x;
			} else {
				a = x;
			}
		}
	}
}

// implementacja metody Newtona
void metoda_newtona(double (*f)(double), double (*f_pochodna)(double), double x0) {
	double x1;
	double est; // estymator bledu
	double res; // residuum
	
	for(int i = 1; i <= N; i++) {
		x1 = x0 - (f(x0) / f_pochodna(x0));
		est = fabs(x1 - x0);
		res = fabs(f(x1));
		
		cout << i << ":\tx_1 = " << x1 << "\test = " << est << "\tres = " << res << endl;
		
		if(est <= TOLX && res <= TOLF) {
			break;
		}
		
		x0 = x1;		
	}
}

// implementacja metody siecznych
void metoda_siecznych(double (*f)(double), double x0, double x1) {
	double x2;
	double est; // estymator bledu
	double res; // residuum
	
	for(int i = 1; i <= N; i++) {
		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
		est = fabs(x2 - x1);
		res = fabs(f(x2));
		
		cout << i << ":\tx_1 = " << x2 << "\test = " << est << "\tres = " << res << endl;
		
		if(est <= TOLX && res <= TOLF) {
			break;
		}
		
		x0 = x1;
		x1 = x2;
	}
}

int main() {
	
	cout << setprecision(12) << scientific;
	
	cout << "\n\n\t\t Metoda Picarda (funkcja 1): \n\n";
	metoda_Picarda(f_1, f_1_Picard, f_1_Picard_pochodna, 1.0d);
	
	cout << "\n\n\t\t Metoda Picarda (funkcja 2): \n\n";
	metoda_Picarda(f_2, f_2_Picard, f_2_Picard_pochodna, 0.7d);
	
	cout << "\n\n\t\t Metoda bisekcji (funkcja 1): \n\n";
	metoda_bisekcji(f_1, -1.5d, 0.7d);
	
	cout << "\n\n\t\t Metoda bisekcji (funkcja 2): \n\n";
	metoda_bisekcji(f_2, 0.0d, 0.7d);
	
	cout << "\n\n\t\t Metoda Newtona (funkcja 1): \n\n";
	metoda_newtona(f_1, f_1_pochodna, 1.0d);
	
	cout << "\n\n\t\t Metoda Newtona (funkcja 2): \n\n";
	metoda_newtona(f_2, f_2_pochodna, 0.7d);
	
	cout << "\n\n\t\t Metoda siecznych (funkcja 1): \n\n";
	metoda_siecznych(f_1, -0.5d, 0.7d);
	
	cout << "\n\n\t\t Metoda siecznych (funkcja 2): \n\n";
	metoda_siecznych(f_2, 0.0d, 1.0d);

	return 0;
}