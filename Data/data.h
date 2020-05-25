#ifndef DATA_H
#define DATA_H
#include<iostream>
#include<vector>
#include<string>
#include "outofboundexception.h"
#include<sstream>
#include<stdexcept>

using std::vector;
using std::cout;
using std::endl;
using std::string;

class Data;

std::ostream& operator<<(std::ostream&, const Data&);

class Data
{
    friend std::ostream& operator<<(std::ostream&, const Data&);
private:
    unsigned short int _giornoCorrente;
    unsigned short int _meseCorrente;
    unsigned short int _annoCorrente;

    static unsigned short int _maxMesi;
    static unsigned short int _minMesi;
    static unsigned short int _minAnni;
    static unsigned short int _maxAnni;
    static unsigned short int _minGiorni;
    unsigned short int _maxGiorni;


    bool isBisestile() const;
    void setMaxGiorni();
    void checkLimiti();
    void aggiustaLimiti();
    void parsingDaStringa(string inputString);


public:
    Data(string inputString);
    Data(unsigned short int=1,unsigned short int=1,unsigned short int=1980);
    const Data& operator+(unsigned short int);
    const Data& aggiungiSettimane(unsigned short int);
    const Data& aggiungiMesi(unsigned short int);
    const Data& aggiungiAnni(unsigned short int);




};

#endif // DATA_H
