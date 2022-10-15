#pragma once
#include <string>
#include "predator.h"

class Animal;
class Predator;

class Prey : public Animal{
public:
    Prey(const std::string &str,Species specie, int e=0) : Animal(str,specie,e){}
    virtual void preyed(Predator* predator);
    virtual void increase()=0;
    virtual void limit_check()=0;
    virtual void attack(Predator* &predator)=0;
    virtual ~Prey(){}
};

class Lemming : public Prey{
public:
    Lemming(const std::string &str,Species specie, int e=0) : Prey(str,Species::LEMMING,e){}
    void preyed(Predator* predator) override;
    void increase() override;
    void limit_check()override;
    void attack(Predator* &predator) override{
        predator=predator->attack(this);
    }
    ~Lemming () {}
};

class Hare : public Prey{
public:
    Hare(const std::string &str,Species specie, int e=0) : Prey(str,Species::HARE,e){}
    void increase() override;
    void limit_check()override;
    void attack(Predator* &predator) override{
        predator=predator->attack(this);
    }
    ~Hare () {}
};

class Gopher : public Prey{
public:
    Gopher(const std::string &str,Species specie ,int e=0) : Prey(str,Species::GOPHER,e){}
    void increase() override;
    void limit_check() override;
    void attack(Predator* &predator) override{
        predator=predator->attack(this);
    }
    ~Gopher () {}
};

