#include "predator.h"
#include "prey.h"

void Wolf::offspring(){
    if(this->turn()%8==0) this->setNumber(this->number()+((this->number()/4)*2));
}

void Fox::offspring(){
    if(this->turn()%8==0) this->setNumber(this->number()+((this->number()/4)*3));
}

void Owl::offspring(){
    if(this->turn()%8==0) this->setNumber(this->number()+(this->number()/4));
}

Predator* Predator::attack(Lemming* p){
    p->preyed(this);
    return this;
}

Predator* Predator::attack(Hare* p){
    p->preyed(this);
    return this;
}

Predator* Predator::attack(Gopher* p){
    p->preyed(this);
    return this;
}

/*
Predator* Wolf::attack(Lemming* p){
    p->preyed(this);
    return this;
}

Predator* Wolf::attack(Hare* p){
    p->preyed(this);
    return this;
}

Predator* Wolf::attack(Gopher* p){
    p->preyed(this);
    return this;
}


Predator* Owl::attack(Lemming* p){
    p->preyed(this);
    return this;
}

Predator* Owl::attack(Hare* p){
    p->preyed(this);
    return this;
}

Predator* Owl::attack(Gopher* p){
    p->preyed(this);
    return this;
}



Predator* Fox::attack(Lemming* p){
    p->preyed(this);
    return this;
}

Predator* Fox::attack(Hare* p){
    p->preyed(this);
    return this;
}

Predator* Fox::attack(Gopher* p){
    p->preyed(this);
    return this;
}
*/
