#include "AgentSecret.h"

AgentSecret::AgentSecret(int n) {
	setRazaVizibilitate(kRazaVizibilitateAgentSecret);
	setHp(kHpAgentSecret);
	char* s = CreeazaNume(kNumeAgentSecret, n);
	setNume(s);
	delete[] s;
}

