#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <iostream>
#include <algorithm>
#include <cctype>
#include "usuario.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

class Usuario;


class Numero
{
public:
	Numero(const Cadena& num);
	operator const char*() const;
	friend bool operator <(const Numero& n1, const Numero& n2);

	enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

	class Incorrecto
	{
	public:
		Incorrecto(const Razon raz):razon_(raz){}
		Razon razon()const {return razon_;}
	private:
		Razon razon_;
	};

	class EsDigito
	{
		bool operator ()(char c){return isdigit(c);}
	};


private:
	Cadena num_;
	Cadena quitarEspacios(const Cadena& cad);
};


class Tarjeta
{
public:
	enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};

	Tarjeta(Tipo tip, const Numero& num, const Usuario& user, const Fecha& cad);
	Tarjeta(const Tarjeta& tar) = delete;
	Tarjeta& operator =(const Tarjeta& tar) = delete;

	const Tipo& tipo() const {return tipo_;};
	const Numero& numero() const {return tarjeta_;};
	const Usuario* titular() const {return user_;};
	const Fecha& caducidad() const {return caducidad_;};
	const Cadena& titular_facial() const {return titular_facial_;};
	
	void anula_titular();


	class Caducada
	{
	public:
		Caducada(const Fecha& fech):fech_(fech){}
		const Fecha& cuando() const {return fech_;};
	private:
		Fecha fech_;
	};

	~Tarjeta();

private:
	Tipo tipo_;
	Numero tarjeta_;
	const Usuario* user_;
	Fecha caducidad_;
	Cadena titular_facial_;

};

std::ostream& operator <<(std::ostream& os, const Tarjeta& tar);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
bool operator <(const Numero& n1, const Numero& n2);
bool operator <(const Tarjeta& tar1, const Tarjeta& tar2);


#endif