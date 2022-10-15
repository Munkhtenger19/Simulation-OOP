#pragma once
#include <string>
#include "predator.h"

class Animal{
protected:
    std::string _name;
    int _number;
    int _turn;
    Animal(const std::string &str, int e=0) :_name(str), _number(e), _turn(0){}
public:
    bool alive() const { return _number > 0; }
  //  bool quadruple() const{return _number > ;}
    std::string name() const{return _name;}
    int turn() const { return _turn;}
    int number() const {return _number;}
};

class Prey : public Animal{
public:
    Prey(const std::string &str, int e=0) : Animal(str,e){}
    virtual void preyed(Predator* &predator);
    virtual void increase()=0;
    virtual void limit_check()=0;
    virtual void change(Predator* &predator)=0;
    virtual ~Prey();
};

class Lemming : public Prey{
public:
    Lemming(const std::string &str, int e=0) : Prey(str,e){}
    void preyed(Predator* &predator) override;
    void increase(Predator* &predator) override;
    void limit_check()override;
    void change(Predator* &predator) override{
        predator=predator->attack(this);
    }
};

class Hare : public Prey{
public:
    Hare(const std::string &str, int e=0) : Prey(str,e){}
    void increase(Predator* &predator) override;
    void limit_check()override;
    void change(Predator* &predator) override{
        predator=predator->attack(this);
    }
};

class Gopher : public Prey{
public:
    Gopher(const std::string &str, int e=0) : Prey(str,e){}
    void increase(Predator* &predator) override;
    void Gopher::limit_check() override;
    void change(Predator* &predator) override{
        predator=predator->attack(this);
    }
};
