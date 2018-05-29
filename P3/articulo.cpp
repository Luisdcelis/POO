#include "articulo.hpp"

using namespace std;


Articulo::Articulo(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre):cod_(cod), titulo_(tit), publicacion_(pub), precio_(pre)
{
	if(aut.size() == 0)
		throw Autores_vacios();
	else
		autores_ = aut;
}

std::ostream& operator <<(std::ostream& os, const Articulo& A)
{
	os << "[" << A.referencia() << "] \""<< A.titulo() << ", de";

	for(auto c : A.autores())
		os << c.apellidos() << "," << c.nombre() << ".";

	os << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << A .precio() << " €" << "\n";

	A.impresion_especifica(os) ;
}

void Libro::impresion_especifica(std::ostream& os) const
{
		os << "\t" << n_pag_ << " págs.," << stock_ << " unidades." << "\n";
}

void Cederron::impresion_especifica(std::ostream& os) const
{
		os << "\t" << tam_ << " MB, " << stock_ << " unidades." << "\n";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
		os << "\t" <<"A la venta hasta el" << f_expir_ <<" ." << "\n";
}
