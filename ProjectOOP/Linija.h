#ifndef LINIJA_H
#define LINIJA_H

#include <string>
#include <vector>
#include "Stajaliste.h"

class Linija {
private:
    std::string oznaka_linije;
    std::vector<Stajaliste*> stajalista;

public:
    // Konstruktor
    Linija(std::string oznaka);

    // Destruktor
    ~Linija() {}

    // Geteri
    inline std::string getOznakaLinije() const { return oznaka_linije; }
    inline const std::vector<Stajaliste*>& getStajalista() const { return stajalista; }
    std::vector<Stajaliste*> getVaznaStajalista() const;
    std::vector<int> getSifraVaznihStajalista() const;


    // Dodaj stajaliste na liniju
    void dodajStajaliste(Stajaliste* stajaliste);

    //print
    std::string print() {
        return oznaka_linije + " - " + std::to_string(stajalista.size());
    }

};

#endif // LINIJA_H