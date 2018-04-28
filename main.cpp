#include <iostream>
#include "GameController.h"

// Conventii de denumire:
//		toate variabilele se vor denumi in stil camelCase
//		toate metodele se vor denumi in stil PascalCase
//		toate constantele se vor denumi in stil camelCase cu un "k" la inceput
// Conventii de indentare:
//		pentru a arata subordonarea blocurilor se foloseste indentare de 4 spatii
//		orice bloc va fi scris intre 2 acolade, chiar si daca acesta va consta intr-o singura instructiune
//		 exceptie: daca acea unica instructiune se scrie pe aceeasi linie cu if-ul/for-ul corespunzator, nu se mai folosesc acolade

int main() {
	GameController joc;
	int rundeSimulate;

	cout << "\n";
	for (int i = 1; i <= 22 + kIndentMatrice; i++) cout << "=";
	cout << " THE SHOOTOUT ";
	for (int i = 1; i <= 22 + kIndentMatrice; i++) cout << "=";
	cout << "\n\n";

	cin >> joc;
	joc.InitializeazaJoc();
	cout << "\n\n Harta initiala: \n" << joc.getMap() << "\n";
	while (!joc.IsOver()) {
		cout << "\nNr runde de simulat: ";
		cin >> rundeSimulate;
		joc.SimuleazaRunde(rundeSimulate);
	}
	joc.Ending();
	return 0;
}