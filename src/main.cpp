#include "KsiazkaAdresowa.hpp"
#include <iostream>

using namespace std;

int main()
{
    KsiazkaAdresowa ksiazka{};
    Pozycja         a("Karol",
              "Bielaszka",
                      48,
                      123456789,
              "karol.bielaszka@gmail.com",
              "Jasiniec",
              "6",
                      3299,
              "Warszawa",
              "Polska");
    // a.print();
    ksiazka.new_pozycja(a);
    ksiazka.new_pozycja(Pozycja("Piotr",
              "Bielaszka",
                      48,
                      987654321,
              "piotr.bielaszka@gmail.com",
              "Jasiniec",
              "6",
                      3299,
              "Warszawa",
              "Polska"));
    ksiazka.new_pozycja(Pozycja("Andrzej",
              "Graska",
                      48,
                      69420,
              "piotr.bielaszka@gmail.com",
              "Jasiniec",
              "6",
                      69420,
              "Warszawa",
              "Polska"));
    ksiazka.print_indeks_pozycji();
    cout << "\n";
    ksiazka.print_pozycje();
}
