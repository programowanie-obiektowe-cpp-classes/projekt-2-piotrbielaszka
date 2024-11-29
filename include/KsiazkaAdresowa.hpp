#pragma once

#include "IntToString.hpp"
#include "Kontakt.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Pozycja
{
private:
    string                          imie;
    string                          nazwisko;
    vector< unique_ptr< Kontakt > > dane_kontaktowe;

public:
    Pozycja(string Imie, string Nazwisko, vector< unique_ptr< Kontakt > > DaneKontaktowe)
        : imie(Imie), nazwisko(Nazwisko), dane_kontaktowe(DaneKontaktowe)
    {}

    Pozycja() {}

    string get_imie() { return imie; }
    string get_nazwisko() { return nazwisko; }
    string nazwa() { return (imie + " " + nazwisko); }

    void add_Kontakt(unique_ptr< Kontakt > k) { dane_kontaktowe.push_back(k);}

    vector< unique_ptr< Kontakt > > get_dane_kontaktowe() { return dane_kontaktowe; }

    void print()
    {
        cout << nazwa() << "\n";
        for (vector<unique_ptr<Kontakt>>::iterator it = dane_kontaktowe.begin();it!=dane_kontaktowe.end();it++)
        {
            (*it)->print();
        }
    }
};

class KsiazkaAdresowa
{
private:
    vector< Pozycja > pozycje;

public:
    Pozycja operator[](int id) { return pozycje[id]; }
    Pozycja get_pozycja(int id) { return this->pozycje[id]; }

    void new_pozycja(Pozycja p) { pozycje.push_back(p); }

    void print_indeks_pozycji()
    {
        int i = 0;
        for (Pozycja p : pozycje)
        {
            cout << i << ":\t" << p.nazwa() << "\n";
            i++;
        }
    }
    void print_pozycje()
    {
        for (Pozycja p : pozycje)
        {
            p.print();
            cout << "\n";
        }
    }
};