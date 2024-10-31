// Z podanego zbioru danych wyselekcjonuj 5 o największej wartości na jednostkę, znając kategorię obiektu
// Dane znajdują się w folderze "dane" w pliku "zbiór_wejściowy.json" oraz "kategorie.json"
// Wynik przedstaw w czytelnej formie na standardowym wyjściu
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <locale>
#include <map>
#include <algorithm>

using namespace std;

struct Dane {
    string typ;
    double masa;
    double wartosc;
    string czystosc;
    string barwa;
    string pochodzenie;
    string wlasciciel;
};


int main() {
    string linia = "", typ = "", pom, barwa;
    int wartosc, linia_size, a = 0;
    unordered_map<string, int> ceny;
    ifstream kategorie("kategorie.json");

    while (getline(kategorie, linia)) {
        linia_size = linia.size();
        for(int i = 0; i < linia_size; ++i) {
            if(linia[i] == '\"') {
                ++i;
                while(linia[i] != ':') {++i;}
                i+=2;
                if(linia[i] == '\"') {++i;}
                while(linia[i] != '\"' && linia[i] != ',') {
                    pom += linia[i];
                    ++i;
                }
                ++i;
                break;
            }
        }
        if(pom.size() == 0) {
                continue;
            }
            switch (a)
            {
            case 0:
                typ += pom;
                ++a;
                break;
            case 1:
                wartosc = stoi(pom);
                ++a;
                break;
            case 2:
                typ += pom;
                ceny[typ] = wartosc;
                typ = "";
                a = 0;
            default:
                break;
            }
        pom = "";
    }

    kategorie.close();

    ifstream zbior_wejsciowy("zbior_wejsciowy.json");
    Dane pom2;
    map <double,vector<Dane>> wartosci;

    while (getline(zbior_wejsciowy, linia)) {
        linia_size = linia.size();
        for(int i = 0; i < linia_size; ++i) {
            if(linia[i] == '\"') {
                ++i;
                while(linia[i] != ':') {++i;}
                i+=2;
                if(linia[i] == '\"') {++i;}
                while(linia[i] != '\"' && i < linia_size) {
                    pom += linia[i];
                    ++i;
                }
                ++i;
                break;
            }
        }
        if(pom.size() == 0) {
                continue;
            }
        switch (a) {
            case 0:
                pom2.typ += pom;
                ++a;
                break;
            case 1:
                if(pom[pom.size() - 1] == 'g') {
                    replace(pom.begin(), pom.end(), ',', '.');
                    pom2.masa = stod(pom)/(28.34952981);
                } else {
                    replace(pom.begin(), pom.end(), ',', '.');
                    pom2.masa = stod(pom);
                }
                ++a;
                break;
            case 2:
                pom2.czystosc += pom;
                ++a;
                break;
            case 3:
                pom2.barwa += pom;
                ++a;
                break;
            case 4:
                pom2.pochodzenie += pom;
                ++a;
                break;
            case 5:
                pom2.wlasciciel += pom;
                pom2.wartosc = pom2.masa * ceny[pom2.typ + pom2.czystosc];
                wartosci[pom2.wartosc].push_back(pom2);
                pom2.typ = "";
                pom2.barwa = "";
                pom2.czystosc = "";
                pom2.masa = 0;
                pom2.pochodzenie = "";
                pom2.wartosc = 0;
                pom2.wlasciciel = "";
                a = 0;
                break;
            default:
                break;
        }
        pom = "";
    }

    int i = 0, ilosc = 5;

    for(auto it = wartosci.rbegin(); it != wartosci.rend() && i < ilosc; ++it, ++i) {
        cout << i + 1 << " Wartosc: " << it->second[0].wartosc << '\n';
        for(auto x: it->second) {
            cout << "Typ: " << x.typ << '\n';
            cout << "Masa: " << x.masa << '\n';
            cout << "Czystosc: " << x.czystosc << '\n';
            cout << "Barwa: " << x.barwa << '\n';
            cout << "Pochodzenie: " << x.pochodzenie << '\n';
            cout << "Wlasciciel: " << x.wlasciciel << "\n\n";
        }
    }

    kategorie.close();
    zbior_wejsciowy.close();
    return 0;
}