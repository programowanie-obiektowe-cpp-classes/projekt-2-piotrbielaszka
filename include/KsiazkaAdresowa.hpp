#pragma once

#include "IntToString.hpp"
#include "Kontakt.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Pozycja
{
private:
    string             imie;
    string             nazwisko;
    vector< Kontakt* > dane_kontaktowe;

public:
    Pozycja(string Imie, string Nazwisko, vector< Kontakt* > DaneKontaktowe)
        : imie(Imie), nazwisko(Nazwisko), dane_kontaktowe(DaneKontaktowe)
    {}

    Pozycja() {}

    string get_imie() { return imie; }
    string get_nazwisko() { return nazwisko; }
    string get_nazwa() { return (imie + " " + nazwisko); }

    void add_Kontakt(Kontakt* k) { dane_kontaktowe.push_back(k); }

    vector< Kontakt* > get_dane_kontaktowe() { return dane_kontaktowe; }

    void print()
    {
        cout << get_nazwa() << "\n";
        for (Kontakt* k : dane_kontaktowe)
        {
            k->print();
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
            cout << i << ":\t" << p.get_nazwa() << "\n";
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