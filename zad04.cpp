#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define N 30		// ograniczenie na liczbe iteracji
#define TOLX 1e-12  // zadana tolerancja bledu
#define TOLF 1e-12	// zadana tolerancja residuum

double max3(double tab[3]) {
	double max = tab[0];
	if(tab[1] > max) max = tab[1];
	if(tab[2] > max) max = tab[2];
	return max;
}

double f_1(double v[3]) {
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] - 2.0d;
}

double f_2(double v[3]) {
	return v[0] * v[0] + v[1] * v[1] - 1.0d;
}

double f_3(double v[3]) {
	return v[0] * v[0] - v[1];
}

// funkcja znajdujaca wartosci odwrotnej macierzy Jakobiego
void licz_macierz__odwrotna_Jakobiego(double macierz_odwrotna_Jakobiego[][3], double x_n[3]) {
	
	macierz_odwrotna_Jakobiego[0][0] = 0.0d;
	macierz_odwrotna_Jakobiego[0][1] = 0.0d;
	macierz_odwrotna_Jakobiego[0][2] = 1.0d / (2.0d * x_n[2]);
	macierz_odwrotna_Jakobiego[1][0] = 1.0d / (4.0d * x_n[0] * x_n[1] + 2.0d * x_n[0]);
	macierz_odwrotna_Jakobiego[1][1] = 1.0d / (2.0d * x_n[1] + 1);
	macierz_odwrotna_Jakobiego[1][2] = -1.0d / (2.0d * x_n[2]);
	macierz_odwrotna_Jakobiego[2][0] = x_n[1] / (2.0d * x_n[0] * x_n[1] + x_n[0]);
	macierz_odwrotna_Jakobiego[2][1] = -1 / (2.0d * x_n[1] + 1.0d);
	macierz_odwrotna_Jakobiego[2][2] = 0.0d;
}

int main() {
	
	cout << setprecision(20) << scientific;
	double x_n[3] = {1.0d, 1.0d, 1.1d};		// wektor x_n
	double x_n_nowy[3]; 					// wektor x_n+1
	double fx[3]; 							// wektor f(X_n)
	double d[3];							// delta n_1
	double est[3]; 							// estymatory bledow
	double res[3]; 							// residua
	double estymator, residuum;
	double macierz_odwrotna_Jakobiego[3][3];

	cout << "0:\tx = " << x_n[0] << " | y = " << x_n[1] << " | z = " << x_n[2] << endl;
	
	for(int i = 1; i <= N; i++) {
		
		// wyznaczanie wartosci w odwroconej macierzy Jakobiego
		licz_macierz__odwrotna_Jakobiego(macierz_odwrotna_Jakobiego, x_n);
		
		// wyznaczanie wartosci wektora f(X_n)
		fx[0] = f_1(x_n);
		fx[1] = f_2(x_n);
		fx[2] = f_3(x_n);
		
		// wyznaczenie wektora delta_n+1
		d[0] = fx[0] * macierz_odwrotna_Jakobiego[0][0] + fx[1] * macierz_odwrotna_Jakobiego[0][1] + fx[2] * macierz_odwrotna_Jakobiego[0][2];
		d[1] = fx[0] * macierz_odwrotna_Jakobiego[1][0] + fx[1] * macierz_odwrotna_Jakobiego[1][1] + fx[2] * macierz_odwrotna_Jakobiego[1][2];
		d[2] = fx[0] * macierz_odwrotna_Jakobiego[2][0] + fx[1] * macierz_odwrotna_Jakobiego[2][1] + fx[2] * macierz_odwrotna_Jakobiego[2][2];
		
		// wyznacznie wartosci nowego przyblizenia
		x_n_nowy[0] = x_n[0] - d[0];
		x_n_nowy[1] = x_n[1] - d[1];
		x_n_nowy[2] = x_n[2] - d[2];
		
		// wyznaczenie estymatora bledu i residuum
		est[0] = fabs(x_n[0] - x_n_nowy[0]);
		est[1] = fabs(x_n[1] - x_n_nowy[1]);
		est[2] = fabs(x_n[2] - x_n_nowy[2]);
		res[0] = fabs(f_1(x_n_nowy));
		res[1] = fabs(f_2(x_n_nowy));
		res[2] = fabs(f_3(x_n_nowy));
		estymator = max3(est);
		residuum = max3(res);
		
		// wyswietlenie na ekran wyniku
		cout << i << ":\tx = " << x_n_nowy[0] << " | y = " << x_n_nowy[1] << " | z = " << x_n_nowy[2] << " | est = "<< estymator << " | res = " << residuum << endl;
		
		// sprawdzenie warunkow konca iteracji
		if(estymator <= TOLX && residuum <= TOLF) {
			break;
		}
		
		// podstawienie nowych wartosci przyblizenia wyniku
		x_n[0] = x_n_nowy[0];
		x_n[1] = x_n_nowy[1];
		x_n[2] = x_n_nowy[2];
	}
	
	return 0;
}