#include <iostream>
#include <vector>
#include "prey.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

void create(const string &str, vector<Prey*> &preys, vector<Predator*> &predators)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}
    int n,m;
    f >> n>>m;
    preys.resize(n);
    for( int i=0; i<n; ++i ){
        char ch; string name; int p;
        f >> name >> ch >> p;

        switch(ch){
            case 'l' : preys[i] = new Lemming(name,Species::LEMMING, p); break;
            case 'h' : preys[i] = new Hare(name,Species::HARE ,p); break;
            case 'g' : preys[i] = new Gopher(name,Species::GOPHER,p); break;
        }
    }
    predators.resize(m);
    for( int j=0; j<m; ++j ) {
        char ch; string name; int p;
        f >> name >> ch >> p;
        switch(ch){
            case 'o' : predators[j] = new Owl(name,Species::OWL ,p); break;
            case 'f' : predators[j] = new Fox(name,Species::FOX,p); break;
            case 'w' : predators[j] = new Wolf(name,Species::WOLF,p); break;
        }
    }
}

int initialSum(vector<Prey*> &preys){
    int initial_sum=0;
    for(unsigned int i=0; i<preys.size();++i){
        initial_sum+=preys[i]->number();
    }
    return initial_sum;
}

bool all_extinct_prey(vector<Prey*> &preys){
    bool all_logic=true;
    for(unsigned int i=0; i<preys.size();++i){
        all_logic= (preys[i]->dead()) && all_logic;
    }
    return all_logic;
}

bool quadruple(vector<Prey*> &preys,int initial_sum)
{
    int sum=0;
    for(unsigned int i=0; i<preys.size();++i){
        sum+=preys[i]->number();
    }
    if(initial_sum*4<=sum) return true;
    else{return false;}
}

bool all_extinct_predator(vector<Predator*> &predators){
    bool dead_bool=true;
    for( unsigned int j=0; j<predators.size();++j){
        dead_bool= dead_bool && (predators[j]->dead());
    }
    return dead_bool;
}

vector<int> alive_prey(vector<Prey*> &preys){
    vector<int> alivePreys;
    for(unsigned int i=0; i<preys.size();++i){
        if(preys[i]->alive()) alivePreys.push_back(i);
    }
    return alivePreys;
}

void each_turn(vector<Prey*> &preys, vector<Predator*> &predators)
{
    srand((unsigned) (time(0)));
    int i=1;
    int init_Sum=initialSum(preys);
    while(!all_extinct_prey(preys) && !quadruple(preys,init_Sum))
    {
        vector<int> aliveOnes=alive_prey(preys);
        cout<<"\tTurn "<<i<<endl;
        for(unsigned int i=0; i<preys.size();++i){
            if(preys[i]->alive()){
                preys[i]->incTurn();
                preys[i]->increase();
            }
        }
        for( unsigned int j=0; j<predators.size();++j){
            int rand_ind = rand() % (aliveOnes.size());
            if(predators[j]->alive()){
                predators[j]->incTurn();
                predators[j]->offspring();
                preys[aliveOnes[rand_ind]]->attack(predators[j]);
            }
        }
        for(unsigned int k=0; k<preys.size();++k){
            if(preys[k]->alive()){
                preys[k]->limit_check();
            }
        }
        cout<<"~~Preys data~~"<<endl;
        for(unsigned int i=0; i<preys.size();++i){
            cout<<"(Number of turns this prey colony is alive: "<<preys[i]->turn()<<" ) ";
            switch(preys[i]->specie()){
                case 3:
                    cout<<preys[i]->name()<<" LEMMING "<<preys[i]->number()<<endl;
                    break;
                case 4:
                    cout<<preys[i]->name()<<" HARE "<<preys[i]->number()<<endl;
                    break;
                default:
                    cout<<preys[i]->name()<<" GOPHER "<<preys[i]->number()<<endl;
            }
        }
        cout<<"~~Predators data~~"<<endl;
        for( unsigned int j=0; j<predators.size();++j){
            cout<<"(Number of times this predator attacked random prey colony: "<<predators[j]->turn()<<") ";
            switch(predators[j]->specie()){
                case 0:
                    cout<<predators[j]->name()<<" OWL "<<predators[j]->number()<<endl;
                    break;
                case 1:
                    cout<<predators[j]->name()<<" FOX "<<predators[j]->number()<<endl;
                    break;
                default:
                    cout<<predators[j]->name()<<" WOLF "<<predators[j]->number()<<endl;
            }
        }
        i++;
        cout<<endl;
    }
}

void destroyPrey(vector<Prey*> &preys)
{
    for(int i=0; i<(int)preys.size(); ++i) delete preys[i];
}

void destroyPredator(vector<Predator*> &predators)
{
    for(int i=0; i<(int)predators.size(); ++i) delete predators[i];
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    vector<Prey*> preys;
    vector<Predator*> predators;
    create("input.txt", preys, predators);

    each_turn(preys,predators);

    destroyPrey(preys);
    destroyPredator(predators);
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1 Predator, 1 Prey", "inp1*.txt")
{
    vector<Prey*> preys;
    vector<Predator*> predators;

    SECTION("OWL attacking LEMMING")
    {
        create("input11.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==8);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("OWL attacking HARE")
    {
        create("input12.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==4);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("OWL attacking GOPHER")
    {
        create("input13.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==10);
        CHECK(predators[0]->turn()==30);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("FOX attacking LEMMING")
    {
        create("input14.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==8);
        CHECK(predators[0]->turn()==8);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("FOX attacking HARE")
    {
        create("input15.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==4);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("FOX attacking GOPHER")
    {
        create("input16.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==14);
        CHECK(predators[0]->turn()==17);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("WOLF attacking LEMMING")
    {
        create("input17.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==7);
        CHECK(predators[0]->turn()==8);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("WOLF attacking HARE")
    {
        create("input18.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==4);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("WOLF attacking GOPHER")
    {
        create("input19.txt", preys, predators);

        CHECK(preys[0]->number()==90);
        CHECK(predators[0]->number()==6);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==12);
        CHECK(predators[0]->turn()==19);

        destroyPrey(preys);
        destroyPredator(predators);
    }
}

TEST_CASE("Conditional cases", "inp2*.txt")
{
    vector<Prey*> preys;
    vector<Predator*> predators;

    SECTION("Check if every 4th Owl perishes when there is not enough prey")
    {
        create("input20.txt", preys, predators);

        CHECK(preys[0]->number()==1);
        CHECK(predators[0]->number()==25);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==19);
        CHECK(predators[0]->turn()==1);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("Check if every 4th Fox perishes when there is not enough prey")
    {
        create("input21.txt", preys, predators);

        CHECK(preys[0]->number()==1);
        CHECK(predators[0]->number()==25);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==19);
        CHECK(predators[0]->turn()==1);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("Check if every 4th Wolf perishes when there is not enough prey")
    {
        create("input22.txt", preys, predators);

        CHECK(preys[0]->number()==1);
        CHECK(predators[0]->number()==25);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==19);
        CHECK(predators[0]->turn()==1);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("Check if the prey number is initially 0 so it gives no output")
    {
        create("input23.txt", preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==100);
        CHECK(predators[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==0);
        CHECK(predators[0]->number()==100);
        CHECK(predators[0]->turn()==0);

        destroyPrey(preys);
        destroyPredator(predators);
    }
    SECTION("Check if the predator number is 0 so Lemming's number quadruples or more")
    {
        create("input24.txt", preys, predators);

        CHECK(preys[0]->number()==2);
        CHECK(predators[0]->number()==0);
        CHECK(predators[0]->turn()==0);
        CHECK(preys[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==8);
        CHECK(predators[0]->number()==0);
        CHECK(preys[0]->turn()==4);
        CHECK(predators[0]->turn()==0);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("Check if the predator number is 0 so Hare's number quadruples or more")
    {
        create("input25.txt", preys, predators);

        CHECK(preys[0]->number()==2);
        CHECK(predators[0]->number()==0);
        CHECK(predators[0]->turn()==0);
        CHECK(preys[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==9);
        CHECK(predators[0]->number()==0);
        CHECK(predators[0]->turn()==0);
        CHECK(preys[0]->turn()==8);

        destroyPrey(preys);
        destroyPredator(predators);
    }

    SECTION("Check if the predator number is 0 so Gopher's number quadruples or more")
    {
        create("input26.txt", preys, predators);

        CHECK(preys[0]->number()==2);
        CHECK(predators[0]->number()==0);
        CHECK(predators[0]->turn()==0);
        CHECK(preys[0]->turn()==0);

        each_turn(preys, predators);

        CHECK(preys[0]->number()==8);
        CHECK(predators[0]->number()==0);
        CHECK(predators[0]->turn()==0);
        CHECK(preys[0]->turn()==8);

        destroyPrey(preys);
        destroyPredator(predators);
    }
}

#endif // NORMAL_MODE
