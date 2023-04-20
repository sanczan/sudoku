#include "sudoku.h"

int  ratunek = 0;

//podpunkt 1

int Sudoku::poziom_trudnosci() {
	int poziom_trudnosci{};
	do {
		cout << "Wybierz poziom trudnosci:" << endl;
		cout << "1. Latwy" << endl;
		cout << "2. Sredni" << endl;
		cout << "3. Trudny" << endl;
		cin >> poziom_trudnosci;
		if (!cin) {//ignoruje bledne znaki
			cin.clear();
			cin.ignore(40, '\n');
		}
		system("CLS");//czysci konsole po wprowadzeniu blednych znakow
	} while (poziom_trudnosci < 1 || poziom_trudnosci > 3);

	return poziom_trudnosci;
}

string Sudoku::pomoc() {
	string podpowiedz{};
	do {
		cout << "Czy chcesz skorzystac z podpowiedzi? (tak/nie)" << endl;
		cin >> podpowiedz;
		system("cls");
	} while (podpowiedz != "tak" && podpowiedz != "nie" && podpowiedz != "TAK" && podpowiedz != "NIE");
	return podpowiedz;
}

int** Sudoku::podmiana(int** tab_2D, int poziom_trudnosci) {
	int pola_do_podmiany{};
	switch (poziom_trudnosci) {
	case 1:
		pola_do_podmiany = 15;
		break;
	case 2:
		pola_do_podmiany = 30;
		break;
	case 3:
		pola_do_podmiany = 50;
		break;
	default:
		break;
	}
	for (int i = 0; i < pola_do_podmiany; i++) {
		int a{}, b{};
		a = rand() % 9;
		b = rand() % 9;
		if (tab_2D[a][b] == 0) {
			i--;
		}
		else {
			tab_2D[a][b] = 0;
		}
	}
	return tab_2D;
}

bool Sudoku::czy_ta_sama(int tab[9]) { // pomocna pêtla sprawdzaj¹ca czy w kwadracie 3x3 cyfra siê powtarza
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tab[i] != 0 && i != j) {
				if (tab[i] == tab[j]) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Sudoku::czy_ta_sama_2(int tab[9], int pozycja) { // bardziej 'wyspecjalizowana' wersja poprzedniej funkcji
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tab[i] != 0 && i != j) {
				if (tab[i] == tab[j] && tab[i] == pozycja) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Sudoku::poziom(int ** tab_2D, int q, int r, int pozycja) {
	for (int i = 0; i < 9; i++) {
		if (pozycja == tab_2D[q][i] && i != r) {
			return true;
		}
	}
	return false;
}

bool Sudoku::pion(int ** tab_2D, int q, int r, int pozycja) {
	for (int i = 0; i < 9; i++) {
		if (pozycja == tab_2D[i][r] && i != q) {
			return true;
		}
	}
	return false;
}

bool Sudoku::kwadrat(int ** tab_2D, int q, int r, int pozycja) {
	int pomoc[9]{};
	int licznik{}, kwadrat_poziom{}, kwadrat_pion{};
	kwadrat_poziom = r / 3;
	kwadrat_pion = q / 3;
	for (int i = 3 * kwadrat_pion; i < (3 * kwadrat_pion) + 3; i += 3) {
		for (int j = 3 * kwadrat_poziom; j < (3 * kwadrat_poziom) + 3; j += 3) {
			for (int k = i; k < (3 * kwadrat_pion) + 3; k++) {
				for (int l = j; l < (3 * kwadrat_poziom) + 3; l++) {
					pomoc[licznik] = tab_2D[k][l];
					licznik++;
				}
			}
			if (czy_ta_sama_2(pomoc, pozycja) == true && pozycja == tab_2D[q][r]) {
				return true;
			}
			licznik = 0;
		}
	}
	return false;
}

bool Sudoku::czy_poprawnie(int ** tab_2D) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tab_2D[i][j] == 0) {
				continue;
			}
			else {
				for (int k = 0; k < 9; k++) {
					if (j != k && tab_2D[i][k] != 0) {
						if ((tab_2D[i][j] == tab_2D[i][k]) && tab_2D[i][j] != 0) {
							return false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tab_2D[j][i] == 0) {
				continue;
			}
			else {
				for (int k = 0; k < 9; k++) {
					if (j != k && tab_2D[k][i] != 0) {
						if ((tab_2D[j][i] == tab_2D[k][i]) && tab_2D[j][i] != 0) {
							return false;
						}
					}
				}
			}
		}
	}

	int pomoc[9]{};
	int licznik{};
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			for (int k = i; k < 3; k++) {
				for (int l = j; l < 3; l++) {
					pomoc[licznik] = tab_2D[k][l];
					licznik++;
				}
			}
			if (czy_ta_sama(pomoc) == true) {
				return false;
			}
			licznik = 0;
		}
	}
	return true;
}

bool Sudoku::czy_wygrana(int ** tab_2D) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tab_2D[i][j] == 0) {
				return false;
			}
		}
	}
	if (czy_poprawnie(tab_2D) == true) {
		return true;
	}
	else {
		return false;
	}
}

bool Sudoku::poprawnosc(int x) {
	if (x >= 0 && x <= 9) {
		return true;
	}
	else {
		return false;
	}
}

void Sudoku::sudoku(int ** tab_2D, string podpowiedz, Sudoku prosze_dzialaj, int poziom_trudnosci) {
	clock_t start;
	double czas_trwania, czas_koncowy;
	start = clock();

	do {
		int rzad{}, kolumna{}, wartosc{}, pozycja{};

		//zabawa w kolory i formatowanie
		printf("\033[1;32m");
		cout << "   " << "#  ";
		printf("\033[1;37m");
		cout << "1" << " " << "2" << " " << "3" << "   " << "4" << " " << "5" << " " << "6" << "   " << "7" << " " << "8" << " " << "9" << endl;
		printf("\033[1;32m");
		cout << " # # # # # # # # # # # # # #";
		printf("\033[1;37m");

		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {		//co 3 daje odstep
				cout << endl;
			}
			cout << " " << i + 1;
			printf("\033[1;32m");
			cout << " #";
			printf("\033[1;37m");
			for (int j = 0; j < 9; j++) {
				pozycja = tab_2D[i][j];
				if (j % 3 == 0) {		//i tu tez daje odstep
					cout << "  ";
				}
				if (tab_2D[i][j] == 0) {		//zaznaczenie '0', zeby ulatwic odczyt uzytkownikowi
					printf("\033[1;34m");
					cout << "0";
					printf("\033[1;37m");
					cout << " ";
				}
				else if ((poziom(tab_2D, i, j, pozycja) == true || pion(tab_2D, i, j, pozycja) == true || kwadrat(tab_2D, i, j, pozycja) == true) && (podpowiedz == "tak" || podpowiedz == "TAK")) {		//zaznacza bledne dane
					printf("\033[1;31m");
					cout << tab_2D[i][j] << " ";
					printf("\033[1;37m");
				}
				else {
					cout << tab_2D[i][j] << " ";
				}
			}
			cout << endl;
		}
		printf("\033[1;32m");
		cout << "   #" << endl;
		printf("\033[1;37m");

		//wprowadzenie danych 
		cout << "Podaj kolumne, rzad i wartosc:" << endl;
		cin >> kolumna;
		cin >> rzad;
		cin >> wartosc;

		if (!cin) {		//sprawdzenie czy liczba
			cin.clear();
			cin.ignore(40, '\n');
		}

		else if (poprawnosc(kolumna) == true && poprawnosc(rzad) == true && poprawnosc(wartosc) == true) {	//sprawdzenie czy w przedziale
			tab_2D[rzad - 1][kolumna - 1] = wartosc;	//podmiana cyfry podanej przez u¿ytkownika
		}

		system("CLS");

	} while (czy_wygrana(tab_2D) != true);		//koniec petli

	czas_trwania = (clock() - start) / (double)CLOCKS_PER_SEC;
	czas_koncowy = czas_trwania;

	cout << "gratuluje wygranej!!!" << endl;
	int godziny{}, minuty{}, sekundy{};
	sekundy = czas_koncowy;
	minuty = sekundy / 60;
	godziny = minuty / 60;
	cout << "Twoj czas wynosi: " << int(godziny) << ":" << int(minuty) << ":" << int(sekundy%60) << '\n';


	string nick = "anonimowy";
	ofstream plik("wyniki.txt", ios::app);
	cout << "Podaj swoj nick aby zapisac sie na tablice wynikow: \n";
	cin.ignore();

	getline(cin, nick);

	if (nick.length() > 14 || nick.empty()) {
		do {
			cout << "Nick powinien byc pusty/miec wiecej niz 14 znakow:\n";
			getline(cin, nick);
		} while (nick.length() > 14 || nick.empty());
	}
	replace(nick.begin(), nick.end(), ' ', '_');
	plik << nick << " " << czas_koncowy << " " << podpowiedz  << " " << poziom_trudnosci << endl;
	plik.close();
	system("pause");
	cout << "kliknij dowolny przycisk aby powrocic do menu:\n";
	menu(prosze_dzialaj);
}

int** Sudoku::tablica_dwuwymiarowa() {
	srand(time(NULL));


	//tablice 'losowe'
	int tab_1[9][9] = {
		{5, 3, 4, 6, 7, 8, 9, 1, 2},
		{6, 7, 2, 1, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 2, 5, 6, 7},
		{8, 5, 9, 7, 6, 1, 4, 2, 3},
		{4, 2, 6, 8, 5, 3, 7, 9, 1},
		{7, 1, 3, 9, 2, 4, 8, 5, 6},
		{9, 6, 1, 5, 3, 7, 2, 8, 4},
		{2, 8, 7, 4, 1, 9, 6, 3, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};

	int tab_2[9][9] = {
		{2, 4, 7, 9, 1, 3, 8, 6, 5},
		{1, 9, 5, 6, 8, 7, 2, 4, 3},
		{8, 6, 3, 2, 5, 4, 7, 9, 1},
		{3, 1, 2, 4, 7, 9, 5, 8, 6},
		{9, 5, 8, 1, 6, 2, 4, 3, 7},
		{6, 7, 4, 5, 3, 8, 9, 1, 2},
		{7, 8, 1, 3, 4, 5, 6, 2, 9},
		{4, 3, 9, 7, 2, 6, 1, 5, 8},
		{5, 2, 6, 8, 9, 1, 3, 7, 4}
	};

	int tab_3[9][9] = {
		{1, 6, 8, 2, 5, 4, 7, 9, 3},
		{3, 7, 5, 9, 8, 6, 1, 2, 4},
		{9, 4, 2, 3, 7, 1, 8, 6, 5},
		{6, 2, 1, 5, 3, 8, 9, 4, 7},
		{4, 5, 9, 7, 1, 2, 3, 8, 6},
		{8, 3, 7, 4, 6, 9, 5, 1, 2},
		{5, 9, 4, 8, 2, 3, 6, 7, 1},
		{2, 1, 3, 6, 9, 7, 4, 5, 8},
		{7, 8, 6, 1, 4, 5, 2, 3, 9}
	};

	int tab_4[9][9] = {
		{4, 9, 6, 1, 7, 5, 8, 3, 2},
		{2, 1, 8, 3, 6, 9, 7, 4, 5},
		{7, 5, 3, 2, 4, 8, 1, 9, 6},
		{5, 3, 1, 6, 2, 7, 9, 8, 4},
		{6, 4, 9, 8, 1, 3, 2, 5, 7},
		{8, 2, 7, 5, 9, 4, 6, 1, 3},
		{1, 8, 5, 7, 3, 6, 4, 2, 9},
		{9, 6, 2, 4, 5, 1, 3, 7, 8},
		{3, 7, 4, 9, 8, 2, 5, 6, 1}
	};

	int losuj_tab = rand() % 4 + 1;
	int** array2D = 0;
	array2D = new int* [9];

	//automatyzacja wyboru tablicy
	switch (losuj_tab) {
	case 1:
		for (int i = 0; i < 9; i++)
		{
			array2D[i] = new int[9];

			for (int j = 0; j < 9; j++)
			{
				array2D[i][j] = tab_1[i][j];

			}
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++)
		{
			array2D[i] = new int[9];

			for (int j = 0; j < 9; j++)
			{
				array2D[i][j] = tab_2[i][j];

			}
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++)
		{
			array2D[i] = new int[9];

			for (int j = 0; j < 9; j++)
			{
				array2D[i][j] = tab_3[i][j];

			}
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++)
		{
			array2D[i] = new int[9];

			for (int j = 0; j < 9; j++)
			{
				array2D[i][j] = tab_4[i][j];

			}
		}
		break;
	default:
		break;
	}
	return array2D;
}

void menu(Sudoku prosze_dzialaj) {
	system("cls");
	int opcja{};
	cout << "SUDOKU\n";
	cout << "###################################\n";
	cout << "1. Nowa gra\n";
	cout << "2. Tablica wynikow\n";
	cout << "3. Automatyczne rozwiazanie\n";
	cout << "4. Zakoncz program\n";
	cout << "###################################\n";
	do {
		cin >> opcja;
		if (!cin) {		//sprawdzenie czy liczba
			cin.clear();
			cin.ignore(40, '\n');
		}
		system("cls");
		cout << "SUDOKU\n";
		cout << "###################################\n";
		cout << "1. Nowa gra\n";
		cout << "2. Tablica wynikow\n";
		cout << "3. Automatyczne rozwiazanie\n";
		cout << "4. Zakoncz program\n";
		cout << "###################################\n";
	} while (opcja < 1 || opcja > 4);

	if (opcja == 1) {
		system("cls");						//wywolanie funkcji i przypisanie je do zmiennych
		int poziom_trudnosci = prosze_dzialaj.poziom_trudnosci();
		string podpowiedz = prosze_dzialaj.pomoc();
		int** my2DArray = prosze_dzialaj.tablica_dwuwymiarowa();
		int** tab_2D = prosze_dzialaj.podmiana(my2DArray, poziom_trudnosci);
		system("cls");
		prosze_dzialaj.sudoku(tab_2D, podpowiedz, prosze_dzialaj, poziom_trudnosci);
	}
	if (opcja == 2) {
		tablica(prosze_dzialaj);
	}
	if (opcja == 3) {
		ratunek = 0;
		rozwiaz_zadana_tablice(prosze_dzialaj);
	}
	else {
		exit;
	}
}

Sudoku::~Sudoku() {
}


//podpunkt 2

void tablica(Sudoku prosze_dzialaj) {
	system("cls");

	int zlicz = 1;
	string czas{}, nick{}, podpowiedz{};
	int poziom_trudnosci{};
	ifstream plik("wyniki.txt");
	cout << "TABLICA WYNIKOW\n";
	cout << "############################################################################\n";
	cout << "Pozycja" << "  nick" << "\t\tczas\t" << "czy uzyto podpowiedzi\t" << "poziom trudnosci\n";
	cout << "############################################################################\n";
	while (plik >> nick >> czas >> podpowiedz >> poziom_trudnosci) {
		int godziny{}, minuty{}, sekundy{};
		sekundy = stoi(czas);
		minuty = sekundy / 60;
		godziny = minuty / 60;

		cout << zlicz << ".\t " << nick;;
		if (nick.length() < 7) {
			cout << "\t\t";
		}
		else if (nick.length() < 10) {
			cout << "\t";
		}
		else {
			cout << "\t";
		}
		cout << int(godziny) << ":" << int(minuty) << ":" << int(sekundy % 60) << "\t\t" << podpowiedz << "\t\t";
		switch (poziom_trudnosci)
		{
		case 1:
			cout << "latwy\n";
			break;
		case 2:
			cout << "sredni\n";
			break;
		case 3:
			cout << "trudny\n";
			break;
		default:
			break;
		}
		zlicz++;
	}
	cout << "############################################################################\n\n";
	system("pause");
	cout << "kliknij dowolny przycisk aby powrocic do menu:\n";
	menu(prosze_dzialaj);

	plik.close();
}


//podpunkt 3

bool kolumnaa(int ** array2D, int kolumna, int n) {            //czy numer jest w danej kolumnie
	for (int rzad = 0; rzad < 9; rzad++)
		if (array2D[rzad][kolumna] == n)
			return true;
	return false;
}

bool rzadd(int** array2D, int rzad, int n) {           //czy numer jest w danym rzedzie
	for (int kolumna = 0; kolumna < 9; kolumna++)
		if (array2D[rzad][kolumna] == n)
			return true;
	return false;
}

bool trzy_na_trzy(int** array2D, int kwadrat_poczatkowy_rzad, int kwadrat_poczatkowa_kolumna, int n) {      //czy numer jest w danym pomniejszym kwadracie 3x3
	for (int rzad = 0; rzad < 3; rzad++)
		for (int kolumna = 0; kolumna < 3; kolumna++)
			if (array2D[rzad + kwadrat_poczatkowy_rzad][kolumna + kwadrat_poczatkowa_kolumna] == n)
				return true;
	return false;
}

void sudokuGrid(int** array2D, Sudoku prosze_dzialaj) {                                                 //wypisz sudoku
	printf("\033[1;32m");
	cout << "   " << "#  ";
	printf("\033[1;37m");
	cout << "1" << " " << "2" << " " << "3" << "   " << "4" << " " << "5" << " " << "6" << "   " << "7" << " " << "8" << " " << "9" << endl;
	printf("\033[1;32m");
	cout << " # # # # # # # # # # # # # #";
	printf("\033[1;37m");

	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) {		//co 3 daje odstep
			cout << endl;
		}
		cout << " " << i + 1;
		printf("\033[1;32m");
		cout << " #";
		printf("\033[1;37m");
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0) {		//i tu tez daje odstep
				cout << "  ";
			}
			if (array2D[i][j] == 0) {		//zaznaczenie '0', zeby ulatwic odczyt uzytkownikowi
				printf("\033[1;34m");
				cout << "0";
				printf("\033[1;37m");
				cout << " ";
			}
			else {
				cout << array2D[i][j] << " ";
			}
		}
		cout << endl;
	}

	printf("\033[1;32m");
	cout << "   #" << endl;
	printf("\033[1;37m");
	cout << "Tablica zostala poprawnie wygenerowana\n";
	cout << "Kliknij dowolny przycisk aby powrocic do menu:\n";
	system("pause");
	menu(prosze_dzialaj);
}

bool puste(int** array2D, int& rzad, int& kolumna) {                           //szuka wolnych miejsc (w domysle sa to zera)
	for (rzad = 0; rzad < 9; rzad++)
		for (kolumna = 0; kolumna < 9; kolumna++)
			if (array2D[rzad][kolumna] == 0)
				return true;
	return false;
}

bool spelnia_miejsce(int ** array2D, int rzad, int kolumna, int n) {      //jezeli nie znajdzie danej cyfry w rzedzie, kolumnie i kwadracie
	return !rzadd(array2D, rzad, n) && !kolumnaa(array2D, kolumna, n) && !trzy_na_trzy(array2D, rzad - rzad % 3,
		kolumna - kolumna % 3, n);
}

bool rozwiaz(int ** array2D) {
	int rzad{}, kolumna{}, pozycja{};
	if (!puste(array2D, rzad, kolumna))
		return true;                                            //wszystko uzupelnione
	for (int n = 1; n <= 9; n++) {
		if (ratunek > 20000) {
			return false;
		}
		ratunek++;
		if (spelnia_miejsce(array2D, rzad, kolumna, n)) {    //jezeli cyfra spelnia warunki to zostaje ona wpisana do sudoku
			array2D[rzad][kolumna] = n;
			if (rozwiaz(array2D))                                  //rekursywnie szuka innych miejsc w sudoku
				return true;
			array2D[rzad][kolumna] = 0;                                 //przypisz 0 jezeli warunki nie zostaly spelnione
		}
	}
	return false;
}

bool poprawnosc(int x) {
	if (x >= 0 && x <= 9) {
		return true;
	}
	else {
		return false;
	}
}

void rozwiaz_zadana_tablice(Sudoku prosze_dzialaj) {
	int grid[9][9]{0};


	int** array2D = 0;
	array2D = new int* [9];
	for (int i = 0; i < 9; i++)
	{
		array2D[i] = new int[9];

		for (int j = 0; j < 9; j++)
		{
			array2D[i][j] = grid[i][j];

		}
	}

	string koniec{};
	do {
		int rzad{}, kolumna{}, wartosc{}, pozycja{};

		//zabawa w kolory i formatowanie
		system("cls");

		printf("\033[1;32m");
		cout << "   " << "#  ";
		printf("\033[1;37m");
		cout << "1" << " " << "2" << " " << "3" << "   " << "4" << " " << "5" << " " << "6" << "   " << "7" << " " << "8" << " " << "9" << endl;
		printf("\033[1;32m");
		cout << " # # # # # # # # # # # # # #";
		printf("\033[1;37m");

		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {		//co 3 daje odstep
				cout << endl;
			}
			cout << " " << i + 1;
			printf("\033[1;32m");
			cout << " #";
			printf("\033[1;37m");
			for (int j = 0; j < 9; j++) {
				//pozycja = array2D[i][j];
				if (j % 3 == 0) {		//i tu tez daje odstep
					cout << "  ";
				}
				if (array2D[i][j] == 0) {		//zaznaczenie '0', zeby ulatwic odczyt uzytkownikowi
					printf("\033[1;34m");
					cout << "0";
					printf("\033[1;37m");
					cout << " ";
				}
				else {
					cout << array2D[i][j] << " ";
				}
			}
			cout << endl;
		}

		printf("\033[1;32m");
		cout << "   #" << endl;
		printf("\033[1;37m");

		//wprowadzenie danych 
		cout << "Podaj kolumne, rzad i wartosc:" << endl;
		cin >> kolumna;
		cin >> rzad;
		cin >> wartosc;

		if (!cin) {		//sprawdzenie czy liczba
			cin.clear();
			cin.ignore(40, '\n');
		}

		else if (poprawnosc(kolumna) == true && poprawnosc(rzad) == true && poprawnosc(wartosc) == true) {	//sprawdzenie czy w przedziale
			array2D[rzad - 1][kolumna - 1] = wartosc;	//podmiana cyfry podanej przez u¿ytkownika
		}

		system("cls");

		printf("\033[1;32m");
		cout << "   " << "#  ";
		printf("\033[1;37m");
		cout << "1" << " " << "2" << " " << "3" << "   " << "4" << " " << "5" << " " << "6" << "   " << "7" << " " << "8" << " " << "9" << endl;
		printf("\033[1;32m");
		cout << " # # # # # # # # # # # # # #";
		printf("\033[1;37m");

		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {		//co 3 daje odstep
				cout << endl;
			}
			cout << " " << i + 1;
			printf("\033[1;32m");
			cout << " #";
			printf("\033[1;37m");
			for (int j = 0; j < 9; j++) {
				//pozycja = array2D[i][j];
				if (j % 3 == 0) {		//i tu tez daje odstep
					cout << "  ";
				}
				if (array2D[i][j] == 0) {		//zaznaczenie '0', zeby ulatwic odczyt uzytkownikowi
					printf("\033[1;34m");
					cout << "0";
					printf("\033[1;37m");
					cout << " ";
				}
				else {
					cout << array2D[i][j] << " ";
				}
			}
			cout << endl;
		}
		printf("\033[1;32m");
		cout << "   #" << endl;
		printf("\033[1;37m");

		
		cout << "Czy chcesz zakonczyc uzupelnianie tablicy?(tak/nie)\n";
		cin >> koniec;

		system("CLS");

	} while (koniec != "tak");

	if (rozwiaz(array2D) == true) {
		sudokuGrid(array2D, prosze_dzialaj);
	}
	else {
		cout << "Brak mozliwych rozwiazan\n";
		cout << "Kliknij dowolny przycisk aby powrocic do menu:\n";
		system("pause");
		menu(prosze_dzialaj);
	}
}