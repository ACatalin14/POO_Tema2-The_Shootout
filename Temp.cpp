#include "Temp.h"

Temp::Temp(char *linie) {
	arr = linie;
}

char& Temp::operator[](int coloana) const {
	return arr[coloana];
}
