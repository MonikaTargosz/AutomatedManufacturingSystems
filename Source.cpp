/*Algorytm Johnsona - system przepływowy
Algorytm wykonuje optymalizację dla pracy dwóch jednostek produkcyjnych na „n” działkach roboczych. 
Algorytm ten pozwala poszukiwać najkrótszy czas pracy dwóch maszyn (oznaczamy je M1, M2) na dowolnej liczbie działek n. 
Na każdej działce, kolejność pracy maszyn jest stała, a więc najpierw pracuje maszyna M1, a potem M2. 
Dane są czasy pracy obu maszyn na każdej działce. Czas pracy maszyny M1 na działce i oznaczamy m1[i] , maszyny M2 na działce i m2[i]*/

#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

void sort(int *m, int size, int *nr_t) {
	bool s;
	do {
		s = false;
		for (int i = 0; i < size - 1; ++i) {
			if (m[i] > m[i + 1]) {
				/*Zamiana wartości numerów maszyn i wartości czasów*/
				swap(m[i], m[i + 1]);
				swap(nr_t[i], nr_t[i + 1]);
				s = true;
			}
		}
	} while (s);
}

int main()
{
	int q_machine = 2;
	int q_task = 6;
	int *M1, *M2, *nr_m, *m1, *m2, *nr_t, *nr_j;

	M1 = new int[q_task];
	M2 = new int[q_task];
	nr_j = new int[q_task + 1];
	nr_m = new int[q_task];
	nr_t = new int[q_task];
	int sum_t1 = 0;

	M1[0] = 5;
	M1[1] = 4;
	M1[2] = 3;
	M1[3] = 2;
	M1[4] = 2;
	M1[5] = 1;

	M2[0] = 5;
	M2[1] = 3;
	M2[2] = 3;
	M2[3] = 1;
	M2[4] = 3;
	M2[5] = 2;

	/*Wybranie wyrobów i, dla których t1i <= t2i*/
	for (int i = 0; i<q_task; i++) {
		if (M1[i] <= M2[i]) {
			sum_t1++;			
		}
	}

	int size = sum_t1;
	m1 = new int[size]; 
	sum_t1 = 0;

	/*Przydzielanie operacji dla wybranych m1*/
	for (int i = 0; i<q_task; i++) {
		if (M1[i] <= M2[i]) {

			m1[sum_t1] = M1[i]; 
			nr_t[sum_t1] = i;
			sum_t1++;
		}
	}

	/*Sortowanie wartości z m1[]*/
	sort(m1, size, nr_t);
	
	/*Szeregowanie w kolejności - t1 rosnąco*/
	sum_t1 = 0;

	for (int i = 0; i<size; i++) {
		nr_m[sum_t1] = nr_t[i];
		sum_t1++;
	}
	delete[] m1;

	/*Dla pozostałych zadań - m2[]*/
	size = q_task - sum_t1;
	m2 = new int[size];
	sum_t1 = 0;

	for (int i = 0; i<q_task; i++) {
		if (M1[i] > M2[i]) {
			m2[sum_t1] = M2[i];
			nr_t[sum_t1] = i;
			sum_t1++;
		}
	}

	/*Sortowanie wartości z m2[]*/
	sort(m2, size, nr_t);

	/*Szeregowanie w kolejności t2 malejąco*/
	sum_t1 = q_task - size;

	for (int i = size - 1; i >= 0; i--) {
		nr_m[sum_t1] = nr_t[i];
		sum_t1++;
	}

	/*Szeregowanie na maszynach*/

	sum_t1 = 0;
	cout << "ALGORYTM JOHNSONA" << "\n";
	cout << "M1: ";
	for (int i = 0; i<q_task; i++) {
		int j = 0;
		/*Wyświetlenie nr zadania tyle razy ile wynosi jego t*/
		while (j<M1[nr_m[i]]) {
			cout << nr_m[i] + 1<<"  ";
			j++;
			sum_t1++;
		}
		if (i == 0)
			nr_j[i] = j;
		else
			nr_j[i] = nr_j[i - 1] + j;
	}
	cout << "\n";

	/*Wypisanie operacji na maszynę wg kolejności z M1[]*/
	int n;
	cout << "M2: ";
	for (int i = 0; i<q_task; i++) {
		int j = 0;
		if (i<q_task - 1)
			n = nr_j[i + 1] - nr_j[i];
		else
			n = 0;
		if (n < M2[nr_m[i]])
			nr_j[i + 1] += M2[nr_m[i]] - n;

		if (i == 0) {
			for (int z = 0; z <M1[nr_m[0]]; z++)
				cout << "_ ";
		}
		while (j<M2[nr_m[i]] || j<n) {
			if (j < M2[nr_m[i]])
				cout << nr_m[i] + 1<<"  ";
			else
				cout << "_ ";
			j++;
		}

	}
	/*Wyznaczenie czasów zakończenia i średniego czasu przepływu*/
	sum_t1 = 0;

	cout << "\n Czasy zakonczenia zlecen:\n";

	for (int i = 0; i<q_task; i++) {
		cout <<nr_m[i] + 1 << " - ";
		cout << nr_j[i] + M2[nr_m[i]] << " \n";
		sum_t1 += nr_j[i] + M2[nr_m[i]];
	}

	cout << "\n Fsr: "<<(sum_t1 / (q_task*1.0))<<"\n";

	/**/
	delete[] M1;
	delete[] M2;
	delete[] nr_m;
	delete[] m2;
	delete[] nr_t;
	delete[] nr_j;
	system("PAUSE");
	return 0;
}
