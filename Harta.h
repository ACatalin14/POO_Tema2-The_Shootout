#ifndef THE_SHOOTOUT_HARTA_H
#define THE_SHOOTOUT_HARTA_H

#include "Temp.h"
#include <iostream>

using namespace std;

// harta as vrea sa o folosesc doar pentru interfata, nimic mai mult
// toata logica jocului si gestionarea propriu-zisa a hartii sta in GameController

const int kIndentMatrice = 10;	// indentare pt afisarea matricii

class GameController;

class Harta {
protected:
	char **array;	// harta propriu-zisa
	int n, m;		// dimensiunile hartii: nr linii si nr coloane

public:
	Harta() : n(0), m(0), array(0) {};
	~Harta();

	void InitializeazaHarta();	// alocarea dinamica a hartii

	Temp operator[] (int linie) const;	// pentru a putea folosi map[i][j]; mai comod & clar decat map(i,j)

	friend class GameController;	// GameController contine un obiect Harta si trebuie sa stie tot
									// mai ales ca are nevoie sa foloseasca map[i][j] (prin operatorul [])
	friend istream& operator>>(istream &flux, GameController &g);
	friend ostream& operator<<(ostream &flux, const Harta &map);
};


#endif //THE_SHOOTOUT_HARTA_H
