#include <iostream>
#include "cadena.cpp"


using namespace std;	

int main()
{
	Cadena a("0123456789");
	cout << a.substr(3, 5) << endl;
	
	Cadena grande("Nihil novum sub solem");
    Cadena nuevo = grande.substr(6, 5);  // nuevo <- "novum"
    cout << "substr(6, 5) de " << grande << ": \"" << nuevo << "\"" << endl;
}

