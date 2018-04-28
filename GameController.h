#ifndef THE_SHOOTOUT_GAMECONTROLLER_H
#define THE_SHOOTOUT_GAMECONTROLLER_H

#include "Harta.h"

#include "Agent.h"
#include "AgentSecret.h"
#include "Ninja.h"
#include "Samurai.h"

class GameController {
	Harta map;
	Agent **serieAgenti;	// un vector de pointeri la Agent
	int nrAgenti;
	int nrAgentiAlive;
	int rundaCurenta;

	void InitializeazaSerieAgenti();
	void PozitioneazaAgenti();
	void AfiseazaSituatieInitiala();

	int* CreeazaOrdineAgenti();
	// ordinea agentilor ar trebui sa fie aleasa random deoarece
	// si in jocuri de tip shooter fiecare jucator vrea sa fie primul care actioneaza, sa nu fie in urma altora

	void SimuleazaAtac(const Agent* const &jucator, int indexDusman);
	void SimuleazaDeplasareInteligenta(Agent* const &jucator);
	void SimuleazaDeplasareRandom(Agent* const &jucator);
	void SimuleazaActiuniRunda();	// afiseaza toate actiunile din runda curenta

public:
	GameController() : serieAgenti(0), nrAgenti(0), nrAgentiAlive(0), rundaCurenta(0) {};

	void InitializeazaJoc();
	void SimuleazaRunde(int nrRunde);
	bool IsOver() const;
	void Ending() const;
	const Harta& getMap() const;

	friend istream& operator>> (istream &flux, GameController &g);
};


#endif //THE_SHOOTOUT_GAMECONTROLLER_H
