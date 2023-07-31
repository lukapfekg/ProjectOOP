#ifndef MREZA_GRADSKOG_PREVOZA_H
#define MREZA_GRADSKOG_PREVOZA_H

#include <vector>
#include <string>
#include "Stajaliste.h"
#include "Linija.h"

class MrezaGradskogPrevoza {
private:
    std::vector<Stajaliste*> stajalista;
    std::vector<Linija*> linije;
    bool isInteger(std::string);
public:
    // Konstruktor
    MrezaGradskogPrevoza() {}

    // Metode za ucitavanje podataka iz fajlova
    void loadStationsFromFile(std::string putanja_do_stajalista);
    void loadLinesFromFile(std::string putanja_do_linija);

    std::vector<Stajaliste*> getStajalista() const { return stajalista; };
    std::vector<Linija*> getLinije() const { return linije; };


    // Metode za dobijanje informacija
    Linija* getLinija(std::string oznaka);
    Stajaliste* getStajaliste(int sifra);
    Stajaliste getStationInformation(int sifra_stajalista) const;
    Linija getLineInformation(const std::string& oznaka_linije) const;

    void sortirajLinije();
    void sortirajVaznaStajalista();

    void prikazInformacijeOStajalistu(int sifra_stajalista);
    void prikazInformacijeOLiniji(std::string oznaka_linije);

    // Metod za pronalazenje putanje izmedju dva stajalista
    std::vector<Linija*> findPathBetweenStations(int pocetno_stajaliste, int krajnje_stajaliste, int strategija);
};

#endif // MREZA_GRADSKOG_PREVOZA_H
