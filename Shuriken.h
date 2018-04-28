#ifndef THE_SHOOTOUT_SHURIKEN_H
#define THE_SHOOTOUT_SHURIKEN_H

#include "Arma.h"
#include "Agent.h"

// initial ma gandeam la un simplu shuriken dar acela ar ataca precum un pistol,
// asa ca vom presupune ca vorbim de un shuriken mare de tip boomerang, care taie tot ce-i iese in cale
// traiectoria shuriken-ului va fi in forma de patrat cu latura egala cu max(deltaX, deltaY)
// unde deltaX si deltaY reprezinta diferentele de coordonate pe componente dintre 2 agenti
// dar, acest patrat nu poate avea lungimea laturii prea mare, shuriken-ul va fi limitat la o anumita raza de atac
// exemplu: agentul A vrea sa il atace pe agentul B. El va arunca shuriken-ul in felul urmator:
//
//	_ _ _ _ _ _ _			_ > > > > > v
//	_ > > > > v _			_ > > > > v v	exista mai multe variante daca A si B sunt pe aceeasi linie/coloana;
//	_ ^ _ _ _ v _			_ ^ _ _ _ v v	se alege varianta cu raza cea mai mare si care taie cei mai multi inamici
//	_ ^ _ _ _ B _			_ ^ _ _ _ v C
//	_ ^ _ _ _ v _			_ ^ _ _ _ v v
//	_ A < < < < _			_ A < < < B <
//	_ _ _ _ _ _ _			_ _ _ _ _ _ _
//
// mereu se va arunca in sensul acelor de ceasornic
// deci orice traiectorie este descrisa unic de pozitia de start de unde se arunca, o directie de aruncare, si o raza

class Shuriken : public Arma {
protected:
	const int razaAtac = 8;
	int razaAruncare;		// raza de aruncare, in primul exemplu este 4 = max(deltaX,deltaY)
	int directieAruncare;	// directia de aruncare, in exemplul dat este 0 (NORD)
	Agent** serieAgenti;		// shuriken-ul are nevoie sa stie toti agentii de pe harta
	int nrAgenti;
	int nrLiniiHarta, nrColoaneHarta;	// trebuie sa stim si dimensiunile hartii, pt a nu iesi din ea

public:
	Shuriken();

	const char* Directie(int dir) const;
	// daca dir == 0, returneaza "nord" etc...

	void AtacaAgent(Agent &inamic) const;

	void IncrementeazaTinte(int* nrTinte) const;

	void ExecutaFunctie(int f, Agent &inamic, int* nrTinte = 0) const;
	// o functie multifunctionala
	// f = 0 -> executa AtacaAgent()
	// f = 1 -> executa IncrementeazaTinte()

	void ExistaInamicPePozitie(Pozitie loc, bool &exista, Agent* &inamic) const;
	// primeste o pozitie si verifica daca exista un inamic pe acea pozitie
	// daca exista, "exista" se face true, iar "inamic" va contine un pointer la inamicul respectiv

	void ParcurgeDirectie(int f, Pozitie start, int dir, int raza, int* nrTinte = 0) const;
	// ataca/numara toti inamicii pe directia dir incepand cu pozitia start pe o anumita raza
	// daca se iese din harta, se ignora pozitiile respective
	// pozitia start nu se va ataca/numara daca ea contine un agent
	// nrTinte este folosit pt numarare cand f == 1

	void SchimbaColt(int dir, int raza, Pozitie &colt) const;
	// primeste o directie si un colt al treaiectoriei shuriken-ului
	// modifica acest colt in sensul directiei de mers al shuriken-ului

	void ParcurgeTraiectorie(int f, Pozitie start, int dir, int raza, int* nrTinte = 0) const;
	// parcurge traiectoria descrisa de pozitia de start, directie, si latura patratului
	// iar cand gaseste un agent pe traiectorie executa o functie data de "f"
	// nu puteam sa fac f sa fie pointer la functii pt ca functiile mele difera prin parametrii si tipul returnat

	void Ataca(Agent &inamic) const;

	int NumaraTinte(Pozitie start, int dir, int raza) const;
	// numara cate tinte se afla pe traiectoria descrisa de pozistia de start, directie, si latura patratului

	bool ModificaMaxTinte(int directie, int raza, bool &primaVarianta, int &maxTinte);
	// o functie facuta pt a nu mai face copy-paste la aflarea lui maxTinte in mai multe cazuri
	// returneaza true cand s-a modificat maxTinte si false altfel

	int AlegeActiune(int nrInamici, Agent** &inamici, int nrLinii, int nrColoane);
	// daca posesorul shuriken-ului nu are niciun agent in raza de atac, atunci se va deplasa (ret -1)
	// daca exista inamici in jur, va analiza fiecare agent vizibil din raza de atac si va gandi toate
	// posibilitatile de aruncare pentru a-si acapara inamicul in atac, incercand in acelasi timp ca
	// shuriken-ul sa aiba o raza de aruncare maxima si sa cuprinda
	// cat mai multe tinte (din cele pe care le vede), returnandu-se indexul inamicului principal

	void Deplaseaza(Pozitie &destinatie) const;
	// cel care are shuriken va incerca sa fie pe aceeasi linie/coloana cu cel mai apropiat
	// inamic care se afla in raza sa de vizibilitate si cat mai aproape de inamicul acesta,
	// crescand astfel sansele sa atace mai multi inamici dintr-o lovitura intr-o runda urmatoare
};


#endif //THE_SHOOTOUT_SHURIKEN_H
