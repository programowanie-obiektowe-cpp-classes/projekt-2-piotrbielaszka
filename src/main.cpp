#include "KsiazkaAdresowa.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <memory>

using namespace std;
using namespace tinyxml2;

int main()
{

    KsiazkaAdresowa ksiazka{};
    Osoba           a("Karol",
            "Bielaszka",
            vector< shared_ptr< Kontakt > >{make_shared< Telefon >(48, 123456789),
                                                      make_shared< Email >("karol.bielaszka@gmail.com"),
                                                      make_shared< AdresPolski >("Jasiniec", "Warszawa", "6", 3299)});
    // a.print();

    ksiazka.new_pozycja(a);
    ksiazka.new_pozycja(
        Osoba("Piotr",
              "Bielaszka",
              vector< shared_ptr< Kontakt > >{make_shared< Telefon >(353, 42069),
                                              make_shared< Email >("piotr.bielaszka@gmail.com"),
                                              make_shared< AdresPolski >("Jasiniec", "Warszawa", "6", 3299),
                                              make_shared< Faks >(228787854, 48)}));
    ksiazka.print_indeks_pozycji();
    cout << "\n";
    ksiazka.print_pozycje();
    ksiazka.generujXML("kontakty.xml");

    cout << "ksiazka 2:\n\n";
    KsiazkaAdresowa ksiazka2{};
    ksiazka2.cztyajXML("kontakty.xml");

    ksiazka2.print_pozycje();
}
