#ifndef STAJALISTE_H
#define STAJALISTE_H

#include <string>
#include <vector>
#include <set>

class Linija;

class Stajaliste {
private:
    int sifra_stajalista;
    std::string naziv_stajalista;
    bool vazno;
    std::vector<Linija*> linije;

public:
    // Konstruktor
    Stajaliste(int sifra, std::string naziv, bool vazno = false);

    // Destruktor
    ~Stajaliste() {}

    // Geteri
    inline int getSifraStajalista()         const { return sifra_stajalista; }
    inline std::string getNazivStajalista() const { return naziv_stajalista; }
    inline bool isVaznoStajaliste()         const { return vazno; }
    inline const std::vector<Linija*>& getLinije() const { return linije; }
    std::set<std::string, std::less<std::string>> getOznakeLinija();

    // Setri
    inline void setSifraStajalista(int sifra) { sifra_stajalista = sifra; }
    inline void setNazivStajalista(std::string naziv) { naziv_stajalista = naziv; }
    inline void setVaznoStajaliste(bool vazno_) { vazno = vazno_; }

    void addLinija(Linija* l);

    // print
    std::string print() {
        return std::to_string(sifra_stajalista) + "-" + naziv_stajalista + "-" + std::to_string(vazno) + "-" + std::to_string(linije.size());
    }

};

#endif // STAJALISTE_H
