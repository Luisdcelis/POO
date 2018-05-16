#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include "clave.hpp"

using namespace std;

Clave::Clave(const char* contra)
{
	Cadena contrasena{contra};
	if(contrasena.length() < 5)
		throw Incorrecta(CORTA);
	else
	{
		const char * seedchars ="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		char* seed;

		seed[0] = seedchars[rand() % 64];
		seed[1] = seedchars[rand() % 64]; 

		clave_ = crypt(contrasena, seed);

		if(clave_ == NULL)
			throw Incorrecta(ERROR_CRYPT);

		delete[] contrasena;
	}
}

inline Cadena Clave::clave(){return clave_};

bool Clave::verifica(const char* contra)
{
	Cadena aux{contra};
	char* seed = {clave_[0], clave_[1]};

	return(clave_ == crypt(aux, seed));
}