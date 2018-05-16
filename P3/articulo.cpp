#include "articulo.hpp"

using namespace std;

std::ostream& operator <<(std::ostream& os, const Articulo& A)
{
	os << "[" << A.referencia() << "] \"" << A.titulo() << "\" , " << A.f_publi().anno() << ". " << A.precio() << "€";
	return os;
}

