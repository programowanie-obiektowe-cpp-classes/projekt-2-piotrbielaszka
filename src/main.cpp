#include "KsiazkaAdresowa.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazka{};
    Pozycja         a("Karol",
              "Bielaszka",
              vector< unique_ptr<Kontakt> >{make_unique<Telefon>(48, 123456789),
                                         make_unique<Email>("karol.bielaszka@gmail.com"),
                                         make_unique<Adres>("Jasiiec", "Warszawa", "6", 3299, "Polska")});
    a.print();

    ksiazka.new_pozycja(a);
    ksiazka.print_indeks_pozycji();
    cout << "\n";
    ksiazka.print_pozycje();
}
