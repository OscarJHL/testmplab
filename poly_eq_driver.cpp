#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string toString(int n, double *p){
	string msg;
	msg = "P(x)=" + to_string(p[0]) + " + ";
		for(int i = 1; i <= n; i++) {
			msg = msg + to_string(p[i]) + " x^" + to_string(i) + " + ";
		}
	return msg;
}

void printPoly(int n, double *p){
	cout << toString(n, p) << endl;
}

double * generatePossibleRoots(int n, double *p, int &npr){
	double *pr1 = new double[(int)p[0]],
		*prf,
		*pr2 = new double[(int)p[n]];
	int count1 = 0, count2 = 0;
	for (int i = 0; i < (p[0] / 2) + 1; i++){
		if ((int)p[0] % (i + 1) == 0){
			pr1[count1] = i + 1;
			count1++;
			if (p[0] / (i + 1) != i + 1){
				pr1[count1] = i + 1;
				count1++;
			}
		}
	}
	for (int i = 0; i < (p[n] / 2) + 1; i++){
		if ((int)p[n] % (i + 1) == 0){
			pr2[count2] = i + 1;
			count2++;
			if (p[n] / (i + 1) != i + 1){
				pr2[count2] = i + 1;
				count2++;
			}
		}
	}
	prf = new double[count1*count2 * 2];
	int j = 0;
	int k = 0;
	bool sign = false;
	for (int i = 0; i < count1*count2 * 2; i++){
		if (sign){
			prf[i] = -pr1[j] / pr2[k];
			j++;
			if (j == count1){
				j = 0;
				k++;
			}
		}
		else{
			prf[i] = pr1[j] / pr2[k];
			j++;
			if (j == count1){
				j = 0;
				k++;
			}
		}
		if (k == count2&&!sign){
			k = 0;
			sign = true;
		}
	}
	return prf;
}

bool readPolyFromFile(string fileName, int &n, double * &p){
	bool flag = false;
	ifstream ifs;
	ifs.open(fileName);
	if (ifs.is_open()){
		flag = true;
		ifs >> n;
		p = new double[n + 1];
		for (int i = 0; i <= n;i++){
			ifs >> p[i];
		}
		ifs.close();
	}
	else{
	
	}
	return flag;
}
//nr-numero real de raices racionales
double * solveBySynDiv(int n, double *p, int &nr){
	int npr;//numero de posibles raices
	//reordenamos p
	double *p2 = new double[n + 1];
	for (int i = 0; i <= n;i++){
		p2[i] = p[n-i];
	}
	//declaramos arreglos necesarios
	double *pr = new double[12];//caso particular
	double *q = new double[n+1];
	double *r = new double[n];
	//llamamos a la funcion que genera las posibles raices;



	/*npr = 12;
	pr[0] = -1.0;
	pr[1] = -1.0/2.0;
	pr[2] = -3.0;
	pr[3] = -3.0/2.0;
	pr[4] = -9.0;
	pr[5] = -9.0/2.0;
	pr[6] = 1.0;
	pr[7] = 1.0/ 2.0;
	pr[8] = 3.0;
	pr[9] = 3.0/ 2.0;
	pr[10] = 9.0;
	pr[11] = 9.0 / 2.0;*/
	pr=generatePossibleRoots(n,p,npr);
	//algoritmo de division sintetica:
	int i = 0;
	int j = 0;
	while (i<npr&&j<n){
		//fill q
		q[0] = p2[0];
		for (int k = 1; k <= n;k++){
			q[k] = q[k - 1] * pr[i] + p2[k];
		}
		if (fabs(q[n]) <= 0.000000001){
			r[j] = pr[i];
			j++;
			i++;
		}
		else{
			i++;
		}
	}
	nr = j;
	return r;
}
void printRoots(int nr,double *r){
	cout << "Raices racionales: " << nr << endl;
	for (int i = 0; i < nr; i++){
		cout <<"Raiz "<<i<<":"<< r[i] << endl;
	}
}

int main(){
	int n; //orden del polinomio
	int nr;//numero de raices
	double *p; //arreglo del polinomio p:a0+a1x...+anx^n
	double *r;//arreglo de raices racionales del polinomio p
	if (readPolyFromFile("poly.data", n, p)){
		printPoly(n, p);
		r = solveBySynDiv(n, p, nr);
		printRoots(nr,r);
	}
	else{
		cout << "sorry, no se pudo abrir" << endl;
	}
	return 0;
}