#include "Ninja.h"

Ninja::Ninja(int n) {
	setRazaVizibilitate(kRazaVizibilitateNinja);
	setHp(kHpNinja);
	char* s = CreeazaNume(kNumeNinja, n);
	setNume(s);
	delete[] s;
}
