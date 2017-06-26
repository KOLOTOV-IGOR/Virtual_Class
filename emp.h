#pragma once
#ifndef EMP_H_
#define EMP_H_
#include <iostream>
#include <string>
using std::string;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

class abstr_emp {
private:
	string fname;
	string lname;
	string job;
public:
	abstr_emp() : fname("no where"), lname("man"), job("none") {};
	abstr_emp(const string fn, const string ln, const string j) : fname(fn), lname(ln), job(j) {};
	virtual void ShowAll() const; //Выводит все данные с именами.
	virtual void SetAll(); //Запрашивает значения у пользователей.
	friend ostream &operator<<(ostream &os, const abstr_emp &e);//Выводит только имя и фамилию.
	virtual ~abstr_emp() = 0;//Виртуальный базовый класс.
};

class employee : public abstr_emp {
public:
	employee() : abstr_emp() {};
	employee(const string fn, const string ln, const string j) : abstr_emp(fn, ln, j) {};
	virtual void ShowAll() const;
	virtual void SetAll();
};

class mananger : virtual public abstr_emp {
private:
	int inchargeof; //Кол-во управляемых abstr_emp
protected:
	int InChargeOf() const { return inchargeof; }
	int &InChargeOf() { return inchargeof; }
public:
	mananger() : abstr_emp(), inchargeof(0) {};
	mananger(const string fn, const string ln, const string j, int ico) : abstr_emp(fn, ln, j), inchargeof(ico) {};
	mananger(const abstr_emp &e, int ico) : abstr_emp(e), inchargeof(ico) {};
	mananger(const mananger &m) : abstr_emp(m), inchargeof(m.inchargeof) {};
	friend ostream &operator<<(ostream &os, const mananger &m);
	virtual void ShowAll() const;
	virtual void SetAll();
};

class fink : virtual public abstr_emp {
private:
	string reportsto;
protected:
	const string RepotrsTo() const { return reportsto; }
	string &RepotsTo() { return reportsto; }
public:
	fink() : abstr_emp(), reportsto("Boss") {};
	fink(const string &fn, const string &ln, const string &j, const string &rpo) : abstr_emp(fn, ln, j), reportsto(rpo) {};
	fink(const abstr_emp &e, const string &rpo) : abstr_emp(e), reportsto(rpo) {};
	fink(const fink &f) : abstr_emp(f), reportsto(f.reportsto) {};
	virtual void ShowAll() const;
	virtual void SetAll();
	friend ostream &operator<<(ostream &os, const fink &f);
};

class highfink : public mananger, public fink {
public:
	highfink() {};
	highfink(const string &fn, const string &ln, const string &j, const string &rpo, int ico)
		: abstr_emp(fn, ln, j), mananger(fn, ln, j, ico), fink(fn, ln, j, rpo) {};
	highfink(const abstr_emp &e, const string &rpo, int ico)
		: abstr_emp(e), mananger(e, ico), fink(e, rpo) {};
	highfink(const fink &f, int ico)
		: abstr_emp(f), mananger(f, ico), fink(f) {};
	highfink(const mananger &m, const string &rpo)
		: abstr_emp(m), fink(m, rpo), mananger(m) {};
	highfink(const highfink &h) : fink(h), mananger(h) {};
	virtual void ShowAll() const;
	virtual void SetAll();
	//friend ostream &operator<<(ostream &os, const highfink &h);
};
//METHODS///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//abstr_emp's methods
abstr_emp::~abstr_emp() {}

void abstr_emp::ShowAll() const {
	cout << "First name: " << fname << "\n";
	cout << "Last name: " << lname << "\n";
	cout << "Job: " << job << "\n";
}

void abstr_emp::SetAll() {
	cout << "Enter worker's first name: ";
	getline(cin, fname);
	cout << "Enter worker's last name: ";
	getline(cin, lname);
	cout << "Enter worker's job: ";
	getline(cin, job);
	//while (cin.get() != '\n')
	//	continue;
}

ostream &operator<<(ostream &os, const abstr_emp &e) {
	os << "First name: " << e.fname << "\n";
	os << "Last name: " << e.lname << "\n";
	os << "Job: " << e.job << "\n";
	return os;
}
//employee's methods/////////////////////////////////////////////////////////////
void employee::ShowAll() const {
	abstr_emp::ShowAll();
}

void employee::SetAll() {
	abstr_emp::SetAll();
}
//mananger's methods///////////////////////////////////////////////////////////////
void mananger::ShowAll() const {
	abstr_emp::ShowAll();
	cout << "Inchargeof: " << inchargeof << endl;
}

void mananger::SetAll() {
	abstr_emp::SetAll();
	cin >> inchargeof;
}

/*mananger::mananger(const mananger &m) {
	mananger(m, m.inchargeof);
}*/

ostream &operator<<(ostream &os, const mananger &m) {
	os << (const abstr_emp &) m;//Приведение типов для использования дружественной функции класса предка. 
	os << "Inchargeof: " << m.inchargeof << "\n";
	return os;
}
//fink's methods/////////////////////////////////////////////////////////////////////////////
void fink::ShowAll() const {
	abstr_emp::ShowAll();
	cout << "ReportsTo: " << reportsto << endl;
}

void fink::SetAll() {
	abstr_emp::SetAll();
	cout << "ReportsTo: ";
	cin >> reportsto;
}

/*fink::fink(const fink &f) {
	fink(f, f.reportsto);
}*/

ostream &operator<<(ostream &os, const fink &f) {
	os << (const abstr_emp &)f;//Приведение типов для использования дружественной функции класса предка. 
	os << "ReportsTo: " << f.reportsto << "\n";
	return os;
}
//highfink's methods/////////////////////////////////////////////////////////////////////////////
void highfink::ShowAll() const {
	mananger::ShowAll();
	cout << "ReportsTo: " << RepotrsTo() << endl;
}

void highfink::SetAll() {
	fink::SetAll();
	cout << "InChargeOf: ";
	cin >> InChargeOf();
}
#endif