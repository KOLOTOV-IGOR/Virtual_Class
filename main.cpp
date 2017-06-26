#include "emp.h"

int main() {
	employee em("Trip", "Harris", "Thumper");
	cout << em << endl;
	em.ShowAll();
	mananger ma("Amorphia", "Spindragon", "Nuancer", 5);
	cout << endl << ma << endl;
	ma.ShowAll();
	fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
	cout << endl << fi << endl;
	fi.ShowAll(); cout << endl;
	highfink hf(ma, "Curly Kew");
	hf.ShowAll();
	cout << "Press Enter for next phase:\n";
	cin.get();
	highfink hf2;
	hf2.SetAll();
	//hf2.ShowAll();
	cout << endl;
	abstr_emp *tri[4] = {&em, &fi, &hf, &hf2};
	for (int i = 0; i < 4; i++)
		tri[i]->ShowAll();

	return 0;
}