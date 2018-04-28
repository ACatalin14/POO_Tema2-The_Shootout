#ifndef THE_SHOOTOUT_AGENT_H
#define THE_SHOOTOUT_AGENT_H

#include <iostream>

#include "Arma.h"
#include "Pistol.h"
#include "Shuriken.h"
#include "Katana.h"

#include "Armura.h"
#include "VestaAntiglont.h"
#include "Camuflaj.h"
#include "Kimono.h"

using namespace std;

const int kTipuriAgenti = 3;
const float kIndiceDeplasare = 0.75;	// apartine intervalului (0,1)
const int kRazaVizibilitateAgentSecret = 6;
const int kRazaVizibilitateNinja = 12;
const int kRazaVizibilitateSamurai = 9;
const int kHpAgentSecret = 100;
const int kHpNinja = 75;
const int kHpSamurai = 80;
const char* const kNumeAgentSecret = "AgentSecret";
const char* const kNumeNinja = "Ninja";
const char* const kNumeSamurai = "Samurai";

struct Pozitie {
	int x;
	int y;
};

class Arma;

class Agent {
protected:
	int hp;
	int razaVizibilitate;
	char* nume;
	Arma* weapon;
	Armura* armor;
	Pozitie pos;
	Agent** inamiciVizibili;	// vector cu pointeri la inamici vii de tip Agent care se afla in aria de vizibilitate
	int nrInamiciVizibili;		// inamiciVizibli si nrInamiciVizibili ar fi trebuit sa ii dau ca parametrii in
								// multe functii asa ca am ales sa ii incorporez in clasa Agent pt lejeritate

public:
	Agent();
	~Agent();

	int getHp() const;
	void setHp(int q);
	int getRazaVizibilitate() const;
	void setRazaVizibilitate(int r);
	char* getNume() const;
	void setNume(const char *s);
	const Arma* const getWeapon() const;
	const Armura* const getArmor() const;
	Pozitie getPos() const;
	void setPos(int y, int x);
	void setPos(Pozitie p);
	Agent** getInamiciVizibili() const;
	void setInamiciVizibili(int nr, Agent* const* const inamici);
	int getNrInamiciVizibili() const;
	void setNrInamiciVizibili(int nr);

	char* CreeazaNume(const char* s, int n) const;	// ret. un nume pt agent ex: "Ninja3", "AgentSecret"(n=0)
	void Ataca(Agent &inamic) const;
	void Deplaseaza(int y, int x);
	void Deplaseaza(Pozitie p);
	bool IsAlive() const;

	int AlegeActiune(int nrInamici, Agent**&inamici, int nrLinii, int nrColoane);
	// se primeste un vector de inamici si nr acestora; dimensiunile hartii
	// se returneaza  -1 daca agentul alege sa se deplaseze
	//				  un index (al unui agent) intre 0 - nrAgenti-1, daca agentul alege sa atace un alt agent

	void CreeazaInamiciVizibili(int nrInamici, Agent* const* const &dusmani);
	// se primeste un vector de dusmani si nr acestora
	// se seteaza nr de inamici vizibili in viata si vector cu indicii lor

	void NormalizeazaPozitieValida(Pozitie &p, int dir, int frontieraNord, int frontieraEst, int frontieraSud,
									   int frontieraVest) const;
	// primeste o pozitie p si o directie 0-3 (nord, est, sud, vest)
	// frontiere care limiteaza harta (ele sunt incluse in harta)
	// "normalizeaza" pozitia incercand sa o faca cea mai departata pozitie posibila in care agentul se poate deplasa
	// vezi: CreeazaPozitiiValide();

	void CreeazaPozitiiValide(int frontieraSud, int frontieraEst, Pozitie* pozitiiValide) const;
	// se primesc dimensiunile hartii si un vector gol cu 4 elemente de tip Pozitie
	// vectorul trebuie modificat a.i.
	// pozitiiValide[0] sa contina cea mai departata pozitie corecta daca agentul se deplaseaza spre NORD
	//  spun "corecta" pt ca agentul poate sa se afle aproape de marginea hartii si deplasandu-se spre nord ar iesi din harta
	//  sau deplasandu-se spre NORD cu pasul sau normal (kIndiceDeplasare*vizibilitate) ar putea sa intre intr-o casuta cu un alt agent
	//  in cel mai rau caz pozitiiValide[0] va contine fix pozitia actuala a agentului
	// pozitiiValide[1] [...] EST
	// pozitiiValide[2] [...] SUD
	// pozitiiValide[3] [...] VEST

	void DeplaseazaPentruAtac(Pozitie &destinatie);
	// agentul se va deplasa in mod ofensiv

	void DeplaseazaPentruFuga(Pozitie &destinatie, int frontieraSud, int frontieraEst);
	// agentul se va deplasa in mod defensiv, va incerca sa se deplaseze intr-una din cele 4 directii
	// cat de departe posibil de pozitia sa curenta

	Agent* CelMaiApropiatInamic() const;
	// calculeaza cel mai apropiat inamic care se afla in aria de vizibilitate a agentului

	Agent* CelMaiSlabInamic() const;
	// calculeaza cel mai slab inamic care se afla in aria de vizibilitate a agentului
	// slab inseamna sa aiba suma HP + ARMOR cat mai mica

	friend ostream& operator<< (ostream& flux, const Agent &a);
};


#endif //THE_SHOOTOUT_AGENT_H
