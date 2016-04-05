#ifndef head_hpp
#define head_hpp

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>      //do ustawiania daty
// #include <time.h>
// #include <math.h>
#include <string>
#include <fstream>
#include <windows.h>
#include "head.hpp"



using namespace std;


// FUNKCJE

void posprzataj_bufor();
void wyczysc_linie(int nr_lini);
void gotoxy(int x, int y);
char komunikat_sortowania();
int menu_wstepne();
int wybor_biblioteki();
int wczytaj_dane_biblioteki();
int zapisz_dane_biblioteki();
int menu_biblioteczne();



//KLASY


class Element
{
    private:
    // public:
        float rozmiar_MB;
        string tytul;
        string autor;
        char typ; // 1 Muzyka 2 Film 3 Zdjecia 4 Gry 5 Dokumenty 6 Inne
        string wlasciciel;
        string data_dodania;
        string data_edycji;
        bool zaznaczenie_wyszukania = false;


    public:
        Element();
        void ustaw_rozmiar_MB();
        void wczytaj_rozmiar_MB(float zmienna);
        void wyswietl_rozmiar_MB();
        void ustaw_autora();
        void wczytaj_autora(string zmienna);
        void wyswietl_autora();
        void ustaw_tytul();
        void wczytaj_tytul(string zmienna);
        void wyswietl_tytul();
        void ustaw_typ();
        void wczytaj_typ(char zmienna);
        void wyswietl_typ();
        void ustaw_wlasciciela();
        void wczytaj_wlasciciela(string zmienna);
        void wyswietl_wlasciciela();
        void ustaw_date_dodania();
        void wczytaj_date_dodania(string zmienna);
        void wyswietl_date_dodania();
        void ustaw_date_edycji();
        void wczytaj_date_edycji(string zmienna);
        void wyswietl_date_edycji();
        void wlacz_zaznaczenie_wyszukania();
        void wylacz_zaznaczenie_wyszukania();
        bool zwroc_zaznaczenie_wyszukiwania();


        float   zwroc_rozmiar_MB();
        string  zwroc_tytul();
        string  zwroc_autora();
        char    zwroc_typ();
        string  zwroc_wlasciciela();
        string  zwroc_date_dodania();
        string  zwroc_date_edycji();


        //WSKAZNIKI

        Element *next_el = NULL;
        Element *prev_el = NULL;

};

class Lista
{
    private:
    // public:
        int rozmiar_Listy;
        bool wyszukiwanie = false;
        bool sortowanie = false;

    public:

        Element *Glowa = NULL;
        Element *Dupa = NULL;
        Element *Podgladacz = Glowa;
        Element *Pomocnik = NULL;


    public:

        //METODY
        Lista();
        ~Lista();
        void dodaj_element_Listy();
        char usun_element_Listy(int liczba_elementow_listy, int numer_obecnego_elementu);
        void inkrementuj_rozmiar_Listy();
        void dekrementuj_rozmiar_Listy();
        int  zwroc_rozmiar_Listy();
        void wyswietl_pierwszy_element_Listy();
        void wyswietl_ostatni_element_Listy();
        void przegladaj_Liste();
        void edytuj_element_Listy();
        void wczytaj_z_bazy_do_listy(char numer_bazy);
        int zapisz_liste_do_pliku(char numer_bazy);
        int zapisz_wyszukana_liste_do_pliku(char numer_bazy, int rozmiar_listy_wyszukanej);
        void sortuj_Liste_kreator(); // Tworzy liste ktora bedziemy sortowac wg okreslonego kryterium
        void sortuj_Liste_sprzatacz();
        void wlacz_wyszukiwanie();
        void wylacz_wyszukiwanie();
        void sprzataj_wyszukiwanie();
        bool zwroc_stan_wyszukiwania();
        int wyszukaj(int numer_wyszukiwanego_typu, string wartosc_wyszukiwanego_typu);
        void nadpisanie(Element *elemencik_zrodlo, Element *elemencik_cel);
        void wlacz_sortowanie();
        void wylacz_sortowanie();
        bool zwroc_stan_sortowania();

};


#endif
