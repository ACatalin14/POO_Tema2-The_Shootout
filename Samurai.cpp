#include "Samurai.h"

Samurai::Samurai(int n) {
	setRazaVizibilitate(kRazaVizibilitateSamurai);
	setHp(kHpSamurai);
	char* s = CreeazaNume(kNumeSamurai, n);
	setNume(s);
	delete[] s;
}
