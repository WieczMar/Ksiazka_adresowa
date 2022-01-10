#include <iostream>
#include <cstdio>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct Uzytkownik
{
    int id;
    string login, haslo;
};

struct Adresat
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
    string slowo = linia.substr(0, pozycja);
    linia.erase(0, pozycja+1);

    return slowo;
}

void odczytajDaneUzytkownikowzPliku(vector<Uzytkownik> &uzytkownicy)
{
    string linia = "";
    Uzytkownik uzytkownik;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == true)
    {
        while(getline(plik, linia))
        {
            uzytkownik.id = atoi(wytnijCzescLancucha(linia).c_str());
            uzytkownik.login = wytnijCzescLancucha(linia);
            uzytkownik.haslo = wytnijCzescLancucha(linia);

            uzytkownicy.push_back(uzytkownik);
        }
    }
    plik.close();
}

void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
    bool uzytkownikJuzIstnieje;
    Uzytkownik uzytkownik;

    do
    {   uzytkownikJuzIstnieje = false;
        cout << "Podaj nazwe uzytkownika: ";
        uzytkownik.login = wczytajLinie();

        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec = uzytkownicy.end(); itr != koniec; ++itr)
        {
            if((itr->login == uzytkownik.login))
            {
                cout << endl << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika." << endl;
                uzytkownikJuzIstnieje = true;
                break;
            }
        }
    }
    while(uzytkownikJuzIstnieje == true);

    cout << "Podaj haslo: ";
    uzytkownik.haslo = wczytajLinie();

    if (uzytkownicy.empty() == true)
    {
        uzytkownik.id = 1;
    }
    else uzytkownik.id = uzytkownicy.back().id + 1;

    uzytkownicy.push_back(uzytkownik);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out|ios::app);

    if (plik.good() == true)
    {
        plik << uzytkownik.id << "|";
        plik << uzytkownik.login << "|";
        plik << uzytkownik.haslo << "|";
        plik << endl;

        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
    }

    cout << endl << "Zarejestrowano nowego uzytkowanika." << endl;
    system("pause");
}

int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;

    cout << "Podaj nazwe uzytkownika: ";
    uzytkownik.login = wczytajLinie();

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec = uzytkownicy.end(); itr != koniec; ++itr)
    {
        if((itr->login == uzytkownik.login))
        {
            for(int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo: ";
                uzytkownik.haslo = wczytajLinie();
                if(itr->haslo == uzytkownik.haslo)
                {
                    cout << endl << "Zalogowales sie poprawnie." << endl;
                    Sleep(1000);
                    return itr->id;
                }
                else
                {
                    cout << "Bledne haslo. Pozostala ilosc prob: " << (2 - proby) << ". ";
                }
            }
            cout << endl << "Podano 3 razy bledne haslo. Program wstrzymany na 3 sekundy." << endl;
            Sleep(3000);
            return 0;
        }
    }

    cout << endl << "Uzytkownik o podanej nazwie nie istnieje." << endl;
    system("pause");
    return 0;
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    haslo = wczytajLinie();

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec = uzytkownicy.end(); itr != koniec; ++itr)
    {
        if((itr->id == idZalogowanegoUzytkownika))
        {
            itr->haslo = haslo;
            fstream plik;
            plik.open("Uzytkownicy.txt", ios::out);

            if (plik.good() == true)
            {
                for (vector<Uzytkownik>::iterator itr2 = uzytkownicy.begin(), koniec2 = uzytkownicy.end(); itr2 != koniec2; ++itr2)
                {
                    plik << itr2->id << "|";
                    plik << itr2->login << "|";
                    plik << itr2->haslo << "|";
                    plik << endl;
                }
                plik.close();
            }
            else
            {
                cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            }
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1000);
            break;
        }
    }
}

void odczytajDaneAdresatowzPliku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika, int &idOstatniegoAdresata)
{
    int idUzytkownika;
    string linia = "";
    Adresat adresat;
    adresat.id = 0;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in);

    if (plik.good() == true)
    {
        while(getline(plik, linia))
        {
            adresat.id = atoi(wytnijCzescLancucha(linia).c_str());
            idUzytkownika = atoi(wytnijCzescLancucha(linia).c_str());
            if(idUzytkownika != idZalogowanegoUzytkownika) continue;
            adresat.imie = wytnijCzescLancucha(linia);
            adresat.nazwisko = wytnijCzescLancucha(linia);
            adresat.telefon = wytnijCzescLancucha(linia);
            adresat.email = wytnijCzescLancucha(linia);
            adresat.adres = wytnijCzescLancucha(linia);

            adresaci.push_back(adresat);
        }
    }
    plik.close();
    idOstatniegoAdresata = adresat.id;
}

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika, int &idOstatniegoAdresata)
{
    Adresat adresat;
    bool adresatIstnieje = false;

    adresat.id = idOstatniegoAdresata + 1;
    idOstatniegoAdresata += 1;

    cout << "Podaj imie nowego adresata: ";
    adresat.imie = wczytajLinie();
    cout << "Podaj nazwisko nowego adresata: ";
    adresat.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu nowego adresata: ";
    adresat.telefon = wczytajLinie();
    cout << "Podaj e-mail nowego adresata: ";
    adresat.email = wczytajLinie();
    cout << "Podaj adres nowego adresata: ";
    adresat.adres = wczytajLinie();

    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) // czy adresat juz istnieje?
    {
        if((itr->imie == adresat.imie) && (itr->nazwisko == adresat.nazwisko) && (itr->telefon == adresat.telefon)
           && (itr->email == adresat.email) && (itr->adres == adresat.adres))
        {
            cout << endl << "Adresat o takich danych juz istnieje w ksiazce adresowej." << endl;
            adresatIstnieje = true;
            system("pause");
        }
    }

    if(adresatIstnieje == false)
    {
        adresaci.push_back(adresat);

        fstream plik;
        plik.open("Ksiazka adresowa.txt", ios::out|ios::app);

        if (plik.good() == true)
        {
            plik << adresat.id << "|";
            plik << idZalogowanegoUzytkownika << "|";
            plik << adresat.imie << "|";
            plik << adresat.nazwisko << "|";
            plik << adresat.telefon << "|";
            plik << adresat.email << "|";
            plik << adresat.adres << "|";
            plik << endl;

            plik.close();
            cout << endl << "Nowy adresat dodany do ksiazki adresowej." << endl;
            system("pause");
        }
        else
        {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            system("pause");
        }
    }
}

void wyszukajAdresatowpoImieniu(vector<Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << endl << "Brak adresatow w ksiazce adresowej :(" << endl;
    }
    else
    {
        bool adresatIstnieje = false;
        cout << "Podaj imie: ";
        string imie = wczytajLinie();

        for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr)
        {
            if(itr->imie == imie)
            {
                cout << endl << "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko << endl;
                cout << "Nr tel.: " << itr->telefon << endl;
                cout << "E-mail: " << itr->email << endl;
                cout << "Adres: " << itr->adres << endl;
                adresatIstnieje = true;
            }
        }
        if(adresatIstnieje == false)
        {
            cout << endl << "Brak adresatow o wpisanym imieniu w ksiazce adresowej." << endl;
        }
    }
    cout << endl << "Nacisnij dowolny klawisz, by wrocic do menu." << endl;
    system("pause");
}

void wyszukajAdresatowpoNazwisku(vector<Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << endl << "Brak adresatow w ksiazce adresowej :(" << endl;
    }
    else
    {
        bool adresatIstnieje = false;
        cout << "Podaj nazwisko: ";
        string nazwisko = wczytajLinie();

        for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr)
        {
            if(itr->nazwisko == nazwisko)
            {
                cout << endl << "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko << endl;
                cout << "Nr tel.: "<< itr->telefon << endl;
                cout << "E-mail: "<< itr->email << endl;
                cout << "Adres: "<< itr->adres << endl;
                adresatIstnieje = true;
            }
        }
        if(adresatIstnieje == false)
        {
            cout << endl << "Brak adresatow o wpisanym nazwisku w ksiazce adresowej." << endl;
        }
    }
    cout << endl << "Nacisnij enter, by wrocic do menu." << endl;
    system("pause");
}

void pokazListeWszystkichAdresatow(vector<Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << endl << "Brak adresatow w ksiazce adresowej :(" << endl;
    }
    else
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr)
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

void usunAdresata(vector<Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << endl << "Brak adresatow w ksiazce adresowej :(" << endl;
    }
    else
    {
        char znak;
        bool adresatIstnieje = false;
        cout << "Podaj id adresata: ";
        int idUsuwanegoAdresata = atoi(wczytajLinie().c_str());

        for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr)
        {
            if(itr->id == idUsuwanegoAdresata)
            {
                adresatIstnieje = true;
                cout << "Aby usunac adresata o id: " << idUsuwanegoAdresata << ", wcisnij klawisz 't'." << endl;
                znak = tolower(wczytajZnak());

                if(znak == 't')
                {
                    adresaci.erase(itr);
                    Adresat adresat;
                    string linia = "";

                    fstream plikBazowy, plikTymczasowy;
                    plikBazowy.open("Ksiazka adresowa.txt", ios::in);
                    plikTymczasowy.open("Ksiazka adresowa_tymczasowy.txt", ios::out);
                    if (plikBazowy.good() == true)
                    {
                        while(getline(plikBazowy, linia))
                        {
                            adresat.id = atoi(wytnijCzescLancucha(linia).c_str());

                            if(adresat.id == idUsuwanegoAdresata) continue;
                            else
                            {
                                plikTymczasowy << adresat.id << "|" << linia << endl;
                            }
                        }
                        plikBazowy.close();
                        plikTymczasowy.close();
                        if(remove("Ksiazka adresowa.txt") == 0)
                        {
                            rename( "Ksiazka adresowa_tymczasowy.txt", "Ksiazka adresowa.txt" );
                        }
                        else
                        {
                            cout << "Nie udalo sie nadpisac nowych danych do pliku.";
                        }
                        cout << "Adresat usuniety z ksiazki adresowej." << endl;

                    }
                    else
                    {
                        cout << "Nie udalo sie otworzyc pliku i zaktualizowac danych." << endl;
                    }
                }
                else
                {
                    cout << "Operacja anulowana. Nie usunieto adresata." << endl;
                }
            }
        }
        if (adresatIstnieje == false) cout << "Nie ma adresata o wpisanym id." << endl;
    }
    system("pause");
}

void edytujDaneAdresata(vector<Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << endl << "Brak adresatow w ksiazce adresowej :(" << endl;
    }
    else
    {
        char wybor;
        string nowaDana;
        bool adresatIstnieje = false, wprowadzonoZmiany = true;
        cout << "Podaj id adresata: ";
        int idEdytowanegoAdresata = atoi(wczytajLinie().c_str());

        for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr)
        {
            if(itr->id == idEdytowanegoAdresata)
            {
                adresatIstnieje = true;
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
                    Adresat adresat;
                    int idUzytkownika;
                    string linia = "";

                    fstream plikBazowy, plikTymczasowy;
                    plikBazowy.open("Ksiazka adresowa.txt", ios::in);
                    plikTymczasowy.open("Ksiazka adresowa_tymczasowy.txt", ios::out);

                    if (plikBazowy.good() == true)
                    {
                        while(getline(plikBazowy, linia))
                        {
                            adresat.id = atoi(wytnijCzescLancucha(linia).c_str());

                            if(adresat.id == idEdytowanegoAdresata)
                            {
                                idUzytkownika = atoi(wytnijCzescLancucha(linia).c_str());
                                plikTymczasowy << adresat.id << "|";
                                plikTymczasowy << idUzytkownika << "|";
                                plikTymczasowy << itr->imie << "|";
                                plikTymczasowy << itr->nazwisko << "|";
                                plikTymczasowy << itr->telefon << "|";
                                plikTymczasowy << itr->email << "|";
                                plikTymczasowy << itr->adres << "|";
                                plikTymczasowy << endl;
                            }
                            else
                            {
                                plikTymczasowy << adresat.id << "|" << linia << endl;
                            }
                        }
                        plikBazowy.close();
                        plikTymczasowy.close();
                        if(remove("Ksiazka adresowa.txt") == 0)
                        {
                            rename( "Ksiazka adresowa_tymczasowy.txt", "Ksiazka adresowa.txt" );
                        }
                        else
                        {
                            cout << "Nie udalo sie nadpisac nowych danych do pliku.";
                        }
                        cout << "Zmiany zatwierdzone." << endl;
                    }
                    else
                    {
                        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                    }
                }
            }
        }
        if(adresatIstnieje == false)
        {
            cout << "Nie ma adresata o wpisanym id." << endl << endl;
        }
    }
    cout << endl << "Nacisnij dowolny klawisz, by wrocic do menu." << endl;
    system("pause");
}

int main()
{
    char wybor;
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int idOstatniegoAdresata = 0;

    odczytajDaneUzytkownikowzPliku(uzytkownicy);

    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            if(wybor == '1')  rejestracja(uzytkownicy);
            else if(wybor == '2') idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            else if(wybor == '9') exit(0);
            else
            {
                cout << "Bledny wybor. Wybierz ponownie." << endl;
                Sleep(1000);
            }
        }
        else
        {
            vector<Adresat> adresaci;

            odczytajDaneAdresatowzPliku(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);

            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            if(wybor == '1')  dodajAdresata(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);
            else if(wybor == '2') wyszukajAdresatowpoImieniu(adresaci);
            else if(wybor == '3') wyszukajAdresatowpoNazwisku(adresaci);
            else if(wybor == '4') pokazListeWszystkichAdresatow(adresaci);
            else if(wybor == '5') usunAdresata(adresaci);
            else if(wybor == '6') edytujDaneAdresata(adresaci);
            else if(wybor == '7') zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
            else if(wybor == '9') idZalogowanegoUzytkownika = 0;
            else
            {
                cout << "Bledny wybor. Wybierz ponownie." << endl;
                Sleep(1000);
            }
        }
    }
    return 0;
}



