#include <iostream>
#include <iomanip>
#include "articulo.hpp"

using namespace std;


Articulo::Articulo(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre):cod_(cod), titulo_(tit), publicacion_(pub), precio_(pre), autores_(aut)
{
	if(aut.size() == 0)
		throw Autores_vacios();
}

std::ostream& operator <<(std::ostream& os, const Articulo& A)
{
	auto it = A.autores().begin();

	os << "[" << A.referencia() << "] \""<< A.titulo() << "\", de ";

	os << (*it)->apellidos();


	for(++it; it != A.autores().end(); it++)
	{
		os << ", " << (*it)->apellidos();
	}

	os << ". ";

	os << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << A.precio() << " €" << "\n\t";

	A.impresion_especifica(os);

	return os;
}
	
void Libro::impresion_especifica(std::ostream& os) const
{
		os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const
{
		os << tam_ << " MB, " << stock_ << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
		os << "A la venta hasta el " << f_expir_ <<".";
}
