#include <iostream>
#include <iomanip>
#include <cmath>

#define N 4

using namespace std;

void wypisz_wektor(double* wektor) {
	
	cout << " | ";
	for(int i = 0; i < N; i++) {
		cout << wektor[i] << "\t|\t";
	}
	cout << "\n";
}

void wypisz_macierz(double** M) {
	
	for(int i = 0; i < N; i++) {
		wypisz_wektor(M[i]);
	}
}

void zamien(double* a, double* b) {
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void zamien_w_macierzy(double** a, double** b) {
	double* tmp = *a;
	*a = *b;
	*b = tmp;
}

int wybierz_element_podstawowy(double** M, int n) {
	
	int indeks = n;
	
	for(int i = n+1; i < N; i++) {
		if(fabs(M[i][n]) > fabs(M[indeks][n])) {
			indeks = i;
		}
	}
	
	return indeks;
}

// pierwsza część algorytmu
void dekomponuj_LU(double** A, double** L, double* b) {
	double iloraz, tmp2;
	int element_podstawowy;
	
	for(int i = 0; i < N; i++) {
		
		if(A[i][i] == 0.0d) { // natrafilismy na 0 w rozkladzie
			element_podstawowy = wybierz_element_podstawowy(A, i);
			
			zamien_w_macierzy(&A[i], &A[element_podstawowy]);
			zamien_w_macierzy(&L[i], &L[element_podstawowy]);
			zamien(&b[i], &b[element_podstawowy]);
		}
		
		for(int j = i; j < N-1; j++) {
			iloraz = A[j+1][i] / A[i][i];
			
			for(int k = i; k < N; k++) {
				A[j+1][k] -= A[i][k] * iloraz;
			}
			
			L[j+1][i] = iloraz;
		}
		L[i][i] = 1;
	}
}

// druga część algorytmu
void rozwiaz_rownanie(double** L, double** U, double* b, double* y, double* x) {
	
	// rozwiazanie rownania Ly = b
	for(int i = 0; i < N; i++) {
		y[i] = b[i];
	}
	
	for(int i = 1; i < N; i++) {
		for(int j = i; j < N; j++) {
			y[j] -= y[i-1] * L[j][i-1];
		}
	}
	
	// rozwiązanie równania Ux = y
	double suma = 0;
	
	x[N-1] = y[N-1] / U[N-1][N-1];
	
	for(int i = N-2; i >= 0; i--) {
		for(int j = N-1; j > i; j--) {
			suma += x[j] * U[i][j];
		}
		x[i] = (y[i] - suma) / U[i][i];
		suma = 0;
	}
	
}

int main() {
	
	cout << fixed;
	
	double** A = new double*[N]; 	// macierz A
	double** L = new double*[N]; 	// macierz L
	double** U = A;					// macierz U
	
	double* b = new double[N];		// wektor b
	double* x = new double[N];		// wektor x
	double* y = new double[N];		// wektor y
	
	for(int i = 0; i < N ;i++) { 	// alokacje tablic
		A[i] = new double[N];
		L[i] = new double[N];
	}
	
	// wprowadzenie wartości macierzy A
	A[0][0] = 1.0d;			A[0][1] = -20.0d;		A[0][2] = 30.0d;		A[0][3] = -4.0d;
	A[1][0] = 2.0d;			A[1][1] = -40.0d;		A[1][2] = -6.0d;		A[1][3] = 50.0d;
	A[2][0] = 9.0d;			A[2][1] = -180.0d;		A[2][2] = 11.0d;		A[2][3] = -12.0d;
	A[3][0] = -16.0d;		A[3][1] = 15.0d;		A[3][2] = -140.0d;		A[3][3] = 13.0d;
	
	// wprowadzenie wartości wektora b
	b[0] = 35.0d; 			b[1] = 104.0d;			b[2] = -366.0d;			b[3] = -354.0d;	
	
	// wyzerowanie macierzy L
	for(int i = 0; i < N; i++ ) {
		for(int j = 0; j < N; j++) {
			L[i][j] = 0.0d;
		}
	}
	
	cout << "\tMacierz A: " << endl;
	wypisz_macierz(A);
	cout << "\n";	

	cout << "\tWektor b (przed dekompozycja): " << endl;
	wypisz_wektor(b);
	cout << "\n";
	
	// uruchomienie dekompozycji
	cout << "\tDekomponuje... \n" << endl;
	dekomponuj_LU(A, L, b);
	
	cout << "\tMacierz L: " << endl;
	wypisz_macierz(L);
	cout << "\n";
	
	cout << "\tMacierz U: " << endl;
	wypisz_macierz(U);
	cout << "\n";
	
	cout << "\tWektor b (po dekompozycji): " << endl;
	wypisz_wektor(b);
	cout << "\n";
	
	// rozwiazanie rownania
	cout << "\tRozwiazuje rownanie... \n" << endl;
	rozwiaz_rownanie(L, U, b, y, x); 

	cout << "\tWektor y: " << endl;
	wypisz_wektor(y);
	cout << "\n";
	
	cout << "\tWektor x (rozwiazanie): " << endl;
	wypisz_wektor(x);
	cout << "\n";
	
	for(int i = 0; i < N; i++) {
		delete[] A[i];
		delete[] L[i];
	}
	
	delete[] A;
	delete[] L;
} 