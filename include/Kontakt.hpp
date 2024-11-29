#pragma once

#include "IntToString.hpp"
#include <iostream>
#include <string>

using namespace std;

class Kontakt
{
public:
    virtual void print() {}
    virtual bool sprawdz_poprawnosc() {}
};

class Telefon : public Kontakt
{
    int prefiks_miedzynarodowy;
    int numer_telefonu;

public:
    Telefon(int NumerKierunkowy, int NumerTelefonu)
        : prefiks_miedzynarodowy(NumerKierunkowy), numer_telefonu(NumerTelefonu)
    {}
    Telefon() {}

    int    get_numer_telefonu() { return numer_telefonu; }
    int    get_prefiks_miedzynarodowy() { return prefiks_miedzynarodowy; }
    string get_pelen_numer_telefonu()
    {
        return ("+" + IntToString(prefiks_miedzynarodowy, 1) + " " + IntToString(numer_telefonu, 9, 3));
    }

    void set_numer_telefonu(int n) { numer_telefonu = n; }
    void set_prefiks_miedzynarodowy(int n) { prefiks_miedzynarodowy = n; }

    void print() override { cout << "tel.: " << get_pelen_numer_telefonu() << "\n"; }
};

class Email : public Kontakt
{
    string email;

public:
    Email(string NewEMail) : email(NewEMail) {}

    string get_email() { return email; }
    void   set_email(string NewEMail) { email = NewEMail; }

    void print() override { cout << "email: " << email << "\n"; }
};

class AdresPolski : public Kontakt
{
    string ulica;
    string miasto;
    string numer_budynku;
    int    kod_pocztowy;

public:
    AdresPolski(string Ulica, string Miasto, string NumerBudynku, int KodPocztowy)
        : ulica(Ulica), miasto(Miasto), numer_budynku(NumerBudynku), kod_pocztowy(KodPocztowy)
    {}

    string get_kod_pocztowy()
    {
        return IntToString(kod_pocztowy / 1000, 2) + "-" + IntToString(kod_pocztowy % 1000, 3);
    }
    string get_adres() { return ("ul. " + ulica + " " + numer_budynku + "\n" + get_kod_pocztowy() + " " + miasto); }

    void print() override { cout << get_adres() << "\n"; }
};

class AdresZagraniczny : Kontakt
{};

class Faks : public Telefon
{
public:
    void print() override { cout << "faks: " << get_pelen_numer_telefonu() << "\n"; }

    Faks(int NumerFaksu, int NumerKierunkowy)
    {
        set_numer_telefonu(NumerFaksu);
        set_prefiks_miedzynarodowy(NumerKierunkowy);
    }
};