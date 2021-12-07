#include <string>
#include "Landscape.cpp"

using namespace std;

class Hospital {
public:
	virtual string info() = 0;
	virtual int therapy(Warrior*) = 0;
	virtual bool CanTreatedHere(Warrior*) = 0;
};

class cavalryHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Всадники" || unit->info() == "Кавалерия");
	}
public:
	string info()override {
		return "Больница конницы";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юинт не может лечиться здесь\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class infantryHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Мечники" || unit->info() == "Копейщик");
	}
public:
	string info()override {
		return "Больница пехоты";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юнит не может здесь лечиться\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class archersHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Арбалетчики" || unit->info() == "Пращники");
	}
public:
	string info()override {
		return "Больница лучников";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юнит не может здесь лечиться\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};
