#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
//#include <cstdio>

using namespace std;

//definicja naszej klasy

class Sudoku {

	string podpowiedz{};
	int** tab_2D{};
	int tab[9][9];

public:
	int poziom_trudnosci();
	string pomoc();
	int** podmiana(int** tab_2D, int poziom_trudnosci);
	int** tablica_dwuwymiarowa();
	bool czy_ta_sama(int tab[9]);
	bool czy_ta_sama_2(int tab[9], int pozycja);
	bool poziom(int ** tab_2D, int q, int r, int pozycja);
	bool pion(int ** tab_2D, int q, int r, int pozycja);
	bool kwadrat(int ** tab_2D, int q, int r, int pozycja);
	bool czy_poprawnie(int ** tab_2D);
	bool czy_wygrana(int ** tab_2D);
	bool poprawnosc(int x);
	void sudoku(int** tab_2D, string podpowiedz, class Sudoku, int poziom_trudnosci);
	~Sudoku();
};

void menu(class Sudoku);
void tablica(class Sudoku);

void rozwiaz_zadana_tablice(Sudoku prosze_dzialaj);

bool poprawnosc(int x);
bool kolumnaa(int** array2D, int kolumna, int n);
bool rzadd(int** array2D, int rzad, int n);
bool trzy_na_trzy(int** array2D, int kwadrat_poczatkowy_rzad, int kwadrat_poczatkowa_kolumna, int n);
void sudokuGrid(int** array2D, class Sudoku);
bool puste(int** array2D, int& rzad, int& kolumna);
bool spelnia_miejsce(int** array2D, int rzad, int kolumna, int n);
bool rozwiaz(int** array2D);