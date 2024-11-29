#pragma once

#include <string>

using namespace std;

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