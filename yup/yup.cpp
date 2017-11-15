#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

long long int t = 0;

int alg_partycjoujacy(long long int tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby
											//sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	int x = tablica[p]; // obieramy x, czyli oœ
	int i = p, j = r;
	int w; // i, j - indeksy w tabeli
	while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (tablica[j] > x) // dopoki elementy sa wieksze od x
			j--;
		while (tablica[i] < x) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
			t++;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

void quicksort(long long int tablica[], int p, int r) 
{
	int q;
	if (p < r)
	{
		q = alg_partycjoujacy(tablica, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(tablica, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

void kopcowe(long long int tablica[], int N, long long int &T)
{
	int i, indeksOjca, indeksSyna, m, x, bufor;

	for (i = 2; i < N; i++)
	{
		indeksOjca = i; 
		indeksSyna = indeksOjca / 2;
		x = tablica[i];

		while ((indeksSyna > 0) && (tablica[indeksSyna] < x))
		{
			tablica[indeksOjca] = tablica[indeksSyna];
			indeksOjca = indeksSyna; 
			indeksSyna = indeksSyna / 2;
		}
		tablica[indeksOjca] = x;
	}

	for (i = N; i > 1; i--)
	{
		bufor = tablica[1];
		tablica[1] = tablica[i];
		tablica[i] = bufor;

		indeksOjca = 1; 
		indeksSyna = 2;

		while (indeksSyna < i)
		{

			if ((indeksSyna + 1 < i) && (tablica[indeksSyna + 1] > tablica[indeksSyna]))
				m = indeksSyna + 1;
			else
				m = indeksSyna;
			if (tablica[m] <= tablica[indeksOjca])
				break;

			bufor = tablica[indeksOjca];
			tablica[indeksOjca] = tablica[m];
			tablica[m] = bufor;

			indeksOjca = m; 
			indeksSyna = indeksOjca + indeksOjca;
			T++;

		}

	}
}

void merge(long long int *tab, int poczatek, int mid, int koniec)
{
	//p,k - granice sortowanej aktulnie podtablicy
	//mid - srodek tablicy, granica kazdej z podtablic przy podziale na pol

	//jedna tablica od p do mid, druga od mid do k

	int *tmp = new int[koniec - poczatek + 1];

	int i = poczatek, j = mid + 1; //iteratory dla pierwszej i drugiej czesci tablicy
	int m = 0; //iterator dla tablicy pomocniczej

			   //mid - p rozmiar 1. tab
			   //k - mid rozmiar 2. tab

	while (i != mid + 1 && j != koniec + 1) //iterator dochodzi do ostatniego elementu w jednej z tablic
	{
		if (tab[i] < tab[j])    
			tmp[m++] = tab[i++];
		else tmp[m++] = tab[j++];
	}

	if (i == mid && j == koniec) 
		for (int l = poczatek, m = 0; l < koniec + 1; l++, m++) 
			tab[l] = tmp[m];

	if (i == mid + 1) 
		for (j; j < koniec + 1; j++, m++) 
			tmp[m] = tab[j];
	else if (j == koniec + 1) 
		for (i; i < mid + 1; i++, m++) 
			tmp[m] = tab[i];

	//for (int jk = 0; jk < koniec - poczatek + 1; jk++) 
	//	cout << tmp[jk] << ' ';
	//cout << "\n";

	for (int l = poczatek, m = 0; l <= koniec; l++, m++) 
		tab[l] = tmp[m]; //spisujemy dane posortowane z tablicy pomocniczej
																 // delete tmp;

	return;
}

void mergeSort(long long int *tab, int poczatek, int koniec)
{
	int mid = (poczatek + koniec) / 2;
	//cout << mid;
	//_getch();

	if (poczatek != koniec)
	{
		mergeSort(tab, poczatek, mid); //sortujemy lewa czesc tablicy
		mergeSort(tab, mid + 1, koniec); //sortujemy prawa czesc tablicy
		merge(tab, poczatek, mid, koniec); //scalamy posortowane czesci
	}
	return;
}

void mojSort(long long int temp[], int dlugosc)
{
	int indexMaxa = 0, MIN = temp[0], MAX = temp[0];
	long long int *tablica = new long long int[dlugosc];

	for (int i = 1; i < dlugosc; i++)
	{
		if (temp[i] < MIN)
		{
			MIN = temp[i];
		}
	}
	//cout << endl << MIN;
	//_getch();
	while (t < dlugosc)
	{

		for (int i = 1; i < dlugosc; i++)
		{
			if (temp[i] > MAX)
			{
				MAX = temp[i];
				indexMaxa = i;
			}
			//else
			//	indexMaxa = 0;
		}
		temp[indexMaxa] = MIN;
		//MAX = MIN;
		tablica[t] = MAX;
		MAX = MIN;
		t++;
	}

	for (int a = 0; a < dlugosc; a++)
		temp[a] = tablica[a];

}

int partition(long long int c[], int a, int b)
//int partition(string c[], int a, int b)
{
	int e, tmp;
//	string e, tmp;
	e = c[a];        //elemennt dzielacy
	while (a<b)
	{
		while ((a<b) && (c[b] >= e)) b--;
		while ((a<b) && (c[a] <  e)) a++;
		if (a<b)
		{
			tmp = c[a];
			c[a] = c[b];
			c[b] = tmp;
		}
	}
	return a;
}

int main()
{
	clock_t start = clock();
//	printf("Czas wykonywania: %lu ms\n", clock() - start);
//	cout << "Czas: " << clock() - start;
	int i, /*t = 0*/ n, ile;
	long double C, czas;
	char odp2, odp;
	srand(time(NULL));
	cout << "ktory algorytm? (1/2/3/4/5/6)?" << endl;

	odp = _getch();

	if (odp == '1')
	{
		string a;
		char p;
		cout << "Podaj ciag: ";
		cin >> a;
		n = a.length();
		
		while (t != n)
		{
			cout << a[t] << " ";
			t++;
		}
		t = 0;
		//	long long int n = a.length();

		i = 0;


		cout << /*n <<*/ endl;







		C = (double)t / ((double)n*(double)n);
		i = 0;

		while (i != n)
		{
			cout << a[i] << " ";
			i++;
		}
		ile = n;
		start = clock();

		for (int j = 1; j < n; j++)
		{
			p = a[j];
			i = j - 1;

			while (i >= 0 && a[i] > p)
			{
				a[i + 1] = a[i];
				i--;
				t++;
				//cout << "A";
			}
			t++;

			a[i + 1] = p;

		}
		czas = clock() - start;
		C = (double)t / ((double)n*(double)n);
//		C = (double)t / double(n * log2(n));

		i = 0;
		cout << endl;
		while (i != ile - 1)
		{
			cout << a[i + 1] << " ";
			i++;
		}
		cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
		cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;


	}
	else if (odp == '2')
	{

	

		cout << "rêcznie czy auto (r/a)?" << endl;
		odp2 = _getch();

		if (odp2 == 'r')
		{
			int k = 0;
			cout << endl << "podaj ile: ";
			cin >> n; ile = n;
			long long int *a = new long long int[n];

//			cout << "'k' aby zakonczyæ " << endl;
			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}

			while (k != n)
			{
				cout << endl << "podaj kolejny: ";
				cin >> a[k];
				k++;
			}

			while (t != ile)
			{
				cout << a[t] << " ";
				t++;
			}
			t = 0;
			cout << /*n <<*/ endl;
			start = clock();

			quicksort(a, 0, n - 1);
			czas = clock() - start;
			C = (double)t / ((double)n*(double)n);
			i = 0;
			cout << endl;
			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}
			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;


		}
		else
		{
			cout << endl << "podaj ile: ";
			cin >> n;	ile = n;
			long long int *a = new long long int[n];

			for (int j = 0; j <= n; j++)
			{
				a[j] = (rand() % 100);
			}

			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}
			while (t != ile)
			{
				cout << a[t] << " ";
				t++;
			}
			t = 0;
			i = 0;

			cout << /*n <<*/ endl;
			start = clock();

			quicksort(a, 0, n - 1);
			czas = clock() - start;
			C = (double)t / ((double)n*(double)n);
			i = 0;
			cout << endl;
			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}
			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;

		}
		// string a;

	}
	else if (odp == '3')
	{
		cout << "rêcznie czy auto (r/a)?" << endl;
		odp2 = _getch();

		if (odp2 == 'r')
		{
			int k = 0;
			cout << endl << "podaj ile: ";
			cin >> n; ile = n;
			long long int *a = new long long int[n + 1];

			//			cout << "'k' aby zakonczyæ " << endl;
			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}

			while (k != n)
			{
				cout << endl << "podaj kolejny: ";
				cin >> a[k];
				k++;
			}

			while (t != ile)
			{
				cout << a[t] << " ";
				t++;
			}
			t = 0;
			cout << /*n <<*/ endl;
			start = clock();
			kopcowe(a, n + 1, t);
			czas = clock() - start;
			C = (double)t / double(n * log2(n));
			i = 0;
			cout << endl;
			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}
			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;

		}
		else
		{
			cout << endl << "podaj ile: ";
			cin >> n;	ile = n;
			long long int *a = new long long int[n + 1];

			for (int j = 0; j <= n + 1; j++)
			{
				a[j] = (rand() % 100);
			}

			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}
			while (t != ile - 1)
			{
				cout << a[t + 1] << " ";
				t++;
			}
			t = 0;
			i = 0;

		//	cout << "iuageefiuaehofoaeihfoia" << endl;
			start = clock();
			kopcowe(a, n + 1, t);
			czas = clock() - start;
			C = (double)t / double(n * log2(n));
			i = 0;
			cout << endl;
			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}
			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;

			//delete a;

		}
	//	kopcowe(a,);


	}
	else if (odp == '4')

	{
		cout << "rêcznie czy auto (r/a)?" << endl;
		odp2 = _getch();

		if (odp2 == 'r')
		{
			int k = 0;
			cout << endl << "podaj ile: ";
			cin >> n; ile = n;
			long long int *a = new long long int[n + 1];

			//			cout << "'k' aby zakonczyæ " << endl;
			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}

			while (k != n)
			{
				cout << endl << "podaj kolejny: ";
				cin >> a[k];
				k++;
			}

			while (t != ile)
			{
				cout << a[t] << " ";
				t++;
			}

			t = 0;
			cout << /*n <<*/ endl;

			start = clock();
//			kopcowe(a, n + 1, t);
			mergeSort(a, 0, n - 1);

			czas = clock() - start;

			C = (double)t / double(n * log2(n));
			i = 0;
			cout << endl;

			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}
			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;
			delete a;

		}
		else
		{
			cout << endl << "podaj ile: ";
			cin >> n;	ile = n;
			long long int *a = new long long int[n];

			for (int j = 0; j <= n; j++)
			{
				a[j] = (rand() % 100);
			}

			if (n > 20)
			{
				cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
				cin >> ile;
			}
			while (t != ile - 1)
			{
				cout << a[t + 1] << " ";
				t++;
			}
			t = 0;
			i = 0;

			//	cout << "iuageefiuaehofoaeihfoia" << endl;
			start = clock();
	//		kopcowe(a, n + 1, t);
			mergeSort(a, 0, n - 1);

			czas = clock() - start;

			C = (double)t / double(n * log2(n));
			i = 0;
			cout << endl;

			while (i != ile - 1)
			{
				cout << a[i + 1] << " ";
				i++;
			}

			cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
			cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;

			// delete a;

		}
		//	kopcowe(a,);


	}
	else if (odp == '5')
	{
		cout << endl << "podaj ile: ";
		cin >> n;	ile = n;
		long long int *a = new long long int[n];

		for (int j = 0; j <= n; j++)
		{
			a[j] = (rand() % 100);
		}

		if (n > 20)
		{
			cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
			cin >> ile;
		}
		while (t != ile - 1)
		{
			cout << a[t] << " ";
			t++;
		}
		t = 0;
		i = 0;

		//	cout << "iuageefiuaehofoaeihfoia" << endl;
		start = clock();
		//		kopcowe(a, n + 1, t);
		mojSort(a, n - 1);
//		_getch();
		czas = clock() - start;

		C = (double)t / double(n * log2(n));
		i = 0;
		cout << endl;

		while (i != ile - 1)
		{
			cout << a[i] << " ";
			i++;
		}

		cout << endl << "Ilosc: " << ile << endl << "Zamian: " << t << endl << C << endl;
		cout << "Czas: " << czas / CLOCKS_PER_SEC /*/ 100*/;

//		delete a;

	}
	else
	{
		int n, i, j, k, w;

		cout << endl << "podaj ile: ";
		cin >> n;	ile = n;
		long long int *a = new long long int[n];
		//string a[100];
		for (int j = 0; j <= n; j++)
		{
			a[j] = (rand() % 100000);
		//	cin >> a[j];
		}

		if (n > 20)
		{
			cout << "jest wiecej niz 20. Ile wyswietlic? " << endl;
			cin >> ile;
		}
		while (t != ile - 1)
		{
			cout << a[t] << " ";
			t++;
		}

		cout << endl << "Podaj ktory element obliczyc" << endl;
		cin >> w;
		//w--;
		//algorytm Hoare'a
		i = 0;
		j = n - 1;
		n = w;
		while (i != j)
		{
			k = partition(a, i, j);
			k = k - i + 1;
			if (k >= w) j = i + k - 1;
			if (k<w)
			{
				w -= k;
				i += k;
			}
		}

		cout << endl << n << "element ciagu to" << a[i] << endl;
	//	_getch();
	}
//	char p;
switch (odp)
{
case 49:
	cout << "kutas";
	break;

case 50:
	break;

case 51:
	break;

case 52:
	break;

case 53:
	break;

case 54:
	break;

default:
	break;
}
	_getch();
    return 0;
}

