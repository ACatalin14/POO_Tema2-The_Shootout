#include "Arma.h"
#include "Agent.h"
#include <cstring>

class Agent;

Arma::~Arma() {
	delete[] nume;
}

int Arma::getDamage() const {
	return damage;
}

void Arma::setDamage(int q) {
	damage = q;
}

char *Arma::getNume() const {
	return nume;
}

void Arma::setNume(const char *s) {
	delete[] nume;
	try {
		nume = new char[strlen(s) + 1];
	}
	catch (bad_alloc) {
		cout << "Alocare Dinamica Arma::setNume() FAILED\n";
	}
	strcpy(nume, s);
}

Agent *const Arma::getPosesor() const {
	return posesor;
}

void Arma::setPosesor(Agent* const p) {
	posesor = p;
}
