#include "Scene.cpp"
#include "windows.h"
#include "logs.cpp"
using namespace std;
class Game {
private:
	Scene scene;
public:
	MyLog* log;
	Game() {
		log = new MyLog;
		//scene = *new Scene;
		startMenu();
	}
	void startMenu() {
		cout << "1.�����\n2.������ ����� ����\n";
		int com;
		cin >> com;
		if (com == 2) {
			log->makeNewLog("user: nachat' igru");
			game();
		}
		else {
			log->makeNewLog("user: exit");
			return;
		}
	}
	void game() {
		string sizeOfField = scene.createGameField();
		log->makeNewLog("������������ ������ ����� � �������� " + sizeOfField + " X " + sizeOfField);
		while (true) {
			Sleep(1000);////
			scene.printGameField();
			cout << "\n1.����������\n2.���������� ������ ���� \n3.���������� �������\n4.���������� ���������\n5.�����\n ";
			int com;
			cin >> com;
			if (com == 1) {
				log->makeNewLog("user: ����������");
				scene.printGameField();
				infoMenu();
			}
			if (com == 2) {
				log->makeNewLog("user: ���������� ������ ����");
				scene.printGameField();
				basesMenu();
			}
			if (com == 3) {
				log->makeNewLog("user: ���������� �������");
				scene.printGameField();
				unitsMenu();
			}
			if (com == 4) {
				log->makeNewLog("user: ���������� ���������");
				scene.printGameField();
				hospitalsMenu();
			}
			if (com == 5) {
				log->makeNewLog("user: �����");
				break;
			}
		}
		//system("cls");
		cout << "\n----------------�����---------------- \n";
		//log->outputLogs();
		Log* adaptLog = new Adapter(log);
		cout << "\n���� �������� ����\n1.�������\n2.log.txt\n";
		int comm;
		cin >> comm;
		pair<string, string>  res = adaptLog->printLog(comm);
		ofstream fout;
		fout.open(res.second);
		fout << res.first;
		/*if (comm == 1) {
			system("pause");
		}*/
		//Sleep(5000);
		return;
	}
	void infoMenu() {
		cout << "\n1.����� ������ �� �����\n2.����� ��� �� �����\n3.����� ������� �� �����\n";
		int com;
		cin >> com;
		if (com == 1) {
			log->makeNewLog("user: ����� ������ �� �����");
			scene.totalUnitsOnMap();
		}
		if (com == 2) {
			log->makeNewLog("user: ����� ��� �� �����");
			scene.totalBasesOnMap();
		}
		if (com == 3) {
			log->makeNewLog("user: ����� ������� �� �����");
			scene.totalHospitalsOnMap();
		}
	}

	void unitsMenu() {
		cout << "\n1.������� ����� ����\n2.����������������� �� ������������\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: ������� ����� ����");
			cout << "\n ������� ���������� ����, ��� �� ������ ������� ����\n";
			log->makeNewLog("user: ������� ���������� ����� ����");
			int x, y;
			cin >> x >> y;
			combatBase* base = scene.getBaseFromCoord(x, y);
			Warrior* unit = nullptr;
			if (base == nullptr) {
				log->makeNewLog("user: ���� ������������ ���������");
				cout << "\n ������������ ����\n";
			}
			else {
				cout << "\n ����� ����:\n1.������\n2.�������\n3.�������\n";
				int squad;
				cin >> squad;
				scene.printGameField();
				if (squad == 1) {
					cout << "\n������ ����:\n1.�������\n 2.���������\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(InfantrySquad, Spearmen_INF);
						log->makeNewLog("user: ����� �������");
					}
					if (type == 2) {
						unit = base->createUnit(InfantrySquad, Swordsmen_INF);
						log->makeNewLog("user: ����� ��������� ");

					}
				}

				if (squad == 2) {
					cout << "\n������ ����:\n1.��������\n2.���������\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(�avalrySquad, Horsemen_CVR);
						log->makeNewLog("user: ����� ��������");
					}
					if (type == 2) {
						unit = base->createUnit(�avalrySquad, Caval_CVR);
						log->makeNewLog("user: ����� ���������");
					}
				}

				if (squad == 3) {
					cout << "\n������ ����:\n1.�����������\n2.��������\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(ArchersSquad, �rossbowmen_ARC);
						log->makeNewLog("user: ����� �����������");
					}
					if (type == 2) {
						unit = base->createUnit(ArchersSquad, Slingers_ARC);
						log->makeNewLog("user: ����� ��������");
					}
				}
			}
			if (unit == nullptr) {
				cout << "\n������������ ����\n";
				log->makeNewLog("user: ������������ ����");
			}
			else {
				scene.printGameField();
				cout << "\n������� ���������� ��� ���������� �����\n";
				int x, y;
				cin >> x >> y;
				log->makeNewLog("user: ���� ��������� �����");
				if (scene.addUnit(unit, x, y) != -1)
					log->makeNewLog(unit->info() + ": ���������� ���� ������� �������������");
				else
					log->makeNewLog("user: ����� ������������ ���������");
			}
		}
		else {
			cout << "\n1.���������\n2.��������\n3.���������\n4.��������\n5.�����\n6.�����\n7.���������� � �����\n";
			int com;
			cin >> com;
			scene.printGameField();
			cout << "\n�������� ���������� �����\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: ���� ��������� �����, � ������� ����� ����������������� ������������");
			Warrior* unit = scene.getUnitFromCoord(x, y);
			scene.printGameField();
			if (unit != nullptr) {
				if (com == 1) {
					log->makeNewLog("user: ���� ��������� �����, � ������� ����� ����������������� ������������");
					cout << "\n ������� a,w,d,s ���� ���������\n";
					char myStep;
					cin >> myStep;
					scene.step(unit, myStep);
				}
				if (com == 2) {
					log->makeNewLog("user: ����� �������� ����");
					cout << "\n������� ���������� ��������, ���� �������� ����\n";
					int hx, hy;
					cin >> hx >> hy;
					Hospital* hospital = scene.getHospitalFromCoord(x, y);
					if (hospital != nullptr) {
						hospital->therapy(unit);
						log->makeNewLog(unit->info() + " : ��� ������� � ��������  " + hospital->info());
					}
				}
				if (com == 3) {
					log->makeNewLog("user: ��������� ����");
					cout << "\n������� ���������� ��� �����\n";
					int ax, ay;
					cin >> ax >> ay;
					Warrior* enemyUnit = scene.getUnitFromCoord(x, y);
					if (enemyUnit != nullptr) {
						log->makeNewLog(scene.fight(unit, enemyUnit));
					}
				}
				if (com == 4) {
					log->makeNewLog("user: ������ �������� �����");
					cout << scene.getUnitHealth(unit) << endl;
				}
				if (com == 5) {
					log->makeNewLog("user: ������ ����� �����");
					cout << scene.getUnitArmour(unit) << endl;
				}
				if (com == 6) {
					log->makeNewLog("user: ������ ����� �����");
					cout << scene.getUnitAttack(unit) << endl;
				}
				if (com == 7) {
					log->makeNewLog("user: ������ ���������� � �����");
					cout << scene.getUnitInfo(unit) << endl;
				}
			}
		}
	}
	void basesMenu() {
		cout << "\n1.������� ����� ����\n2.���������� � ������������ ����\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: ������� ����� ����");
			cout << "\n������� ���������� ��� �������� ����\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: ������� ���������� ��� ����� ����");
			//combatBase base = scene.createBase();
			scene.addBase(new combatBase, x, y);
		}
		if (com == 2) {
			log->makeNewLog("user: ���������� � ������������ ����");
			cout << "\n������� ���������� ����\n";
			log->makeNewLog("user: ������� ���������� ������������ ����");
			int x, y;
			cin >> x >> y;
			combatBase* base = nullptr;
			base = scene.getBaseFromCoord(x, y);
			if (base != nullptr) {
				cout << "\n1.������� �������\n2.������� ����� ����� �������\n";
				int func;
				cin >> func;
				if (func == 1) {
					log->makeNewLog("user: ������� �������");
					cout << scene.countOfUnitsOnBase(base) << endl;
				}
				if (func == 2) {
					log->makeNewLog("user: ������� ����� ����� �������");
					cout << scene.maximumCountOfUnitsOnBase(base) << endl;
				}
			}
		}
	}
	void hospitalsMenu() {
		cout << "\n1.������� ��������\n2.���������� � ��������\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: ������� �������� ");
			cout << "\n������� ���������� ��� �������� ��������\n";
			int x, y;
			cin >> x >> y;
			scene.printGameField();
			cout << "\n������ �����:\n1.������\n2.�������\n3.�������\n";
			int func;
			cin >> func;
			if (func == 1) {
				scene.addHospital(scene.createHospital(�avalrySquad), x, y);
			}
			if (func == 2) {
				scene.addHospital(scene.createHospital(InfantrySquad), x, y);
			}
			if (func == 3) {
				scene.addHospital(scene.createHospital(ArchersSquad), x, y);
			}
		}
		if (com == 2) {
			cout << "\n������� ���������� �������� ��� ��������� ����������\n";
			int x, y;
			cin >> x >> y;
			Hospital* hospital = scene.getHospitalFromCoord(x, y);
			if (hospital != nullptr) {
				log->makeNewLog("user: ��������� ���������� � ��������");
				scene.getHospitalInfo(hospital);
			}
		}
	}

};