#pragma once

#include "IntToString.hpp"
#include "Kontakt.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace tinyxml2;

class Osoba
{
private:
    string                          imie;
    string                          nazwisko;
    vector< unique_ptr< Kontakt > > dane_kontaktowe;

public:
    Osoba(string Imie, string Nazwisko, vector< unique_ptr< Kontakt > > DaneKontaktowe)
        : imie(move(Imie)), nazwisko(move(Nazwisko)), dane_kontaktowe(move(DaneKontaktowe))
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawne imie lub nazwisko");
    }
    Osoba(string Imie, string Nazwisko) : imie(move(Imie)), nazwisko(move(Nazwisko))
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawne imie lub nazwisko");
    }

    Osoba() = default;

    const string& get_imie() const { return imie; }
    const string& get_nazwisko() const { return nazwisko; }
    string        get_nazwa() const { return (imie + " " + nazwisko); }

    void add_Kontakt(unique_ptr< Kontakt > k) { dane_kontaktowe.push_back(move(k)); }
    void usun_kontkat(int n) { dane_kontaktowe.erase(dane_kontaktowe.begin() + n); }

    const vector< unique_ptr< Kontakt > >& get_dane_kontaktowe() const { return dane_kontaktowe; }

    void print() const
    {
        cout << get_nazwa() << "\n";
        for (const auto& k : dane_kontaktowe)
            k->print();
    }

    void print_kontakty() const
    {
        int i = 0;
        for (const auto& k : dane_kontaktowe)
        {
            cout << "----" << i << "----\n";
            k->print();
            i++;
        }
    }

    bool sprawdz_poprawnosc() { return !(imie.length() == 0 || nazwisko.length() == 0); }
};

class KsiazkaAdresowa
{
private:
    vector< Osoba > osoby;

public:
    const Osoba& operator[](int id) const { return osoby[id]; }
    Osoba&       operator[](int id) { return osoby[id]; }
    const Osoba& get_pozycja(int id) const { return this->osoby[id]; }
    Osoba&       get_pozycja(int id) { return this->osoby[id]; }

    void new_pozycja(Osoba o) { osoby.push_back(move(o)); }

    void usun_pozycje(int n) { osoby.erase(osoby.begin() + n); }

    void print_indeks_pozycji() const
    {
        int i = 0;
        for (const auto& o : osoby)
        {
            cout << i << ":\t" << o.get_nazwa() << "\n";
            i++;
        }
    }
    void print_pozycje() const
    {
        for (const auto& o : osoby)
        {
            o.print();
            cout << "\n";
        }
    }

    void generujXML(string nazwaPliku)
    {
        XMLDocument doc;
        XMLElement* root = doc.NewElement("Osoby");
        doc.InsertFirstChild(root);
        XMLElement* el;
        for (const auto& o : osoby)
        {
            el = doc.NewElement("Osoba");
            el->SetAttribute("Imie", o.get_imie().c_str());
            el->SetAttribute("Nazwisko", o.get_nazwisko().c_str());
            for (const auto& k : o.get_dane_kontaktowe())
            {
                el->InsertEndChild(k->getXML(root));
            }
            root->InsertEndChild(el);
        }
        doc.SaveFile(nazwaPliku.c_str());
    }

    void cztyajXML(string nazwaPliku)
    {
        XMLDocument doc;
        XMLError    eResult = doc.LoadFile(nazwaPliku.c_str());
        if (eResult == XML_SUCCESS)
        {
            XMLNode* root      = doc.FirstChild();
            string   xml_value = root->Value();
            if (xml_value == "Osoby")
            {
                XMLElement* xml_osoba = root->FirstChildElement();
                XMLElement* xml_kontakt;
                string      imie, nazwisko;
                while (xml_osoba != nullptr)
                {
                    xml_value = xml_osoba->Value();
                    if (xml_value == "Osoba")
                    {
                        if (xml_osoba->Attribute("Imie") != nullptr)
                            imie = xml_osoba->Attribute("Imie");
                        if (xml_osoba->Attribute("Nazwisko") != nullptr)
                            nazwisko = xml_osoba->Attribute("Nazwisko");

                        Osoba o     = Osoba(imie, nazwisko);
                        xml_kontakt = xml_osoba->FirstChildElement();
                        unique_ptr< Kontakt > k;
                        while (xml_kontakt != nullptr)
                        {
                            xml_value = xml_kontakt->Value();
                            if (xml_value == "Telefon")
                            {
                                try
                                {
                                    k = make_unique< Telefon >(xml_kontakt->GetText());
                                }
                                catch (exception ex)
                                {
                                    cout << "niepoprawny faks";
                                }
                            }
                            else if (xml_value == "Email")
                            {
                                try
                                {
                                    k = make_unique< Email >(xml_kontakt->GetText());
                                }
                                catch (exception ex)
                                {
                                    cout << "niepoprawny email";
                                }
                            }
                            else if (xml_value == "Faks")
                            {
                                try
                                {
                                    k = make_unique< Faks >(xml_kontakt->GetText());
                                }
                                catch (exception ex)
                                {
                                    cout << "niepoprawny faks";
                                }
                            }
                            else if (xml_value == "Adres")
                            {
                                if (!(xml_kontakt->Attribute("Ulica") == nullptr ||
                                      xml_kontakt->Attribute("Miasto") == nullptr ||
                                      xml_kontakt->Attribute("NumerBudynku") == nullptr ||
                                      xml_kontakt->Attribute("KodPocztowy") == nullptr))
                                {
                                    try
                                    {
                                        k = make_unique< AdresPolski >(xml_kontakt->Attribute("Ulica"),
                                                                       xml_kontakt->Attribute("Miasto"),
                                                                       xml_kontakt->Attribute("NumerBudynku"),
                                                                       xml_kontakt->Attribute("KodPocztowy"));
                                    }
                                    catch (exception ex)
                                    {
                                        cout << "niepoprawny adres";
                                    }
                                }
                            }
                            o.add_Kontakt(move(k));
                            xml_kontakt = xml_kontakt->NextSiblingElement();
                        }
                        osoby.push_back(move(o));
                    }
                    xml_osoba = xml_osoba->NextSiblingElement();
                }
            }
            else
                throw "XML jest niepoprawnie sformatowany!";
        }
    }
};