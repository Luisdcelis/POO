#ifndef CLAVE_HPP_
#define CLAVE_HPP_
#include "cadena.hpp"
#include "fecha.hpp"

class Clave
{
public:
	Clave(const char* contra);
	Cadena clave() const;
	bool verifica(const char* contra);

	enum Razon {CORTA, ERROR_CRYPT};

	class Incorrecta
	{
	public: 
		Incorrecta(const Razon error):razon_(error){}
		Razon razon() const {return razon_;}
	private:
		const Razon razon_
	}


private:
	Cadena clave_;
};

#endif