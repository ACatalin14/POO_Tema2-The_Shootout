#ifndef THE_SHOOTOUT_PISTOL_H
#define THE_SHOOTOUT_PISTOL_H

#include "Arma.h"
#include "Agent.h"

class Pistol : public Arma {
protected:
	const int razaAtac = 4;	// raza ne ofera "aria" in care poate ataca pistolul
public:
	Pistol();

	void Ataca(Agent &inamic) const;

	int AlegeActiune(int nrInamici, Agent** &inamici, int nrLinii, int nrColoane);
	// agentul care are un pistol se va uita la inamicii lui vizibili care sunt in raza de atac a pistolului
	// daca nu exista inamici in raza de atac, atunci agentul se deplaseaza (ret. -1)
	// daca exista inamici in raza de atac, agentul il va ataca pe CEL MAI APROPIAT agent (ret. indexul inamicului)

	void CeaMaiApropiataPozitieDeAtac(Pozitie &inamic, int dir, int maxDeplasare, Pozitie &destinatie) const;
	// calculeaza in destinatie cea mai apropiata pozitie de posesorul armei pe directia dir
	// cu o deplasare maxima de maxDeplasare unitati, a.i. sa poata ataca un inamic
	// i.e. posesorul pistolului vrea sa fie cat mai departat de tinta sa dar sa il poata impusca

	void Deplaseaza(Pozitie &destinatie) const;
	// face ca posesorul sa se deplaseze mai aproape de inamicul cel mai apropiat
	// pe care il vede a.i. sa-l poata impusca
};


#endif //THE_SHOOTOUT_PISTOL_H
