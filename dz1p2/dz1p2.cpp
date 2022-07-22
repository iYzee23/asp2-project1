#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int ind;
int endInd;
int inp;
int counterFin;
const int maxx = 45;
int fibb[maxx] = { 0,1 };

void setFibb(int* fibb) {
	for (int i = 2; i < maxx; i++) {
		fibb[i] = fibb[i - 1] + fibb[i - 2];
		//cout << fibb[i] << endl;
	}
}

void function(int k, int arrLen, double targ, double* arr, int exp) {
	int j = fibb[k];
	int p = fibb[k - 1];
	int q = fibb[k - 2];
	int temp;
	while (true) {
		if (targ == arr[j]) {
			x:
			cout << "Found number: ";
			cout << targ / exp << endl;
			cout << "Steps: ";
			cout << ++counterFin << endl << endl;;
			return;
		}
		else if (targ < arr[j]) {
			if (q == 0) {
				if (targ == arr[0]) goto x;
				cout << "You entered invalid number";
				cout << endl << endl;
				return;
			}
			j -= q;
			temp = p;
			p = q;
			q = temp - q;
		}
		else {
			if (p == 1) {
				cout << "You entered invalid number";
				cout << endl << endl;
				return;
			}
			j += q;
			p -= q;
			q -= p;
		}
		counterFin++;
	}
}

void function(int k, int arrLen, double* arr, int exp) {
	int j = fibb[k];
	int p = fibb[k - 1];
	int q = fibb[k - 2];
	int temp, inp, ind = 0;
	double targ;
	while (true) {
		x:
		targ = arr[j];
		cout << "\nTargeted number? " << targ/exp << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - Smaller" << endl;
		cout << "3 - Bigger" << endl;
		cout << "Option? "; cin >> inp;
		switch (inp) {
			case 1:
				cout << "Steps: ";
				cout << ++counterFin << endl << endl;;
				return;
			case 2:
				if (q == 0) {
					if (!ind) {
						ind = 1;
						j = 0;
						goto x;
					}
					cout << "You pressed bad option somewhere";
					cout << endl << endl;
					return;
				}
				j -= q;
				temp = p;
				p = q;
				q = temp - q;
				break;
			case 3:
				if (p == 1) {
					cout << "You pressed bad option somewhere";
					cout << endl << endl;
					return;
				}
				j += q;
				p -= q;
				q -= p;
				break;
			default:
				cout << "Bad input, try again";
				cout << endl << endl;
				break;
		}
		counterFin++;
	}
}

void printMenu() {
	cout << "1 - Play game" << endl;
	cout << "0 - End program" << endl;
	cout << "Option? "; cin >> inp;
}

int main() {
	setFibb(fibb);
	double a, b, targ;
	double* arr;
	int dec, exp, arrLen, k;
	while (!endInd) {
		printMenu();
		switch (inp) {
			case 0:
				endInd = 1;
				cout << "Enjoy your day! :)";
				cout << endl << endl;
				break;
			case 1:
				counterFin = 0;
				cout << "Down limit? "; cin >> a;
				cout << "Up limit? "; cin >> b;
				cout << "Decimal precision? "; cin >> dec;
				//cout << "Targeted number? "; cin >> targ;
				exp = pow(10, dec);
				a = ceil(a * exp);
				b = floor(b * exp);
				arrLen = b - a + 1;
				for (int i = 0; i < maxx; i++) {
					if (fibb[i] - 1 >= arrLen) {
						arrLen = fibb[i] - 1;
						k = i - 1;
						break;
					}
				}
				arr = new double[arrLen];
				for (int i = 0; i < arrLen; arr[i] = a + i, i++);
				//targ = round(targ * exp);
				function(k, arrLen, arr, exp);
				//function(k, arrLen, targ, arr, exp);
				break;
			default:
				cout << "Bad input, try again";
				cout << endl << endl;
				break;
		}
	}
}