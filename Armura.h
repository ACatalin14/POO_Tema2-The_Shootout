#ifndef THE_SHOOTOUT_ARMURA_H
#define THE_SHOOTOUT_ARMURA_H

const int kTipuriArmuri = 3;
const int kHighestAbsorb = 30;
const int kAbsorbVestaAntiglont = 20;
const int kAbsorbCamuflaj = 30;
const int kAbsorbKimono = 10;
const char* const kNumeVestaAntiglont = "Vesta Antiglont";
const char* const kNumeCamuflaj = "Camuflaj";
const char* const kNumeKimono = "Kimono";

struct Pozitie;
class Agent;

class Armura {
protected:
	int absorb;
	char* nume;
	Agent* posesor;

public:
	Armura() : absorb(0), nume(0), posesor(0) {};
	~Armura();

	int getAbsorb() const;
	void setAbsorb(int q);
	char* getNume() const;
	void setNume(const char* s);
	Agent* getPosesor() const;
	void setPosesor(Agent* posesor);
};


#endif //THE_SHOOTOUT_ARMURA_H
