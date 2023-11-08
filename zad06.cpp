#include <iostream>
#include <iomanip>

#define N 6

using namespace std;

void wypisz_wektor(double* wektor, int rozmiar) {
	
	for(int i = 0; i < rozmiar; i++) {
		cout << wektor[i] << ",\t";
	}
	cout << endl;
}

// procedura pierwsza - działająca na macierzy A
void algorytmThomasa_A(double* U, double* D, double* L, double* E) {
	
	E[0] = D[0];  // przepisanie pierwszej wartości
	
	for (int i = 1; i < N; i++) { // wyliczenie wektora Eta ze znanego wzoru
		E[i] = D[i] - L[i-1] * U[i-1] / E[i-1];
	}
}

// procedura druga - działająca na wektorze b
void algorytmThomasa_b(double* U, double* L, double* B, double* X, double* E, double* R) {
	
	R[0] = B[0]; // przepisanie pierwszej wartości
	
	for(int i = 1; i < N; i++) { // wyliczenie wektora R ze znanego wzoru
		R[i] = B[i] - L[i-1] * R[i-1] / E[i-1];
	}
	
	X[N-1] = R[N-1] / E[N-1]; // znalezienie rozwiązania dla X_n
	
	for(int i = N-2; i >= 0; i--) { // znalezienie pozostałych rozwiązań
		X[i] = (R[i] - U[i] * X[i+1]) / E[i];
	}
}

int main() {
	
	cout << setprecision(12) << scientific;
	
	double* U = new double[N-1]; // wektor wartości nad przekątną
	double* D = new double[N];   // wektor wartości na przekątnej
	double* L = new double[N-1]; // wektor wartości pod przekątną
	double* B = new double[N];   // wektor B
	double* E = new double[N];   // wektor Eta
	double* R = new double[N];   // wektor R
	double* X = new double[N];   // wektor rozwiązania
	
	// zdefiniowanie macierzy A
	U[0] = 1.0d / 2.0d;		U[1] = 1.0d / 4.0d;		U[2] = 1.0d / 6.0d;		U[3] = 1.0d / 8.0d;		U[4] = 1.0d / 10.0d;
	D[0] = 10.0d;			D[1] = 20.0d;			D[2] = 30.0d;			D[3] = 30.0d;			D[4] = 20.0d;			D[5] = 10.0d;
	L[0] = 1.0d / 3.0d;		L[1] = 1.0d / 5.0d;		L[2] = 1.0d / 7.0d;		L[3] = 1.0d / 9.0d;		L[4] = 1.0d / 11.0d;
	B[0] = 31.0d;			B[1] = 165.0d / 4.0d;	B[2] = 917.0d / 30.0d;	B[3] = 851.0d / 28.0d;	B[4] = 3637.0d / 90.0d;	B[5] = 332.0d / 11.0d;
	
	// wywołanie procedur algorytmu Thomasa
	algorytmThomasa_A(U, D, L, E);
	algorytmThomasa_b(U, L, B, X, E, R);
	
	// wypisanie wyników
	cout << "Wektor U:\t";
	wypisz_wektor(U, N-1);
	
	cout << "Wektor D:\t";
	wypisz_wektor(D, N);
	
	cout << "Wektor L:\t";
	wypisz_wektor(L, N-1);
	
	cout << "Wektor B:\t";
	wypisz_wektor(B, N);
	
	cout << "Wektor E:\t";
	wypisz_wektor(E, N);
	
	cout << "Wektor R:\t";
	wypisz_wektor(R, N);
	
	cout << "Wektor X:\t";
	wypisz_wektor(X, N);
	
	delete[] U;
	delete[] D;
	delete[] L;
	delete[] B;
	delete[] E;
	delete[] R;
	delete[] X;
	
	return 0;
}