#include "KsiazkaAdresowa.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <memory>

using namespace std;
using namespace tinyxml2;

void print_help()
{
    cout << "Lista dostepnych komend:\n";
    cout << "readX - zaczytaj ksiazke z pliku XML\n";
    cout << "writeX - zapisz obecna ksiazke do plku XML\n";
    cout << "print - wypisz liste kontaktow\n";
    cout << "printF - wypisz pelna liste kontaktow\n";
    cout << "add - dodaj osobe\n";
    cout << "ch - zmien pozycje\n";
    cout << "rm - usun pozycje\n";
    cout << "exit - zamknij program\n";
}

unique_ptr< Kontakt > stworz_kontakt()
{
    cout << "Wpisz typ kontaktu:\n";
    cout << "tel - nr. telefonu\n";
    cout << "email - adres email\n";
    cout << "faks - nr.faks\n";
    cout << "adres - adres zamieszkania\n";
    string in;
    cin >> in;
    if (in == "tel")
    {
        cout << "Podaj nr. telefonu: ";
        cin >> in;
        return make_unique< Telefon >(in);
    }
    else if (in == "faks")
    {
        cout << "Podaj nr. faks: ";
        cin >> in;
        return make_unique< Faks >(in);
    }
    else if (in == "email")
    {
        cout << "Podaj adres email: ";
        cin >> in;
        return make_unique< Email >(in);
    }
    else if (in == "adres")
    {
        string ulica;
        string miasto;
        string numer;

        cout << "Podaj ulice: ";
        cin >> ulica;
        cout << "Podaj numer budynku: ";
        cin >> numer;
        cout << "Podaj miasto: ";
        cin >> miasto;
        cout << "Podaj kod pocztowy: ";
        cin >> in;

        return make_unique< AdresPolski >(ulica, miasto, numer, in);
    }
}

void zmien_pozycje(int n, KsiazkaAdresowa* ksiazka)
{
    string in;
    Osoba& o = ksiazka->get_pozycja(n);
    o.print();
    cout << "\nimie - zmien imie\n";
    cout << "nazwisko - zmien nazwisko\n";
    cout << "kontakt - dodaj kontakt\n";
    cin >> in;
    if (in == "imie") {}
    else if (in == "nazwisko") {}
    else if (in == "kontakt")
    {
        cout << "add - dodaj kontakt\n";
        cout << "rm - usun kontakt\n";
        cin >> in;
        if (in == "add")
            o.add_Kontakt(stworz_kontakt());
        if (in == "rm")
        {
            o.print_kontakty();
            cout << "Wpisz nr. kontaktu: ";
            int n2;
            cin >> n2;
            o.usun_kontkat(n2);
        }
    }
}

int main()
{
    string          in;
    KsiazkaAdresowa ksiazka;
    print_help();
    while (in != "exit")
    {
        cout << "Wpisz komende: ";
        cin >> in;
        if (in == "readX")
        {
            cout << "Wpisz nazwe pliku: ";
            cin >> in;
            ksiazka.cztyajXML(in);
        }
        else if (in == "writeX")
        {
            cout << "Wpisz nazwe pliku: ";
            cin >> in;
            ksiazka.generujXML(in);
        }
        else if (in == "print")
        {
            ksiazka.print_indeks_pozycji();
        }
        else if (in == "printF")
        {
            ksiazka.print_pozycje();
        }
        else if (in == "add")
        {
            cout << "Wpisz imie: ";
            cin >> in;
            string nazwisko;
            cout << "Wpisz nazwisko: ";
            cin >> nazwisko;
            Osoba o(in, nazwisko);
            try
            {
                o.add_Kontakt(stworz_kontakt());
            }
            catch (exception ex)
            {
                cout << "Niepoprawny kontakt!\n";
            }
            ksiazka.new_pozycja(move(o));
        }
        else if (in == "ch")
        {
            ksiazka.print_indeks_pozycji();
            cout << "\nWpisz numer kontaktu do modyfikacji: ";
            int n;
            cin >> n;
            zmien_pozycje(n, &ksiazka);
        }
        else if (in == "rm")
        {
            ksiazka.print_indeks_pozycji();
            cout << "\n Wpisz numer kontaktu do usuniecia: ";
            int n;
            cin >> n;
            ksiazka.usun_pozycje(n);
        }
        else if (in == "help")
            print_help();
    }
}
