#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

struct Znajomy
{
    int id;
    string imie,nazwisko,telefon,email,adres;
};

string wczytajLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak  = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

string wytnijCzescLancucha(string &linia)
{
    size_t pozycja = linia.find("|");
    string word = linia.substr(0, pozycja);
    linia.erase(0, pozycja+1);

    return word;
}

int odczytajDanezPliku(vector<Znajomy> &znajomi,int iloscZnajomych)
{
    string linia = "";
    Znajomy znajomy;
    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in);

    if (plik.good() == true)
    {
        while(getline(plik, linia))
        {
            znajomy.id = atoi(wytnijCzescLancucha(linia).c_str());
            znajomy.imie = wytnijCzescLancucha(linia);
            znajomy.nazwisko = wytnijCzescLancucha(linia);
            znajomy.telefon = wytnijCzescLancucha(linia);
            znajomy.email = wytnijCzescLancucha(linia);
            znajomy.adres = wytnijCzescLancucha(linia);

            znajomi.push_back(znajomy);
            iloscZnajomych++;
        }
    }
    plik.close();

    return iloscZnajomych;
}

int dodajZnajomego(vector<Znajomy> &znajomi,int iloscZnajomych)
{
    Znajomy znajomy;
    bool znajomyIstnieje = false;

    if (iloscZnajomych > 0)
    {
        znajomy.id = znajomi[iloscZnajomych - 1].id + 1; // ustaw id wieksze o 1 od ostatniego przypisanego id
    }
    else znajomy.id = 1;
    cout << "Podaj imie nowego znajomego: ";
    znajomy.imie = wczytajLinie();
    cout << "Podaj nazwisko nowego znajomego: ";
    znajomy.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu nowego znajomego: ";
    znajomy.telefon = wczytajLinie();
    cout << "Podaj e-mail nowego znajomego: ";
    znajomy.email = wczytajLinie();
    cout << "Podaj adres nowego znajomego: ";
    znajomy.adres = wczytajLinie();

    for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr) // czy znajomy juz istnieje?
    {
        if((itr->imie == znajomy.imie) && (itr->nazwisko == znajomy.nazwisko) && (itr->telefon == znajomy.telefon)
           && (itr->email == znajomy.email) && (itr->adres == znajomy.adres))
        {
            cout << endl << "Znajomy o takich danych juz istnieje w ksiazce adresowej." << endl;
            znajomyIstnieje = true;
            system("pause");
        }
    }

    if(znajomyIstnieje == false)
    {
        znajomi.push_back(znajomy);
        iloscZnajomych++;

        fstream plik;
        plik.open("Ksiazka adresowa.txt", ios::out|ios::app);

        if (plik.good() == true)
        {
            if(iloscZnajomych != 1) plik << endl;
            plik << znajomy.id << "|";
            plik << znajomy.imie << "|";
            plik << znajomy.nazwisko << "|";
            plik << znajomy.telefon << "|";
            plik << znajomy.email << "|";
            plik << znajomy.adres << "|";

            plik.close();
            cout << endl << "Nowy znajomy dodany do ksiazki adresowej." << endl;
            system("pause");
        }
        else
        {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            system("pause");
        }
    }
    return iloscZnajomych;
}

void wyszukajZnajomychpoImieniu(vector<Znajomy> &znajomi)
{
    if(znajomi.empty())
    {
        cout << endl << "Brak znajomych w ksiazce adresowej :(" << endl;
    }
    else
    {
        bool znajomyIstnieje = false;
        cout << "Podaj imie: ";
        string imie = wczytajLinie();

        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr)
        {
            if(itr->imie == imie)
            {
                cout << endl << "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko << endl;
                cout << "Nr tel.: " << itr->telefon << endl;
                cout << "E-mail: " << itr->email << endl;
                cout << "Adres: " << itr->adres << endl;
                znajomyIstnieje = true;
            }
        }
        if(znajomyIstnieje == false)
        {
            cout << endl << "Brak znajomych o wpisanym imieniu w ksiazce adresowej." << endl;
        }
    }
    cout << endl << "Nacisnij dowolny klawisz, by wrocic do menu." << endl;
    system("pause");
}

void wyszukajZnajomychpoNazwisku(vector<Znajomy> &znajomi)
{
    if(znajomi.empty())
    {
        cout << endl << "Brak znajomych w ksiazce adresowej :(" << endl;
    }
    else
    {
        bool znajomyIstnieje = false;
        cout << "Podaj nazwisko: ";
        string nazwisko = wczytajLinie();

        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr)
        {
            if(itr->nazwisko == nazwisko)
            {
                cout << endl << "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko << endl;
                cout << "Nr tel.: "<< itr->telefon << endl;
                cout << "E-mail: "<< itr->email << endl;
                cout << "Adres: "<< itr->adres << endl;
                znajomyIstnieje = true;
            }
        }
        if(znajomyIstnieje == false)
        {
            cout << endl << "Brak znajomych o wpisanym nazwisku w ksiazce adresowej." << endl;
        }
    }
    cout << endl << "Nacisnij enter, by wrocic do menu." << endl;
    system("pause");
}

void pokazListeWszystkichZnajomych(vector<Znajomy> &znajomi)
{
    if(znajomi.empty())
    {
        cout << endl << "Brak znajomych w ksiazce adresowej :(" << endl;
    }
    else
    {
        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr)
        {
            cout << endl << "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko << endl;
            cout << "Nr tel.: " << itr->telefon << endl;
            cout << "E-mail: " << itr->email << endl;
            cout << "Adres: " << itr->adres << endl;
        }
    }
    cout << endl << "Nacisnij dowolny klawisz, by wrocic do menu." << endl;
    system("pause");
}

int usunZnajomego(vector<Znajomy> &znajomi, int iloscZnajomych)
{
    if(znajomi.empty())
    {
        cout << endl << "Brak znajomych w ksiazce adresowej :(" << endl;
    }
    else
    {
        char znak;
        cout << "Podaj id znajomego: ";
        int id = atoi(wczytajLinie().c_str());

        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr)
        {
            if(itr->id == id)
            {
                cout << "Aby usunac znajomego o id: " << id << ", wcisnij klawisz 't'." << endl;
                znak = tolower(wczytajZnak());

                if(znak == 't')
                {
                    znajomi.erase(itr);
                    iloscZnajomych--;

                    //NADpis danych do pliku
                    fstream plik;
                    plik.open("Ksiazka adresowa.txt", ios::out);

                    if (plik.good() == true)
                    {
                        for (vector<Znajomy>::iterator itr2 = znajomi.begin(), koniec2 = znajomi.end(); itr2 != koniec2; ++itr2)
                        {
                            plik << itr2->id << "|";
                            plik << itr2->imie << "|";
                            plik << itr2->nazwisko << "|";
                            plik << itr2->telefon << "|";
                            plik << itr2->email << "|";
                            plik << itr2->adres << "|";
                            if(itr2 != koniec2 - 1) plik << endl;
                        }
                        plik.close();
                        cout << "Znajomy usuniety z ksiazki adrsowej." << endl;
                    }
                    else
                    {
                        cout << "Nie udalo sie otworzyc pliku i zaktualizowac danych." << endl;
                    }
                }
                else
                {
                    cout << "Operacja anulowana. Nie usunieto znajomego." << endl;
                }
                system("pause");
                return iloscZnajomych;
            }
        }
        cout << "Nie ma znajomego o wpisanym id." << endl;
    }
    system("pause");
    return iloscZnajomych;
}

void edytujDaneZnajomego(vector<Znajomy> &znajomi, int iloscZnajomych)
{
    if(znajomi.empty())
    {
        cout << endl << "Brak znajomych w ksiazce adresowej :(" << endl;
    }
    else
    {
        char wybor;
        string nowaDana;
        bool znajomyIstnieje = false, wprowadzonoZmiany = true;
        cout << "Podaj id znajomego: ";
        int id = atoi(wczytajLinie().c_str());

        for (vector<Znajomy>::iterator itr = znajomi.begin(), koniec = znajomi.end(); itr != koniec; ++itr)
        {
            if(itr->id == id)
            {
                znajomyIstnieje = true;
                system( "cls");
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. e-mail" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Powrot do menu" << endl;
                cout << "Wybor danej do edycji: ";
                wybor = wczytajZnak();

                if(wybor == '1' || wybor == '2' || wybor == '3' || wybor == '4' || wybor == '5')
                {
                    cout << "Wprawadz nowe dane: ";
                    nowaDana = wczytajLinie();
                }
                else if(wybor == '6') wprowadzonoZmiany = false;
                else
                {
                    wprowadzonoZmiany = false;
                    cout << "Bledny wybor. Powrot do menu glownego." << endl;
                    system("pause");
                }
                if(wybor == '1') itr->imie = nowaDana;
                else if(wybor == '2') itr->nazwisko = nowaDana;
                else if(wybor == '3') itr->telefon = nowaDana;
                else if(wybor == '4') itr->email = nowaDana;
                else if(wybor == '5') itr->adres = nowaDana;

                if(wprowadzonoZmiany == true)
                {
                    fstream plik;
                    plik.open("Ksiazka adresowa.txt", ios::out);

                    if (plik.good() == true)
                    {
                        for (vector<Znajomy>::iterator itr2 = znajomi.begin(), koniec2 = znajomi.end(); itr2 != koniec2; ++itr2)
                        {
                            plik << itr2->id << "|";
                            plik << itr2->imie << "|";
                            plik << itr2->nazwisko << "|";
                            plik << itr2->telefon << "|";
                            plik << itr2->email << "|";
                            plik << itr2->adres << "|";
                            if(itr2 != koniec2 - 1) plik << endl;
                        }
                        plik.close();
                        cout << "Zmiany zatwierdzone." << endl;
                    }
                    else
                    {
                        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                    }
                }
            }
        }
        if(znajomyIstnieje == false)
        {
            cout << "Nie ma znajomego o wpisanym id." << endl << endl;
        }
    }
    cout << endl << "Nacisnij dowolny klawisz, by wrocic do menu." << endl;
    system("pause");
}

int main()
{
    char wybor;
    vector<Znajomy> znajomi;
    int iloscZnajomych = 0;

    iloscZnajomych = odczytajDanezPliku(znajomi, iloscZnajomych);

    while(1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj znajomego" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich znajomych" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();

        if(wybor == '1') iloscZnajomych=dodajZnajomego(znajomi, iloscZnajomych);
        else if(wybor == '2') wyszukajZnajomychpoImieniu(znajomi);
        else if(wybor == '3') wyszukajZnajomychpoNazwisku(znajomi);
        else if(wybor == '4') pokazListeWszystkichZnajomych(znajomi);
        else if(wybor == '5') iloscZnajomych=usunZnajomego(znajomi, iloscZnajomych);
        else if(wybor == '6') edytujDaneZnajomego(znajomi, iloscZnajomych);
        else if(wybor == '9') exit(0);
        else
        {
            cout << "Bledny wybor. Wybierz ponownie." << endl;
            Sleep(1000);
        }
    }
    return 0;
}
