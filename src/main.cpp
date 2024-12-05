#include "KsiazkaAdresowa.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <memory>

using namespace std;
using namespace tinyxml2;

int main()
{

    KsiazkaAdresowa ksiazka{};
    Osoba         a("Karol",
              "Bielaszka",
              vector< Kontakt* >{new Telefon(48, 123456789),
                                         new Email("karol.bielaszka@gmail.com"),
                                         new AdresPolski("Jasiniec", "Warszawa", "6", 3299)});
    // a.print();

    ksiazka.new_pozycja(a);
    ksiazka.new_pozycja(Osoba("Piotr",
                                "Bielaszka",
                                vector< Kontakt* >{new Telefon(353, 42069),
                                                   new Email("piotr.bielaszka@gmail.com"),
                                                   new AdresPolski("Jasiniec", "Warszawa", "6", 3299),
                                                   new Faks{228787854, 48}}));
    ksiazka.print_indeks_pozycji();
    cout << "\n";
    ksiazka.print_pozycje();
    ksiazka.generujXML("kontakty.xml");

    cout<<"ksiazka 2:\n\n";
    KsiazkaAdresowa ksiazka2{};
    ksiazka2.cztyajXML("kontakty.xml");

    ksiazka2.print_pozycje();
}
