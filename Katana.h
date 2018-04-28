#ifndef THE_SHOOTOUT_KATANA_H
#define THE_SHOOTOUT_KATANA_H

#include "Arma.h"
#include "Agent.h"

// ca sa deosebesc katana de pistol, pe langa raza de atac extrem de redusa si damage-ul OP, vom zice ca aceasta arma
// ofera o abilitate speciala agentului: sa vada hp-ul si armura inamicilor, iar in felul acesta se poate
// indrepta catre cei mai slabi/nepregatiti agenti pentru a-i ucide dintr-o lovitura (asta ar fi strategia ofensiva)

class Katana : public Arma {
	const int razaAtac = 1;
public:
	Katana();

	void Ataca(Agent &inamic) const;

	int AlegeActiune(int nrInamici, Agent** &inamici, int nrLinii, int nrColoane);
	// agentul care are o katana se va uita la inamicii care sunt in vecinatate cu o casuta
	// daca nu exista inamici in raza de atac, atunci agentul se deplaseaza (ret. -1)
	// daca exista inamici in raza de atac, agentul il va ataca pe agentul CEL MAI SLAB
	// din aria de vizibilitate (nu stiu daca este o strategie buna, dar totusi, este o strategie)
	// (ret. indexul inamicului)

	void Deplaseaza(Pozitie &destinatie) const;
	// face ca posesorul katanei sa se deplaseze mai aproape de inamicul CEL MAI SLAB
	// pe care il vede a.i. sa-l poata ucide dintr-o singura lovitura daca se poate
};


#endif //THE_SHOOTOUT_KATANA_H
