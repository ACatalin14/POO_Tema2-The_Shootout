#ifndef THE_SHOOTOUT_TEMP_H
#define THE_SHOOTOUT_TEMP_H

// o clasa Temporara facuta pt a ma ajuta la supraincarcarea operatorului [] pt matrice
// clasa Temp reprezinta de fapt o linie de matrice a hartii

class Temp {
protected:
	char *arr;
public:
	Temp(char *linie);
	char& operator[] (int coloana) const;
};


#endif //THE_SHOOTOUT_TEMP_H
