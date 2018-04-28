#ifndef THE_SHOOTOUT_ARMA_H
#define THE_SHOOTOUT_ARMA_H

const int kTipuriArme = 3;
const int kHighestDamage = 90;
const int kDamagePistol = 55;
const int kDamageShuriken = 35;
const int kDamageKatana = 90;
const char* const kNumePistol = "Pistol";
const char* const kNumeShuriken = "Shuriken";
const char* const kNumeKatana = "Katana";

struct Pozitie;
class Agent;

class Arma {
protected:
	int damage;
	char *nume;
	Agent* posesor;

public:
	Arma() : damage(0), nume(0), posesor(0) {};
	~Arma();

	int getDamage() const;
	void setDamage(int q);
	char* getNume() const;
	void setNume(const char *s);
	Agent* const getPosesor() const;
	void setPosesor(Agent* const p);

	virtual void Ataca(Agent &inamic) const = 0;

	virtual int AlegeActiune(int nrInamici, Agent**&inamici, int nrLinii, int nrColoane) = 0;
	// alegerea actiunii variaza in functie de tipul armei;
	// vezi functia cu acelasi nume din Agent.h

	virtual void Deplaseaza(Pozitie &destinatie) const = 0;
	// deplaseaza agentul a.i. sa poata folosi arma (eficient) asupra altor agenti
	// este asigurat ca in aria de vizibilitate a agentului exista macar un alt agent
};


#endif //THE_SHOOTOUT_ARMA_H
