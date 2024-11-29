#pragma once

#include "IntToString.hpp"
#include <iostream>
#include <string>

using namespace std;

class Kontakt
{
public:
    virtual void print() {}
};

class Telefon : public Kontakt
{
    int numer_kierunkowy;
    int numer_telefonu;

public:
    Telefon(int NumerKierunkowy, int NumerTelefonu) : numer_kierunkowy(NumerKierunkowy), numer_telefonu(NumerTelefonu)
    {}

    int    get_numer_telefonu() { return numer_telefonu; }
    int    get_numer_kierunkowy() { return numer_kierunkowy; }
    string get_pelen_numer_telefonu()
    {
        return ("+" + IntToString(numer_kierunkowy, 2) + IntToString(numer_telefonu, 9));
    }

    void print() override { cout << "tel.: " << get_pelen_numer_telefonu() << "\n"; }
};

class Email : public Kontakt
{
    string email;

public:
    Email(string Mail) : email(Mail) {}

    string get_email() { return email; }
    void   print() override { cout << "email:" << email << "\n"; }
};

class Adres : public Kontakt
{
    string ulica;
    string miasto;
    string numer_budynku;
    int    kod_pocztowy;
    string kraj;

public:
    Adres(string Ulica, string Miasto, string NumerBudynku, int KodPocztowy, string Kraj)
        : ulica(Ulica), miasto(Miasto), numer_budynku(NumerBudynku), kod_pocztowy(KodPocztowy), kraj(Kraj)
    {}

    string get_kod_pocztowy()
    {
        return IntToString(kod_pocztowy / 1000, 2) + "-" + IntToString(kod_pocztowy % 1000, 3);
    }
    string get_adres() { return ("ul. " + ulica + " " + numer_budynku + "\n" + get_kod_pocztowy() + " " + miasto); }

    void print() override { cout << get_adres(); }
};