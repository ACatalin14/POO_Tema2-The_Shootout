#include "Harta.h"

Harta::~Harta() {
	for (int i = 0; i < n; i++) {
		delete[] array[i];
	}
	delete[] array;
}

void Harta::InitializeazaHarta() {
	try {
		array = new char*[n];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica Linii Harta FAILED\n";
	}
	for (int i = 0; i < n; i++) {
		try {
			array[i] = new char[m];
		}
		catch (bad_alloc) {
			cout << "Alocare Dinamica Coloane pe linia i Harta FAILED\n";
		}
		for (int j = 0; j < m; j++) {
			array[i][j] = '_';
		}
	}
}

Temp Harta::operator[](int linie) const {
	Temp t(array[linie]);
	return t;
}

ostream& operator<<(ostream &flux, const Harta &map) {
	int i, j;
	// afisarea zecilor coloanelor
	for (i = 0; i < kIndentMatrice + 3 + 1 + 9 + 9; i++) flux << " ";
	for (i = 10; i <= map.m; i++) flux << i / 10 << " ";
	flux << "\n";
	// afisarea unitatilor coloanelor
	for (i = 0; i < kIndentMatrice + 3 + 1; i++) flux << " ";
	for (i = 0; i < map.m; i++) flux << (i + 1) % 10 << " ";
	flux << "\n";
	// afisarea liniilor
	for (i = 0; i < map.n; i++) {
		for (j = 0; j < kIndentMatrice; j++) flux << " ";
		if (i < 100 - 1) flux << " ";
		if (i < 10 - 1) flux << " ";
		flux << i + 1 << " ";
		for (j = 0; j < map.m; j++) flux << map[i][j] << " ";
		flux << "\n";
	}
	return flux;
}
