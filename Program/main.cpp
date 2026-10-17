#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <filesystem>
using namespace std;

const int N = 20;

// true  -> pierwszy wiersz w pliku mapa.txt to GORNY wiersz mapy (tak jak wyglada na ekranie)
// false -> pierwszy wiersz w pliku to DOLNY wiersz mapy (y = 0)
const bool PIERWSZY_WIERSZ_U_GORY = true;

class Pole {
public:
    int cyfra = 0;
    Pole* rodzic = nullptr;   // nullptr -> jestesmy na polu start
    Pole* dol = nullptr;
    Pole* lewo = nullptr;
    Pole* gora = nullptr;
    Pole* prawo = nullptr;
    double f = INFINITY;      // INFINITY = "puste"
    int x = 0;                // kolumna
    int y = 0;                // wiersz liczony od dolu
    double g = 0;
};

Pole mapa[N][N];              // mapa[y][x]
vector<Pole*> lista_otwarta;
vector<Pole*> lista_zamknieta;
Pole* cel;

bool zawiera(const vector<Pole*>& lista, Pole* p) {
    return find(lista.begin(), lista.end(), p) != lista.end();
}

void obsluzKierunek(Pole* pole, Pole* sasiad, bool poza_mapa) {
    if (poza_mapa || sasiad->cyfra == 5 || zawiera(lista_zamknieta, sasiad)) {
        return; // zignoruj
    }
    double nowe_g = pole->g + 1;
    double dx = sasiad->x - cel->x;
    double dy = sasiad->y - cel->y;
    double nowa_wartosc = nowe_g + sqrt(dx * dx + dy * dy);

    if (sasiad->f > nowa_wartosc) {   // f puste (INFINITY) lub gorsze
        sasiad->f = nowa_wartosc;
        sasiad->g = nowe_g;
        sasiad->rodzic = pole;
    }
    if (!zawiera(lista_otwarta, sasiad)) {
        lista_otwarta.push_back(sasiad);
    }
}

void obsluzSasiadow(Pole* pole) {
    obsluzKierunek(pole, pole->gora,  pole->y + 1 > 19);
    obsluzKierunek(pole, pole->dol,   pole->y - 1 < 0);
    obsluzKierunek(pole, pole->lewo,  pole->x - 1 < 0);
    obsluzKierunek(pole, pole->prawo, pole->x + 1 > 19);
}

Pole* znajdzNajtanszaOdKonca() {
    Pole* najtansze = lista_otwarta.back();
    for (int i = (int)lista_otwarta.size() - 1; i >= 0; i--) {
        if (lista_otwarta[i]->f < najtansze->f) {
            najtansze = lista_otwarta[i];
        }
    }
    return najtansze;
}

bool wczytajMape(const string& nazwap) {
    int wym1 = 20, wym2 = 20;

    int rows = wym2 + 1;
    double **G = new double*[rows];
    while (rows--) G[rows] = new double[wym1 + 1];

    ifstream plik(nazwap.c_str());
    if (!plik) {
        for (int i = 0; i < wym2 + 1; i++) delete[] G[i];
        delete[] G;
        return false;
    }
    for (unsigned int i = 1; i < wym2 + 1; i++)
        for (unsigned int j = 1; j < wym1 + 1; j++)
            plik >> G[i][j];
    plik.close();

    for (int i = 1; i <= wym2; i++)
        for (int j = 1; j <= wym1; j++) {
            int y = PIERWSZY_WIERSZ_U_GORY ? (wym2 - i) : (i - 1);
            mapa[y][j - 1].cyfra = (int)G[i][j];
        }

    for (int i = 0; i < wym2 + 1; i++) delete[] G[i];
    delete[] G;
    return true;
}

void wypisz() {
    for (int y = N - 1; y >= 0; y--) {
        for (int x = 0; x < N; x++) cout << mapa[y][x].cyfra << ' ';
        cout << '\n';
    }
}

int main() {
    if (!wczytajMape("grid.txt")) {
        cerr << "Nie mozna wczytac grid.txt\n";
        return 1;
    }


    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            mapa[y][x].x = x;
            mapa[y][x].y = y;
            if (y + 1 < N) mapa[y][x].gora  = &mapa[y + 1][x];
            if (y - 1 >= 0) mapa[y][x].dol   = &mapa[y - 1][x];
            if (x - 1 >= 0) mapa[y][x].lewo  = &mapa[y][x - 1];
            if (x + 1 < N) mapa[y][x].prawo = &mapa[y][x + 1];
        }
    }

    Pole* pole_startowe = &mapa[0][0];
    cel = &mapa[19][19];

    pole_startowe->g = 0;
    pole_startowe->rodzic = nullptr;
    lista_zamknieta.push_back(pole_startowe);

    obsluzSasiadow(pole_startowe);

    Pole* aktualna_pozycja = pole_startowe;

    // Glowna petla algorytmu
    while ((aktualna_pozycja->x != cel->x || aktualna_pozycja->y != cel->y)
           && !lista_otwarta.empty()) {

        Pole* najtansza_kratka = znajdzNajtanszaOdKonca();
        aktualna_pozycja = najtansza_kratka;

        lista_otwarta.erase(find(lista_otwarta.begin(), lista_otwarta.end(), aktualna_pozycja));
        lista_zamknieta.push_back(aktualna_pozycja);

        if (aktualna_pozycja->x != cel->x || aktualna_pozycja->y != cel->y) {
            obsluzSasiadow(aktualna_pozycja);
        }
    }

    // Odtwarzanie trasy
    if (aktualna_pozycja->x == cel->x && aktualna_pozycja->y == cel->y) {
        vector<Pole*> najlepsza_trasa;
        cel->cyfra = 3;
        najlepsza_trasa.push_back(cel);
        Pole* aktualna_kratka = cel;

        while (aktualna_kratka->rodzic != nullptr) {
            aktualna_kratka->rodzic->cyfra = 3;
            najlepsza_trasa.push_back(aktualna_kratka->rodzic);
            aktualna_kratka = aktualna_kratka->rodzic;
        }

        cout << "Dlugosc trasy (liczba pol): " << najlepsza_trasa.size() << "\n\n";
        wypisz();
    } else {
        cout << "Brak mozliwosci dotarcia do celu!\n";
    }
    return 0;
}