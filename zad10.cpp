#include <iostream>
#include <fstream>
#include <cmath>
#include "calerf.h"
#include "calerf.cpp"

using namespace std;

double D = 1.0;
const double LAMBDA = 0.4;// 1 lub 0.4 dla kmb
const double T_MAX = 2.0;
const double H = 0.1;
const double eps = 1e-16;

const double A = 6.0 * sqrt(D * T_MAX);
const double DT = (LAMBDA * H * H) / D;
const int N = (int)((T_MAX / DT));
const int M = (int)((A / H));	

double** allocMatrix(int n, int m) {
    auto** matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];
    return matrix;
}

double** analitycznie(const double* dt_vec, const double* h_vec, int n, int m) {
    double** flag = allocMatrix(n, m);
    for (int i = 0; i < m; i++)
        flag[0][i] = 0.0;
    for (int i = 0; i < n; i++) {
        flag[i][M - 1] = 0.0;
        flag[i][0] = 1.0;
    }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m - 1; j++)
            flag[i][j] = erfc(h_vec[j] / (2.0 * sqrt(D * dt_vec[i])));
    return flag;
}

long double roz_analityczne(long double time, long double pos) {
	return 1.0 - calerf::ERF_L(pos / 2*sqrt(D* time));
	
}

// procedura pierwsza - działająca na macierzy A
/*void algorytmThomasa_A(double* u, double* d, double* l) {
	
	for (int i = 1; i < N; i++) {
		d[i] = d[i] - (l[i-1] / d[i-1]) * u[i-1];
	}
}

// procedura druga - działająca na wektorze b
void algorytmThomasa_b(double* u, double* d, double* l, double* x, double* b) {
	
	for (int i = 1; i < N; i++) {
		b[i] = b[i] - (l[i-1] / d[i-1]) * b[i-1];
	}
	
	x[N-1] = b[N-1] / d[N-1];
	
	for (int i = N-2; i >= 0; i--) {
		x[i] = (b[i] - u[i] * x[i+1]) / d[i];
	}
}*/

void metodaBezposrenia(double** U, double lambda, int n, int m) {
    for (int i = 0; i < m; i++)
        U[0][i] = 0;
    for (int i = 0; i < n; i++) {
        U[i][M - 1] = 0.0;
        U[i][0] = 1.0;
    }

    for (int k = 1; k < n; k++)
        for (int i = 1; i < m - 1; i++)
            U[k][i] = U[k - 1][i] + lambda * (U[k - 1][i - 1] - (2 * U[k - 1][i]) + U[k - 1][i + 1]);
}

void zapis_do_pliku(const string& fileName, double** matrix, int n, int m) {
    ofstream out;
    out.open(fileName);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            out << matrix[i][j] << "\t";
        out << std::endl;
    }
    out.close();
}

void oblicz_bledy(double** err, double** analit, double** calculatedValues, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            err[i][j] = abs(calculatedValues[i][j] - analit[i][j]);
}

int main() {
	auto* dt_vec = new double[N];
    auto* h_vec = new double[M];
    auto* h_l = h_vec;
    
    double** analityczne = allocMatrix(N, M);
    analityczne = analitycznie(dt_vec, h_vec, N, M);
	
	double** U = allocMatrix(N, M);
    double** errorMatrix = allocMatrix(N, M);
    
    metodaBezposrenia(U, LAMBDA, N, M);
    
    string filename1 = "KMBerrors.txt";
    string filename2 = "KMBvalues.txt";
    
    oblicz_bledy(errorMatrix, analityczne, U, N, M);
    zapis_do_pliku(filename1, errorMatrix, N, M);
    zapis_do_pliku(filename2, U, N, M);
    
    ofstream file04;
    ofstream file10;
    ofstream file16;
    
    string method = "KMB";
    string filename3 = method +"_analit04.txt";
    string filename4 = method +"_analit10.txt";
    string filename5 = method +"_analit16.txt";

    file04.open(filename3);
    file10.open(filename4);
    file16.open(filename5);
    
    for (int i = 0; i < N; i++) {
        if (abs(h_l[i + 1]) < eps || abs(U[100][i + 1]) < eps)
            break;
        file04 << h_l[i + 1] << "\t" << U[100][i + 1] << "\t" << analityczne[100][i + 1] << endl; // d_t = 0.3
    }

    for (int i = 0; i < N; i++) {
        if (abs(h_l[i + 1]) < eps || abs(U[250][i + 1]) < eps)
            break;
        file10 << h_l[i + 1] << "\t" << U[250][i + 1] << "\t" << analityczne[250][i + 1] << endl; // d_t = 1.0
    }

    for (int i = 0; i < N; i++) {
        if (abs(h_l[i + 1]) < eps || abs(U[400][i + 1]) < eps)
            break;
        file16 << h_l[i + 1] << "\t" << U[400][i + 1] << "\t" << analityczne[400][i + 1] << endl; // d_t = 1.7
    }
        
    double* maxerrors = maxErrFL(errorMatrix, N, M);
    ofstream filemaxerrors;
    string filename6 = method+"-time.txt";
    filemaxerrors.open(filename6);
    for (int i = 0; i < N - 1; i++){
        if (abs(dt_vec[i + 1]) < eps || (maxerrors[i + 1]) < eps)
            break;
        filemaxerrors << dt_vec[i + 1] << "\t" << maxerrors[i + 1] << endl;
    }

    cout << method << " " <<  H << " " << maxerrors[M - 1] << endl;

    filemaxerrors.close();

    deleteMatrix(U, N);
    deleteMatrix(errorMatrix, N);
    delete[] maxerrors;
}