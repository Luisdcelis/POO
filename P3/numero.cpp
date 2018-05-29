#include <ctype.h>
#include "numero.h"

Cadena Numero::quitarEspacios(const Cadena& cad)
{
	Cadena aux{cad};
	aux.erase(remove_if(aux.begin(),aux.end()+1,[](char x){return isspace(x);}), aux.end());
	return aux;
}


Numero::Numero(const Cadena& num)
{
	int i = 0;
	num_ = quitarEspacios(num);

	while(i < num_.length()) //comprobar que todos son digitos
	{
		if(!isdigit(num_[i]))
			throw Incorrecto(DIGITOS);
	}


	if(num_ < 13 || num_ > 19)  		  //comprobar la longuitud
		throw Incorrecto(LONGITUD);

	if(!luhn(num_))						  //comprovar la validez
		throw Incorrecto(NO_VALIDO);
}

Numero::operator const char*() const
{
	return num_.c_str();
}

bool operator <(const Numero& n1, const Numero& n2)
{
	return (n1.num_ < n2.num_);
}

