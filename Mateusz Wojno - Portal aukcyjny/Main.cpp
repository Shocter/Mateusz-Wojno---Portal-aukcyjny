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
	int size = 0;
	while (!plik.eof())
	{
		string l;
		getline(plik, l);
		size++;
	}
	plik.close();
	string *tab = new string[size];
	plik.open("plik.txt", ios::in);
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
	delete[] tab;
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

void zapisz_do_pliku(el_listy *lista)
{
	el_listy *wsk = lista;
	fstream plik;
	plik.open("plik.txt", ios::trunc | ios::out);
	int i = 0;
	while (wsk->next != NULL)
	{
		if (i == 0)
		{
			plik << wsk->next->nazwa << endl;
			plik << wsk->next->unikalny_nr << endl;
			plik << wsk->next->kategoria << endl;
			plik << wsk->next->status << endl;
			plik << wsk->next->cena << endl;
			plik << wsk->next->wlasciciel << endl;
			plik << wsk->next->kupujacy << endl;
			plik << wsk->next->opis; 
		}
		else 
		{
			plik << endl;
			plik << wsk->next->nazwa << endl;
			plik << wsk->next->unikalny_nr << endl;
			plik << wsk->next->kategoria << endl;
			plik << wsk->next->status << endl;
			plik << wsk->next->cena << endl;
			plik << wsk->next->wlasciciel << endl;
			plik << wsk->next->kupujacy << endl;
			plik << wsk->next->opis;
		}
		wsk = wsk->next;
		i++;
	}
	plik.close();
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

void kup (el_listy *lista, int nr)
{
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy == "Brak") && (wsk->next->wlasciciel != "Jan Kowalski"))
		{
			wsk->next->kupujacy = "Jan Kowalski";
			wsk->next->status = "Sprzedane";
			cout << "Kupuje..." << endl;
			wsk = wsk->next;
			break;
		}
		else if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy != "Brak"))
		{
			cout << "Nie mozna kupic przedmiotu, poniewaz ktos juz go kupil" << endl;
			wsk = wsk->next;
			break;
		}
		else if ((wsk->next->unikalny_nr == nr) && (wsk->next->wlasciciel == "Jan Kowalski"))
		{
			cout << "Nie mozesz kupic przedmiotu wystawionego przez siebie" << endl;
			wsk = wsk->next;
			break;
		}
		else
		{
			wsk = wsk->next;
		}
	}
}

void edytuj(el_listy *lista, int nr, string nazwa, string kategoria, int cena, string opis)
{
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if (wsk->next->unikalny_nr == nr)
		{
			wsk->next->nazwa = nazwa;
			wsk->next->kategoria = kategoria;
			wsk->next->cena = cena;
			wsk->next->opis = opis;
			wsk = wsk->next;
		}
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
		cout.width(20);
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
	int id;

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
	if (wybor == 1)
	{
		dodaj_do_listy_z_pliku(first);
		do
		{
			system("CLS");

			logo();

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << left;
			cout.width(23);
			cout << "Nazwa przedmiotu";
			cout.width(10);
			cout << "ID";
			cout.width(20);
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
				//logo();

				cout << "Podaj nazwe ";
				cin.clear();
				cin.ignore();
				getline(cin, nazwa);
				cout << "Podaj kateorie ";
				getline(cin, kategoria);
				cout << "Podaj cene ";
				cin >> cena;
				cout << "Podaj opis ";
				cin.clear();
				cin.ignore();
				getline(cin, opis);

				dodaj_do_listy(first, nazwa, kategoria, cena, opis);
				zapisz_do_pliku(first);
				break;
			case 2:
				cout << "Podaj ID aukcji: ";
				cin >> id;
				kup(first, id);
				Sleep(3000);
				zapisz_do_pliku(first);
				break;
			case 3: 
				cout << "Jeszcze nie napisana" << endl;
				break;
			case 4:  
				cout << "Podaj ID aukcji: ";
				cin >> id;
				cout << "Podaj nazwe ";
				cin.clear();
				cin.ignore();
				getline(cin, nazwa);
				cout << "Podaj kateorie ";
				getline(cin, kategoria);
				cout << "Podaj cene ";
				cin >> cena;
				cout << "Podaj opis ";
				cin.clear();
				cin.ignore();
				getline(cin, opis);

				edytuj(first, id, nazwa, kategoria, cena, opis);
				zapisz_do_pliku(first);
				break;
			case 5:
				cout << "Podaj ID aukcji ktora chcesz usuanac: ";
				cin >> id;
				if (usun_z_listy(first, id) == 4)
				{
					system("CLS");
					cout << "Nie mozna usunac aukcji, poniewaz ktos juz kupil na niej przedmiot" << endl;
				}
				zapisz_do_pliku(first);
				break;
			case 6: exit(0); break;
			}
		} while (true);
	}
	else if (wybor == 2)
	{
		cout << "Jeszcze nie napisana" << endl;
	}

	else if (wybor == 3)
	exit(0);

	system("pause");
	return 0;
}