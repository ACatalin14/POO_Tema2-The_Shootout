#include "Armura.h"
#include "Agent.h"
#include <cstring>

Armura::~Armura() {
	delete[] nume;
}

int Armura::getAbsorb() const {
	return absorb;
}

void Armura::setAbsorb(int q) {
	absorb = q;
}

char* Armura::getNume() const {
	return nume;
}

void Armura::setNume(const char* s) {
	delete[] nume;
	try {
		nume = new char[strlen(s) + 1];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica Armura::setNume() FAILED\n";
	}
	strcpy(nume, s);
}

Agent* Armura::getPosesor() const {
	return posesor;
}

void Armura::setPosesor(Agent* const p) {
	posesor = p;
}

