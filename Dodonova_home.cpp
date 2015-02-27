#include <iostream>
#include<string>
#include<Windows.h>
#include<vector>
using namespace std;

// 1. Создайте класс Student, который будет содержать информацию о студенте.
// С помощью механизма наследования, реализуйте класс Aspirant (аспирант - студент, 
// который готовится к защите кандидатской работы) производный от Student. 

class Student {
	string name;
	int id;

public:
	Student() {
		name = "";
		id = -1;
	}

	Student(string _name, int _id) {
		name = _name;
		id = _id;
	}

	int Id() {
		return id;
	}

	string Name() {
		return name;
	}

	virtual void Print() {
		cout << "id: " << id << " name: " << name << endl;
	}
};

class Aspirant : public Student {
	int dissertation;

public:
	Aspirant() : Student() {
		dissertation = -1;
	}

	Aspirant(string _name, int _id, int _dissertation) : Student(_name, _id) {
		dissertation = _dissertation;
	}

	virtual void Print() {
		cout << "id: " << Id() << " name: " << Name() << " dissertation: " << dissertation << endl;
	}
};


// 2. Создайте класс Passport (паспорт), который будет содержать паспортную информацию о 
// гражданине Украниы. С помощью механизма наследования, реализуйте класс ForeignPassport (загран.паспорт)
// производный от Passport. Напомним, что загран.паспорт содержит помимо паспортных данных, 
// также данные о визах, номер загран.паспорта. 

class Passport {
	string series;
	int number;
	string passport_date;

public:
	Passport() {
		series = "";
		number = 0;
		passport_date = "00.00.00";
	}

	Passport(string _series, int _number, string date) {
		series = _series;
		number = _number;
		passport_date = date;
	}

	string Series() {
		return series;
	}

	int Number() {
		return number;
	}

	string Date() {
		return passport_date;
	}

	virtual void Print() {
		cout << "Passport: " << series << number << " Passport date: " << passport_date << endl;
	}
};

class ForeignPassport : public Passport {
	vector<string>visas;

public:
	ForeignPassport(string _series, int _number, string date, string _visa) : Passport( _series, _number, date) {
		visas.push_back(_visa);
	}

	void AddVisa(string visa) {
		visas.push_back(visa);
	}

	virtual void Print() {
		cout << "Foreign Passport: " << Series() << Number() << " Passport date: " << Date() << " visas: ";
		for (int i = 0; i < visas.size(); i++) {
			cout << visas[i] << " ";
		}
	}
};

void main() {
	//Student s("Vasya", 123);
	//s.Print();

	//Aspirant a("Petya", 12, 5263);
	//a.Print();

	//###########################################

	//Passport p("EA", 456234, "24.10.2000");
	//p.Print();

	//ForeignPassport fp("SA", 124563, "05.12.2014", "UK124578");
	//fp.AddVisa("BG784512");
	//fp.Print();

}