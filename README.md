# Simulation of Tundra animals
## Task description
We are simulating the animals of the tundra. There are colonies of prey and predator animals. The number of animals in a colony affect the number of animals in other colonies. There are three predator species: ***the snowy owl, the arctic fox and the wolf***. There are three kinds of prey: ***the lemming, the arctic hare and the gopher***.

If the number of prey animals increase, predators can reproduce more quickly. If the number of prey is very large, most of them will wander away because they cannot find enough food. If the number of predators is large, the number of the prey decreases quicker as they are preyed upon.

Each colony has a name, a species, and the number of animals in the colony. The prey species are affected by the different predator species as follows. The number of animals in their own colony changes first, then they influence the predators.

  - ***Lemming***: If they are preyed upon by a predator colony, the number of animals in their colony decreases by four times the number of animals in the predator colony. The number of animals in their colony doubles every second turn. If there are more than 200 animals in the colony, the number of animals in the colony decreases to 30.
  - ***Gopher***: If they are preyed upon by a predator colony, the number of animals in their colony decreases by double the number of animals in the predator colony. The number of animals in their colony doubles every fourth turn. If there are more than 200 animals in the colony, the number of animals in the colony decreases to 40.
  - ***Hare***: If they are preyed upon by a predator colony, the number of animals in their colony decreases by double the number of animals in the predator colony. The number of animals in their colony grows by 50 percent (to one and a half times their previous number) every second turn. If there are more than 100 animals in the colony, the number of animals in the colony decreases to 20.
  
Predators choose and attack a prey colony randomly in each turn. If there are not enough animals in the attacked colony (for example, there are not four times the number of predators in a lemming colony), the number of predators also decreases: every fourth predator out of the ones who didn't get prey perishes. Predators have offsprings every eighth turn. Normally, the snow owls have 1 offspring per 4 animals, the foxes have 3 offsprings per 4 animals, and the wolves have 2 offsprings per 4 animals.

The program should read the colonies from a text file. The first line contains the number of prey and predator colonies separated by a space. Each of the next lines contains the data of one colony separated by space: their name, their species, their starting number of animals. The species can be: o - owl, f - fox, w - wolf, l - lemming, h - hare, g - gopher.

***Simulate the process until each of the prey colonies becomes extinct or the number of prey animals quadruples compared to its starting value. Print the data of each colony in each turn.***

## Analysis

Concrete objects in the task are the prey colonies and predator colonies. Prey colonies can be divided into 3 different groups: **Lemming, Gopher and Hare**. Predator colonies can be divided into 3 different groups: **Owl, Fox and Wolf**.
All of them have a name, a species, and the number of animals in the colony that can be got. It can be examined what happens when the predator colonies attack the prey colonies each turn. As predator(s) attack randomly each turn, the prey colonies increase their number independently on certain turns and manage their number if it exceeds the limit regardless of it is getting preyed by predator or not. 

Getting preyed by predator effects the prey colony in the following way: 
| Prey        | Colony number changes  | 
| ------------- |:-------------:| 
| Lemming  | -(4 * predator number) |  
| Hare   | -(2 * predator number)  |   
| Gopher  |   -(2 * predator number) | 

The prey number can increase on certain turns: 

| Prey        | Every second turn  | Every fourth turn  |
| ------------- |:-------------:| -----:|
| Lemming  | +(lemming number) |  |
| Hare   | +(hare number/2)  |   |
| Gopher  |    |  +(gopher number) |

There are different limits for each prey and their number decreases to certain numbers: 

| Prey        | number > 200  | number > 100  |
| ------------- |:-------------:| -----:|
| Lemming  | number:= 30 |  |
| Hare   |  | number:= 20 |
| Gopher  |   number:= 40 |  |

Predators have offsprings every eighth turn : 

| Predator         | turn = 8   | 
| ------------- |:-------------:| 
| Owl  | +(number / 4) |  
| Fox   | +((number / 4) * 3)  |   
| Wolf  | +((number / 4) * 2) |

If there are not enough animals in the attacked colony the number of predators also decreases:

| Attacked colony         | Lemming | 
| ------------- |:-------------:| 
| Predator  | -(((( predator number*4)-lemming number) / 4) /4) |  

| Attacked colony         | Hare | 
| ------------- |:-------------:| 
| Predator  | -(((( predator number*2)-lemming number) / 2) /4) |

| Attacked colony         | Gopher | 
| ------------- |:-------------:| 
| Predator  | -(((( predator number*2)-lemming number) / 2) /4) |

## Plan

To describe the prey colonies and predator colonies, 9 classes are introduced: base class ***Animal*** to describe the general properties, enum which contains all possible species and 2 children for the specific colonies: ***Prey and Predator***. 3 children which inherits Prey for the concrete prey species: ***Lemming, Hare and Gopher***. Also, 3 children which inherits Predator for the concrete predator species: ***Owl, Fox, and Wolf***. Regardless the type of the colonies, they have several common properties, like the name (`_name`), the species (`_specie`), the number (`_number`), the turn (`_turn`), the getter of its name (`name()`), the getter of its number (`number()`), the getter of its specie (`specie()`), the getter of its turn (`turn()`), if at least 1 predator and 1 prey colonies are alive (`alive()`) and it can be examined what happens when predator attacks prey colony until each prey colonies extinct or quadruples compared to starting number.

Operation (`attack()`) modifies the number of the prey colony, and if prey number are not enough then predator’s number decreases. Operations `alive()`, `dead()`, `name()`, `specie()`, `number()`, `turn()`, `setNumber()`, `incTurn()`, `dead()` may be implemented in the base class already, but `attack()`, `preyed()`, `increase()`, `limit_check()` just on the level of the concrete classes as its effect depends on species of the prey, also `offspring()` just on the level of the concrete classes as its effect depends on species of the predators. Therefore, the child classes ***Prey, Predator are going to be abstract***, as methods `attack()`, `increase()`, `limit_check()`, `offspring()` are abstract and we do not wish to instantiate such classes.

Predator class has three methods `attack()` that depends on the concrete species of prey and changes the prey colony’s number as well as show how the predator number changes when there is not enough prey. Objects are referred by pointers. 

The concrete children of the prey and predator classes initialize the name, the species, the number, and the turn through the constructor of the base class Animal and override the operation `attack()`, `increase()`, `limit()`, `preyed()` and `offspring()` in a unique way. Initialization and the override are explained in Section Analysis. According to the tables, in method `attack()`, `increase()`, `limit()`, `preyed()` conditionals have to be used in which the specie of the prey is examined. In method offspring() conditionals have to be used in which the specie of the predator is examined. Though, the conditionals are not effective if the program might be extended by new prey specie, as all the methods in all of the concrete prey classes and predator classes have to be modified. To avoid it, design pattern ***Visitor*** is applied where the predator classes are going to have the role of the visitor.

## Additional analysis

Methods `attack()` of the concrete preys expect a Predator object as an input and calls the method which corresponds to the species of the prey. The method `preyed()` can be defined on Prey class as it is not abstract. The method can be implemented identically for Hare and Gopher classes, but Lemming class’s `preyed()` method has slightly different implementation. Therefore, it is overridden in Lemming, but not overridden in Hare and Gopher which use their parent’s implementation. Both `increase()` and `limit_check()` methods are implemented differently in each concrete prey classes. So, both methods are overridden in each 3 children classes.

As attack() method is not dependent on the specie of predator but dependent on the specie of prey, it is sufficient to have these methods in predator class for each prey and no need to define for Owl, Fox, Wolf for each 9 cases. However, offspring() method is dependent on each species of predator, so it should be overridden in the 3 children classes accordingly.

## Testing

Grey box test cases:

***Outer loop:***

- 1) Length based:
  - One colony of both prey and predator
  -	Many colonies of both prey and predator
- 2) One prey colony:
  -	Zero predator colony
  -	One predator colony
  -	Many predators colonies

***Inner loop (conditional cases):***

- 1)	Every fourth predator perishes when there is not enough prey (1 prey colony, 1 predator colony): 
  -	25 Owl, 1 Lemming
  -	25 Fox, 1 Lemming
  -	25 Wolf, 1 Lemming
- 2) Check if the prey number is initially 0 so it gives no output (1 prey colony, 1 predator colony):
  -	100 Wolf, 0 Lemming 
  -	100 Owl, 0 Lemming 
  -	100 Fox, 0 Lemming 
- 3) Check if the predator number is 0 so it stops when prey’s number quadruples or more (1 prey colony, 1 predator colony) : 
  -	0 Wolf, 2 Lemming 
  -	0 Wolf, 2 Hare
  -	0 Wolf, 2 Gopher

***All cases with certain outcomes (1 predator colony and 1 prey colony):***

- 1)	Only 1 Lemming colony: 
  -	Only 1 Wolf colony
  -	Only 1 Owl colony
  -	Only 1 Fox colony

- 2) Only 1 Hare colony: 
  -	Only 1 Wolf colony
  -	Only 1 Owl colony
  -	Only 1 Fox colony

- 3) Only 1 Gopher colony: 
  -	Only 1 Wolf colony
  -	Only 1 Owl colony
  -	Only 1 Fox colony
