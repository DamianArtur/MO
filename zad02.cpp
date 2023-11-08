#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
	
	double x, log_10_x, wart_f, dokladna_wart_f, log_blad_wzgledny, wart_f_popr, log_blad_wzgledny_popr, epsilon_d = 1.0d;
	
	while (1) { // wyzanczenie epsilon
		if (1.0d + epsilon_d / 2.0d == 1.0d) {
			break;
		}
		epsilon_d /= 2.0d;
	}
	
	ifstream plik_wej;
	ofstream plik_wyj;
	ofstream plik_wyj_popr;
	
	// otwarcie plikow
	plik_wej.open("dane.txt");
	plik_wyj.open("wynik.dat");
	plik_wyj_popr.open("wynik_poprawiony.dat");
	
	if (plik_wej.is_open() && plik_wyj.is_open() && plik_wyj_popr.is_open()) {

		plik_wyj << setprecision(20) << scientific;
		plik_wyj_popr << setprecision(20) << scientific;
			
		while (!plik_wej.eof()) {
			plik_wej >> log_10_x;
			plik_wej >> x;
			plik_wej >> dokladna_wart_f;
			
			wart_f = (1.0d - exp(-1 * x)) / x; // obliczenie z funkcji exp()
			log_blad_wzgledny = log10(abs((wart_f - dokladna_wart_f) / dokladna_wart_f));
			
			plik_wyj << log_10_x << "\t" << log_blad_wzgledny << endl;
			
			if (log_10_x < 0.0d) { // obliczenie z rozwiniecia w szereg Taylora
				wart_f_popr = 0.0d;
				int i = 1;
				double wyraz = 1.0d;
				while (abs(wyraz) > epsilon_d) {
					wart_f_popr += wyraz;
					wyraz *= -1 * x / ((double)i + 1.0d);
					i++;
				}

				log_blad_wzgledny_popr = log10(abs((wart_f_popr - dokladna_wart_f) / dokladna_wart_f));

				plik_wyj_popr << log_10_x << "\t" << log_blad_wzgledny_popr << endl;

			} else {
				
				plik_wyj_popr << log_10_x << "\t" << log_blad_wzgledny << endl;
				
			}	 
		}
			 
	} else {                                                         
		
		cout << "Nie udalo sie otworzyc pliku!" << endl;
				
	}
	
	if (plik_wej.is_open())
		plik_wej.close();
	if (plik_wyj.is_open())
		plik_wyj.close();
	if (plik_wyj_popr.is_open())
		plik_wyj_popr.close();
	                                                                      
	return 0;
}