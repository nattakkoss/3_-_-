#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>



using namespace std;
const long long INF = 1e8;

class Observer {
public:
	virtual ~Observer() {};
	virtual void upd(const std::string& message_from_subject) = 0;
	virtual void unitHasDie() = 0;
};

class Subject {
public:
	virtual ~Subject() {};
	virtual void add(Observer* observer) = 0;
	virtual void erase(Observer* observer) = 0;
	virtual void notification() = 0;
};

enum WarriorType {
	Ñrossbowmen_ARC = 0,
	Slingers_ARC,
	Horsemen_CVR,
	Caval_CVR,
	Swordsmen_INF,
	Spearmen_INF,
};
enum Squad {
	ArchersSquad = 0,
	ÑavalrySquad,
	InfantrySquad,
};


class Warrior :Subject {//1

private:
	std::list<Observer*> observers;
	std::string message;

public:
	void add(Observer* _observer)override {
		observers.push_back(_observer);
	}
	void erase(Observer* _observer)override {
		observers.remove(_observer);
	}
	void notification()override {
		for (auto x : observers) {
			x->unitHasDie();
			x->upd(message);
		}
	}
	string makeMessage(string _message) {
		message = _message;
		notification();
		return message;
	}

	virtual int getHealth() = 0;

	virtual int getArmour() = 0;

	virtual int getAttack() = 0;

	virtual int removeHealth(int) = 0;

	virtual int addHealth(int) = 0;
	virtual string info() = 0;

	virtual WarriorType type() = 0;

	virtual Warrior* operator % (Warrior* unit) = 0;


	virtual ~Warrior() = default;
};//1


class Archers : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Archers() {
		health = 150;
		attack = 120;
		armour = 80;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}


	string info() {
		return "Archers";
	};

};//2

class Ñrossbowmen : public Archers {//3
public:
	string info() {
		return "Àðáàëåò÷èê";
	};
	WarriorType type() {
		return Ñrossbowmen_ARC;
	}
};

class Slingers : public Archers {//3
public:
	string info() {
		return "Ïðàùíèê";
	};
	WarriorType type() {
		return Slingers_ARC;
	}
};

class Ñavalry : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Ñavalry() {
		health = 150;
		attack = 140;
		armour = 180;
	}
private:
	int health;
	int attack;
	int armour;


	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Ñavalry";
	};
};

class Horsemen : public Ñavalry {//3
public:
	string info() {
		return "Âñàäíèê";
	};
	WarriorType type() {
		return Horsemen_CVR;
	}
};

class Caval : public Ñavalry {//3
public:
	string info() {
		return "Êàâàëåðèÿ";
	};
	WarriorType type() {
		return Caval_CVR;
	}
};

class Infantry : public Warrior {//2
public:
	Infantry() {
		health = 100;
		attack = 100;
		armour = 100;
	}
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Infantry";
	};
};

class Swordsmen : public Infantry {//3
public:
	string info() {
		return "Ìå÷íèê";
	};
	WarriorType type() {
		return Swordsmen_INF;
	}
};

class Spearmen : public Infantry {//3

public:
	string info() {
		return "Êîïåéùèê";
	};
	WarriorType type() {
		return Spearmen_INF;
	}
};





class Factory {
public:
	virtual Warrior* createWarrior(Squad, WarriorType) = 0;

	virtual ~Factory() = default;
};

class ArchersFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (ArchersSquad, Ñrossbowmen_ARC):
			return new Ñrossbowmen;
		case (ArchersSquad, Slingers_ARC):
			return new Slingers;
		}
	}
};

class CavalryFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (ÑavalrySquad, Horsemen_CVR):
			return new Horsemen;
		case (ÑavalrySquad, Caval_CVR):
			return new Caval;
		}
	}
};

class InfantryFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (InfantrySquad, Swordsmen_INF):
			return new Swordsmen;
		case (InfantrySquad, Spearmen_INF):
			return new Spearmen;
		}
	}
};



class combatBase :public Observer {

public:
	combatBase(/*Warrior& _subject*/) /*: subject(_subject)*/ {
		//this->subject.add(this);
		health = 100;
		maximumNumberOfUnits = 5;///////
		cntOfUnits = 0;
	}
	void unitHasDie()override {
		cntOfUnits--;
	}
	void upd(const std::string& message_from_subject) override {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}
	//void RemoveMeFromTheList() {
		//subject.erase(this);
	//}
	void PrintInfo() {
		cout << this->message_from_subject_ << "\n";
	}

	Warrior* createUnit(Squad squad, WarriorType warriorType) {
		if (cntOfUnits >= maximumNumberOfUnits) {
			cout << "the maximum number of units has been created\n";
			return nullptr;
		}
		cntOfUnits++;
		auto archersFactory = new ArchersFactory;
		auto cavalryFactory = new CavalryFactory;
		auto infantryFactory = new InfantryFactory;

		Warrior* battleUnit = nullptr;

		switch (squad) {
		case ArchersSquad:
			battleUnit = (archersFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		case ÑavalrySquad:
			battleUnit = (cavalryFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;

		case InfantrySquad:
			battleUnit = (infantryFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		}
		cout << "incorrect input\n";
		return battleUnit;
	}
	void eraseObserverInfo() {
		for (auto x : subjects)
			x->erase(this);
	}
	int getHealth() {
		return health;
	}
	int getCntOfUnits() {
		return cntOfUnits;
	}
	int getMaximumCntOfUnits() {
		return maximumNumberOfUnits;
	}
	int removeHealth(int amount) {
		health -= amount;
		return health;
	}
private:
	int health, maximumNumberOfUnits, cntOfUnits;
	string message_from_subject_;
	set<Warrior*> subjects;
};


