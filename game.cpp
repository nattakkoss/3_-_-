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
		cout << "1.Выход\n2.Начать новую игру\n";
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
		log->makeNewLog("Пользователь создал сцены с размером " + sizeOfField + " X " + sizeOfField);
		while (true) {
			Sleep(1000);////
			scene.printGameField();
			cout << "\n1.Информация\n2.Управление боевой базы \n3.Управление юнитами\n4.Управление больницей\n5.Выход\n ";
			int com;
			cin >> com;
			if (com == 1) {
				log->makeNewLog("user: Информация");
				scene.printGameField();
				infoMenu();
			}
			if (com == 2) {
				log->makeNewLog("user: Управление боевой базы");
				scene.printGameField();
				basesMenu();
			}
			if (com == 3) {
				log->makeNewLog("user: Управление юнитами");
				scene.printGameField();
				unitsMenu();
			}
			if (com == 4) {
				log->makeNewLog("user: Управление больницей");
				scene.printGameField();
				hospitalsMenu();
			}
			if (com == 5) {
				log->makeNewLog("user: Выход");
				break;
			}
		}
		//system("cls");
		cout << "\n----------------Конец---------------- \n";
		//log->outputLogs();
		Log* adaptLog = new Adapter(log);
		cout << "\nКуда выводить логи\n1.Консоль\n2.log.txt\n";
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
		cout << "\n1.Всего юнитов на карте\n2.Всего баз на карте\n3.Всего больниц на карте\n";
		int com;
		cin >> com;
		if (com == 1) {
			log->makeNewLog("user: Всего юнитов на карте");
			scene.totalUnitsOnMap();
		}
		if (com == 2) {
			log->makeNewLog("user: Всего баз на карте");
			scene.totalBasesOnMap();
		}
		if (com == 3) {
			log->makeNewLog("user: Всего больниц на карте");
			scene.totalHospitalsOnMap();
		}
	}

	void unitsMenu() {
		cout << "\n1.Создать новый юнит\n2.Взаимодействовать со существующим\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: Создать новый юнит");
			cout << "\n Введите координаты базы, где вы хотите создать юнит\n";
			log->makeNewLog("user: Введите координаты новой базы");
			int x, y;
			cin >> x >> y;
			combatBase* base = scene.getBaseFromCoord(x, y);
			Warrior* unit = nullptr;
			if (base == nullptr) {
				log->makeNewLog("user: Вврд некорректных координат");
				cout << "\n Некорректный ввод\n";
			}
			else {
				cout << "\n Какой юнит:\n1.Пехота\n2.Конница\n3.Лучники\n";
				int squad;
				cin >> squad;
				scene.printGameField();
				if (squad == 1) {
					cout << "\nКакого типа:\n1.Мечники\n 2.Копейщики\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(InfantrySquad, Spearmen_INF);
						log->makeNewLog("user: выбор мечника");
					}
					if (type == 2) {
						unit = base->createUnit(InfantrySquad, Swordsmen_INF);
						log->makeNewLog("user: выбор копейщика ");

					}
				}

				if (squad == 2) {
					cout << "\nКакого типа:\n1.Всадники\n2.Кавалерия\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(СavalrySquad, Horsemen_CVR);
						log->makeNewLog("user: выбор всадника");
					}
					if (type == 2) {
						unit = base->createUnit(СavalrySquad, Caval_CVR);
						log->makeNewLog("user: выбор кавалерии");
					}
				}

				if (squad == 3) {
					cout << "\nКакого типа:\n1.Арбалетчики\n2.Пращники\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(ArchersSquad, Сrossbowmen_ARC);
						log->makeNewLog("user: выбор арбалетчика");
					}
					if (type == 2) {
						unit = base->createUnit(ArchersSquad, Slingers_ARC);
						log->makeNewLog("user: выбор пращника");
					}
				}
			}
			if (unit == nullptr) {
				cout << "\nНекорректный ввод\n";
				log->makeNewLog("user: некорректный ввод");
			}
			else {
				scene.printGameField();
				cout << "\nВыбрать координаты для размещения юнита\n";
				int x, y;
				cin >> x >> y;
				log->makeNewLog("user: ввод координат юнита");
				if (scene.addUnit(unit, x, y) != -1)
					log->makeNewLog(unit->info() + ": координаты были введены пользователем");
				else
					log->makeNewLog("user: ввыод некорректных координат");
			}
		}
		else {
			cout << "\n1.Двигаться\n2.Лечиться\n3.Атаковать\n4.Здоровье\n5.Броня\n6.Атака\n7.Информация о юните\n";
			int com;
			cin >> com;
			scene.printGameField();
			cout << "\nВставьте координаты юнита\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: ввод координат юнита, с которым хочет взаимодействовать пользователь");
			Warrior* unit = scene.getUnitFromCoord(x, y);
			scene.printGameField();
			if (unit != nullptr) {
				if (com == 1) {
					log->makeNewLog("user: ввод координат юнита, с которым хочет взаимодействовать пользователь");
					cout << "\n Введите a,w,d,s чтоб двигаться\n";
					char myStep;
					cin >> myStep;
					scene.step(unit, myStep);
				}
				if (com == 2) {
					log->makeNewLog("user: выбор вылечить юнит");
					cout << "\nВведите координаты больницы, чтоб вылечить юнит\n";
					int hx, hy;
					cin >> hx >> hy;
					Hospital* hospital = scene.getHospitalFromCoord(x, y);
					if (hospital != nullptr) {
						hospital->therapy(unit);
						log->makeNewLog(unit->info() + " : был вылечен в больнице  " + hospital->info());
					}
				}
				if (com == 3) {
					log->makeNewLog("user: атаковать юнит");
					cout << "\nВведите координаты для атаки\n";
					int ax, ay;
					cin >> ax >> ay;
					Warrior* enemyUnit = scene.getUnitFromCoord(x, y);
					if (enemyUnit != nullptr) {
						log->makeNewLog(scene.fight(unit, enemyUnit));
					}
				}
				if (com == 4) {
					log->makeNewLog("user: узнать здоровье юнита");
					cout << scene.getUnitHealth(unit) << endl;
				}
				if (com == 5) {
					log->makeNewLog("user: узнать броню юнита");
					cout << scene.getUnitArmour(unit) << endl;
				}
				if (com == 6) {
					log->makeNewLog("user: узнать атаку юнита");
					cout << scene.getUnitAttack(unit) << endl;
				}
				if (com == 7) {
					log->makeNewLog("user: узнать информацию о юните");
					cout << scene.getUnitInfo(unit) << endl;
				}
			}
		}
	}
	void basesMenu() {
		cout << "\n1.Создать новую базу\n2.Информация о существующей базе\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: создать новую базу");
			cout << "\nВведите координаты для создания базы\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: введите координаты для новой базы");
			//combatBase base = scene.createBase();
			scene.addBase(new combatBase, x, y);
		}
		if (com == 2) {
			log->makeNewLog("user: информация о существующей базе");
			cout << "\nВведите координаты базы\n";
			log->makeNewLog("user: введите координаты существующей базы");
			int x, y;
			cin >> x >> y;
			combatBase* base = nullptr;
			base = scene.getBaseFromCoord(x, y);
			if (base != nullptr) {
				cout << "\n1.Сколько создано\n2.Сколько всего можно создать\n";
				int func;
				cin >> func;
				if (func == 1) {
					log->makeNewLog("user: сколько создано");
					cout << scene.countOfUnitsOnBase(base) << endl;
				}
				if (func == 2) {
					log->makeNewLog("user: сколько всего можно создать");
					cout << scene.maximumCountOfUnitsOnBase(base) << endl;
				}
			}
		}
	}
	void hospitalsMenu() {
		cout << "\n1.Создать больницу\n2.Информация о больнице\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: создать больницу ");
			cout << "\nВведите координаты для создания больницы\n";
			int x, y;
			cin >> x >> y;
			scene.printGameField();
			cout << "\nКакого юнита:\n1.Пехота\n2.Конница\n3.Лучники\n";
			int func;
			cin >> func;
			if (func == 1) {
				scene.addHospital(scene.createHospital(СavalrySquad), x, y);
			}
			if (func == 2) {
				scene.addHospital(scene.createHospital(InfantrySquad), x, y);
			}
			if (func == 3) {
				scene.addHospital(scene.createHospital(ArchersSquad), x, y);
			}
		}
		if (com == 2) {
			cout << "\nВведите координаты больницы для получения информации\n";
			int x, y;
			cin >> x >> y;
			Hospital* hospital = scene.getHospitalFromCoord(x, y);
			if (hospital != nullptr) {
				log->makeNewLog("user: получение информации о больнице");
				scene.getHospitalInfo(hospital);
			}
		}
	}

};