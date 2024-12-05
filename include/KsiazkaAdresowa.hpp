#pragma once

#include "IntToString.hpp"
#include "Kontakt.hpp"
#include <algorithm>
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
    vector< shared_ptr< Kontakt > > dane_kontaktowe;

public:
    Osoba(string Imie, string Nazwisko, vector< shared_ptr< Kontakt > > DaneKontaktowe)
        : imie(Imie), nazwisko(Nazwisko), dane_kontaktowe(DaneKontaktowe)
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawne imie lub nazwisko");
    }
    Osoba(string Imie, string Nazwisko) : imie(Imie), nazwisko(Nazwisko)
    {
        if (!sprawdz_poprawnosc())
            throw logic_error("Niepoprawne imie lub nazwisko");
    }

    Osoba() {}

    ~Osoba()
    {
        // for (Kontakt* k : dane_kontaktowe)
        // {
        //     delete(k);
        // }
    }

    string get_imie() { return imie; }
    string get_nazwisko() { return nazwisko; }
    string get_nazwa() { return (imie + " " + nazwisko); }

    void add_Kontakt(shared_ptr< Kontakt > k) { dane_kontaktowe.push_back(k); }

    vector< shared_ptr< Kontakt > > get_dane_kontaktowe() { return dane_kontaktowe; }

    void print()
    {
        cout << get_nazwa() << "\n";
        for (shared_ptr< Kontakt > k : dane_kontaktowe)
        {
            k->print();
        }
    }

    bool sprawdz_poprawnosc() { return !(imie.length() == 0 || nazwisko.length() == 0); }
};

class KsiazkaAdresowa
{
private:
    vector< Osoba > osoby;

public:
    Osoba operator[](int id) { return osoby[id]; }
    Osoba get_pozycja(int id) { return this->osoby[id]; }

    void new_pozycja(Osoba o) { osoby.push_back(o); }

    void print_indeks_pozycji()
    {
        int i = 0;
        for (Osoba o : osoby)
        {
            cout << i << ":\t" << o.get_nazwa() << "\n";
            i++;
        }
    }
    void print_pozycje()
    {
        for (Osoba o : osoby)
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
        for (Osoba o : osoby)
        {
            el = doc.NewElement("Osoba");
            el->SetAttribute("Imie", o.get_imie().c_str());
            el->SetAttribute("Nazwisko", o.get_nazwisko().c_str());
            for (shared_ptr< Kontakt > k : o.get_dane_kontaktowe())
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
                string      imie     = "";
                string      nazwisko = "";
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
                        shared_ptr< Kontakt > k;
                        while (xml_kontakt != nullptr)
                        {
                            xml_value = xml_kontakt->Value();
                            if (xml_value == "Telefon")
                            {
                                try
                                {
                                    k = make_shared< Telefon >(xml_kontakt->GetText());
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
                                    k = make_shared< Email >(xml_kontakt->GetText());
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
                                    k = make_shared< Faks >(xml_kontakt->GetText());
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
                                        k = make_shared< AdresPolski >(xml_kontakt->Attribute("Ulica"),
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
                            o.add_Kontakt(k);
                            xml_kontakt = xml_kontakt->NextSiblingElement();
                        }
                        osoby.push_back(o);
                    }
                    xml_osoba = xml_osoba->NextSiblingElement();
                }
            }
            else
                throw "XML jest niepoprawnie sformatowany!";
        }
    }
};