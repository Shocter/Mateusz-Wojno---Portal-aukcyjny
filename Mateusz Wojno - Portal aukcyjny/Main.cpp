#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

typedef struct aukcje {
	struct aukcje *next;
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

typedef struct klienci {
	struct klienci *nextt;
	string imie;
	string nazwisko;
	int kwota_zakupow;
	int kwota_sprzedanych;
	string kupione;
	string wystawione;
} el_klientow;

el_klientow *firstt;

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

void usun_z_listy(el_listy *lista, int nr)
{
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy == "Brak"))
		{
			el_listy *usuwany = wsk->next;
			wsk->next = usuwany->next;   /* przesuwam wsk aby omijal usuwany el */
			delete(usuwany);
			cout << "Usuwam..." << endl;
			break;
		}
		else if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy != "Brak"))
		{
			cout << "Nie mozna usunac przedmiotu, poniewaz ktos juz go kupil" << endl;
			wsk = wsk->next;
			break;
		}
		else
		{
			wsk = wsk->next;
		}
	}
}

void kup(el_listy *lista, int nr, el_klientow *listaa)
{
	el_listy *wsk = lista;
	el_klientow *wskk = listaa;
	while (wsk->next != NULL)
	{
		if ((wsk->next->unikalny_nr == nr) && (wsk->next->kupujacy == "Brak") && (wsk->next->wlasciciel != "Jan Kowalski"))
		{
			int cena;
			string nazwa;
			wsk->next->kupujacy = "Jan Kowalski";
			wsk->next->status = "Sprzedane";
			cena = wsk->next->cena;
			nazwa = wsk->next->nazwa;
			cout << "Kupuje..." << endl;
			wsk = wsk->next;
			while (wskk->nextt != NULL)
			{
				if ((wskk->nextt->imie == "Jan") && (wskk->nextt->nazwisko == "Kowalski"))
				{
					wskk->nextt->kwota_zakupow += cena;
					string kupione;
					kupione = wskk->nextt->kupione;
					wskk->nextt->kupione = kupione.insert(kupione.length(), ", ");
					wskk->nextt->kupione = kupione.insert(kupione.length(), nazwa);
					wskk = wskk->nextt;
				}
				break;
			}
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

void sortowanie_cena()
{
	unsigned short int ilosc = 0;
	for (el_listy * wsk = first; wsk; wsk = wsk->next) ++ilosc;
	long int temp_cena;
	string temp_mazwa;
	long int temp_nr;
	string temp_kategoria;
	string temp_status;
	string temp_wlasciciel;
	string temp_kupujacy;
	string temp_opis;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_listy * wsk = first; wsk->next; wsk = wsk->next)
			if (wsk->cena < wsk->next->cena)
			{
				temp_cena = wsk->cena;
				wsk->cena = wsk->next->cena;
				wsk->next->cena = temp_cena;

				temp_mazwa = wsk->nazwa;
				wsk->nazwa = wsk->next->nazwa;
				wsk->next->nazwa = temp_mazwa;

				temp_nr = wsk->unikalny_nr;
				wsk->unikalny_nr = wsk->next->unikalny_nr;
				wsk->next->unikalny_nr = temp_nr;

				temp_kategoria = wsk->kategoria;
				wsk->kategoria = wsk->next->kategoria;
				wsk->next->kategoria = temp_kategoria;

				temp_status = wsk->status;
				wsk->status = wsk->next->status;
				wsk->next->status = temp_status;

				temp_wlasciciel = wsk->wlasciciel;
				wsk->wlasciciel = wsk->next->wlasciciel;
				wsk->next->wlasciciel = temp_wlasciciel;

				temp_kupujacy = wsk->kupujacy;
				wsk->kupujacy = wsk->next->kupujacy;
				wsk->next->kupujacy = temp_kupujacy;

				temp_opis = wsk->opis;
				wsk->opis = wsk->next->opis;
				wsk->next->opis = temp_opis;
			}
}

void sortowanie_nazwy()
{
	unsigned short int ilosc = 0;
	for (el_listy * wsk = first; wsk; wsk = wsk->next) ++ilosc;
	long int temp_cena;
	string temp_mazwa;
	long int temp_nr;
	string temp_kategoria;
	string temp_status;
	string temp_wlasciciel;
	string temp_kupujacy;
	string temp_opis;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_listy * wsk = first; wsk->next; wsk = wsk->next)
			if (wsk->nazwa > wsk->next->nazwa)
			{
				temp_cena = wsk->cena;
				wsk->cena = wsk->next->cena;
				wsk->next->cena = temp_cena;

				temp_mazwa = wsk->nazwa;
				wsk->nazwa = wsk->next->nazwa;
				wsk->next->nazwa = temp_mazwa;

				temp_nr = wsk->unikalny_nr;
				wsk->unikalny_nr = wsk->next->unikalny_nr;
				wsk->next->unikalny_nr = temp_nr;

				temp_kategoria = wsk->kategoria;
				wsk->kategoria = wsk->next->kategoria;
				wsk->next->kategoria = temp_kategoria;

				temp_status = wsk->status;
				wsk->status = wsk->next->status;
				wsk->next->status = temp_status;

				temp_wlasciciel = wsk->wlasciciel;
				wsk->wlasciciel = wsk->next->wlasciciel;
				wsk->next->wlasciciel = temp_wlasciciel;

				temp_kupujacy = wsk->kupujacy;
				wsk->kupujacy = wsk->next->kupujacy;
				wsk->next->kupujacy = temp_kupujacy;

				temp_opis = wsk->opis;
				wsk->opis = wsk->next->opis;
				wsk->next->opis = temp_opis;
			}
}

void sortowanie_status()
{
	unsigned short int ilosc = 0;
	for (el_listy * wsk = first; wsk; wsk = wsk->next) ++ilosc;
	long int temp_cena;
	string temp_mazwa;
	long int temp_nr;
	string temp_kategoria;
	string temp_status;
	string temp_wlasciciel;
	string temp_kupujacy;
	string temp_opis;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_listy * wsk = first; wsk->next; wsk = wsk->next)
			if (wsk->status < wsk->next->status)
			{
				temp_cena = wsk->cena;
				wsk->cena = wsk->next->cena;
				wsk->next->cena = temp_cena;

				temp_mazwa = wsk->nazwa;
				wsk->nazwa = wsk->next->nazwa;
				wsk->next->nazwa = temp_mazwa;

				temp_nr = wsk->unikalny_nr;
				wsk->unikalny_nr = wsk->next->unikalny_nr;
				wsk->next->unikalny_nr = temp_nr;

				temp_kategoria = wsk->kategoria;
				wsk->kategoria = wsk->next->kategoria;
				wsk->next->kategoria = temp_kategoria;

				temp_status = wsk->status;
				wsk->status = wsk->next->status;
				wsk->next->status = temp_status;

				temp_wlasciciel = wsk->wlasciciel;
				wsk->wlasciciel = wsk->next->wlasciciel;
				wsk->next->wlasciciel = temp_wlasciciel;

				temp_kupujacy = wsk->kupujacy;
				wsk->kupujacy = wsk->next->kupujacy;
				wsk->next->kupujacy = temp_kupujacy;

				temp_opis = wsk->opis;
				wsk->opis = wsk->next->opis;
				wsk->next->opis = temp_opis;
			}
}

void sortowanie_kategoria()
{
	unsigned short int ilosc = 0;
	for (el_listy * wsk = first; wsk; wsk = wsk->next) ++ilosc;
	long int temp_cena;
	string temp_mazwa;
	long int temp_nr;
	string temp_kategoria;
	string temp_status;
	string temp_wlasciciel;
	string temp_kupujacy;
	string temp_opis;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_listy * wsk = first; wsk->next; wsk = wsk->next)
			if (wsk->kategoria > wsk->next->kategoria)
			{
				temp_cena = wsk->cena;
				wsk->cena = wsk->next->cena;
				wsk->next->cena = temp_cena;

				temp_mazwa = wsk->nazwa;
				wsk->nazwa = wsk->next->nazwa;
				wsk->next->nazwa = temp_mazwa;

				temp_nr = wsk->unikalny_nr;
				wsk->unikalny_nr = wsk->next->unikalny_nr;
				wsk->next->unikalny_nr = temp_nr;

				temp_kategoria = wsk->kategoria;
				wsk->kategoria = wsk->next->kategoria;
				wsk->next->kategoria = temp_kategoria;

				temp_status = wsk->status;
				wsk->status = wsk->next->status;
				wsk->next->status = temp_status;

				temp_wlasciciel = wsk->wlasciciel;
				wsk->wlasciciel = wsk->next->wlasciciel;
				wsk->next->wlasciciel = temp_wlasciciel;

				temp_kupujacy = wsk->kupujacy;
				wsk->kupujacy = wsk->next->kupujacy;
				wsk->next->kupujacy = temp_kupujacy;

				temp_opis = wsk->opis;
				wsk->opis = wsk->next->opis;
				wsk->next->opis = temp_opis;
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

void znajdz(el_listy *lista)
{
	cout << "Podaj nazwe aukcji ktora chesz wyszukac" << endl;
	string nazwa;
	cin >> nazwa;
	el_listy *wsk = lista;
	while (wsk->next != NULL)
	{
		size_t znaleziona_pozycja = wsk->nazwa.find(nazwa);
		if (znaleziona_pozycja != std::string::npos)
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
		else
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

void dodaj_klienci(el_klientow *lista, int i, string tab[], int size)
{
	el_klientow *wsk, *nowy;
	wsk = lista;
	while (wsk->nextt != NULL)
	{
		wsk = wsk->nextt; /*znajaduje ostatni el listy*/
	}

	nowy = new el_klientow;
	nowy->imie = tab[i];
	i++;
	nowy->nazwisko = tab[i];
	i++;
	nowy->kwota_zakupow = stoi(tab[i]);
	i++;
	nowy->kwota_sprzedanych = stoi(tab[i]);
	i++;
	nowy->kupione = tab[i];
	i++;
	nowy->wystawione = tab[i];


	nowy->nextt = NULL;
	wsk->nextt = nowy;	/*podczepiam wsk po ten element*/
}

void dodaj_do_listy_z_pliku_klienci(el_klientow *lista)
{
	fstream klienci;
	klienci.open("klienci.txt", ios::in);
	int size = 0;
	while (!klienci.eof())
	{
		string l;
		getline(klienci, l);
		size++;
	}
	klienci.close();
	string *tab = new string[size];
	klienci.open("klienci.txt", ios::in);
	for (int i = 0; i < size; i++)
	{
		string line;
		getline(klienci, line);
		tab[i] = line;
	}
	klienci.close();
	int i = 0;
	while (i < size)
	{
		dodaj_klienci(firstt, i, tab, size);
		i = i + 6;
	}
	delete[] tab;
}

void dodaj_do_listy_klienci(el_klientow *lista, string imie, string nazwisko)
{
	el_klientow *wsk, *nowy;
	wsk = lista;
	while (wsk->nextt != NULL)
	{
		wsk = wsk->nextt; /*znajaduje ostatni el listy*/
	}
	nowy = new el_klientow;
	nowy->imie = imie;
	nowy->nazwisko = nazwisko;
	nowy->kwota_zakupow = 0;
	nowy->kwota_sprzedanych = 0;
	nowy->kupione = "Brak";
	nowy->wystawione = "Brak";
	nowy->nextt = NULL;
	wsk->nextt = nowy; /*podczepiam wsk po ten element*/
}

void zapisz_do_pliku_klienci(el_klientow *lista)
{
	el_klientow *wsk = lista;
	fstream klienci;
	klienci.open("klienci.txt", ios::trunc | ios::out);
	int i = 0;
	while (wsk->nextt != NULL)
	{
		if (i == 0)
		{
			klienci << wsk->nextt->imie << endl;
			klienci << wsk->nextt->nazwisko << endl;
			klienci << wsk->nextt->kwota_zakupow << endl;
			klienci << wsk->nextt->kwota_sprzedanych << endl;
			klienci << wsk->nextt->kupione << endl;
			klienci << wsk->nextt->wystawione;
		}
		else
		{
			klienci << endl;
			klienci << wsk->nextt->imie << endl;
			klienci << wsk->nextt->nazwisko << endl;
			klienci << wsk->nextt->kwota_zakupow << endl;
			klienci << wsk->nextt->kwota_sprzedanych << endl;
			klienci << wsk->nextt->kupione << endl;
			klienci << wsk->nextt->wystawione;
		}
		wsk = wsk->nextt;
		i++;
	}
	klienci.close();
}

void usun_z_listy_klienci(el_klientow *lista, string imie, string nazwisko)
{
	el_klientow *wsk = lista;
	while (wsk->nextt != NULL)
	{
		if ((wsk->nextt->imie == imie) && (wsk->nextt->nazwisko == nazwisko))
		{
			el_klientow *usuwany = wsk->nextt;
			wsk->nextt = usuwany->nextt;   /* przesuwam wsk aby omijal usuwany el */
			delete(usuwany);
			cout << "Usuwam..." << endl;
			break;
		}
		else
		{
			wsk = wsk->nextt;
		}
	}
}

void edytuj_klienci(el_klientow *lista, string imie, string nazwisko, string nowe_imie, string nowe_nazwisko)
{
	el_klientow *wsk = lista;
	while (wsk->nextt != NULL)
	{
		if ((wsk->nextt->imie == imie) && (wsk->nextt->nazwisko == nazwisko))
		{
			wsk->nextt->imie = nowe_imie;
			wsk->nextt->nazwisko = nowe_nazwisko;
			wsk = wsk->nextt;
		}
		else
		{
			wsk = wsk->nextt;
		}
	}
}

void sortowanie_kupione_klienci()
{
	unsigned short int ilosc = 0;
	for (el_klientow * wsk = firstt; wsk; wsk = wsk->nextt) ++ilosc;
	long int temp_kwota_zakupow;
	string temp_imie;
	long int temp_kwota_sprzedanych;
	string temp_nazwisko;
	string temp_kupione;
	string temp_wystawione;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_klientow * wsk = firstt; wsk->nextt; wsk = wsk->nextt)
			if (wsk->kwota_zakupow < wsk->nextt->kwota_zakupow)
			{
				temp_kwota_zakupow = wsk->kwota_zakupow;
				wsk->kwota_zakupow = wsk->nextt->kwota_zakupow;
				wsk->nextt->kwota_zakupow = temp_kwota_zakupow;

				temp_imie = wsk->imie;
				wsk->imie = wsk->nextt->imie;
				wsk->nextt->imie = temp_imie;

				temp_kwota_sprzedanych = wsk->kwota_sprzedanych;
				wsk->kwota_sprzedanych = wsk->nextt->kwota_sprzedanych;
				wsk->nextt->kwota_sprzedanych = temp_kwota_sprzedanych;

				temp_nazwisko = wsk->nazwisko;
				wsk->nazwisko = wsk->nextt->nazwisko;
				wsk->nextt->nazwisko = temp_nazwisko;

				temp_kupione = wsk->kupione;
				wsk->kupione = wsk->nextt->kupione;
				wsk->nextt->kupione = temp_kupione;

				temp_wystawione = wsk->wystawione;
				wsk->wystawione = wsk->nextt->wystawione;
				wsk->nextt->wystawione = temp_wystawione;
			}
}

void sortowanie_sprzedane_klienci()
{
	unsigned short int ilosc = 0;
	for (el_klientow * wsk = firstt; wsk; wsk = wsk->nextt) ++ilosc;
	long int temp_kwota_zakupow;
	string temp_imie;
	long int temp_kwota_sprzedanych;
	string temp_nazwisko;
	string temp_kupione;
	string temp_wystawione;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_klientow * wsk = firstt; wsk->nextt; wsk = wsk->nextt)
			if (wsk->kwota_sprzedanych < wsk->nextt->kwota_sprzedanych)
			{
				temp_kwota_zakupow = wsk->kwota_zakupow;
				wsk->kwota_zakupow = wsk->nextt->kwota_zakupow;
				wsk->nextt->kwota_zakupow = temp_kwota_zakupow;

				temp_imie = wsk->imie;
				wsk->imie = wsk->nextt->imie;
				wsk->nextt->imie = temp_imie;

				temp_kwota_sprzedanych = wsk->kwota_sprzedanych;
				wsk->kwota_sprzedanych = wsk->nextt->kwota_sprzedanych;
				wsk->nextt->kwota_sprzedanych = temp_kwota_sprzedanych;

				temp_nazwisko = wsk->nazwisko;
				wsk->nazwisko = wsk->nextt->nazwisko;
				wsk->nextt->nazwisko = temp_nazwisko;

				temp_kupione = wsk->kupione;
				wsk->kupione = wsk->nextt->kupione;
				wsk->nextt->kupione = temp_kupione;

				temp_wystawione = wsk->wystawione;
				wsk->wystawione = wsk->nextt->wystawione;
				wsk->nextt->wystawione = temp_wystawione;
			}
}

void sortowanie_nazwiska_klienci()
{
	unsigned short int ilosc = 0;
	for (el_klientow * wsk = firstt; wsk; wsk = wsk->nextt) ++ilosc;
	long int temp_kwota_zakupow;
	string temp_imie;
	long int temp_kwota_sprzedanych;
	string temp_nazwisko;
	string temp_kupione;
	string temp_wystawione;
	unsigned short int i, j;
	if (ilosc) ilosc--;
	for (i = 0; i < ilosc; i++)
		for (el_klientow * wsk = firstt; wsk->nextt; wsk = wsk->nextt)
			if (wsk->imie > wsk->nextt->imie)
			{
				temp_kwota_zakupow = wsk->kwota_zakupow;
				wsk->kwota_zakupow = wsk->nextt->kwota_zakupow;
				wsk->nextt->kwota_zakupow = temp_kwota_zakupow;

				temp_imie = wsk->imie;
				wsk->imie = wsk->nextt->imie;
				wsk->nextt->imie = temp_imie;

				temp_kwota_sprzedanych = wsk->kwota_sprzedanych;
				wsk->kwota_sprzedanych = wsk->nextt->kwota_sprzedanych;
				wsk->nextt->kwota_sprzedanych = temp_kwota_sprzedanych;

				temp_nazwisko = wsk->nazwisko;
				wsk->nazwisko = wsk->nextt->nazwisko;
				wsk->nextt->nazwisko = temp_nazwisko;

				temp_kupione = wsk->kupione;
				wsk->kupione = wsk->nextt->kupione;
				wsk->nextt->kupione = temp_kupione;

				temp_wystawione = wsk->wystawione;
				wsk->wystawione = wsk->nextt->wystawione;
				wsk->nextt->wystawione = temp_wystawione;
			}
}

void wypisz_klientow(el_klientow *lista)
{
	el_klientow *wsk = lista;
	while (wsk != NULL)
	{
		cout << left;
		cout.width(23);
		cout << wsk->imie;
		cout.width(25);
		cout << wsk->nazwisko;
		cout.width(30);
		cout << wsk->kwota_zakupow;
		cout.width(30);
		cout << wsk->kwota_sprzedanych;
		cout.width(30);
		cout << wsk->kupione;
		cout.width(30);
		cout << wsk->wystawione << endl;
		wsk = wsk->nextt;
	}
}

void znajdz_klientow(el_klientow *lista)
{
	cout << "Podaj nazwisko klienta ktora chesz wyszukac" << endl;
	string nazwisko;
	cin >> nazwisko;
	el_klientow *wsk = lista;
	while (wsk->nextt != NULL)
	{
		size_t znaleziona_pozycja = wsk->nazwisko.find(nazwisko);
		if (znaleziona_pozycja != std::string::npos)
		{
			cout << left;
			cout.width(23);
			cout << wsk->imie;
			cout.width(25);
			cout << wsk->nazwisko;
			cout.width(30);
			cout << wsk->kwota_zakupow;
			cout.width(30);
			cout << wsk->kwota_sprzedanych;
			cout.width(30);
			cout << wsk->kupione;
			cout.width(30);
			cout << wsk->wystawione << endl;
			wsk = wsk->nextt;
		}
		else
			wsk = wsk->nextt;
	}
}

int main()
{
	string nazwa;
	string kategoria;
	string status;
	int cena;
	string opis;
	int id;
	string imie;
	string nazwisko;
	string nowe_imie;
	string nowe_nazwisko;

	first = new el_listy;
	first->nazwa = "Monitor Dell";
	first->unikalny_nr = 1011;
	first->kategoria = "Monitory";
	first->status = "Sprzedane";
	first->cena = 740;
	first->wlasciciel = "Jan Kowalski";
	first->kupujacy = "Miroslaw Kwasniewski";
	first->opis = "Monitor nowy w promocyjnej cenie";
	first->next = NULL;

	firstt = new el_klientow;
	firstt->imie = "Mariusz";
	firstt->nazwisko = "Brzozowski";
	firstt->kwota_zakupow = 0;
	firstt->kwota_sprzedanych = 0;
	firstt->kupione = "Brak";
	firstt->wystawione = "Brak";
	firstt->nextt = NULL;

	logo();
	cout << "Pomyslnie zalogowano na konto Jan Kowalski..." << endl;
	Sleep(2500);
	system("CLS");
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
		dodaj_do_listy_z_pliku_klienci(firstt);
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
			cout << "3. Sortuj aukcje wedlug nazwy" << endl;
			cout << "4. Sortuj aukcje wedlug kategorii" << endl;
			cout << "5. Sortuj aukcje wedlug statusu" << endl;
			cout << "6. Sortuj aukcje wedlug ceny" << endl;
			cout << "7. Wyszukaj aukcje wedlug jej nazwy" << endl;
			cout << "8. Edytuj aukcje" << endl;
			cout << "9. Usun aukcje" << endl;
			cout << "10. Wyjscie z programu" << endl;
			cout << "Twoj wybor: ";
			cin >> wybor;

			switch (wybor)
			{
			case 1:
				cout << "Podaj nazwe aukcji ktora chcesz dodac: ";
				cin.clear();
				cin.ignore();
				getline(cin, nazwa);
				cout << "Podaj kateorie: ";
				getline(cin, kategoria);
				cout << "Podaj cene: ";
				cin >> cena;
				cout << "Podaj opis: ";
				cin.clear();
				cin.ignore();
				getline(cin, opis);

				dodaj_do_listy(first, nazwa, kategoria, cena, opis);
				zapisz_do_pliku(first);
				zapisz_do_pliku_klienci(firstt);
				break;
			case 2:
				cout << "Podaj ID aukcji ktora chcesz kupic: ";
				cin >> id;
				kup(first, id, firstt);
				Sleep(3000);
				zapisz_do_pliku(first);
				zapisz_do_pliku_klienci(firstt);
				break;
			case 3:
				sortowanie_nazwy();
				break;
			case 4:
				sortowanie_kategoria();
				break;
			case 5:
				sortowanie_status();
				break;
			case 6:
				sortowanie_cena();
				break;
			case 7:
				znajdz(first);
				Sleep(9000);
				break;
			case 8:
				cout << "Podaj ID aukcji ktora chcesz edytowac: ";
				cin >> id;
				cout << "Podaj nazwe: ";
				cin.clear();
				cin.ignore();
				getline(cin, nazwa);
				cout << "Podaj kateorie: ";
				getline(cin, kategoria);
				cout << "Podaj cene: ";
				cin >> cena;
				cout << "Podaj opis: ";
				cin.clear();
				cin.ignore();
				getline(cin, opis);

				edytuj(first, id, nazwa, kategoria, cena, opis);
				zapisz_do_pliku(first);
				break;
			case 9:
				cout << "Podaj ID aukcji ktora chcesz usuanac: ";
				cin >> id;
				usun_z_listy(first, id);
				Sleep(3000);
				zapisz_do_pliku(first);
				break;
			case 10: exit(0); break;
			}
		} while (true);
	}
	else if (wybor == 2)
	{
		dodaj_do_listy_z_pliku_klienci(firstt);
		do
		{
			system("CLS");

			logo();

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << left;
			cout.width(23);
			cout << "Imie";
			cout.width(25);
			cout << "Nazwisko";
			cout.width(30);
			cout << "Kwota zakupow";
			cout.width(30);
			cout << "Kwota sprzedanych";
			cout.width(30);
			cout << "Kupione przedmioty";
			cout.width(30);
			cout << "Wystawione przedmioty" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

			wypisz_klientow(firstt);

			cout << endl << "MENU WYBORU" << endl;
			cout << "1. Dodaj klienta" << endl;
			cout << "2. Usun klienta" << endl;
			cout << "3. Edytuj klienta" << endl;
			cout << "4. Wyszukaj wedlug nazwiska" << endl;
			cout << "5. Sortuj klientow wedlug nazwiska" << endl;
			cout << "6. Sortuj kielntow wedlug kwoty zakupow" << endl;
			cout << "7. Sortuj kilentow wedlug kwoty sprzedanych" << endl;
			cout << "8. Wyjscie z programu" << endl;
			cout << "Twoj wybor: ";
			cin >> wybor;

			switch (wybor)
			{
			case 1:
				cout << "Podaj imie klienta ktorego chcesz dodac: " << endl;
				cin >> imie;
				cout << "Podaj nazwisko: " << endl;
				cin >> nazwisko;

				dodaj_do_listy_klienci(firstt, imie, nazwisko);
				zapisz_do_pliku_klienci(firstt);
				break;
			case 2:
				cout << "Podaj imie kilienta ktorego chcesz usuanac: " << endl;
				cin >> imie;
				cout << "Podaj nazwisko" << endl;
				cin >> nazwisko;

				usun_z_listy_klienci(firstt, imie, nazwisko);
				zapisz_do_pliku_klienci(firstt);
				break;
			case 3:
				cout << "Podaj imie klienta ktorego chcesz edytowac" << endl;
				cin >> imie;
				cout << "Podaj nazwisko" << endl;
				cin >> nazwisko;
				cout << "Podaj nowe imie" << endl;
				cin >> nowe_imie;
				cout << "Podaj nowe nazwisko" << endl;
				cin >> nowe_nazwisko;

				edytuj_klienci(firstt, imie, nazwisko, nowe_imie, nowe_nazwisko);
				zapisz_do_pliku_klienci(firstt);
				break;
			case 4:
				znajdz_klientow(firstt);
				Sleep(9000);
				break;
			case 5:
				sortowanie_nazwiska_klienci();
				break;
			case 6:
				sortowanie_kupione_klienci();
				break;
			case 7:
				sortowanie_sprzedane_klienci();
				break;
			case 8: exit(0); break;
			}
		} while (true);
	}

	else if (wybor == 3)
		exit(0);

	system("pause");
	return 0;
}