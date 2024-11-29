#pragma once

#include "IntToString.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pozycja
{
private:
    string imie;
    string nazwisko;
    int    numer_kierunkowy;
    int    numer_telefonu;
    string email;
    string adres_ulica;
    string adres_miasto;
    string adres_nr_budynku;
    int    adres_kod_pocztowy;
    string adres_kraj;

public:
    Pozycja(string Imie, string Nazwisko, int Numer_kierunkowy, int Numer_telefonu)
        : imie(Imie), nazwisko(Nazwisko), numer_kierunkowy{Numer_kierunkowy}, numer_telefonu(Numer_telefonu)
    {}

    Pozycja(string Imie,
            string Nazwisko,
            int    Numer_kierunkowy,
            int    Numer_telefonu,
            string Email,
            string Adres_ulica,
            string Adres_nr_budynku,
            int    Adres_kod_pocztowy,
            string Adres_miasto,
            string Adres_kraj)
        : imie(Imie),
          nazwisko(Nazwisko),
          numer_kierunkowy{Numer_kierunkowy},
          numer_telefonu(Numer_telefonu),
          email(Email),
          adres_ulica(Adres_ulica),
          adres_miasto(Adres_miasto),
          adres_nr_budynku(Adres_nr_budynku),
          adres_kod_pocztowy(Adres_kod_pocztowy),
          adres_kraj(Adres_kraj)
    {}

    Pozycja() {}

    string get_imie() { return imie; }
    string get_nazwisko() { return nazwisko; }
    string get_imie_nazwisko() { return (imie + " " + nazwisko); }
    int    get_numer_telefonu() { return numer_telefonu; }
    int    get_numer_kierunkowy() { return numer_kierunkowy; }
    string get_email() { return email; }

    string get_pelen_numer_telefonu()
    {
        return ("+" + IntToString(numer_kierunkowy, 2) + IntToString(numer_telefonu, 9));
    }
    string get_kod_pocztowy()
    {
        return IntToString(adres_kod_pocztowy / 1000, 2) + "-" + IntToString(adres_kod_pocztowy % 1000, 3);
    }
    string get_adres()
    {
        return ("ul. " + adres_ulica + " " + adres_nr_budynku + "\n" + get_kod_pocztowy() + " " + adres_miasto);
    }

    void print()
    {
        cout << get_imie_nazwisko() << "\n";
        cout << "tel.: " << get_pelen_numer_telefonu() << "\n";
        cout << "e-mail: " << get_email() << "\n";
        cout << "adres: " << get_adres() << "\n";
    }
};

class KsiazkaAdresowa
{
private:
    vector< Pozycja > pozycje;

public:
    Pozycja operator[](int id) { return pozycje[id]; }
    Pozycja get_pozycja(int id) { return this->pozycje[id]; }

    // void new_pozycja(Pozycja& p) { pozycje.push_back(p); }
    void new_pozycja(Pozycja p) { pozycje.push_back(p); }

    void print_indeks_pozycji()
    {
        int i = 0;
        for (Pozycja p : pozycje)
        {
            cout << i << ":\t" << p.get_imie_nazwisko() << "\n";
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
    // Pozycja set_pozycja(int id) { Pozycja. }
};