#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Pole {
public:
    int cyfra = 0;
    Pole* rodzic = nullptr;
    Pole* dol = nullptr;
    Pole* lewo = nullptr;
    Pole* gora = nullptr;
    Pole* prawo = nullptr;
    double f = INFINITY;
    int x = 0;
    int y = 0;
    double g = 0;
};

vector<Pole*> lista_zamknieta;
vector<Pole*> lista_otwarta;
Pole mapa[20][20];
Pole* start;
Pole* cel;

bool posiada(vector<Pole*>& lista, Pole* pole) {
    return find(lista.begin(), lista.end(), pole) != lista.end();
}

void obsluzSasiadow(Pole* pole) {
    //GÓRA
    if (!(pole->y + 1 > 19 || pole->gora->cyfra == 5 || posiada(lista_zamknieta, pole->gora))) {
        double nowe_g = pole->g + 1;
        double nowe_f = nowe_g + sqrt(pow(pole->gora->x - cel->x, 2) + pow(pole->gora->y - cel->y, 2));
        if (pole->gora->f == INFINITY || pole->gora->f > nowe_f) {
            pole->gora->f = nowe_f;
            pole->gora->g = nowe_g;
            pole->gora->rodzic = pole;
        }
        if (!posiada(lista_otwarta, pole->gora)) {
            lista_otwarta.push_back(pole->gora);
        }
    }

    //DÓŁ
    if (!(pole->y - 1 < 0 || pole->dol->cyfra == 5 || posiada(lista_zamknieta, pole->dol))){
        double nowe_g = pole->g + 1;
        double nowe_f = nowe_g + sqrt(pow(pole->dol->x - cel->x, 2) + pow(pole->dol->y - cel->y, 2));
        if (pole->dol->f == INFINITY || pole->dol->f > nowe_f) {
            pole->dol->f = nowe_f;
            pole->dol->g = nowe_g;
            pole->dol->rodzic = pole;
        }
        if (!posiada(lista_otwarta, pole->dol)) {
            lista_otwarta.push_back(pole->dol);
        }
    }
    //LEWO
    if (!(pole->x - 1 < 0 || pole->lewo->cyfra == 5 || posiada(lista_zamknieta, pole->lewo))){
        double nowe_g = pole->g + 1;
        double nowe_f = nowe_g + sqrt(pow(pole->lewo->x - cel->x, 2) + pow(pole->lewo->y - cel->y, 2));
        if (pole->lewo->f == INFINITY || pole->lewo->f > nowe_f) {
            pole->lewo->f = nowe_f;
            pole->lewo->g = nowe_g;
            pole->lewo->rodzic = pole;
        }
        if (!posiada(lista_otwarta, pole->lewo)) {
            lista_otwarta.push_back(pole->lewo);
        }
    }
    //PRAWO
    if (!(pole->x + 1 > 19 || pole->prawo->cyfra == 5 || posiada(lista_zamknieta, pole->prawo))){
        double nowe_g = pole->g + 1;
        double nowe_f = nowe_g + sqrt(pow(pole->prawo->x - cel->x, 2) + pow(pole->prawo->y - cel->y, 2));
        if (pole->prawo->f == INFINITY || pole->prawo->f > nowe_f) {
            pole->prawo->f = nowe_f;
            pole->prawo->g = nowe_g;
            pole->prawo->rodzic = pole;
        }
        if (!posiada(lista_otwarta, pole->prawo)) {
            lista_otwarta.push_back(pole->prawo);
        }
    }
}

Pole* znajdzNajtanszePoleOdKonca(vector<Pole*>& lista) {
    Pole* najtanszePole = lista.back();
    for (int i = (int)lista.size() - 1; i >= 0; i--) {
        if (lista[i]->f < najtanszePole->f) {
            najtanszePole = lista[i];
        }
    }
    return najtanszePole;
}

bool wczytajIWypiszMape(const string& nazwaMapy) {
    int wym1 = 20;
    int wym2 = 20;
    int rows = wym2 + 1;
    double **G = new double*[rows];
    while (rows--) G[rows] = new double[wym1 + 1];

    cout<<"\n\nNacisnij ENTER aby wczytac tablice o nazwie "<< nazwaMapy;
    getchar();

    ifstream plik(nazwaMapy.c_str());
    if (!plik) {
        for (int i = 0; i < wym2 + 1; i++) delete[] G[i];
        delete[] G;
        return false;
    }

    for ( unsigned int i=1;i<wym2+1;i++)
    {
        for ( unsigned int j=1;j<wym1+1;j++)
        {
            plik >> G[i][j];
            mapa[20 - i][j - 1].cyfra = (int)G[i][j];
        }
    }
    plik.close();

    cout<<"\nWypisujemy na ekran\n\n";
    for(int i=1;i<wym2+1;i++)
    {
        for(int j=1;j<wym1+1;j++)
        {
            cout<<" "<<G[i][j];
        }cout<<"\n";
    }

    for(int i=0;i<wym2+1;i++)
    {delete[] G[i];}
    delete[] G;
    return true;
}

int main() {
    if (!wczytajIWypiszMape("grid.txt")) {
        cerr << "Nie mozna wczytac grid.txt\n";
        return 1;
    }

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            mapa[y][x].x = x;
            mapa[y][x].y = y;
            if (y + 1 < 20)  mapa[y][x].gora  = &mapa[y + 1][x];
            if (y - 1 >= 0)  mapa[y][x].dol   = &mapa[y - 1][x];
            if (x - 1 >= 0)  mapa[y][x].lewo  = &mapa[y][x - 1];
            if (x + 1 < 20)  mapa[y][x].prawo = &mapa[y][x + 1];
        }
    }
    start = &mapa[0][0];
    cel = &mapa[19][19];
    start->g = 0;

    lista_zamknieta.push_back(start);
    obsluzSasiadow(start);
    Pole* aktualna_pozycja = start;

    //główna pętla
    while ((aktualna_pozycja->x != cel->x || aktualna_pozycja->y != cel->y) && !lista_otwarta.empty()) {
        Pole* najtanszePole = znajdzNajtanszePoleOdKonca(lista_otwarta);
        aktualna_pozycja = najtanszePole;

        lista_otwarta.erase(find(lista_otwarta.begin(), lista_otwarta.end(), aktualna_pozycja));
        lista_zamknieta.push_back(aktualna_pozycja);

        if (aktualna_pozycja->x != cel->x || aktualna_pozycja->y != cel->y) {
            obsluzSasiadow(aktualna_pozycja);
        }
    }

    //odtworzenie trasy
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
        //==== potrzebne do wizualizacji ====
        ofstream wy("trasa.txt");
        for (int i = (int)najlepsza_trasa.size() - 1; i >= 0; i--) {
            wy << najlepsza_trasa[i]->x << " " << najlepsza_trasa[i]->y << "\n";
        }
        //===================================
        wy.close();
        cout << "\nDlugosc trasy: " << najlepsza_trasa.size() << "\n\n";
        for (int y = 19; y >= 0; y--) {
            for (int x = 0; x < 20; x++) cout << mapa[y][x].cyfra << ' ';
            cout << "\n";
        }
    }
    else {
        cout << "Brak możliwości dotarcia do celu\n";
    }
}