#include "LineaPedido.hpp"
#include <iomanip>

std::ostream& operator <<(std::ostream& os, const LineaPedido& LP)
{
	os << std::setprecision(2) << LP.precio_venta() << "€\t" << LP.cantidad();

	return os;
}
