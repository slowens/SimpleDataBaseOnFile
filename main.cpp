#include "head.hpp"


using namespace std;


int main()
{


    system ("mode con cols=100 lines=50"); // ustawianie rozmiaru konsoli
    gotoxy(10, 6);   cout<< "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    gotoxy(30, 10); cout<<"Witaj w Domowej Bibliotece Multimedialnej";
    gotoxy(10, 15);  cout<< "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED | FOREGROUND_INTENSITY ); // kolorek na czerwono
    gotoxy(34, 26);  cout<< "Wczytywanie ustawien wstepnych....";


   for(int g=0;g<3; g++)
    {
        if(g == 3)
        {
            Beep(1500,1500);
        }else
        {
            Beep(1000,500);
        }
        Sleep(500);
    }


    menu_wstepne();


    return 0;
}
