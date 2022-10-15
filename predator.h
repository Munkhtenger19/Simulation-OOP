#pragma once
#include <string>
//#include "prey.h"

enum Species{OWL=0, FOX, WOLF, LEMMING, HARE, GOPHER};

class Animal{
protected:
    std::string _name;
    Species _specie;
    int _number;
    int _turn;
    Animal(const std::string &str,Species specie, int e=0) :_name(str),_specie(specie), _number(e), _turn(0){}
public:
    void incTurn(){_turn++;}
    void setNumber(int n) {_number=n;}
    bool alive() const { return _number > 0; }
    bool dead() const{return _number <= 0;}
    std::string name() const{return _name;}
    int turn() const { return _turn;}
    int number() const {return _number;}
    Species specie() const {return _specie;}
    virtual ~Animal () {}
};

class Prey;
class Lemming;
class Gopher;
class Hare;

class Predator : public Animal{
public:
    virtual Predator* attack(Lemming* p);
    virtual Predator* attack(Hare* p);
    virtual Predator* attack(Gopher* p);
    Predator(const std::string &str,Species specie, int e=0) : Animal(str,specie,e){}
    virtual void offspring()=0;
    virtual ~Predator(){}
};

class Owl : public Predator{
public:
    Owl(const std::string &str,Species specie, int e=0) : Predator(str,Species::OWL,e){}
    void offspring() override;
    ~Owl(){}
};

class Fox : public Predator{
public:
    Fox(const std::string &str,Species specie ,int e=0) : Predator(str,Species::FOX,e){}
    void offspring() override;
    ~Fox(){}
};

class Wolf : public Predator{
public:
    Wolf(const std::string &str,Species specie, int e=0) : Predator(str,Species::WOLF,e){}
    void offspring() override;
    ~Wolf(){}
};
