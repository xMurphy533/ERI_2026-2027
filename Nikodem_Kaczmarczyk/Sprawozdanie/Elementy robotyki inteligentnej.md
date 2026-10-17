### Algorytm A*
1. Zainicjalizuj dwie listy/tablice - **otwartą** i **zamkniętą**
2. Dodaj do listy zamkniętej pole startowe z wartością g = 0
3. Oblicz wartości dostępnych sąsiadów pola startowego (góra, dół, lewo, prawo) i dodaj ich do **listy otwartej** z informacją, że pole startowe jest ich rodzicem.
#### Tutaj zaczyna się pętla, która działa dopóki nie znajdziemy kratki cel.
1. Wybieramy najtańszą kratkę (o najniższym $f$) z listy otwartej i przenosimy ją na listę zamkniętą. Jeżeli jest kilka kratek o tej samej wartości, wybieramy tę, która została dodana na listę najpóźniej.
2. Dla wybranej przed chwilą kratki sprawdzamy sąsiadów w kolejności: góra - dół - lewo - prawo. Ignorujemy przeszkody oraz pola już znajdujące się na liście zamkniętej.
3. Dodajemy sąsiadów do listy otwartej i zapisujemy aktualną kratkę jako jej rodzica. Dla każdej z tych kratek obliczamy wartość funkcji f = g + h, gdzie
	- g = koszt przebytej drogi
	- h = heurystyka, czyli odległość kratki od kratki celowej, obliczana ze wzoru 
$$
\sqrt{(poz_x - cel_x)^2 + (poz_y - cel_y)^2}
$$
, dodajemy ja do listy otwartej i zapisujemy aktualną kratkę jako jej rodzica.
*Jeśli sąsiad jest już na liście otwartej (ma policzoną wartość), to obliczamy ją na nowo. Jeżeli okaże się, że nowa obliczona wartość jest mniejsza, to zamieniamy wartość kratki na nową i zmieniamy mu rodzica na aktualną kratkę.*
#### Kończymy działanie pętli
4. W tym momencie kratka cel znajduje się w liście zamkniętej.
5. Algorytm cofa się patrząc na to kto jest rodzicem danej kratki do momentu dojścia do kratki start.
Kolejna pętla odwzorowująca znalezioną trasę
Bierzemy kratkę cel i sprawdzamy kto jest jej rodzicem.
Przechodzimy na kratkę która jest rodzicem kratki cel i znowu sprawdzamy jej rodzica.
Działamy tak do momentu znalezienia kratki start.

#### Pseudo kod (dodac sprawdzenie czy nie wychodzimy poza plansze)
```
class Pole{
	cyfra,
	rodzic, // jesli rodzic jest nullem, to jestesmy na polu start
	dol,
	lewo,
	gora,
	prawo,
	f,
	x,
	y,
	g
}

// metoda oblicza wartosci sasiadow i dodaje te pola do listy otwartej z informacją, że pole ktorego sasiadow sprawdzalismy jest rodzicem i zaktualizowanymi wartosciami
metoda obsluzSasiadow(pole){
	// KIERUNEK: GÓRA (sprawdzamy, czy y + 1 nie wychodzi poza górną krawędź równą 19)
	jesli pole.y + 1 > 19 lub pole.gora.cyfra == 5 lub lista_zamknieta.posiada(pole.gora) // zignoruj
	jesli nie{
		nowe_g = pole.g + 1
		nowa_wartosc = nowe_g + sqrt((pole.gora.x - cel.x)^2 + (pole.gora.y - cel.y)^2)
		jesli pole.gora.f jest puste lub pole.gora.f > nowa_wartosc{
			pole.gora.f = nowa_wartosc
			pole.gora.g = nowe_g
			pole.gora.rodzic = pole
		}
		jesli lista_otwarta nie posiada pole.gora{
			lista_otwarta.dodaj(pole.gora)
		}
	}
	
	// KIERUNEK: DÓŁ (sprawdzamy, czy y - 1 nie spada poniżej dolnej krawędzi równej 0)
	jesli pole.y - 1 < 0 lub pole.dol.cyfra == 5 lub lista_zamknieta.posiada(pole.dol) // zignoruj
	jesli nie{
		nowe_g = pole.g + 1
		nowa_wartosc = nowe_g + sqrt((pole.dol.x - cel.x)^2 + (pole.dol.y - cel.y)^2)
		jesli pole.dol.f jest puste lub pole.dol.f > nowa_wartosc{
			pole.dol.f = nowa_wartosc
			pole.dol.g = nowe_g
			pole.dol.rodzic = pole
		}
		jesli lista_otwarta nie posiada pole.dol{
			lista_otwarta.dodaj(pole.dol)
		}
	}

	// KIERUNEK: LEWO (sprawdzamy, czy x - 1 nie spada poniżej lewej krawędzi równej 0)
	jesli pole.x - 1 < 0 lub pole.lewo.cyfra == 5 lub lista_zamknieta.posiada(pole.lewo) // zignoruj
	jesli nie{
		nowe_g = pole.g + 1
		nowa_wartosc = nowe_g + sqrt((pole.lewo.x - cel.x)^2 + (pole.lewo.y - cel.y)^2)
		jesli pole.lewo.f jest puste lub pole.lewo.f > nowa_wartosc{
			pole.lewo.f = nowa_wartosc
			pole.lewo.g = nowe_g
			pole.lewo.rodzic = pole
		}
		jesli lista_otwarta nie posiada pole.lewo{
			lista_otwarta.dodaj(pole.lewo)
		}
	}

	// KIERUNEK: PRAWO (sprawdzamy, czy x + 1 nie wychodzi poza prawą krawędź równą 19)
	jesli pole.x + 1 > 19 lub pole.prawo.cyfra == 5 lub lista_zamknieta.posiada(pole.prawo) // zignoruj
	jesli nie{
		nowe_g = pole.g + 1
		nowa_wartosc = nowe_g + sqrt((pole.prawo.x - cel.x)^2 + (pole.prawo.y - cel.y)^2)
		jesli pole.prawo.f jest puste lub pole.prawo.f > nowa_wartosc{
			pole.prawo.f = nowa_wartosc
			pole.prawo.g = nowe_g
			pole.prawo.rodzic = pole
		}
		jesli lista_otwarta nie posiada pole.prawo{
			lista_otwarta.dodaj(pole.prawo)
		}
	}
}

lista_zamknieta
lista_otwarta

// Inicjalizacja startu
pole_startowe.g = 0
pole_startowe.rodzic = null
lista_zamknieta.dodaj(pole_startowe)

obsluzSasiadow(pole_startowe)

aktualna_pozycja = pole_startowe

// Główna pętla algorytmu
dopoki((aktualna_pozycja.x != cel.x || aktualna_pozycja.y != cel.y) && lista_otwarta.nie_jest_pusta()){
	najtansza_kratka = lista_otwarta.znajdz_najtansza_od_konca() // od konca bo mamy dodac kratke ktora zostala dodana jako ostatnia
	aktualna_pozycja = najtansza_kratka
	
	lista_otwarta.usun(aktualna_pozycja) // usuwamy z otwartej, bo przechodzi do zamknietej
	lista_zamknieta.dodaj(aktualna_pozycja)
	
	// Jeśli właśnie weszliśmy na cel, nie musimy już sprawdzać jego sąsiadów
	jesli (aktualna_pozycja.x != cel.x || aktualna_pozycja.y != cel.y) {
		obsluzSasiadow(aktualna_pozycja)
	}
}

// Odtwarzanie trasy (z zabezpieczeniem na wypadek braku drogi)
jesli (aktualna_pozycja.x == cel.x && aktualna_pozycja.y == cel.y) {
	najlepsza_trasa // kolejna lista
	cel.cyfra = 3
	najlepsza_trasa.dodaj(cel)
	aktualna_kratka = cel
	
	dopoki(aktualna_kratka.rodzic != null){
		aktualna_kratka.rodzic.cyfra = 3
		najlepsza_trasa.dodaj(aktualna_kratka.rodzic)
		aktualna_kratka = aktualna_kratka.rodzic
	}
} w przeciwnym razie {
	wypisz("Brak możliwości dotarcia do celu!")
}
```
