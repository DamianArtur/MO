#include <iostream>
#include <iomanip>
#include <cmath>

#define N 4				// rozmiar macierzy A i wektora b
#define MAX_N 100		// maksymalna liczba iteracji
#define TOLX 1e-12		// zadana tolerancja bledu
#define TOLF 1e-12		// zadana tolerancja residuum
#define OMEGA 0.5d		// parametr omega dla metody SOR

using namespace std;

// funkcja wykorzystujaca metode Jacobiego
void rozwiaz_Jacobiego(double** A, double* b, double* x) {
	
	double* x2 = new double[N];
	for(int i = 0; i < N; i++) {
		x2[i] = 0.0d;
	}
	
	double est = 0.0d; // estymator bledu
	double res = 0.0d; // residuum
	double tmp = 0.0d; // zmienna pomocnicza
	
	cout << "\tMetoda Jacobiego\n\n";
	
	for(int i = 0; i < MAX_N; i++) {
		for(int j = 0; j < N; j++) {
			tmp = 0.0d;
			
			for(int k = 0; k < N; k++) {
				if(j != k) {
					tmp += A[j][k]  * x[k];
				}
			}
			
			x2[j] = (b[j] - tmp) / A[j][j];
			tmp = 0.0d;
			
			for(int k = 0; k < N; k++) {
				tmp += A[j][k]  * x[k];
			}
			
			if(fabs(x2[j] - x[j]) > est) {
				est = fabs(x2[j] - x[j]);
			}
			
			if(fabs(tmp - b[j]) > res) {
				res = fabs(tmp - b[j]);
			}
			
			for(int k = 0; k < N; k++) {
				x[k] = x2[k];
			}
		}
		
		// wyswietlenie wyniku w danym kroku
		cout << i+1 << ".\t\tx[0] = " << x[0] << "\t\tx[1] = " << x[1] << "\t\tx[2] = " << x[2] << "\t\tx[3] = " << x[3] << "\t\test = " << est << "\t\tres = " << res << "\n";
		
		// sprawdzenie warunku zakonczenia iteracji
		if(est < TOLX && res < TOLF) {
			break;
		}
		
		est = 0.0d;
		res = 0.0d;
	}
	cout << "\n\n";
}

// funkcja wykorzystujaca metode Gaussa-Seidela
void rozwiaz_GaussaSeidela(double** A, double* b, double* x) {
	
	double* x2 = new double[N];
	for(int i = 0; i < N; i++) {
		x2[i] = 0.0d;
	}
	
	double est = 0.0d; // estymator bledu
	double res = 0.0d; // residuum
	double tmp = 0.0d; // zmienna pomocnicza
	
	cout << "\tMetoda Gaussa-Seidela\n\n";
	
	for(int i = 0; i < MAX_N; i++) {
		for(int j = 0; j < N; j++) {
			tmp = 0.0d;
			
			for(int k = 0; k < N; k++) {
				if(j != k) {
					tmp += A[j][k]  * x[k];
				}
			}
			
			x2[j] = x[j];
			x[j] = (b[j] - tmp) / A[j][j];
			
			if(fabs(x2[j] - x[j]) > est) {
				est = fabs(x2[j] - x[j]);
			}
		}
		
		for(int j = 0 ; j < N; j++) {
			tmp = 0.0d;
			
			for(int k = 0; k < 4; k++) {
				tmp += A[j][k] * x[k];
			}
			
			if(fabs(tmp - b[j]) > res) {
				res = fabs(tmp - b[j]);
			}
		}
		
		// wyswietlenie wyniku w danym kroku
		cout << i+1 << ".\t\tx[0] = " << x[0] << "\t\tx[1] = " << x[1] << "\t\tx[2] = " << x[2] << "\t\tx[3] = " << x[3] << "\t\test = " << est << "\t\tres = " << res << "\n";
		
		// sprawdzenie warunku zakonczenia iteracji
		if(est < TOLX && res < TOLF) {
			break;
		}
		est = 0.0d;
		res = 0.0d;
	}
	cout << "\n\n";
}

void rozwiaz_SOR(double** A, double* b, double* x) {
	
	double* x2 = new double[N];
	for(int i = 0; i < N; i++) {
		x2[i] = 0.0d;
	}
	
	double est = 0.0d; // estymator bledu
	double res = 0.0d; // residuum
	double tmp = 0.0d;
	
	cout << "\tMetoda SOR\n\n";
	
	for(int i = 0; i < MAX_N; i++) {
		for(int j = 0; j < N; j++) {
			tmp = 0.0d;
			
			for(int k = 0; k < N; k++) {
				if(j != k) {
					tmp += A[j][k]  * x[k];
				}
			}
			
			x2[j] = x[j];
			x[j] = (1.0d - OMEGA) * x[j] + (OMEGA * (b[j] - tmp) / A[j][j]);
			tmp = 0.0d;
			
			for(int k  = 0; k < N; k++) {
				tmp += A[j][k] * x[k];
			}
			
			if(fabs(x2[j] - x[j]) > est) {
				est = fabs(x2[j] - x[j]);
			}
			
			if(fabs(tmp - b[j]) > res) {
				res = fabs(tmp - b[j]);
			}
			
		}

		// wyswietlenie wyniku w danym kroku
		cout << i+1 << ".\t\tx[0] = " << x[0] << "\t\tx[1] = " << x[1] << "\t\tx[2] = " << x[2] << "\t\tx[3] = " << x[3] << "\t\test = " << est << "\t\tres = " << res << "\n";
		
		// sprawdzenie warunku zakonczenia iteracji
		if(est < TOLX && res < TOLF) {
			break;
		}
		
		est = 0.0d;
		res = 0.0d;
	}
	cout << "\n\n";
}

int main() {
	
	cout << setprecision(9) << scientific;
	
	// deklaracja macierzy A i wektorow
	double** A = new double*[N];
	double* b = new double[N];
	double* xJacobiego = new double[N];
	double* xGaussaSeidela = new double[N];
	double* xSOR = new double[N];
	
	// alokacja dla macierzy A
	for(int i = 0; i < N ;i++) {
		A[i] = new double[N];
	}
	
	// wypelnienie macierzy A
	A[0][0] = 100.0d; A[0][1] = -1.0d; A[0][2] = 2.0d; A[0][3] = -3.0d;
	A[1][0] = 1.0d; A[1][1] = 200.0d; A[1][2] = -4.0d; A[1][3] = 5.0d;
	A[2][0] = -2.0d; A[2][1] = 4.0d; A[2][2] = 300.0d; A[2][3] = -6.0d;
	A[3][0] = 3.0d; A[3][1] = -5.0d; A[3][2] = 6.0d; A[3][3] = 400.0d;
	
	// wypelnienie wektora b
	b[0] = 116.0d; b[1] = -226.0d; b[2] = 912.0d; b[3] = -1174.0d;
	
	// wypelnienie wektorow przyblizeniem poczatkowym
	for(int i = 0; i < N; i++) {
		xJacobiego[i]  = xGaussaSeidela[i] = xSOR[i] = 2.0d;
	}
	
	rozwiaz_Jacobiego(A, b, xJacobiego);
	rozwiaz_GaussaSeidela(A, b, xGaussaSeidela);
	rozwiaz_SOR(A, b, xSOR);
	
	for(int i = 0; i < N ;i++) {
		delete[] A[i];
	}
	
	delete[] A;
	delete[] b;
	delete[] xJacobiego;
	delete[] xGaussaSeidela;
	delete[] xSOR;
	
	return 0;
}