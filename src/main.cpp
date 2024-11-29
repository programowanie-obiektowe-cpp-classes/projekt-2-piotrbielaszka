#include "KsiazkaAdresowa.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazka{};
    Pozycja         a("Karol",
              "Bielaszka",
              vector< Kontakt* >{new Telefon(48, 123456789),
                                         new Email("karol.bielaszka@gmail.com"),
                                         new AdresPolski("Jasiniec", "Warszawa", "6", 3299)});
    //a.print();

    ksiazka.new_pozycja(a);
    ksiazka.new_pozycja(Pozycja("Piotr",
                                "Bielaszka",
                                vector< Kontakt* >{new Telefon(353, 42069),
                                                   new Email("piotr.bielaszka@gmail.com"),
                                                   new AdresPolski("Jasiniec", "Warszawa", "6", 3299),
                                                   new Faks{228787854,48}}));
    ksiazka.print_indeks_pozycji();
    cout << "\n";
    ksiazka.print_pozycje();
}
