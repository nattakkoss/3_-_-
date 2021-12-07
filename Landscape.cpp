#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>

#include "warrior1.h"

using namespace std;



class LandScape {
public:
	virtual string info() = 0;
	virtual bool isItPossibleToPass(Warrior*) = 0;
};

class Forest :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Forest() {
		whoCanNotBeHere.insert(Ñrossbowmen_ARC);
		whoCanNotBeHere.insert(Horsemen_CVR);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Forest";
	}
};

class Sand :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Sand() {
		whoCanNotBeHere.insert(Slingers_ARC);
		whoCanNotBeHere.insert(Spearmen_INF);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Sand";
	}
};

class Water :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Water() {
		whoCanNotBeHere.insert(Swordsmen_INF);
		whoCanNotBeHere.insert(Caval_CVR);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Water";
	}
};