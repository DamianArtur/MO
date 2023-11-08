#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double alfa = 0.0, beta = 1.0, gamma = -1.0, fi = 0.0, psi = 1.0, theta = 0.0, p = 1.0, q = 0.0, r = 1.0, s = 0.0;

double **matrixA;
double *vectorX, *vectorB, *accFValue, *tmpVector;
double *B, *X, *L, *U, *D;

double rozwiazanie(double x) {
	return (exp(2.0 - 2.0*x) - 4.0 * exp(4.0-2.0*x) + 4.0 * exp(2.0*x) - exp(2.0 + 2.0*x) -x -x*exp(4)) / (4.0 - 4.0 * exp(4));
}

void algorytmThomasa(double *X, double *B, double *L, double *U, double *D, const int n) {
	for(int i = 1; i < n; i++) {
		D[i] = D[i] - (L[i-1] * U[i-1] / D[i-1]);
		B[i] = B[i] - (L[i-1] * D[i-1] / B[i-1]);
	}
	X[n-1] = 1.0 / D[n-1] * B[n-1];
	
	for(int i = n - 2; i >= 0; i--) {
		X[i] = 1.0 / D[i] * (B[i] - U[i] * X[i+1]);
	}
}

double liczBlad(double *X, double start, double h, int n) {
	double *Blad = new double[n];
	double MaxBlad = fabs(X[0] - rozwiazanie(start));
	
	for(int i = 0; i < n; i++) {
		Blad[i] = fabs(X[i] - rozwiazanie(start));
		if (MaxBlad < Blad[i]) {
			MaxBlad = Blad[i];
		}
		start += h;
	}
	return MaxBlad;
}

bool zapisDoPliku(string nazwa, double krokX, double *X, double h, int n) {
	ofstream File;
	File.open(nazwa.c_str(), ios_base::out);
	
	if(!File.good()) {
		return false;
	} else {
		for(int i = 0; i < n; i++) {
			File << krokX << "\t" << rozwiazanie(krokX) << "\t" << X[i] << endl;
			krokX += h;
		}
	}
	
	File.close();
	return true;
}

double metodaNumerowa(double h, int n, double x0, double x1) {
	B = new double[n];
	D = new double[n];
	L = new double[n-1];
	U = new double[n-1];
	X = new double[n];
	
	B[0] = - gamma;
	D[0] = beta - (alfa / h);
	U[0] = alfa / h;
	B[n-1] = - theta;
	D[n-1] = psi+ (fi / h);
	L[n-2] = -fi / h;
	
	for(int i = 1; i < n -1; i++) {
		D[i] = ((-2.0 *p) / (h*h)) + (r * (10.0 / 12.0));
		U[i] = (p / (h*h)) + (r / 12.0);
		L[i-1] = (p/(h*h)) + (r / 12.0);
		B[i] = (x0 + i * h - h) / 12.0 + ((10.0 / 12.0) * (x0 + i *h)) + (x0 + i *h+h) / 12.0;
		
	}

	algorytmThomasa(X, B, U, L, D, n);

	if(!(zapisDoPliku("metoda_numerowa.txt", x0, X, h, n))) {
		cout << "Blad zapisu";
	}
	double blad = liczBlad(X, x0, h, n);
	
	delete[] B;
	delete[] D;
	delete[] U;
	delete[] L;
	delete[] X;
	
	return blad;
}

double metodaKonwekcjonalna(double h, int n, double x0 ,double x1) {
		B = new double[n];
	D = new double[n];
	L = new double[n-1];
	U = new double[n-1];
	X = new double[n];
	
	B[0] = - gamma;
	D[0] = beta - (alfa / h);
	U[0] = alfa / h;
	B[n-1] = - theta;
	D[n-1] = psi+ (fi / h);
	L[n-2] = -fi / h;
	
	for(int i = 1; i < n -1; i++) {
		D[i] = r + (-2.0 * p) / (h*h);
		L[i-1] = (p / (h*h)) + (q / (2.0 *h));
		U[i] = (p / (h*h))  +(q / (2.0*h));
		B[i] = (i*h)  +x0;
	}
	
	algorytmThomasa(X, B, U, L, D, n);

	if(!(zapisDoPliku("metoda_konwekcjonalna.txt", x0, X, h, n))) {
		cout << "Blad zapisu";
		
	}
	double blad = liczBlad(X, x0, h, n);
	
	delete[] B;
	delete[] D;
	delete[] U;
	delete[] L;
	delete[] X;
	
	return blad;
}

int main() {
	int start = 10;
	int MAX = 1000;
	int step = 10;
	
	double x0 = 0.0;
	double x1 = 1.0;
	double h, bladNumerowa, bladKonwekcjonalnej;
	
	fstream File;
	File.open("blad.txt", ios::out);
	
	for(int i = start; i < MAX; i+= step) {
		h = (x1-x0) / (i-1.0);
		bladKonwekcjonalnej = metodaKonwekcjonalna(h, i, x0, x1);
		bladNumerowa = metodaNumerowa(h, i , x0, x1);
		
		File << log10(h) << " " << log10(bladKonwekcjonalnej) << " " << log10(bladNumerowa) << endl;
		
	}
	
	File.close();
	return 0;
}
