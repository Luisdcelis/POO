#include <iostream>

class LineaPedido
{
public:
	explicit LineaPedido(double p, size_t cant = 1):p_vnt_(p), cant_vnt_(cant){}
	double precio_venta() const {return p_vnt_;}
	size_t cantidad() const {return cant_vnt_;}

private:
	double p_vnt_;
	size_t cant_vnt_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& LP);
