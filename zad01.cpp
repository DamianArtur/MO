#include <iostream>

using namespace std;

int main() {
	
	int mantysa_f = 0; // tutaj znaleziony rozmiar mantysy dla typu float
	int mantysa_d = 0; // tutaj znaleziony rozmiar mantysy dla typu double
	float epsilon_f = 1.0f; // tutaj znaleziona wartosc epsilon dla typu float
	double epsilon_d = 1.0d; // tutaj znaleziona wartosc epsilon dla typu double
	
	while (1) { // generuje kolejne liczby postaci 2^(-t)
		if (1.0f + epsilon_f / 2.0f == 1.0f) { //warunek koncowy
			cout << "Liczba bitow mantysy (float): " << mantysa_f << endl;
			cout << "Epsilon maszynowy (float): " << epsilon_f << endl;
			break;
		}
		epsilon_f /= 2.0f;
		mantysa_f++;
	}
	
	while (1) { // generuje kolejne liczby postaci 2^(-t)
		if (1.0d + epsilon_d / 2.0d == 1.0d) {
			cout << "Liczba bitow mantysy (double): " << mantysa_d << endl;
			cout << "Epsilon maszynowy (double): " << epsilon_d << endl;
			break;
		}
		epsilon_d /= 2.0d;
		mantysa_d++;
	}
	
	return 0;
}