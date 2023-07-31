#include "MrezaGradskogPrevoza.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

bool MrezaGradskogPrevoza::isInteger(std::string str) {
    try {
        size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    }
    catch (const std::exception&) {
        return false; // stoi threw an exception, so it's not an integer.
    }
}

void MrezaGradskogPrevoza::loadStationsFromFile(std::string putanja_do_stajalista){
    std::ifstream file(putanja_do_stajalista);
    if (!file) {
        // izuzeci
        // std::cerr << "Greska pri otvaranju fajla sa stajalistima." << std::endl;
        return;
    }

    int sifra;
    std::string naziv;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> sifra;
        std::getline(iss, naziv, '[');
        naziv.erase(naziv.begin());
        if (!naziv.empty() && naziv.back() == ' ') {
            naziv.pop_back();
        }
        bool vazno = line.back() == ']';

        stajalista.push_back(new Stajaliste(sifra, naziv, vazno));
    }
    file.close();
}

void MrezaGradskogPrevoza::loadLinesFromFile(std::string putanja_do_linija){
    std::ifstream file(putanja_do_linija);
    if (!file) {
        // izuzetak
        // std::cerr << "Greska pri otvaranju fajla sa linijama gradskog prevoza." << std::endl;
        return;
    }

    std::string oznaka;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> oznaka;
        Linija* linija = new Linija(oznaka);
        std::string sifra;
        while (iss >> sifra) {
            if (isInteger(sifra)) {
                Stajaliste* stajaliste = this->getStajaliste(std::stoi(sifra));
                linija->dodajStajaliste(stajaliste);
                stajaliste->addLinija(linija);
            }
            else {
                // baci izuzetak
            }
        }
        this->linije.push_back(linija);
        linija = nullptr;
        delete linija;
    }
    file.close();
}

Linija* MrezaGradskogPrevoza::getLinija(std::string oznaka){
    for (Linija* l : this->linije) {
        if (l->getOznakaLinije() == oznaka) {
            return l;
        }
    }
    return nullptr;
}

Stajaliste* MrezaGradskogPrevoza::getStajaliste(int sifra){
    for (Stajaliste* s : this->stajalista) {
        if (s->getSifraStajalista() == sifra)
            return s;
    }
    return nullptr;
}

void MrezaGradskogPrevoza::prikazInformacijeOStajalistu(int sifra_stajalista){
    Stajaliste* stajaliste = this->getStajaliste(sifra_stajalista);

    std::set<std::string, std::less<std::string>> linije = stajaliste->getOznakeLinija();
    std::set<int, std::less<int>> vaznaStajalista;

    for (Linija* linija : stajaliste->getLinije()) {
        for (int s : linija->getSifraVaznihStajalista()) {
            vaznaStajalista.insert(s);
        }
        /*
        for (int i = 0; i < linija->getStajalista().size(); i++) {
            if (linija->getStajalista().at(i)->getSifraStajalista() == sifra_stajalista) {
                if (linija->getStajalista().at(i - 1)->isVaznoStajaliste())
                    vaznaStajalista.insert(linija->getStajalista().at(i - 1)->getSifraStajalista());
                if (linija->getStajalista().at(i + 1)->isVaznoStajaliste())
                    vaznaStajalista.insert(linija->getStajalista().at(i + 1)->getSifraStajalista());

                break;
            }
        }
        */
    }


    std::string oznake_linija = "[";
    for (std::string ol : linije) {
        oznake_linija += ol + " ";
    }
    oznake_linija.pop_back(); // Ukloni posljednji razmak
    oznake_linija += "]";

    // Pripremi sifre vaznih stajaliata u formatu {! oznake_vaznih_stajalista !}
    std::string vazna_stajalista = "{! ";
    for (int i : vaznaStajalista) {
        vazna_stajalista += std::to_string(i) + " ";
    }
    vazna_stajalista.pop_back(); // Ukloni poslednji razmak
    vazna_stajalista += " !}";

    // Formiraj konacnu informaciju o stajalištu
    std::string informacije_o_stajalistu = std::to_string(sifra_stajalista) + " " + stajaliste->getNazivStajalista() + " " + oznake_linija + " " + vazna_stajalista;

    // Formiraj naziv fajla
    std::string naziv_fajla = "stajaliste_" + std::to_string(sifra_stajalista) + ".txt";

    // Ispisi informacije u fajl
    std::ofstream file(naziv_fajla);
    if (!file) {
        // exception
        //std::cerr << "Greska pri otvaranju fajla " << naziv_fajla << std::endl;
        return;
    }
    file << informacije_o_stajalistu;
    file.close();

    std::cout << "Informacije o stajalistu su uspesno prikazane u fajlu " << naziv_fajla << std::endl;
}

void MrezaGradskogPrevoza::prikazInformacijeOLiniji(std::string oznaka_linije){
    Linija* linija = this->getLinija(oznaka_linije);
    if (linija == nullptr)
        // exception not found 
        return;

    std::vector<Stajaliste*> stajalista = linija->getStajalista();

    std::string out = "";
    out += linija->getOznakaLinije() + " ";
    out += stajalista.front()->getNazivStajalista() + "->" + stajalista.back()->getNazivStajalista() + "\n";

    for (Stajaliste* stajaliste : stajalista) {
        out += std::to_string(stajaliste->getSifraStajalista()) + " " + stajaliste->getNazivStajalista() + (stajaliste->isVaznoStajaliste() ? " [!]\n" : "\n");
    }

    out.pop_back();


    std::string naziv_fajla = "linija_" + oznaka_linije + ".txt";

    // Ispisi informacije u fajl
    std::ofstream file(naziv_fajla);
    if (!file) {
        // exception
        //std::cerr << "Greska pri otvaranju fajla " << naziv_fajla << std::endl;
        return;
    }
    file << out;
    file.close();

    std::cout << "Informacije o liniji su uspesno prikazane u fajlu " << naziv_fajla << std::endl;
}


