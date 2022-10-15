#include "prey.h"
#include "predator.h"

void Prey::preyed(Predator* predator){
    if(this->number() < (predator->number()*2)){
        if(predator->number() <=(((predator->number()*2 - this->number())/2)/4))
            predator->setNumber(0);
        else{
            predator->setNumber(predator->number()-(((predator->number()*2-this->number())/2)/4));
        }
        this->setNumber(0);
    }
    else{this->setNumber(this->number()-(predator->number()*2));}
}

void Lemming::preyed(Predator* predator){
    if(this->number() < (predator->number()*4)){
        if(predator->number() <=(((predator->number()*4 - this->number())/4)/4))
            predator->setNumber(0);
        else{
            predator->setNumber(predator->number()-(((predator->number()*4-this->number())/4)/4));
        }
        this->setNumber(0);
    }
    else{this->setNumber(this->number()-(predator->number()*4));}
}

void Lemming::increase(){
    if(this->turn() % 2==0) this->setNumber(this->number()*2);
}
void Lemming::limit_check() {
    if(this->number()>200) this->setNumber(30);
}

void Hare::increase(){
    if(this->turn() % 2==0) this->setNumber(this->number()*1.5);
}

void Hare::limit_check() {
    if(this->number()>100) this->setNumber(20);
}

void Gopher::increase(){
    if(this->turn() % 4==0) this->setNumber(this->number()*2);
}

void Gopher::limit_check() {
    if(this->number()>200) this->setNumber(40);
}
