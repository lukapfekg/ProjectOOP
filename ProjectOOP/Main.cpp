#include <iostream>
#include <set>
#include "Linija.h"
#include "Stajaliste.h"
#include "MrezaGradskogPrevoza.h"
#include <fstream>
#include <sstream>

int main() {
	/*
	Linija* l = new Linija("1");
	Linija* l2 = new Linija("2");
	Linija* l3 = new Linija("3");
	Linija* l4 = new Linija("4");

	Stajaliste* s = new Stajaliste(26, "Tek", true);
	s->addLinija(l);
	s->addLinija(l2);
	s->addLinija(l4);

	Stajaliste* s2 = new Stajaliste(12, "Bam");
	s2->addLinija(l);
	s2->addLinija(l2);
	s2->addLinija(l3);
	s2->addLinija(l4);


	std::cout << l->print() << std::endl;
	std::cout << s->print() << std::endl;
	std::cout << s2->print() << std::endl;

	for (Linija* tek : s->getLinije()) {
		std::cout << tek->print() << std::endl;
	}

	*/
	
	MrezaGradskogPrevoza* mreza = new MrezaGradskogPrevoza();
	mreza->loadStationsFromFile("stajalista.txt");
	mreza->loadLinesFromFile("linije.txt");

	mreza->prikazInformacijeOStajalistu(422);
	mreza->prikazInformacijeOLiniji("12");
	
	return 0;
}