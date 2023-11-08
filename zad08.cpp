#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#define N 1000
#define M 10
#define M_PI 3.14159265358979323846

using namespace std;

// funkcja sin(x)
template<typename T> T fun(T x) {
	return sin(x);
}

// pochodna z funkcji sin(x)
template<typename T> T poch(T x) {
	return cos(x);
}

// wzor na pochodna przy roznicy wstecznej dwupunktowej
template<typename T> T roznica_wsteczna_2(T x, T h) {
	return (fun(x) - fun(x - h)) / h;
}

// wzor na pochodna przy roznicy centralnej dwupunktowej
template<typename T> T roznica_centralna_2(T x, T h) {
	return (fun(x + h) - fun(x - h)) / ((T)2.0*h);
}

// wzor na pochodna przy roznicy progresywnej dwupunktowej
template<typename T> T roznica_progresywna_2(T x, T h) {
	return (fun(x + h) - fun(x)) / h;
}

// wzor na pochodna przy roznicy wstecznej trzypunktowej
template<typename T> T roznica_wsteczna_3(T x, T h) {
	return ((T)3.0/(T)2.0 * fun(x) - (T)2.0*fun(x - h) + (T)1.0/(T)2.0 * fun(x - h - h)) / h;
}

// wzor na pochodna przy roznicy progresywnej trzypunktowej
template<typename T> T roznica_progresywna_3(T x, T h) {
	return (-(T)3.0/(T)2.0 * fun(x) + (T)2.0*fun(x + h) - (T)1.0/(T)2.0 * fun(x + h + h)) / h;
}

// funkcja znajdujaca wartosci pochodnych wraz z bledami
template<typename T> void licz(T** wyniki, T** bledy, T poczatek, T koniec, T h, T epsilon) {
	T srodek = (poczatek + koniec) / (T)2.0;
	
	for(int i = 0; i < N; i++) {
		if (h < epsilon) {
			break;
		}
		
		wyniki[i][0] = roznica_progresywna_2(poczatek, h);
		wyniki[i][1] = roznica_centralna_2(srodek, h);
		wyniki[i][2] = roznica_wsteczna_2(koniec, h);
		wyniki[i][3] = roznica_progresywna_3(poczatek, h);
		wyniki[i][4] = roznica_progresywna_3(srodek, h);
		wyniki[i][5] = roznica_wsteczna_3(srodek, h);
		wyniki[i][6] = roznica_wsteczna_3(koniec, h);
		wyniki[i][7] = roznica_progresywna_2(srodek, h);
		wyniki[i][8] = roznica_wsteczna_2(srodek, h);
		
		bledy[i][0] = fabs(wyniki[i][0] - poch(poczatek));
		bledy[i][1] = fabs(wyniki[i][1] - poch(srodek));
		bledy[i][2] = fabs(wyniki[i][2] - poch(koniec));
		bledy[i][3] = fabs(wyniki[i][3] - poch(poczatek));
		bledy[i][4] = fabs(wyniki[i][4] - poch(srodek));
		bledy[i][5] = fabs(wyniki[i][5] - poch(srodek));
		bledy[i][6] = fabs(wyniki[i][6] - poch(koniec));
		bledy[i][7] = fabs(wyniki[i][7] - poch(srodek));
		bledy[i][8] = fabs(wyniki[i][8] - poch(srodek));
		bledy[i][9] = h;
		
		h /= (T)1.1;
	}
	
	cout << "Roznica progresywna poczatek dwupunktowa " << wyniki[99][0] << endl;
	cout << "Roznica centralna srodek dwupunktowa " << wyniki[99][1] << endl;
	cout << "Roznica wsteczna koniec dwupunktowa " << wyniki[99][2] << endl;
	cout << "Roznica progresywna poczatek trzypunktowa " << wyniki[99][3] << endl;
	cout << "Roznica progresywna srodek trzypunktowa " << wyniki[99][4] << endl;
	cout << "Roznica wsteczna srodek trzypunktowa " << wyniki[99][5] << endl;
	cout << "Roznica wsteczna koniec trzypunktowa " << wyniki[99][6] << endl;
	cout << "Roznica progresywna srodek dwupunktowa " << wyniki[99][7] << endl;
	cout << "Roznica wsteczna srodek dwupunktowa " <<  wyniki[99][8] << endl;
	
	cout << "\n\n\n";
	cout << "Roznica progresywna poczatek dwupunktowa " << (log10(bledy[20][0]) - log10(bledy[0][0])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica centralna srodek dwupunktowa " << (log10(bledy[20][1]) - log10(bledy[0][1])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica wsteczna koniec dwupunktowa " << (log10(bledy[20][2]) - log10(bledy[0][2])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica progresywna poczatek trzypunktowa " << (log10(bledy[20][3]) - log10(bledy[0][3])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica progresywna srodek trzypunktowa " << (log10(bledy[20][4]) - log10(bledy[0][4])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica wsteczna srodek trzypunktowa " << (log10(bledy[20][5]) - log10(bledy[0][5])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica wsteczna koniec trzypunktowa " << (log10(bledy[20][6]) - log10(bledy[0][6])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica progresywna srodek dwupunktowa " << (log10(bledy[20][7]) - log10(bledy[7][7])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;
	cout << "Roznica wsteczna srodek dwupunktowa " << (log10(bledy[20][8]) - log10(bledy[0][8])) / (log10(bledy[20][9]) - log10(bledy[0][9])) << endl;

}

template<typename T> void zapisz_dane(T** roznice, T h, T epsilon) {
	
	ofstream roznica_progresywna_poczatek_2; 
	ofstream roznica_centralna_srodek_2;
	ofstream roznica_wsteczna_koniec_2;
	ofstream roznica_progresywna_poczatek_3;
	ofstream roznica_progresywna_srodek_3;
	ofstream roznica_wsteczna_srodek_3;
	ofstream roznica_wsteczna_koniec_3;
	ofstream roznica_progresywna_srodek_2;
	ofstream roznica_wsteczna_srodek_2;
	
	// otwarcie plikow
	roznica_progresywna_poczatek_2.open("roznica_progresywna_poczatek_2.txt");
	roznica_centralna_srodek_2.open("roznica_centralna_srodek_2.txt");
	roznica_wsteczna_koniec_2.open("roznica_wsteczna_koniec_2.txt");
	roznica_progresywna_poczatek_3.open("roznica_progresywna_poczatek_3.txt");
	roznica_progresywna_srodek_3.open("roznica_progresywna_srodek_3.txt");
	roznica_wsteczna_srodek_3.open("roznica_wsteczna_srodek_3.txt");
	roznica_wsteczna_koniec_3.open("roznica_wsteczna_koniec_3.txt");
	roznica_progresywna_srodek_2.open("roznica_progresywna_srodek_2.txt");
	roznica_wsteczna_srodek_2.open("roznica_wsteczna_srodek_2.txt");
	
	for(int i = 0; i < N; i++) {
		if(h < epsilon) {
			break;
		}
		
		roznica_progresywna_poczatek_2 << log10(h) << "\t" << log10(roznice[i][0]) << endl;
		roznica_centralna_srodek_2 << log10(h) << "\t" << log10(roznice[i][1]) << endl;
		roznica_wsteczna_koniec_2 << log10(h) << "\t" << log10(roznice[i][2]) << endl;
		roznica_progresywna_poczatek_3 << log10(h) << "\t" << log10(roznice[i][3]) << endl;
		roznica_progresywna_srodek_3 << log10(h) << "\t" << log10(roznice[i][4]) << endl;
		roznica_wsteczna_srodek_3 << log10(h) << "\t" << log10(roznice[i][5]) << endl;
		roznica_wsteczna_koniec_3 << log10(h) << "\t" << log10(roznice[i][6]) << endl;
		roznica_progresywna_srodek_2 << log10(h) << "\t" << log10(roznice[i][7]) << endl;
		roznica_wsteczna_srodek_2 << log10(h) << "\t" << log10(roznice[i][8]) << endl;
		
		h /= (T)1.1;
	}
	
	roznica_progresywna_poczatek_2.close();
	roznica_centralna_srodek_2.close();
	roznica_wsteczna_koniec_2.close();
	roznica_progresywna_poczatek_3.close();
	roznica_progresywna_srodek_3.close();
	roznica_wsteczna_srodek_3.close();
	roznica_wsteczna_koniec_3.close();
	roznica_progresywna_srodek_2.close();
	roznica_wsteczna_srodek_2.close();
}

int main() {
	
	cout << setprecision(12) << scientific;
	
	// alokacja dla tablic typu float
	float** wyniki = new float*[N];
	float** roznice = new float*[N];
	for(int i = 0; i < N; i++) {
		wyniki[i] = new float[M];
	}
	for(int i = 0; i < N; i++) {
		roznice[i] = new float[M];
	}
	
	// alokacja dla tablic typu double
	/*double** wyniki = new double*[N];
	double** roznice = new double*[N];
	for(int i = 0; i < N; i++) {
		wyniki[i] = new double[M];
	}
	for(int i = 0; i < N; i++) {
		roznice[i] = new double[M];
	}*/
	
	licz(wyniki, roznice, 0.0f, (float)M_PI/2.0f, 1.0f, 1e-12f);
	zapisz_dane(roznice, 1.0f, 1e-12f);
	
	//licz(wyniki, roznice, 0.0d, (double)M_PI/2.0d, 1.0d, 1e-18d);
	//zapisz_dane(roznice, 1.0d, 1e-18d);
	
	for(int i = 0; i < N; i++) {
		delete[] wyniki[i];
		delete[] roznice[i];
	}
	delete[] wyniki;
	delete[] roznice;

	return 0;
}