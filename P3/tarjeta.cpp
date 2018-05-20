#include <iomanip>
#include <algorithm>
#include "tarjeta.hpp"



bool luhn(const Cadena& numero);


Cadena Numero::quitarEspacios(const Cadena& cad)
{
	Cadena aux(cad);
	std::remove_if(aux.begin(),aux.end()+1,[](unsigned char x){return std::isspace(x);});
	return Cadena(aux.c_str());
}


Numero::Numero(const Cadena& num)
{

	if(num.length() == 0)
		throw Incorrecto(Razon::LONGITUD);

	Cadena aux = quitarEspacios(num);

	if(find_if(aux.begin(), aux.end(), not1(EsDigito())) != aux.end())
		throw Incorrecto(Razon::DIGITOS);

	if(aux.length() < 13 || aux.length() > 19)  		  //comprobar la longuitud
		throw Incorrecto(Razon::LONGITUD);

	if(!luhn(aux))						  //comprovar la validez
		throw Incorrecto(Razon::NO_VALIDO);

	num_ = aux;
}

Numero::operator const char*() const
{
	return num_.c_str();
}



Tarjeta::Tarjeta(Tipo tip, const Numero& num, const Usuario& user, const Fecha& fech):tipo_(tip), tarjeta_(num), user_(&user),caducidad_(fech), titular_facial_(user.nombre() + Cadena(" ") + user.apellidos())
{

	if(fech < Fecha())
		throw Caducada(fech);

	const_cast<Usuario*>(user_)->es_titular_de(*this);
}


void Tarjeta::anula_titular()
{
	user_ = nullptr;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo)
{
	switch(tipo)
	{
		case Tarjeta::Tipo::VISA:
			os << "VISA"; break;
		case Tarjeta::Tipo::Mastercard:
			os << "Mastercard"; break;
		case Tarjeta::Tipo::Maestro:
			os << "Maestro"; break;
		case Tarjeta::Tipo::JCB:
			os << "JBC"; break;
		case Tarjeta::Tipo::AmericanExpress:
			os << "AmericanExpress"; break;
	}	

	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tar)
{
	os << tar.tipo() << std::endl;
	os << tar.numero() << std::endl;
	os << tar.titular_facial() << std::endl;
	os << "Caduca: " << std::setfill('0') << std::setw(2) 
	<< tar.caducidad().mes() << '/' << std::setw(2) << (tar.caducidad().anno()%100) ;
	return os;
}

bool operator <(const Numero& n1, const Numero& n2)
{
	return (n1.num_ < n2.num_);
}

bool operator <(const Tarjeta& tar1, const Tarjeta& tar2)
{
	return (tar1.numero() < tar2.numero());
}

Tarjeta::~Tarjeta()
{
	if(Usuario* us = const_cast<Usuario*>(user_))
		us->no_es_titular_de(*this);
}



