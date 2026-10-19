Autor: Nikodem Kaczmarczyk
Nr Indeksu: 181135
Przedmiot: Elementy robotyki inteligentnej
Grupa: 1
Specjalizacja: Data science and artificial intelligence w praktyce
Data: 17.10.2026

### 1. Cel ćwiczenia
Zaimplementowanie w C++ algorytmu A* na mapie 20x20 wygenerowanej w programie `map_generator.exe` udostępnionym przez prowadzącego oraz przygotowanie graficznej demonstracji jego działania przy użyciu narzędzi generatywnej sztucznej inteligencji.

### 2. Założenia
- wartość 0 oznacza pole wolne, 5 to przeszkoda, a 3 jest polem należącym do wyznaczonej trasy
- start ma współrzędne (0, 0), a cel (19, 19)
- Heurystyka to odległość euklidesowa obliczana ze wzoru 
$$
\sqrt{(poz_x - cel_x)^2 + (poz_y - cel_y)^2}
$$
- koszt jednego ruchu wynosi 1
- dozwolone ruchy: góra, dół, lewo, prawo (bez ruchów po skosie) sprawdzane w tej kolejności
- konflikty rozwiązywane hierarchiczne (najpóźniej napotkane pole)

### 3. Podział pracy

| Etap                                                                 | Wykonawca |
| -------------------------------------------------------------------- | --------- |
| Analiza polecenia i wybór rozstrzygania konfliktów                   | Ja        |
| Pseudokod algorytmu                                                  | Ja        |
| Przepisanie pseudokodu na C++                                        | Ja        |
| Wygenerowanie mapy                                                   | Ja        |
| Uruchomienie i diagnoza błędu wczytywaniu pliku                      | Ja        |
| Weryfikacja wyniku                                                   | Ja        |
| Pomysł demonstracji (wąż, jabłko, kamienie, trawa)                   | Ja        |
| Wybór formy demonstracji (strona internetowa zamiast biblioteki C++) | Ja        |
| Kod strony HTML/JavaScript                                           | AI        |
| Testy demonstracji                                                   | Ja        |
### 4. Opis algorytmu
Dla każdego pola liczona jest wartość f = g + h, gdzie g to koszt dojścia od startu, a h to odległość euklidesowa do celu. W każdej iteracji z listy otwartej wybierane jest pole o najmniejszym f, a przy remisie wygrywa pole dodane **najpóźniej**. Jego sąsiedzi (w kolejności: góra, dół, lewo, prawo) są dodawani do listy otwartej albo ich wartości są poprawiane, jeśli znaleziono krótszą drogę. Po dotarciu do celu trasa jest odtwarzana przez wskaźniki do rodziców i oznaczana wartością 3.

### 5. Implementacja w C++
Program zawiera klasę `Pole` (współrzędne, f, g, wskaźnik na rodzica i sąsiadów), funkcję obsługi sąsiadów z blokadą krawędzi mapy, pętlę główną oraz odtwarzanie trasy. Mapa jest wczytywana z pliku `grid.txt` (20 wierszy i 20 kolumn), a współrzędna y liczona jest od dołu. 

### 6. Wyniki
Dla mapy z generatora program znalazł trasę o długości 39 pól (38 ruchów). Jest to wartość równa odległości Manhattan między startem a celem, czyli krótszej trasy nie ma. Wynik :
```
0 0 0 0 0 0 0 0 0 5 5 0 0 0 5 5 5 5 5 3
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 3 0 0 0
0 0 0 0 0 0 0 3 3 3 3 3 3 3 3 3 0 0 5 0
0 0 0 0 0 0 0 3 5 0 0 0 0 0 0 0 0 0 5 0
0 0 0 0 0 3 3 3 5 0 0 0 0 0 0 0 0 5 5 0
0 0 0 0 0 3 5 5 5 5 5 5 0 0 0 0 0 5 5 0
0 0 0 0 0 3 0 0 5 0 5 5 0 0 0 0 0 5 5 0
0 0 0 0 0 3 0 0 5 0 5 5 0 0 0 0 0 5 0 0
0 0 3 3 3 3 0 0 5 0 5 5 0 0 0 0 0 5 0 0
0 0 3 5 0 0 0 0 5 0 5 5 0 0 0 0 0 5 0 0
0 0 3 5 0 0 0 0 5 0 0 5 0 0 0 0 5 5 0 0
0 0 3 5 0 0 0 0 5 0 0 0 0 0 0 0 5 5 0 0
0 0 3 5 0 0 0 0 0 0 5 0 0 0 5 5 5 5 5 5
0 0 3 5 0 0 0 0 0 0 5 0 0 0 0 0 5 0 0 0
0 0 3 0 5 0 0 0 0 0 5 5 5 5 5 5 0 0 0 0
0 3 3 0 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 3 0 0 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

### 7. Demonstracja graficzna
Demonstracja to strona internetowa (plik `waz-astar.html`). Wąż startuje w lewym dolnym rogu i pełznie po trasie wyznaczonej algorytmem A* do czerwonego jabłka w prawym górnym rogu. Pola wolne to trawa, a przeszkody to kamienie. Strona pozwala wczytać plik `grid.txt`, zmienić prędkość oraz pokazać trasę. Przy całkowitym zablokowaniu drogi strona informuje o braku możliwości dotarcia do celu.

### 8. Wykorzystanie narzędzi generatywnej AI
Narzędzie: Claude (Anthropic)

### 9. Wnioski
Algorytm A* z heurystyką euklidesową poprawnie znajduje najkrótszą trasę na mapie z przeszkodami przy ruchach ortogonalnych. Wariant rozstrzygania konfliktów wpływa na kształt trasy, ale nie na jej długość. Narzędzia AI przyspieszyły tłumaczenie algorytmu na nieznany mi język i przygotowanie warstwy graficznej, ale wynik wymagał weryfikacji, którą przeprowadziłem samodzielnie.