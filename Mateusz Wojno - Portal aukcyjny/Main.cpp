#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

typedef struct element {
	struct element *next;
	string nazwa;
	int unikalny_nr;
	string kategoria;
	string status;
	int cena;
	string wlasciciel;
	string kupujacy;
	string opis;
} el_listy;

el_listy *first;

void dodaj(el_listy *lista, int i, string tab[], int size)
{
	el_listy *wsk, *nowy;
	wsk = lista;
	while (wsk->next != NULL)
	{
		wsk = wsk->next; /*znajaduje ostatni el listy*/
	}
	nowy = new el_listy;
	nowy->nazwa = tab[i];
	i++;
	nowy->unikalny_nr = stoi(tab[i]);
	i++;
	nowy->kategoria = tab[i];
	i++;
	nowy->status = tab[i];
	i++;
	nowy->cena = stoi(tab[i]);
	i++;
	nowy->wlasciciel = tab[i];
	i++;
	nowy->kupujacy = tab[i];
	i++;
	nowy->opis = tab[i];

	nowy->next = NULL;
	wsk->next = nowy;	/*podczepiam wsk po ten element*/
}

void dodaj_do_listy_z_pliku(el_listy *lista)
{
	fstream plik;
	plik.open("plik.txt", ios::in);
#define size 24
	string tab[size];
	for (int i = 0; i < size; i++)
	{
		string line;
		getline(plik, line);
		tab[i] = line;
	}
	plik.close();
	int i = 0;
	while (i < size)
	{
		dodaj(first, i, tab, size);
		i = i + 8;
	}
}

void dodaj_do_listy(el_listy *lista, string nazwa, string kategoria, int cena, string opis)
{
	srand(time(NULL));
	el_listy *wsk, *nowy;
	wsk = lista;
	while (wsk->next != NULL)
	{
		wsk = wsk->next; /*znajaduje ostatni el listy*/
	}
	nowy = new el_listy;
	nowy->nazwa = nazwa;
	nowy->unikalny_nr = (std::rand() % 889) + 1111;
	nowy->kategoria = kategoria;
	nowy->status = "Na sprzedaz";
	nowy->cena = cena;
	nowy->wlasciciel = "Jan Kowalski";
	nowy->kupujacy = "Brak";
	nowy->opis = opis;
	nowy->next = NULL;
	wsk->next = nowy; /*podczepiam wsk po ten element*/
}

int usun_z_listy(el_listy *lista, int nr)
{
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy == "Brak"))
		{
			el_listy *usuwany = wsk->next;
			wsk->next = usuwany->next;   /* przesuwam wsk aby omijal usuwany el */
			delete(usuwany);
		}
		else if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy != "Brak"))
			return 4;
		else
		{
			wsk = wsk->next;
		}
	}
}

void wypisz_liste(el_listy *lista)
{
	el_listy *wsk = lista;
	while (wsk != NULL)
	{
		cout << left;
		cout.width(23);
		cout << wsk->nazwa;
		cout.width(10);
		cout << wsk->unikalny_nr;
		cout.width(15);
		cout << wsk->kategoria;
		cout.width(15);
		cout << wsk->status;
		cout.width(10);
		cout << wsk->cena;
		cout.width(25);
		cout << wsk->wlasciciel;
		cout.width(25);
		cout << wsk->kupujacy;
		cout.width(60);
		cout << wsk->opis << endl;
		wsk = wsk->next;
	}
}

void logo()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << internal;
	cout.width(100);
	cout << "============================" << endl << endl;
	cout << internal;
	cout.width(100);
	cout << "ALLEDROGO - Portal aukcyjny" << endl << endl;
	cout << internal;
	cout.width(100);
	cout << "============================" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int main()
{
	string nazwa;
	string kategoria;
	string status;
	int cena;
	string opis;

	first = new el_listy;
	first->nazwa = "Monitor Dell";
	first->unikalny_nr = 1011;
	first->kategoria = "Monitory";
	first->status = "Na sprzedaz";
	first->cena = 740;
	first->wlasciciel = "Mariusz Brzozowski";
	first->kupujacy = "Brak";
	first->opis = "Monitor nowy w promocyjnej cenie";
	first->next = NULL;

	logo();

	cout << "MENU WYBORU" << endl;
	cout << "1. Lista aukcji" << endl;
	cout << "2. Lista klientow" << endl;
	cout << "3. Wyjscie z programu" << endl;
	cout << "Twoj wybor: ";
	int wybor;
	cin >> wybor;
	switch (wybor)
	{
	case 1: 
		system("CLS");

		logo();

		dodaj_do_listy_z_pliku(first); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << left;
		cout.width(23);
		cout << "Nazwa przedmiotu";
		cout.width(10);
		cout << "ID";
		cout.width(15);
		cout << "Kategoria";
		cout.width(15);
		cout << "Status";
		cout.width(10);
		cout << "Cena";
		cout.width(25);
		cout << "Wlasciciel";
		cout.width(25);
		cout << "Kupujacy";
		cout.width(60);
		cout << "Opis przedmiotu" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 

		wypisz_liste(first); 

		cout << endl << "MENU WYBORU" << endl;
		cout << "1. Wystaw przedmiot na sprzedaz" << endl;
		cout << "2. Kup przedmiot" << endl;
		cout << "3. Filtruj aukcje" << endl;
		cout << "4. Edytuj aukcje" << endl;
		cout << "5. Usun aukcje" << endl;
		cout << "6. Wyjscie z programu" << endl;
		cout << "Twoj wybor: ";
		cin >> wybor;

		switch (wybor)
		{
		case 1:
			system("CLS");
			logo();

			cout << "Podaj nazwe ";
			getline(cin, nazwa);
			cout << "Podaj kateorie ";
			getline(cin, kategoria);
			cout << "Podaj cene ";
			cin >> cena;
			cout << "Podaj opis ";
			getline(cin, opis);

			dodaj_do_listy(first, nazwa, kategoria, cena, opis);

			system("CLS");
			logo();

			wypisz_liste(first);

			break;
		case 2: cout << "Jeszcze nie napisana" << endl; break;
		case 3: cout << "Jeszcze nie napisana" << endl; break;
		case 4: cout << "Jeszcze nie napisana" << endl; break;
		case 5: 
			int numerek;
			cout << "Podaj ID aukcji ktora chcesz usuanac: " << endl;
			cin >> numerek;
			if (usun_z_listy(first, numerek) == 4)
			{
				system("CLS");
				cout << "Nie mozna usunac aukcji, poniewaz ktos juz kupil na niej przedmiot" << endl;
			}
			wypisz_liste(first);
			break;
		case 6: exit(0); break;
		}
			
	case 2: cout << "Jeszcze nie napisana" << endl; break;
	case 3: exit(0); break;
	}

	system("pause");
	return 0;
}