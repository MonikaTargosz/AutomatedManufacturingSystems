#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void sortownia(int *Sortowanie, int RozmiarSortu, int *kolejka);
int main()
{

	int LiczbaMaszyn = 2;
	int LiczbaZadan = 10;
	int *zadaniaM1, *zadaniaM2, *stos, *Sortowanie, *kolejka, *lista;

	FILE *heurystyka;
	heurystyka = fopen("C:Pulpit\heurystyka.txt", "w");

	//    cout << "Liczba zadan: ";
	//    cin >> LiczbaZadan;

	zadaniaM1 = new int[LiczbaZadan];
	zadaniaM2 = new int[LiczbaZadan];
	lista = new int[LiczbaZadan + 1];
	// wprowadzanie danych 
	int SumaCzasu = 0;
	/*    for(int i=0; i<LiczbaZadan;i++){
	cout << "\nczas na obu maszynach zadania nr." << i+1 << ": ";
	cin >> zadaniaM1[i] >> zadaniaM2[i];
	SumaCzasu += zadaniaM1[i];
	}
	*/
	zadaniaM1[0] = 2;
	zadaniaM1[1] = 0;
	zadaniaM1[2] = 1;
	zadaniaM1[3] = 3;
	zadaniaM1[4] = 5;
	zadaniaM1[5] = 6;
	zadaniaM1[6] = 7;
	zadaniaM1[7] = 4;
	zadaniaM1[8] = 2;
	zadaniaM1[9] = 3;


	zadaniaM2[0] = 7;
	zadaniaM2[1] = 3;
	zadaniaM2[2] = 0;
	zadaniaM2[3] = 3;
	zadaniaM2[4] = 1;
	zadaniaM2[5] = 2;
	zadaniaM2[6] = 0;
	zadaniaM2[7] = 5;
	zadaniaM2[8] = 6;
	zadaniaM2[9] = 4;

	SumaCzasu = 41;

	/*********************************************************/
	stos = new int[LiczbaZadan];
	kolejka = new int[LiczbaZadan];

	int SumaStosu = 0;

	for (int i = 0; i<LiczbaZadan; i++) {
		if (zadaniaM1[i] <= zadaniaM2[i]) {
			SumaStosu++;
		}
	}

	int RozmiarSortu = SumaStosu;
	Sortowanie = new int[RozmiarSortu];
	SumaStosu = 0;
	for (int i = 0; i<LiczbaZadan; i++) {
		if (zadaniaM1[i] <= zadaniaM2[i]) {

			Sortowanie[SumaStosu] = zadaniaM1[i];
			kolejka[SumaStosu] = i;
			SumaStosu++;
		}
	}

	/*********************************************/
	sortownia(Sortowanie, RozmiarSortu, kolejka);
	/*********************************************/

	SumaStosu = 0;

	for (int i = 0; i<RozmiarSortu; i++) {
		stos[SumaStosu] = kolejka[i];
		SumaStosu++;
	}
	delete[] Sortowanie;

	RozmiarSortu = LiczbaZadan - SumaStosu;
	Sortowanie = new int[RozmiarSortu];
	SumaStosu = 0;

	for (int i = 0; i<LiczbaZadan; i++) {
		if (zadaniaM1[i] > zadaniaM2[i]) {
			Sortowanie[SumaStosu] = zadaniaM2[i];
			kolejka[SumaStosu] = i;
			SumaStosu++;
		}
	}

	/*********************************************/
	sortownia(Sortowanie, RozmiarSortu, kolejka);
	/*********************************************/

	SumaStosu = LiczbaZadan - RozmiarSortu;

	for (int i = RozmiarSortu - 1; i >= 0; i--) {
		stos[SumaStosu] = kolejka[i];
		SumaStosu++;
	}
	/*********************************************/
	// wpisywanie na maszyny

	fprintf(heurystyka, "Heurystyka:\n");

	SumaStosu = 0;
	fprintf(heurystyka, "\nM1\n");
	for (int i = 0; i<LiczbaZadan; i++) {
		int j = 0;
		while (j<zadaniaM1[stos[i]]) {
			fprintf(heurystyka, "%d ", stos[i] + 1);
			j++;
			SumaStosu++;
		}
		if (i == 0)
			lista[i] = j;
		else
			lista[i] = lista[i - 1] + j;
	}

	int licznik;

	fprintf(heurystyka, "\nM2\n");
	for (int i = 0; i<LiczbaZadan; i++) {
		int j = 0;
		if (i<LiczbaZadan - 1)
			licznik = lista[i + 1] - lista[i];
		else
			licznik = 0;
		if (licznik < zadaniaM2[stos[i]])
			lista[i + 1] += zadaniaM2[stos[i]] - licznik;
		if (i == 0) {
			for (int z = 0; z<zadaniaM1[stos[0]]; z++)
				fprintf(heurystyka, "_ ");
		}
		while (j<zadaniaM2[stos[i]] || j<licznik) {
			if (j < zadaniaM2[stos[i]])
				fprintf(heurystyka, "%d ", stos[i] + 1);
			else
				fprintf(heurystyka, "_ ");
			j++;
		}

	}
	/*********************************************/
	//czasy zakoñczenia i œredni czas

	SumaStosu = 0;
	fprintf(heurystyka, "\n\nCzasy zakonczenia:\n");
	for (int i = 0; i<LiczbaZadan; i++) {
		fprintf(heurystyka, "C%d -> %d\n", stos[i] + 1, lista[i] + zadaniaM2[stos[i]]);
		SumaStosu += lista[i] + zadaniaM2[stos[i]];
	}
	fprintf(heurystyka, "\nF -> %f\n", (SumaStosu / (LiczbaZadan*1.0)));

	cout << "a teraz zobacz do \"D:\\heurystyka.txt\"\n\n";
	/**********************************************/
	// usuwanie œmieci
	fclose(heurystyka);

	delete[] zadaniaM1;
	delete[] zadaniaM2;
	delete[] stos;
	delete[] Sortowanie;
	delete[] kolejka;
	delete[] lista;
	system("PAUSE");
	return 0;
}

void sortownia(int *Sortowanie, int RozmiarSortu, int *kolejka) {
	bool swapped;
	do {
		swapped = false;
		for (int i = 0; i < RozmiarSortu - 1; ++i) {
			if (Sortowanie[i] > Sortowanie[i + 1]) {
				swap(Sortowanie[i], Sortowanie[i + 1]);
				swap(kolejka[i], kolejka[i + 1]);
				swapped = true;
			}
		}
	} while (swapped);
}