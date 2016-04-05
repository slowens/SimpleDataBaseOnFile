#include "head.hpp"


bool znacznik_wczytaj_z_pliku = 0;      // znacznik czy wczytywac baze czy nie
char Tajemnicza_pomocnicza_x = '0';     // numer bazy do wczytania w charze


using namespace std;

// FUNKCJE

void posprzataj_bufor()
{
    cin.clear();            //czyscimy/zerujemy flagi bledu
    cin.sync();             // czyscimy bufor klawiatury
    FlushConsoleInputBuffer( GetStdHandle( STD_INPUT_HANDLE ) );
}

void wyczysc_linie(int nr_lini)
{
    gotoxy(0, nr_lini); cout<< "                                                                                                              ";
}

void gotoxy(int x, int y)  // Funkcja pozycjonujaca
{
  COORD kolorowy;
  kolorowy.X = x;
  kolorowy.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kolorowy);
}

char komunikat_sortowania()
{
    posprzataj_bufor();
    char a;
    gotoxy(5,28); cout<<"Sortowanie wg typu ustawi elementy w nastepujacej kolejnosci:";
    gotoxy(5,30); cout<<"Elementy typu Muzyka";
    gotoxy(5,32); cout<<"Elementy typu Film";
    gotoxy(5,34); cout<<"Elementy typu Zdjecia";
    gotoxy(5,36); cout<<"Elementy typu Gry";
    gotoxy(5,38); cout<<"Elementy typu Dokumenty";
    gotoxy(5,40); cout<<"Elementy typu Inne";
    gotoxy(5,42); cout<<"Czy na pewno chcesz kontynuowac? t/n";
    while((a !='n') && (a !='N') && (a !='t') && (a !='T'))
    {
        posprzataj_bufor();
        wyczysc_linie(44);
        gotoxy(5,44);cin>>a;
    }

    return a;
}

int menu_wstepne()
{

	string Menu[5] = {  "",
                        " Przegladaj Biblioteke",
                        " Utworz Nowa Biblioteke",
                        "       O Autorze",
                        "        Wyjscie"              };

	int obecny = 0;

	while(true)
	{
		system("cls");
		// system("color 92"); // niebieski kolorek tla

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 90);
		gotoxy(44, 5); cout << "Menu Biblioteki"<< endl<<endl;

		for (int i = 0; i < 5; ++i)
		{
			if (i == obecny)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED); // RED, 70);
				gotoxy(40, i*2+10); cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(40, i*2+10); cout << Menu[i] << endl;
			}
                gotoxy(0, i*2+25);  // pozycja znaku zachety
		}

		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				obecny -= 1;
				if (obecny == -1)
				{
					obecny = 4;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				obecny += 1;
				if (obecny == 5)
				{
					obecny = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (obecny)
				{
					case 0:
					{
                        ;
					} break;
					case 1:
					{
                        wybor_biblioteki();
						Sleep(3000);

					} break;
					case 2:
					{
                        menu_biblioteczne();
						Sleep(1000);

					} break;

					case 3:
					{
					    posprzataj_bufor();
					    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_GREEN); // GREEN
					    system("cls");
						gotoxy(5,2);cout << "Autor: Przemyslaw Slowik"<<endl;
						gotoxy(5,4);cout << "Grupa: 3BZI"<<endl;
						gotoxy(5,6);cout << "Uczelnia: WSTI w Katowicach"<<endl;
						gotoxy(5,8);cout << "Kierunek: Informatyka"<<endl;
						gotoxy(5,10);cout << "Przedmiot: Podstawy Programowania Obiektowego"<<endl;
						gotoxy(5,12);cout << "All Rights Reserved!!!"<<endl;
						getchar();
						menu_wstepne();
						posprzataj_bufor();

					} break;

					case 4:
					{
						exit(0);
					} break;

				}
				break;
			}
		}

		Sleep(200); // czas pomiedzy przeskokiem opcji w menu zmiany koloru napisu po wczytani danego klawisza
	}

	return 0;
}

int wybor_biblioteki() // Wczytywanie Biblioteki
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_BLUE); // LIGHT BLUE
    fstream plik_biblioteczny;
    char a = 0;
    while ((a != '1') && (a != '2') && (a != '3') && (a != '4') && (a != '5') && (a != '6') && (a != '7') && (a != '8') && (a != '9'))
    {
        gotoxy(29, 30);cout <<"Podaj numer biblioteki (1-9) ktora chcesz wczytac: ";
        posprzataj_bufor();
        gotoxy(80, 30);cin>>a;
    }

    string nazwa_pliku = "Pliki_tekstowe\\\\Baza";
    nazwa_pliku.push_back(a);
    nazwa_pliku = nazwa_pliku + ".txt";

    getchar();

    plik_biblioteczny.open(nazwa_pliku.c_str(), ios::in);   // pobranie danych za pomoca metody.c_str()
                                                            // mozna tez uzyc metody GetOpenFileName() z biblioteki windows.h
    if( plik_biblioteczny.good() == true )
        {
            char stan_pliku = '\n';
            plik_biblioteczny>>stan_pliku;

            if(stan_pliku == '\n')
            {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_RED);
                system("cls");
                gotoxy(30, 20);cout<<"Uwazaj co podajesz!!! Plik jest pusty!!!";
                Sleep(3500);
                posprzataj_bufor();
                menu_wstepne();
                return 0;
            }
            else
            {
                system("cls");
                plik_biblioteczny.close();
                znacznik_wczytaj_z_pliku = 1;
                Tajemnicza_pomocnicza_x = static_cast<int>(a);
                posprzataj_bufor();
                menu_biblioteczne();
                return 0;
            }
        }

        else
        {
            char aa = '0';
            gotoxy(32, 24);     cout << "Biblioteka o podanym numerze nie istnieje!" <<endl;
            gotoxy(38, 26);     cout << "Wcisnij Enter aby kontynuowac";
            getchar();
            system("cls");
            while((aa != '1') && (aa != '2') && (aa != '3'))
            {
                gotoxy(35, 14);     cout << "Wybierz co chcesz teraz zrobic: "<<endl;
                gotoxy(35, 16);     cout << "1. Sprobuj wybrac inna biblioteke"<<endl;
                gotoxy(35, 18);     cout << "2. Utworz nowa biblioteke "<<endl;
                gotoxy(35, 20);     cout << "3. Wroc do glownego menu"<< endl;
                gotoxy(57, 22);     cin>>aa; gotoxy(35, 22);  cout << "Wybrales opcje nr: ";
            }
            switch (aa)
            {
                case '1':
                {
                    posprzataj_bufor();
                    wybor_biblioteki();
                    return 0;
                }break;
                case '2':
                {
                    posprzataj_bufor();
                    menu_biblioteczne();
                }break;
                case '3':
                {
                    posprzataj_bufor();
                    menu_wstepne();
                }break;
            }

        }

    return  0 ;
}

char wybor_biblioteki2() // Zapisywanie Biblioteki
{
    char ss; //zmienna do zwrocenia
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_BLUE); // LIGHT BLUE
    fstream plik_biblioteczny;
    char a = 0;
    bool pstryczek = 0;
    while ((a != '1') && (a != '2') && (a != '3') && (a != '4') && (a != '5') && (a != '6') && (a != '7') && (a != '8') && (a != '9'))
    {

        gotoxy(25, 5);cout <<"Podaj numer pliku (1-9) do ktorego chcesz zapisac biblioteke: ";
        posprzataj_bufor();
        gotoxy(90, 5);cin>>a;
        if(pstryczek == 1)
        {
            gotoxy(25, 3);cout <<"Podales niepoprawny numer sproboj ponownie!!!";
        }
        pstryczek = 1;
    }

    ss = a;
    string nazwa_pliku = "Pliki_tekstowe\\\\Baza";
    nazwa_pliku.push_back(a);
    nazwa_pliku = nazwa_pliku + ".txt";

    plik_biblioteczny.open(nazwa_pliku.c_str(), ios::in);   // pobranie danych ze zmiennej za pomoca metody.c_str()
                                                            // mozna tez uzyc metody GetOpenFileName() z biblioteki windows.h
    if( plik_biblioteczny.good() == true )
        {
            char stan_pliku = '\n';
            plik_biblioteczny>>stan_pliku;

            if(stan_pliku != '\n')
            {
                system("cls");
                gotoxy(20, 15);cout<<"Plik do ktorego chcesz zapisac biblioteke nie jest pusty !!!";
                gotoxy(30, 18);cout<< "Czy pomimo to chcesz kontynuowac? T/N:";

                char decyzja = '0';
                gotoxy(70, 18);cin >> decyzja;
                while ((decyzja != 't') && (decyzja != 'n') && (decyzja != 'T') && (decyzja != 'N'))
                       {
                            gotoxy(28, 23);cout <<"Podales bledny znak sprobuj ponownie: ";
                            posprzataj_bufor();
                            gotoxy(65, 23);cin>>decyzja;
                            posprzataj_bufor();
                        }

                if((decyzja == 'n') || (decyzja == 'N'))
                {
                    gotoxy(37, 8);cout <<"Anulowano operacje zapisu. ";
                    Sleep(2500);
                    ss = 'z';
                }

            }
            else
            {
                gotoxy(25, 3);cout <<"Zapisuje do pustego pliku...";
                Sleep(3000);
            }

            plik_biblioteczny.close();
            posprzataj_bufor();
        }

       return ss;
}

int menu_biblioteczne()
{
    class Lista L1;
    Lista *pom007 = &L1;

    int znacznik = 0;
    int licznik_listy = 0;
    int licznik_wyszukanej_listy = 0; // zmienna liczba wskazuje aktualny element listy wyszukanej
    int wyszukane_ele = 0; // liczba elementow listy wyszukanej
    int maxymalne_przesuniecie = 0;


    if(znacznik_wczytaj_z_pliku == 1)
        {
        pom007->wczytaj_z_bazy_do_listy(Tajemnicza_pomocnicza_x);
        znacznik_wczytaj_z_pliku = 0;
        pom007->Podgladacz=pom007->Glowa;
        licznik_listy=1;
        }


    {
    string drugi_guzik, trzeci_guzik, siodmy_guzik, dziewiaty_guzik, osmy_guzik;
    bool booool = pom007->zwroc_stan_wyszukiwania();            // stan wyszukiwania
    bool booool_sortowania = pom007->zwroc_stan_sortowania();
   	int obecny = 0; // bardzo wazna zmienna wskazuje poczatek listy


    string Menu[11] = {     "",
                            " Wyswietl pierwszy element",
                            drugi_guzik,
                            trzeci_guzik,
                            " Dodaj nowy element ",
                            " Edytuj obecny element",
                            " Usun obecny element",
                            siodmy_guzik,
                            osmy_guzik,
                            " Zapisz biblioteke",
                            " Wroc do menu glowengo"              };


                    if(booool == false)
                    {
                        drugi_guzik =" Wyswietl nastepny element";
                        trzeci_guzik = " Wyswietl poprzedni element";
                        siodmy_guzik = " Wyszukaj w bibliotece";
                    }
                    else if(booool == true)
                    {
                        drugi_guzik =" Wyswietl nastepny wyszukany element";
                        trzeci_guzik = " Wyswietl poprzedni wyszukany element";
                        siodmy_guzik = " Zakoncz wyszukiwanie";
                    }

                    if(booool_sortowania == false)
                    {
                        osmy_guzik = " Sortowanie wg typu";
                    }
                    else if(booool_sortowania == true)
                    {
                        osmy_guzik = " Przywroc domyslna kolejnosc";
                    }



	while(true)
	{

        booool = pom007->zwroc_stan_wyszukiwania();
        booool_sortowania = pom007->zwroc_stan_sortowania();
	    string Menu[11] = {     "",
                            " Wyswietl pierwszy element",
                            drugi_guzik,
                            trzeci_guzik,
                            " Dodaj nowy element ",
                            " Edytuj obecny element",
                            " Usun obecny element",
                            siodmy_guzik,
                            osmy_guzik,
                            " Zapisz biblioteke",
                            " Wroc do menu glownego"              };


                    if(booool == false)
                    {
                        drugi_guzik =" Wyswietl nastepny element";
                        trzeci_guzik = " Wyswietl poprzedni element";
                        siodmy_guzik = " Wyszukaj w bibliotece";
                    }
                    else if(booool == true)
                    {
                        drugi_guzik =" Wyswietl nastepny wyszukany element";
                        trzeci_guzik = " Wyswietl poprzedni wyszukany element";
                        siodmy_guzik = " Zakoncz wyszukiwanie";
                    }

                      if(booool_sortowania == false)
                    {
                        osmy_guzik = " Sortowanie wg typu";
                    }
                    else if(booool_sortowania == true)
                    {
                        osmy_guzik = " Przywroc domyslna kolejnosc";
                    }


		system("cls");
		// system("color 92"); // niebieski kolorek tla

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 90);
		gotoxy(5, 4); cout << "Menu glowne"<< endl<<endl;

		for (int i = 0; i < 11; ++i)
		{
			if (i == obecny)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED); // RED, 70);
				gotoxy(4, i*2+6); cout << Menu[i] << endl;


                    if (i==10)
                    {
                        if(pom007->zwroc_rozmiar_Listy() > 0)
                        {
                            pom007->przegladaj_Liste ();
                            gotoxy(40,2);cout<<"Uwaga! wszelkie niezapisane zmiany zostana utracone";
                        }
                    }
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(4, i*2+6); cout << Menu[i] << endl;

				 if (i==10)
                    {
                        if(pom007->zwroc_rozmiar_Listy() > 0)
                            {
                                pom007->przegladaj_Liste ();
                                if (booool == false)
                                {
                                    gotoxy(80,2);cout<< licznik_listy << "/" << pom007->zwroc_rozmiar_Listy();
                                }
                                else if(booool == true)
                                {
                                    gotoxy(69,3);cout<< "Wyszukane: "<<licznik_wyszukanej_listy << "/" << wyszukane_ele;
                                }
                            }
                    }

			}
                gotoxy(0, i*2+10);  // pozycja znaku zachety

		}

		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				obecny -= 1;
				if (obecny == -1)
				{
					obecny = 10;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				obecny += 1;
				if (obecny == 11)
				{
					obecny = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (obecny)
				{
				    case 0:
					{
                    ;
					} break;
/* -->opcja */      case 1:     // Wyswietl pierwszy element
					{
					    if(booool == true)
                        {
                                if(pom007->Glowa != NULL )
                                    {
                                        pom007->Podgladacz = pom007->Glowa;
                                        znacznik = 1;
                                        licznik_listy = 1;
                                        while (pom007->Podgladacz->zwroc_zaznaczenie_wyszukiwania() != true)
                                        {
                                            pom007->Podgladacz = pom007->Podgladacz->next_el;
                                            znacznik = 1;
                                            licznik_wyszukanej_listy = 1;
                                            maxymalne_przesuniecie = wyszukane_ele;
                                        }
                                        pom007->Pomocnik = pom007->Podgladacz;
                                    }
                        }
					    else if(pom007->Glowa != NULL )
                        {
                            pom007->Podgladacz = pom007->Glowa;
                            znacznik = 1;
                            licznik_listy = 1;
					    }
					     else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "Biblioteka jest pusta!!!";
                                Sleep(2000);
                            }

					} break;

/* -->opcja */ 		case 2:     // Wyswietl nastepny element
					{
					    if(booool == true)
                        {
                            if(maxymalne_przesuniecie>1)
                            {
                                do
                                {
                                    pom007->Podgladacz = pom007->Podgladacz->next_el;
                                }
                                while(pom007->Podgladacz->zwroc_zaznaczenie_wyszukiwania() != true);

                                maxymalne_przesuniecie--;
                                licznik_wyszukanej_listy++;
                                licznik_listy++;
                                posprzataj_bufor();
                                obecny = 2;
                            }
                                else
                                {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "To jest ostatni wyszukany element !!!";
                                Sleep(2500);
                                }
                        }

					    else if(booool == false)
					    {
                        if(pom007->zwroc_rozmiar_Listy() >0)
                        {
                            if(pom007->Podgladacz->next_el != NULL)
                            {
                                pom007->Podgladacz = pom007->Podgladacz->next_el;
                                znacznik = 2;
                                licznik_listy++;
                            }
                            else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "To jest ostatni element biblioteki !!!";
                                Sleep(2500);
                            }
                        }
                        else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "Biblioteka jest pusta!!!";
                                Sleep(2500);
                            }
					    }

					} break;
/* -->opcja */ 		case 3:     // Wyswietl poprzedni element
					{
					    if(booool == true)
                        {
                            if(maxymalne_przesuniecie<wyszukane_ele)
                            {
                                do
                                {
                                    pom007->Podgladacz = pom007->Podgladacz->prev_el;
                                }
                                while(pom007->Podgladacz->zwroc_zaznaczenie_wyszukiwania() != true);

                                maxymalne_przesuniecie++;
                                licznik_wyszukanej_listy--;
                                licznik_listy--;
                                posprzataj_bufor();
                                obecny = 3;
                            }
                                else
                                {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "To jest pierwszy wyszukany element !!!";
                                Sleep(2500);
                                }
                        }
                        else if(booool == false)
					    {
					    if(pom007->zwroc_rozmiar_Listy() >0)
                        {
                            if(pom007->Podgladacz->prev_el  != NULL)
                            {
                                pom007->Podgladacz = pom007->Podgladacz->prev_el;
                                znacznik = 3;
                                licznik_listy--;
                            }
                            else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "To jest pierwszy element biblioteki !!!";
                                Sleep(2000);
                            }
                        }
                        else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "Biblioteka jest pusta!!!";
                                Sleep(2500);
                            }
					    }

					} break;
/* -->opcja */ 		case 4:     // Dodaj nowy element
					{
                        if(booool == true)
                        {
                            gotoxy(35,26); cout<<" Obecnie opcja jest niedostepna. ";
                            gotoxy(35,28); cout<<" Wyjdz z trybu wyszukiwania aby moc jej uzyc.";
                            Sleep(2000);
                        }
                        else
                        {
					    posprzataj_bufor();
					    pom007->dodaj_element_Listy();         //L1.dodaj_element_Listy();
					    licznik_listy = 1;
					    gotoxy(35,20); cout<<" Pomyslnie dodano nowy element Listy.";
					    gotoxy(35,22); cout<<" Wcisnij enter aby kontynuowac...";
					    getchar();
						obecny = 0;
						znacznik = 4;
                        }

                    } break;
/* -->opcja */ 		case 5:     // Edytuj obecny element
					{
                        if(pom007->Podgladacz != 0)
                            {
                                pom007->edytuj_element_Listy();
                                znacznik = 5;
                                obecny = 0;
                            }

					} break;
/* -->opcja */ 		case 6:     // Usun obecny element
					{

                        if(pom007->zwroc_stan_wyszukiwania() == false)
                        {
                            char decyzja = 'o';

                            while((decyzja != 'n') && (decyzja != 'N') && (decyzja != 't') && (decyzja != 'T'))
                            {
                                gotoxy(10,28); cout<<"Czy na pewno chcesz usunac obecny element? t/n";
                                gotoxy(10,30); cin>>decyzja;
                                wyczysc_linie(28);wyczysc_linie(30);
                            }

                            if((decyzja == 't') || (decyzja == 'T'))
                            {
                                /*if(booool == true)
                                {
                                    if (licznik_wyszukanej_listy>1)
                                    {
                                        licznik_wyszukanej_listy--;
                                        maxymalne_przesuniecie == wyszukane_ele - 1;
                                        wyszukane_ele--;
                                    }
                                }*/


                            char wrrrrrrrrr = '0';
                            wrrrrrrrrr = pom007->usun_element_Listy(pom007->zwroc_rozmiar_Listy(),licznik_listy);

                            if( wrrrrrrrrr == '5')
                            {
                                gotoxy(30, 6); cout<< "Sory Gregory biblioteka jest pusta!! NIC nie da sie usunac!!!";
                                Sleep(2500);
                                posprzataj_bufor();
                            }
                            else if(wrrrrrrrrr == '4')
                            {
                                pom007->dekrementuj_rozmiar_Listy();
                            }
                            else if(wrrrrrrrrr == '3')
                            {
                                licznik_listy = 0;
                                pom007->dekrementuj_rozmiar_Listy();
                            }
                            else if(wrrrrrrrrr == '2')
                            {
                                pom007->dekrementuj_rozmiar_Listy();
                                licznik_listy--;
                            }
                            else if(wrrrrrrrrr == '1')
                            {
                                pom007->dekrementuj_rozmiar_Listy();
                                licznik_listy--;
                            }
                            else
                            {

                            wrrrrrrrrr = '0';

                            }

                            posprzataj_bufor();
                            obecny = 0;
                            znacznik = 6;

                            }
                        }
                            else
                            {

                                gotoxy(35,26); cout<<" Obecnie opcja jest niedostepna. ";
                                gotoxy(35,28); cout<<" Wyjdz z trybu wyszukiwania aby moc jej uzyc.";
                                Sleep(3000);
                                posprzataj_bufor();
                                obecny = 0;
                           }


					} break;
/* -->opcja */ 		case 7:     // Wyszukaj w bibliotece
					{
					    if(pom007->zwroc_rozmiar_Listy() >0)
                        {

					    if (booool == false)
                        {
						gotoxy(34, 27);cout << "Wyszukiwanie";
						Sleep(1000);
						wyczysc_linie(27);


						char nowyPomocnik = '0';
                        while ( (nowyPomocnik != '1') &&
                        (nowyPomocnik != '2') &&
                        (nowyPomocnik != '3') &&
                        (nowyPomocnik != '4')
                               //&& (nowyPomocnik != '5')
                               )
                        {
                        gotoxy(10,30);       cout<< " Wybierz wg jakiego kryteruim"; gotoxy(10,31); cout<<" chcesz wyszukiwac?"<<endl;
                        gotoxy(10,32);       cout<< " 1. Autor"<<endl;
                        gotoxy(10,34);       cout<< " 2. Tytul"<<endl;
                        gotoxy(10,36);       cout<< " 3. Wlasciciel"<<endl;
                        gotoxy(10,38);       cout<< " 4. Typ"<<endl;
                        // gotoxy(10,40);       cout<< " 5. Data dodania"<<endl;
                        gotoxy(11,42);       cin>>nowyPomocnik;
                        wyczysc_linie(30);wyczysc_linie(32);wyczysc_linie(31);wyczysc_linie(34);wyczysc_linie(36);wyczysc_linie(38);wyczysc_linie(40);wyczysc_linie(42);
                        posprzataj_bufor();
                        }

                        string pomocnikA;
                        string pomocnikDnia, pomocnikMiesiaca, pomocnikRoku;
                        char pomocnikTyp = '0';
                        int ilosc_elementow_lity = pom007->zwroc_rozmiar_Listy();
                        int pomocnikZwrotnik = 0;

                            if(nowyPomocnik == '1')
                            {
                                    posprzataj_bufor();
                                    gotoxy(10,30); cout<< "Podaj Autora ktorego chcesz wyszukac: "<<endl;
                                    gotoxy(10,32); getline(std::cin, pomocnikA);
                                    pomocnikZwrotnik = 1;

                                    posprzataj_bufor();

                            }
                            else if(nowyPomocnik == '2')
                            {
                                    posprzataj_bufor();
                                    gotoxy(10,30); cout<< "Podaj Tytul ktory chcesz wyszukac: "<<endl;
                                    gotoxy(10,32); getline(std::cin, pomocnikA);
                                    pomocnikZwrotnik = 2;

                                    posprzataj_bufor();
                            }
                            else if(nowyPomocnik == '3')
                            {
                                    posprzataj_bufor();
                                    gotoxy(10,30); cout<< "Podaj Wlasciciela ktorego chcesz wyszukac: "<<endl;
                                    gotoxy(10,32); getline(std::cin, pomocnikA);
                                    pomocnikZwrotnik = 3;

                                    posprzataj_bufor();

                            }
                            else if(nowyPomocnik == '4')
                            {
                                    posprzataj_bufor();
                                    while ( (pomocnikTyp != '1') &&
                                    (pomocnikTyp != '2') &&
                                    (pomocnikTyp != '3') &&
                                    (pomocnikTyp != '4') &&
                                    (pomocnikTyp != '5') &&
                                    (pomocnikTyp != '6')      )
                                    {
                                        gotoxy(10,30);      cout<< "Podaj Typ elementu ktory chcesz wyszukac: "<<endl;
                                        gotoxy(10,32);      cout<< " 1. Muzyka"<<endl;
                                        gotoxy(10,34);      cout<< " 2. Film"<<endl;
                                        gotoxy(10,36);      cout<< " 3. Zdjecia"<<endl;
                                        gotoxy(10,38);      cout<< " 4. Gry"<<endl;
                                        gotoxy(10,40);      cout<< " 5. Dokumenty"<<endl;
                                        gotoxy(10,42);      cout<< " 6. Inne"<<endl;
                                        gotoxy(10,44);      cin>>pomocnikTyp;
                                        wyczysc_linie(44);
                                    }
                                    pomocnikZwrotnik = 5;
                                    pomocnikA = pomocnikTyp;

                                    posprzataj_bufor();
                            }
                            /*
                            else if(nowyPomocnik == '5')
                            {
                                    posprzataj_bufor();
                                    gotoxy(10,30); cout<< "Podaj Date dodania ktora chcesz wyszukac: "<<endl;
                                    gotoxy(10,32); cout<< "PAMIETAJ !!! DATA DODANIA MA FORMAT DZIEN - MIESIAC - ROK ZAPISANE W FORMIE CYFR"<<endl;
                                    gotoxy(10,33); cout<< "PAMIETAJ !!! PODAWAJ TYLKO CYFRY BEZ ZER LUB INNYCH DODADKOWYCH ZNAKOW"<<endl;
                                    gotoxy(10,34); cout<< "PODAJ DZIEN: "<<endl;
                                    gotoxy(27,34); cin>>  pomocnikDnia;
                                    gotoxy(10,36); cout<< "PODAJ MIESIAC: "<<endl;
                                    gotoxy(27,36); cin>>  pomocnikMiesiaca;
                                    gotoxy(10,38); cout<< "PODAJ ROK: "<<endl;
                                    gotoxy(27,38); cin>>  pomocnikRoku;
                                    pomocnikZwrotnik = 4;

                                    posprzataj_bufor();
                            }*/

                            int zmpomo = pom007->wyszukaj(pomocnikZwrotnik, pomocnikA);
                            wyszukane_ele = zmpomo;
                            maxymalne_przesuniecie = wyszukane_ele;
                            if(zmpomo != 0)
                            {
                                licznik_wyszukanej_listy++;
                                pom007->wyszukaj(pomocnikZwrotnik, pomocnikA);
                                pom007->wlacz_wyszukiwanie();
                                wyczysc_linie(45);
                                gotoxy(10, 45); cout<< "Melduje zakonczenie procesu wyszukiwania!!!!";
                                Sleep(3000);
                                wyczysc_linie(45);
                            }
                            else
                            {
                                gotoxy(10, 45); cout<< "Niestety nic nie znaleziono  !!!!";
                                Sleep(3000);
                                wyczysc_linie(45);
                            }

                            posprzataj_bufor();
                        }
                        else if(booool == true)
                        {
                            pom007->wylacz_wyszukiwanie();
                            pom007->sprzataj_wyszukiwanie();
                            licznik_wyszukanej_listy = 0;
                            wyszukane_ele = 0;
                            licznik_listy = 1;
                            pom007->Podgladacz = pom007->Glowa;

                            wyczysc_linie(45);
                            gotoxy(10, 45); cout<< "Melduje zakonczenie wyszukiwania!!!!";
                            Sleep(3000);
                            wyczysc_linie(45);
                            posprzataj_bufor();
                        }
                        }
                        else
                            {
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),55);
                                gotoxy(50, 6); cout<< "Biblioteka jest pusta!!!";
                                Sleep(2000);
                            }

                        obecny = 0;

					} break;
/* -->opcja */ 		case 8:     // Sortowanie wg typu
					{
					    if(booool == true)
                        {
                            gotoxy(35,26); cout<<" Obecnie opcja jest niedostepna. ";
                            gotoxy(35,28); cout<<" Wyjdz z trybu wyszukiwania aby moc jej uzyc.";
                            Sleep(2000);
                        }
                        else
                        {
                            if(pom007->zwroc_stan_sortowania() == false)
                            {
                                char a = '0';
                                a = komunikat_sortowania();
                                if((a == 't') || (a == 'T'))
                                    {
                                        pom007->sortuj_Liste_kreator();
                                        pom007->wlacz_sortowanie();
                                        licznik_listy = 1;
                                    }

                            }
                            else
                            {
                                wyczysc_linie(30);
                                gotoxy(10,30); cout<<"Powrot do kolejnosci domyslnej"; Sleep(2500);
                                pom007->sortuj_Liste_sprzatacz();
                                pom007->wylacz_sortowanie();
                                licznik_listy = 1;
                            }

                        }
                        obecny = 0;


					} break;
/* -->opcja */ 		case 9:     // Zapisz biblioteke
					{

                        if(pom007->zwroc_stan_wyszukiwania() == false)
                        {
                            if(pom007->zwroc_rozmiar_Listy() == 0)
                            {
                                gotoxy(30, 6);cout<< "Nie ma co zapisac! Lista jest pusta!!!";
                                Sleep(2500);
                            }
                            else
                            {
                                char podajnik;
                                podajnik = wybor_biblioteki2();

                                if ((podajnik == '1') || (podajnik == '2') || (podajnik == '3')
                                    || (podajnik == '4') || (podajnik == '5') || (podajnik == '6')
                                    || (podajnik == '7') || (podajnik == '8') || (podajnik == '9'))
                                {

                                    int zwrot;
                                    zwrot = pom007->zapisz_liste_do_pliku(podajnik);
                                    if(zwrot == 0)
                                    {
                                        gotoxy(34, 27);cout<< "Zapis zakonczony sukcesem!!!";
                                        Sleep(2500);
                                    }
                                    else
                                    {
                                        gotoxy(30, 6);cout<< "Cos sie stalo ze sie zesralo";
                                        Sleep(2500);
                                    }

                                }
                            }
                            znacznik = 9;
                            obecny = 0;
                            posprzataj_bufor();
                        }
                        else
                        {

                            if(wyszukane_ele == 0)
                            {
                                gotoxy(30, 6);cout<< "Nie ma co zapisac! Wyszukana Lista jest pusta!!!";
                                Sleep(2500);
                            }
                            else
                            {
                                char podajnik;
                                podajnik = wybor_biblioteki2();

                                if ((podajnik == '1') || (podajnik == '2') || (podajnik == '3')
                                    || (podajnik == '4') || (podajnik == '5') || (podajnik == '6')
                                    || (podajnik == '7') || (podajnik == '8') || (podajnik == '9'))
                                {

                                    int zwrot;
                                    zwrot = pom007->zapisz_wyszukana_liste_do_pliku(podajnik, wyszukane_ele);
                                    if(zwrot == 0)
                                    {
                                        gotoxy(34, 27);cout<< "Zapis zakonczony sukcesem!!!";
                                        Sleep(2500);
                                    }
                                    else
                                    {
                                        gotoxy(30, 6);cout<< "Cos sie stalo ze sie zesralo";
                                        Sleep(2500);
                                    }

                                }
                            }
                            znacznik = 9;
                            obecny = 0;
                            posprzataj_bufor();

                        }


					} break;
/* -->opcja */ 		case 10:    // Wroc do menu glowengo
					{
					    pom007 = NULL;
					    delete pom007;
                        L1.~Lista();
                        menu_wstepne();
					} break;

                }
				break;
			}
		}

		Sleep(200); // czas pomiedzy przeskokiem opcji w menu zmiany koloru napisu po wczytani danego klawisza
	}

	return 0;
}


}




// KLASA LISTA

Lista::Lista()
{
 rozmiar_Listy = 0;
}
Lista::~Lista()
{
    this->Glowa = NULL;
    this->Dupa = NULL;
    this->Podgladacz =NULL;
    delete Glowa;
    delete Dupa;
    delete Podgladacz;
    rozmiar_Listy = 0;
}

void Lista::inkrementuj_rozmiar_Listy()
{
    rozmiar_Listy++;
}

void Lista::dekrementuj_rozmiar_Listy()
{
    rozmiar_Listy--;
}

int  Lista::zwroc_rozmiar_Listy()
{
    return rozmiar_Listy;
}

void Lista::dodaj_element_Listy()
{

    posprzataj_bufor();

    Element *Nowy_Element = new Element;
    cout<< "Podaj rozmiar w MB elementu dodawanego do biblioteki : ";     Nowy_Element->ustaw_rozmiar_MB();
    cout<< "Podaj autora elementu dodawanego do biblioteki       : ";     Nowy_Element->ustaw_autora();
    cout<< "Podaj tytul elementu dodawanego do biblioteki        : ";     Nowy_Element->ustaw_tytul();
    cout<< "Podaj wlasciciela elementu dodawanego do biblioteki  : ";     Nowy_Element->ustaw_wlasciciela();

                                                                          Nowy_Element->ustaw_typ();
                                                                          Nowy_Element->ustaw_date_dodania();

    if (rozmiar_Listy == 0)
    {
        Glowa = Nowy_Element;
        Glowa->next_el = NULL;
        Glowa->prev_el = NULL;
        Podgladacz = Glowa;
    }
    else
    {
        Podgladacz = Dupa;
        Element *Pomocniczy = Glowa;

        while (Pomocniczy->next_el != NULL )
        {
            Pomocniczy = Pomocniczy->next_el;
        }
        Pomocniczy->next_el = Nowy_Element;
        Nowy_Element->prev_el = Pomocniczy;
        Dupa = Nowy_Element;
        Podgladacz = Glowa;

    }


    inkrementuj_rozmiar_Listy();

    posprzataj_bufor();

}

char Lista::usun_element_Listy(int liczba_elementow_listy, int numer_obecnego_elementu)
{
    char s = '0';
    Element *Nowy_Element_pomocniczy = new Element;

    if( liczba_elementow_listy == 0 ) // kiedy lista jest pusta
    {
        //gotoxy(30,1);cout<< "Tu jestem tutaj 5 !!!!!!!!";
        //Sleep(4000);

        s='5';
    }
    else if ((liczba_elementow_listy>numer_obecnego_elementu) && (numer_obecnego_elementu == 1)) // wskazywany element to pierszy element listy
                                                                                                 // kiedy elementow jest wiecej niz 1
    {
        Nowy_Element_pomocniczy = Podgladacz->next_el;
        Nowy_Element_pomocniczy->prev_el = NULL;
        Podgladacz ->next_el = NULL;
        Podgladacz->prev_el = NULL;
        Podgladacz = Nowy_Element_pomocniczy;
        Glowa = Podgladacz;

        //gotoxy(30,2);cout<< "Tu jestem tutaj 4 !!!!!!!!";
        //Sleep(4000);

        s='4';


    }
    else if((numer_obecnego_elementu == 1) && (liczba_elementow_listy == numer_obecnego_elementu)) // wskazywany element to pierszy i jedyny element listy
    {
        Podgladacz->next_el = NULL;
        Podgladacz->prev_el = NULL;
        Podgladacz = NULL;

        //dekrementuj_rozmiar_Listy();

        //gotoxy(30,3);cout<< "Tu jestem tutaj 3 !!!!!!!!";
        //Sleep(4000);

        s='3';

    }
    else if((numer_obecnego_elementu == liczba_elementow_listy) && (liczba_elementow_listy>1))  // wskazywany element to ostatni element listy
                                                                                                // kiedy istenieja elementy poprzednie
    {
        Nowy_Element_pomocniczy = Podgladacz->prev_el;
        Nowy_Element_pomocniczy->next_el =NULL;
        //Podgladacz->next_el->next_el = NULL;
        //Podgladacz->next_el->prev_el = NULL;
        Podgladacz = Nowy_Element_pomocniczy;

        //gotoxy(30,4);cout<< "Tu jestem tutaj 2 !!!!!!!!";
        //Sleep(4000);


        s='2';

    }
    else // wskazywany element to jakis element ze srodka listy
    {
        Element *Nowy2_Element_pomocniczy = new Element;

        Nowy_Element_pomocniczy = Podgladacz->next_el;
        Nowy2_Element_pomocniczy = Podgladacz->prev_el;
        Nowy2_Element_pomocniczy->next_el = Nowy_Element_pomocniczy;
        Nowy_Element_pomocniczy->prev_el = Nowy2_Element_pomocniczy;
        Podgladacz->next_el = NULL;
        Podgladacz->prev_el = NULL;
        Podgladacz = Nowy2_Element_pomocniczy;


        //gotoxy(30,5);cout<< "TU JESTEM TUTAJ 1 !!!!!!!!";
        //Sleep(4000);


        s = '1';

    }


    return s;

}

void Lista::edytuj_element_Listy()
{
    posprzataj_bufor();
    cout<< "Podaj rozmiar w MB elementu dodawanego do biblioteki : ";     Podgladacz->ustaw_rozmiar_MB();
    cout<< "Podaj autora elementu dodawanego do biblioteki       : ";     Podgladacz->ustaw_autora();
    cout<< "Podaj tytul elementu dodawanego do biblioteki        : ";     Podgladacz->ustaw_tytul();
    cout<< "Podaj wlasciciela elementu dodawanego do biblioteki  : ";     Podgladacz->ustaw_wlasciciela();

                                                                          Podgladacz->ustaw_typ();
                                                                          Podgladacz->ustaw_date_edycji();
}

void Lista::wczytaj_z_bazy_do_listy(char numer_bazy)
{

        fstream plik_biblioteczny;

        string nazwa_pliku = "Pliki_tekstowe\\\\Baza";
        nazwa_pliku.push_back(numer_bazy);
        nazwa_pliku = nazwa_pliku + ".txt";
        plik_biblioteczny.open(nazwa_pliku.c_str(), ios::in);

        gotoxy(20,20); cout << "Uzyskano dostep do pliku " <<nazwa_pliku<<"!";
        Sleep(3000);


        string pomocnicza1, pom_autor, pom_tytul, pom_wlasciciel, pom_data_dodania, pom_data_edycji;
        float pom_rozmiar;
        char pom_typ;
        int pom_rozmiar_listy = 0;
        plik_biblioteczny>>pom_rozmiar_listy;
        getline( plik_biblioteczny, pomocnicza1);   // zczytanie znaku nowej lini do zmiennej pomocniczej


        while((pom_rozmiar_listy-1) != 0)
        {
        plik_biblioteczny>>pom_rozmiar;
        getline( plik_biblioteczny, pomocnicza1);   // zczytanie znaku nowej lini do zmiennej pomocniczej
        getline( plik_biblioteczny, pom_autor);
        getline( plik_biblioteczny, pom_tytul);
        getline( plik_biblioteczny, pom_wlasciciel);
        plik_biblioteczny>>pom_typ;
        getline( plik_biblioteczny, pomocnicza1);
        getline( plik_biblioteczny, pom_data_dodania);
        getline( plik_biblioteczny, pom_data_edycji);


        Element *Nowy_Element = new Element;
        Nowy_Element->wczytaj_rozmiar_MB(pom_rozmiar);
        Nowy_Element->wczytaj_autora(pom_autor);
        Nowy_Element->wczytaj_tytul(pom_tytul);
        Nowy_Element->wczytaj_wlasciciela(pom_wlasciciel);
        Nowy_Element->wczytaj_typ(pom_typ);
        Nowy_Element->wczytaj_date_dodania(pom_data_dodania);
        Nowy_Element->wczytaj_date_edycji(pom_data_edycji);

        if (rozmiar_Listy == 0)
            {
                Glowa = Nowy_Element;
                Glowa->next_el = NULL;
                Glowa->prev_el = NULL;
                Podgladacz = Glowa;
            }
        else
            {
            Element *Pomocniczy = Glowa;

            while (Pomocniczy->next_el != NULL )
                {
                Pomocniczy = Pomocniczy->next_el;
                }
            Pomocniczy->next_el = Nowy_Element;
            Nowy_Element->prev_el = Pomocniczy;
            Dupa = Nowy_Element;
            Podgladacz = Dupa;

            pom_rozmiar_listy--;

            }
            inkrementuj_rozmiar_Listy();
        }


    plik_biblioteczny.close();

    posprzataj_bufor();
}

int Lista::zapisz_liste_do_pliku(char numer_bazy)
{
    int a = 0;
    fstream plik_biblioteczny;

        string nazwa_pliku = "Pliki_tekstowe\\\\Baza";
        nazwa_pliku.push_back(numer_bazy);
        nazwa_pliku = nazwa_pliku + ".txt";
        plik_biblioteczny.open(nazwa_pliku.c_str(), ios::out);

    if( plik_biblioteczny.good() )
    {

    string pomocnicza1 = "\n", // pomocnicza na znak nowej lini
    pom_autor,
    pom_tytul,
    pom_wlasciciel,
    pom_data_dodania,
    pom_data_edycji;
    float pom_rozmiar;
    char pom_typ;
    int pom_rozmiar_listy = zwroc_rozmiar_Listy();

    if(pom_rozmiar_listy == 0)
    {
        a=1;
    }
    else
    {

            plik_biblioteczny<<pom_rozmiar_listy<<pomocnicza1;
            plik_biblioteczny.flush();              //czyszczenie bufora pliku
            Element *Nowy_Element = new Element;
            Nowy_Element = Glowa;

        while(pom_rozmiar_listy != 0)
        {


            pom_rozmiar = Nowy_Element->zwroc_rozmiar_MB();
            pom_autor = Nowy_Element->zwroc_autora();
            pom_tytul = Nowy_Element->zwroc_tytul();
            pom_wlasciciel= Nowy_Element->zwroc_wlasciciela();
            pom_typ = Nowy_Element->zwroc_typ();
            pom_data_dodania = Nowy_Element->zwroc_date_dodania();
            pom_data_edycji = Nowy_Element->zwroc_date_edycji();


            plik_biblioteczny<<pom_rozmiar<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_autor<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_tytul<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_wlasciciel<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_typ<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_data_dodania<<pomocnicza1;
            plik_biblioteczny.flush();
            plik_biblioteczny<<pom_data_edycji<<pomocnicza1;
            plik_biblioteczny.flush();


            posprzataj_bufor();
            pom_rozmiar_listy--;
            Nowy_Element=Nowy_Element->next_el;

        }


    }

    plik_biblioteczny.close();

    posprzataj_bufor();

}
    a=0;
    return a;

}

int Lista::zapisz_wyszukana_liste_do_pliku(char numer_bazy, int rozmiar_listy_wyszukanej)
{
    int a = 0;
    fstream plik_biblioteczny;

        string nazwa_pliku = "Pliki_tekstowe\\\\Baza";
        nazwa_pliku.push_back(numer_bazy);
        nazwa_pliku = nazwa_pliku + ".txt";
        plik_biblioteczny.open(nazwa_pliku.c_str(), ios::out);

    if( plik_biblioteczny.good() )
    {

    string pomocnicza1 = "\n", // pomocnicza na znak nowej lini
    pom_autor,
    pom_tytul,
    pom_wlasciciel,
    pom_data_dodania,
    pom_data_edycji;
    float pom_rozmiar;
    char pom_typ;
    int pom_rozmiar_listy = rozmiar_listy_wyszukanej;

    if(pom_rozmiar_listy == 0)
    {
        a=1;
    }
    else
    {

            plik_biblioteczny<<pom_rozmiar_listy<<pomocnicza1;
            plik_biblioteczny.flush();              //czyszczenie bufora pliku
            Element *Nowy_Element = new Element;
            Nowy_Element = Glowa;

        while(pom_rozmiar_listy != 0)
        {

            if(Nowy_Element->zwroc_zaznaczenie_wyszukiwania() == true)
            {
                pom_rozmiar = Nowy_Element->zwroc_rozmiar_MB();
                pom_autor = Nowy_Element->zwroc_autora();
                pom_tytul = Nowy_Element->zwroc_tytul();
                pom_wlasciciel= Nowy_Element->zwroc_wlasciciela();
                pom_typ = Nowy_Element->zwroc_typ();
                pom_data_dodania = Nowy_Element->zwroc_date_dodania();
                pom_data_edycji = Nowy_Element->zwroc_date_edycji();


                plik_biblioteczny<<pom_rozmiar<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_autor<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_tytul<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_wlasciciel<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_typ<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_data_dodania<<pomocnicza1;
                plik_biblioteczny.flush();
                plik_biblioteczny<<pom_data_edycji<<pomocnicza1;
                plik_biblioteczny.flush();


                posprzataj_bufor();
                pom_rozmiar_listy--;
                Nowy_Element=Nowy_Element->next_el;
            }
            else
            {
                Nowy_Element=Nowy_Element->next_el;
            }



        }


    }

    plik_biblioteczny.close();

    posprzataj_bufor();

}
    a=0;
    return a;
}

void Lista::wyswietl_pierwszy_element_Listy ()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); // PURPLE

    gotoxy(50,8);   cout<<"Pierwszy Element:";     cout<<endl;
    gotoxy(50,10);  cout<<"Data dodania:    ";     Glowa->wyswietl_date_dodania();     cout<<endl;
    gotoxy(50,12);  cout<<"Tytyl:           ";     Glowa->wyswietl_tytul();            cout<<endl;
    gotoxy(50,14);  cout<<"Autor:           ";     Glowa->wyswietl_autora();           cout<<endl;
    gotoxy(50,16);  cout<<"Katoalog:        ";     Glowa->wyswietl_typ();              cout<<endl;
    gotoxy(50,18);  cout<<"Rozmiar w MB:    ";     Glowa->wyswietl_rozmiar_MB();       cout<<endl;
    gotoxy(50,20);  cout<<"Wlasciciel:      ";     Glowa->wyswietl_wlasciciela();      cout<<endl;
    // getchar();
    // system( "cls" );        // czyscimy ekran
}

void Lista::wyswietl_ostatni_element_Listy ()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); // PURPLE

    gotoxy(50,8);   cout<<"Ostatni Element: ";     cout<<endl;
    gotoxy(50,10);  cout<<"Data dodania:    ";     Glowa->wyswietl_date_dodania();     cout<<endl;
    gotoxy(50,12);  cout<<"Tytyl:           ";     Glowa->wyswietl_tytul();            cout<<endl;
    gotoxy(50,14);  cout<<"Autor:           ";     Glowa->wyswietl_autora();           cout<<endl;
    gotoxy(50,16);  cout<<"Katoalog:        ";     Glowa->wyswietl_typ();              cout<<endl;
    gotoxy(50,18);  cout<<"Rozmiar w MB:    ";     Glowa->wyswietl_rozmiar_MB();       cout<<endl;
    gotoxy(50,20);  cout<<"Wlasciciel:      ";     Glowa->wyswietl_wlasciciela();      cout<<endl;
    // getchar();
    // system( "cls" );        // czyscimy ekran

}

void Lista::przegladaj_Liste () //aktualny element listy
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); // PURPLE

    gotoxy(50,8);   cout<<"Obecny Element:  ";     cout<<endl;
    gotoxy(50,10);  cout<<"Data dodania:    ";     Podgladacz->wyswietl_date_dodania();     cout<<endl;
    gotoxy(50,12);  cout<<"Tytyl:           ";     Podgladacz->wyswietl_tytul();            cout<<endl;
    gotoxy(50,14);  cout<<"Autor:           ";     Podgladacz->wyswietl_autora();           cout<<endl;
    gotoxy(50,16);  cout<<"Katoalog:        ";     Podgladacz->wyswietl_typ();              cout<<endl;
    gotoxy(50,18);  cout<<"Rozmiar w MB:    ";     Podgladacz->wyswietl_rozmiar_MB();       cout<<endl;
    gotoxy(50,20);  cout<<"Wlasciciel:      ";     Podgladacz->wyswietl_wlasciciela();      cout<<endl;
    if(Podgladacz->zwroc_date_edycji() != "")
        {
    gotoxy(50,22);  cout<<"Data edycji:     ";     Podgladacz->wyswietl_date_edycji();      cout<<endl;
        }


}

void Lista::wlacz_wyszukiwanie()
{
    wyszukiwanie = true;
}

void Lista::wylacz_wyszukiwanie()
{
    wyszukiwanie = false;
}

int Lista::wyszukaj(int numer_wyszukiwanego_typu, string wartosc_wyszukiwanego_typu)
{
    posprzataj_bufor();
    string pomocnicza_do_wyszukania;
    Pomocnik = Glowa;
    int zwracana = 0;

    while(Pomocnik!= NULL)
    {

            if(numer_wyszukiwanego_typu == 1)
            {

                pomocnicza_do_wyszukania = Pomocnik->zwroc_autora();
                if (wartosc_wyszukiwanego_typu == pomocnicza_do_wyszukania)
                {
                    Pomocnik->wlacz_zaznaczenie_wyszukania();
                    zwracana++;
                }
            }else if(numer_wyszukiwanego_typu == 2)
            {
                pomocnicza_do_wyszukania = Pomocnik->zwroc_tytul();
                if (pomocnicza_do_wyszukania == wartosc_wyszukiwanego_typu)
                {
                    Pomocnik->wlacz_zaznaczenie_wyszukania();
                    zwracana++;
                }
            }
            else if(numer_wyszukiwanego_typu == 3)
            {
                pomocnicza_do_wyszukania = Pomocnik->zwroc_wlasciciela();
                if (pomocnicza_do_wyszukania == wartosc_wyszukiwanego_typu)
                {
                    Pomocnik->wlacz_zaznaczenie_wyszukania();
                    zwracana++;
                }
            }
            else if(numer_wyszukiwanego_typu == 4)
            {
                pomocnicza_do_wyszukania = Pomocnik->zwroc_date_dodania();
                if (pomocnicza_do_wyszukania == wartosc_wyszukiwanego_typu)
                {
                    Pomocnik->wlacz_zaznaczenie_wyszukania();
                    zwracana++;
                }
            }
            else if(numer_wyszukiwanego_typu == 5)
            {
                pomocnicza_do_wyszukania = Pomocnik->zwroc_typ();
                if (pomocnicza_do_wyszukania == wartosc_wyszukiwanego_typu)
                {
                    Pomocnik->wlacz_zaznaczenie_wyszukania();
                    zwracana++;
                }
            }

            Pomocnik = Pomocnik->next_el;

        }

        Pomocnik = Glowa;
        if(zwracana != 0)
            {
            while(Pomocnik->zwroc_zaznaczenie_wyszukiwania()!=true)
            {
                Pomocnik = Pomocnik->next_el;
            }
            Podgladacz = Pomocnik;
            }
        return zwracana;

    }

void Lista::sprzataj_wyszukiwanie()
{
    Pomocnik = Glowa;

    while(Pomocnik!= NULL)
    {
        Pomocnik->wylacz_zaznaczenie_wyszukania();
        Pomocnik = Pomocnik->next_el;
    }

}

bool Lista::zwroc_stan_wyszukiwania()
{
    return wyszukiwanie;
}

void Lista::nadpisanie(Element *elemencik_zrodlo, Element *elemencik_cel)
    {
        Element *Sortownik = new Element;

        Sortownik->wczytaj_rozmiar_MB(elemencik_cel->zwroc_rozmiar_MB());
        Sortownik->wczytaj_autora(elemencik_cel->zwroc_autora());
        Sortownik->wczytaj_tytul(elemencik_cel->zwroc_tytul());
        Sortownik->wczytaj_wlasciciela(elemencik_cel->zwroc_wlasciciela());
        Sortownik->wczytaj_typ(elemencik_cel->zwroc_typ());
        Sortownik->wczytaj_date_dodania(elemencik_cel->zwroc_date_dodania());
        Sortownik->wczytaj_date_edycji(elemencik_cel->zwroc_date_edycji());

        elemencik_cel->wczytaj_rozmiar_MB(elemencik_zrodlo->zwroc_rozmiar_MB());
        elemencik_cel->wczytaj_autora(elemencik_zrodlo->zwroc_autora());
        elemencik_cel->wczytaj_tytul(elemencik_zrodlo->zwroc_tytul());
        elemencik_cel->wczytaj_wlasciciela(elemencik_zrodlo->zwroc_wlasciciela());
        elemencik_cel->wczytaj_typ(elemencik_zrodlo->zwroc_typ());
        elemencik_cel->wczytaj_date_dodania(elemencik_zrodlo->zwroc_date_dodania());
        elemencik_cel->wczytaj_date_edycji(elemencik_zrodlo->zwroc_date_edycji());

        elemencik_zrodlo->wczytaj_rozmiar_MB(Sortownik->zwroc_rozmiar_MB());
        elemencik_zrodlo->wczytaj_autora(Sortownik->zwroc_autora());
        elemencik_zrodlo->wczytaj_tytul(Sortownik->zwroc_tytul());
        elemencik_zrodlo->wczytaj_wlasciciela(Sortownik->zwroc_wlasciciela());
        elemencik_zrodlo->wczytaj_typ(Sortownik->zwroc_typ());
        elemencik_zrodlo->wczytaj_date_dodania(Sortownik->zwroc_date_dodania());
        elemencik_zrodlo->wczytaj_date_edycji(Sortownik->zwroc_date_edycji());

        delete Sortownik;
        Sortownik = NULL;
    }

void Lista::sortuj_Liste_kreator()
{

    int roz_lis = zwroc_rozmiar_Listy();
    int roz_lis2 = zwroc_rozmiar_Listy();
    Pomocnik = Glowa;


    for(int i= 0; i<roz_lis; i++)
    {
        for(int j = 0; j<roz_lis2-1; j++ )
        {
            int x = static_cast<int>(Pomocnik->zwroc_typ());
            int y = static_cast<int>(Pomocnik->next_el->zwroc_typ());
            if( x > y )
            {
                nadpisanie((Pomocnik), (Pomocnik)->next_el);
            }

                Pomocnik = Pomocnik->next_el;

        }
        Pomocnik = Glowa;
        roz_lis2--;

    }
    Podgladacz = Glowa;
}

void Lista::sortuj_Liste_sprzatacz()
{
    int roz_lis = zwroc_rozmiar_Listy();
    int roz_lis2 = zwroc_rozmiar_Listy();
    Pomocnik = Glowa;


    for(int i= 0; i<roz_lis; i++)
    {
        for(int j = 0; j<roz_lis2-1; j++ )
        {

            string data_dodania_x = Pomocnik->zwroc_date_dodania();
            string dzien_x = data_dodania_x.substr(0,2);
            string miesiac_x = data_dodania_x.substr(3,2);
            string rok_x = data_dodania_x.substr(6, 4);
            string godzina_x = data_dodania_x.substr(20, 2);
            string minuta_x = data_dodania_x.substr(23, 2);
            string sekunda_x = data_dodania_x.substr(26, 2);

            string data_dodania_y = Pomocnik->next_el->zwroc_date_dodania();
            string dzien_y = data_dodania_y.substr(0,2);
            string miesiac_y = data_dodania_y.substr(3,2);
            string rok_y = data_dodania_y.substr(6, 4);
            string godzina_y = data_dodania_y.substr(20, 2);
            string minuta_y = data_dodania_y.substr(23, 2);
            string sekunda_y = data_dodania_y.substr(26, 2);

            std::istringstream istrx(rok_x);
            int x;
            istrx >> x;
            std::istringstream istry(rok_y);
            int y;
            istry >> y;

            if(x == y)
            {
                std::istringstream istrx(miesiac_x);
                istrx >> x;
                std::istringstream istry(miesiac_y);
                istry >> y;

                if(x == y)
                {
                    std::istringstream istrx(dzien_x);
                    istrx >> x;
                    std::istringstream istry(dzien_y);
                    istry >> y;

                    if(x == y)
                    {
                        std::istringstream istrx(godzina_x);
                        istrx >> x;
                        std::istringstream istry(godzina_y);
                        istry >> y;

                        if(x == y)
                        {
                            std::istringstream istrx(minuta_x);
                            istrx >> x;
                            std::istringstream istry(minuta_y);
                            istry >> y;

                            if(x == y)
                            {
                                std::istringstream istrx(sekunda_x);
                                istrx >> x;
                                std::istringstream istry(sekunda_y);
                                istry >> y;
                            }
                        }
                    }

                }


            }



            if( x > y )
            {
                nadpisanie((Pomocnik), (Pomocnik)->next_el);
            }

                Pomocnik = Pomocnik->next_el;

        }
        Pomocnik = Glowa;
        roz_lis2--;

    }
    Podgladacz = Glowa;
}

void Lista::wlacz_sortowanie()
{
    sortowanie = true;
}

void Lista::wylacz_sortowanie()
{
    sortowanie = false;
}

bool Lista::zwroc_stan_sortowania()
{
    return sortowanie;
}

//KLASA ELEMENT

Element::Element()
{
    rozmiar_MB      = 0;
    autor           = "nieznany";
    wlasciciel      = "nieznany";
    tytul           = "nieznany";
    data_dodania    = "domyslna";
    typ             = 6;
    data_dodania    = "";

};

void Element::ustaw_rozmiar_MB()
{

    float nowaRozmiar_MB = 0;
    cin.precision(5); cin>>nowaRozmiar_MB;
    rozmiar_MB = (nowaRozmiar_MB >=0) ? nowaRozmiar_MB : 0;      // ustawiamy wartosc na nowa wartosc jesli jest dodatnia jesli nie ustawiamy na 0
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();

}

void Element::wyswietl_rozmiar_MB()
{
    cout.precision(); cout <<rozmiar_MB ;
    // getchar();
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::ustaw_autora()
{
    string NowyAutorek = "";
    getline(cin,NowyAutorek);
    autor ="";
    autor.insert(0, NowyAutorek);
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::wyswietl_autora()
{
    cout <<autor;
    // getchar();
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::ustaw_tytul()
{
    string NowyTytyl = "";
    getline(cin,NowyTytyl);
    tytul="";
    tytul.insert(0, NowyTytyl);
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::wyswietl_tytul()
{
    cout <<tytul;
    // getchar();
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::ustaw_typ()
{
    char nowyTypek = 0;
    while ( (nowyTypek != '1') &&
            (nowyTypek != '2') &&
            (nowyTypek != '3') &&
            (nowyTypek != '4') &&
            (nowyTypek != '5') &&
            (nowyTypek != '6')      )
    {
    gotoxy(68,30);       cout<< " Podaj do jakiej kategorii"; gotoxy(68,31); cout<<" nalezy dodawany element: "<<endl;
    gotoxy(68,32);       cout<< " 1. Muzyka"<<endl;
    gotoxy(68,34);       cout<< " 2. Film"<<endl;
    gotoxy(68,36);       cout<< " 3. Zdjecia"<<endl;
    gotoxy(68,38);       cout<< " 4. Gry"<<endl;
    gotoxy(68,40);       cout<< " 5. Dokumenty"<<endl;
    gotoxy(68,42);       cout<< " 6. Inne"<<endl;
    gotoxy(69,44);       cin>>nowyTypek;
    typ = nowyTypek;
    system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
    }
}

void Element::wyswietl_typ()
{
    char typek = typ;
    string typekString = "nieznany";
    switch (typek)
    {
    case '1' :
        {
        typekString = "Muzyka";
        break;
        }
    case '2':
        {
        typekString = "Film";
        break;
        }
    case '3':
        {
        typekString = "Zdjecia";
        break;
        }
    case '4':
        {
        typekString = "Gry";
        break;
        }
    case '5':
        {
        typekString = "Dokumenty";
        break;
        }
    case '6':
        {
        typekString = "Inne";
        break;
        }
    }

    cout <<typekString;
    //  getchar();
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::ustaw_wlasciciela()
{
    string NowyWlasciciel = "";
    getline(cin,NowyWlasciciel);
    wlasciciel="";
    wlasciciel.insert(0, NowyWlasciciel);
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::wyswietl_wlasciciela()
{
    cout << wlasciciel;
    // getchar();
    // system( "cls" );        // czyscimy ekran
    posprzataj_bufor();
}

void Element::ustaw_date_dodania()
{

    SYSTEMTIME czasik;              // struktura czasik typu SYSTEMTIME bodajze windows.h biblioteka
    GetLocalTime(&czasik);          // pobranie danych do struktury
    ostringstream rok; rok<<czasik.wYear;         // przypisanie danych ze struktury do zmiennych typu ostringstream z bibloteki <sstream>
    ostringstream miesiac; miesiac<< czasik.wMonth;
    ostringstream dzien; dzien<< czasik.wDay;
    ostringstream godzina; godzina<< czasik.wHour;
    ostringstream minuta; minuta<< czasik.wMinute;
    ostringstream sekunda; sekunda<< czasik.wSecond;

    string dniowka = dzien.str();
    string miesiaczek = miesiac.str();
    string minutka = minuta.str();
    string godzinka = godzina.str();
    string sekundka = sekunda.str();

    if  ((dniowka == "1") || (dniowka == "2") || (dniowka == "3") || (dniowka == "4") || (dniowka == "5")
        || (dniowka == "6") || (dniowka == "7") || (dniowka == "8") || (dniowka == "9"))
    {
        string a= "0";
       dniowka = a + dniowka;
    }

    if  ((miesiaczek == "1") || (miesiaczek == "2") || (miesiaczek == "3") || (miesiaczek == "4") || (miesiaczek == "5")
        || (miesiaczek == "6") || (miesiaczek == "7") || (miesiaczek == "8") || (miesiaczek == "9"))
    {
        string a= "0";
       miesiaczek = a + miesiaczek;
    }

    if  ((minutka == "1") || (minutka == "2") || (minutka == "3") || (minutka == "4") || (minutka == "5")
        || (minutka == "6") || (minutka == "7") || (minutka == "8") || (minutka == "9"))
    {
        string a= "0";
       minutka = a + minutka;
    }

    if  ((godzinka == "1") || (godzinka == "2") || (godzinka == "3") || (godzinka == "4") || (godzinka == "5")
        || (godzinka == "6") || (godzinka == "7") || (godzinka == "8") || (godzinka == "9"))
    {
        string a= "0";
       godzinka = a + godzinka;
    }

    if  ((sekundka == "1") || (sekundka == "2") || (sekundka == "3") || (sekundka == "4") || (sekundka == "5")
        || (sekundka == "6") || (sekundka == "7") || (sekundka == "8") || (sekundka == "9"))
    {
        string a= "0";
       sekundka = a + sekundka;
    }

    data_dodania = dniowka + "."            // rzutowanie za pomoca funkcji .str() z biblioteki <sstream> wartosci intowych na string
    + miesiaczek + "."
    + rok.str() + " r."
    + " " + "godz. " + godzinka + ":"
    + minutka + ":"
    + sekundka;
}

void Element::wyswietl_date_dodania()
{
 cout<< data_dodania;
 posprzataj_bufor();
}

void Element::ustaw_date_edycji()
{

    SYSTEMTIME czasik;              // struktura czasik typu SYSTEMTIME bodajze windows.h biblioteka
    GetLocalTime(&czasik);          // pobranie danych do struktury
    ostringstream rok; rok<<czasik.wYear;         // przypisanie danych ze struktury do zmiennych typu ostringstream z bibloteki <sstream>
    ostringstream miesiac; miesiac<< czasik.wMonth;
    ostringstream dzien; dzien<< czasik.wDay;
    ostringstream godzina; godzina<< czasik.wHour;
    ostringstream minuta; minuta<< czasik.wMinute;
    ostringstream sekunda; sekunda<< czasik.wSecond;


    data_edycji = dzien.str() + "."            // rzutowanie za pomoca funkcji .str() z biblioteki <sstream> wartosci intowych na string
    + miesiac.str() + "."
    + rok.str() + " r."
    + " " + "godz. " + godzina.str() + ":"
    + minuta.str() + ":"
    + sekunda.str();
}

void Element::wyswietl_date_edycji()
{
 cout<< data_edycji;
 posprzataj_bufor();
}

float   Element::zwroc_rozmiar_MB()
{
    return rozmiar_MB;
}

string  Element::zwroc_tytul()
{
    return tytul;
}

string  Element::zwroc_autora()
{
    return autor;
}

char Element::zwroc_typ()
{
    return typ;
}

string  Element::zwroc_wlasciciela()
{
    return wlasciciel;
}

string  Element::zwroc_date_dodania()
{
    return data_dodania;
}

string  Element::zwroc_date_edycji()
{
    return data_edycji;
}

void Element::wczytaj_rozmiar_MB(float zmienna)
{
    rozmiar_MB = zmienna;
}

void Element::wczytaj_autora(string zmienna)
{
    autor = zmienna;
}

void Element::wczytaj_tytul(string zmienna)
{
    tytul = zmienna;
}

void Element::wczytaj_typ(char zmienna)
{
    typ = zmienna;
}

void Element::wczytaj_wlasciciela(string zmienna)
{
    wlasciciel = zmienna;
}

void Element::wczytaj_date_dodania(string zmienna)
{
    data_dodania = zmienna;
}

void Element::wczytaj_date_edycji(string zmienna)
{
    data_edycji = zmienna;
}

void Element::wlacz_zaznaczenie_wyszukania()
{
    zaznaczenie_wyszukania = true;
}

void Element::wylacz_zaznaczenie_wyszukania()
{
    zaznaczenie_wyszukania = false;
}

bool Element::zwroc_zaznaczenie_wyszukiwania()
{
    return zaznaczenie_wyszukania;
}






//plik_biblioteczny.seekp( 0, ios_base::cur); // przy pomocy metody seekp() przesuniecie aktualnej pozycji (ios_base::cur) kursora
                                                    // w pliku wskazywanym przez plik_biblioteczny o 1 offset
                                                    // czyli w tym wypadku do nowej lini aby mozna zczytac kolejne linie


