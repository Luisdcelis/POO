#ifndef NUMERO_HPP_
#define NUMERO_HPP_

#include <iostream>
#include <algorithm>
#include "cadena.hpp"
#include "fecha.hpp"

bool luhn(const Cadena& numero);

class Numero
{
public:
	Numero(const Cadena& num);
	operator const char*() const;
	friend bool operator <(const Numero& n1, const Numero& n2);

	enum Razon {LONGITUD, DIGITOS, NO_VALIDO}

	class Incorrecto
	{
	public:
		Incorrecto(const Razon raz):razon_(raz){}
		Razon razon()const {return razon_;}
	private:
		Razon razon_;
	}

private:
	Cadena num_;
	Cadena quitarEspacios(const Cadena& cad);
}

bool operator <(const Numero& n1, const Numero& n2);

#endif