#include "Linija.h"


Linija::Linija(std::string oznaka): oznaka_linije(oznaka) {}

std::vector<Stajaliste*> Linija::getVaznaStajalista() const{
	std::vector<Stajaliste*> out;
	for (Stajaliste* s : this->stajalista) {
		if (s->isVaznoStajaliste()) {
			out.push_back(s);
		}
	}
	return out;
}

std::vector<int> Linija::getSifraVaznihStajalista() const{
	std::vector<int> out;
	for (Stajaliste* s : this->stajalista) {
		if (s->isVaznoStajaliste()) {
			out.push_back(s->getSifraStajalista());
		}
	}
	return out;
}

void Linija::dodajStajaliste(Stajaliste* stajaliste){
	this->stajalista.push_back(stajaliste);
}
