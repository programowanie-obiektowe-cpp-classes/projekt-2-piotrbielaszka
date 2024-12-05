#pragma once

#include "IntToString.hpp"
#include "tinyxml2.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using namespace tinyxml2;

class Kontakt
{
public:
    virtual XMLElement* getXML(XMLElement* root)
    {
        XMLElement* el = root->InsertNewChildElement("Pusty");

        return el;
    }
    virtual void print() {}
    virtual bool sprawdz_poprawnosc() { return true; }
};

class Telefon : public Kontakt
{
    int prefiks_miedzynarodowy;
    int numer_telefonu;

public:
    Telefon(int NumerKierunkowy, int NumerTelefonu)
        : prefiks_miedzynarodowy(NumerKierunkowy), numer_telefonu(NumerTelefonu)
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny nr. telefonu");
    }
    Telefon() {}
    Telefon(string Numer)
    {
        Numer.erase(remove(Numer.begin(), Numer.end(), ' '), Numer.end());
        if (Numer.find('+') != Numer.npos)
        {
            Numer.erase(remove(Numer.begin(), Numer.end(), '+'), Numer.end());
            if (Numer.size() > 9)
            {
                prefiks_miedzynarodowy = stoi(Numer.substr(0, Numer.size() - 9));
                numer_telefonu         = stoi(Numer.substr(Numer.size() - 9, 9));
            }
        }
        else
        {
            numer_telefonu         = stoi(Numer);
            prefiks_miedzynarodowy = 48;
        }
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny nr. telefonu");
    }

    int    get_numer_telefonu() { return numer_telefonu; }
    int    get_prefiks_miedzynarodowy() { return prefiks_miedzynarodowy; }
    string get_pelen_numer_telefonu()
    {
        return ("+" + IntToString(prefiks_miedzynarodowy, 1) + " " + IntToString(numer_telefonu, 9, 3));
    }

    void set_numer_telefonu(int n) { numer_telefonu = n; }
    void set_prefiks_miedzynarodowy(int n) { prefiks_miedzynarodowy = n; }

    void print() override { cout << "tel.: " << get_pelen_numer_telefonu() << "\n"; }

    bool sprawdz_poprawnosc() override { return (numer_telefonu < 1e9); }

    XMLElement* getXML(XMLElement* root) override
    {
        XMLElement* el = root->InsertNewChildElement("Telefon");
        el->SetText(get_pelen_numer_telefonu().c_str());
        return el;
    }
};

class Email : public Kontakt
{
    string email;

public:
    Email(string NewEMail) : email(NewEMail)
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny email");
    }

    string get_email() { return email; }
    void   set_email(string NewEMail) { email = NewEMail; }

    void print() override { cout << "email: " << email << "\n"; }
    bool sprawdz_poprawnosc() override { return !(email.find('@') == string::npos || email.find('.') == string::npos); }
    XMLElement* getXML(XMLElement* root) override
    {
        XMLElement* el = root->InsertNewChildElement("Email");
        el->SetText(email.c_str());
        return el;
    }
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
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny adres");
    }
    AdresPolski(string Ulica, string Miasto, string NumerBudynku, string KodPocztowy)
        : ulica(Ulica), miasto(Miasto), numer_budynku(NumerBudynku)
    {
        KodPocztowy.erase(remove(KodPocztowy.begin(), KodPocztowy.end(), '-'), KodPocztowy.end());
        kod_pocztowy = stoi(KodPocztowy);

        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny adres");
    }

    string get_kod_pocztowy()
    {
        return IntToString(kod_pocztowy / 1000, 2) + "-" + IntToString(kod_pocztowy % 1000, 3);
    }
    string get_adres() { return ("ul. " + ulica + " " + numer_budynku + "\n" + get_kod_pocztowy() + " " + miasto); }

    void print() override { cout << get_adres() << "\n"; }

    bool sprawdz_poprawnosc() override
    {
        return !(ulica.length() == 0 || miasto.length() == 0 || numer_budynku.length() == 0);
    }
    XMLElement* getXML(XMLElement* root) override
    {
        XMLElement* el = root->InsertNewChildElement("Adres");
        el->SetAttribute("Ulica", ulica.c_str());
        el->SetAttribute("Miasto", miasto.c_str());
        el->SetAttribute("NumerBudynku", numer_budynku.c_str());
        el->SetAttribute("KodPocztowy", get_kod_pocztowy().c_str());
        return el;
    }
};

class AdresZagraniczny : Kontakt
{
    string line1;
    string line2;
    string line3;
    string kraj;

public:
    AdresZagraniczny(string Line1, string Line2, string Line3, string Kraj)
        : line1(Line1), line2(Line2), line3(Line3), kraj(Kraj)
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny adres");
    }
    bool sprawdz_poprawnosc() override { return !(line1.length() == 0 || kraj.length() == 0); }

    XMLElement* getXML(XMLElement* root) override
    {
        XMLElement* el = root->InsertNewChildElement("Adres");
        el->SetAttribute("Line 1", line1.c_str());
        el->SetAttribute("Line 2", line2.c_str());
        el->SetAttribute("Line 3", line3.c_str());
        el->SetAttribute("Kraj", kraj.c_str());
        return el;
    }
};

class Faks : public Telefon
{
public:
    void print() override { cout << "faks: " << get_pelen_numer_telefonu() << "\n"; }

    Faks(int NumerFaksu, int NumerKierunkowy)
    {
        set_numer_telefonu(NumerFaksu);
        set_prefiks_miedzynarodowy(NumerKierunkowy);
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny nr. faksu");
    }
    Faks(string numer)
    {
        Telefon t = Telefon(numer);
        set_numer_telefonu(t.get_numer_telefonu());
        set_prefiks_miedzynarodowy(t.get_prefiks_miedzynarodowy());
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawny nr. faksu");
    }

    XMLElement* getXML(XMLElement* root) override
    {
        XMLElement* el = root->InsertNewChildElement("Faks");
        el->SetText(get_pelen_numer_telefonu().c_str());
        return el;
    }
};