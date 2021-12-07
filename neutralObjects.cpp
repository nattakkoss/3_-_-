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
		return(unit->info() == "��������" || unit->info() == "���������");
	}
public:
	string info()override {
		return "�������� �������";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "���� ���� �� ����� �������� �����\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class infantryHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "�������" || unit->info() == "��������");
	}
public:
	string info()override {
		return "�������� ������";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "���� ���� �� ����� ����� ��������\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class archersHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "�����������" || unit->info() == "��������");
	}
public:
	string info()override {
		return "�������� ��������";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "���� ���� �� ����� ����� ��������\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};
