#pragma once

#include <string>
#include <vector>

using namespace std;

/// zwraca int o ilosci cyfr >= ilosc_cyfr
string IntToString(const int wejscie, const unsigned int ilosc_cyfr)
{
    string retstring    = to_string(wejscie);
    int    zeros_to_add = ilosc_cyfr - retstring.length();
    for (int i = 0; i < zeros_to_add; i++)
    {
        retstring.insert(0, "0");
    }
    return retstring;
}

/// zwraca int o ilosci cyfr >= ilosc_cyfr ze spacjami co ilosc_spacja cyfr
string IntToString(const int wejscie, const unsigned int ilosc_cyfr, const unsigned int ilosc_spacja)
{
    string retstring    = to_string(wejscie);
    int    len          = retstring.length();
    int    zeros_to_add = ilosc_cyfr - len;
    for (int i = 0; i < zeros_to_add; i++)
    {
        retstring.insert(0, "0");
    }
    len = retstring.length();
    for (int i = ilosc_spacja; i < len; i += ilosc_spacja + 1)
    {
        retstring.insert(i, " ");
    }
    return retstring;
}
