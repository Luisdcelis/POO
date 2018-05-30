#include "pedido-articulo.hpp"
#include <iomanip>


void Pedido_Articulo::pedir(Pedido& pe, Articulo& ar, double precio, unsigned cantidad)
{
	directa_[&pe].insert(std::make_pair(&ar, LineaPedido(precio, cantidad)));
	inversa_[&ar].insert(std::make_pair(&pe, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& ar, Pedido& pe, double precio, unsigned cantidad)
{
	pedir(pe,ar,precio,cantidad);
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pe) 
{
	return directa_[&pe];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& ar)
{
	return inversa_[&ar];
}


std::ostream& operator <<(std::ostream& os, const LineaPedido& LP)
{
	os << std::fixed << std::setprecision(2) << LP.precio_venta() << ' ' << "€" << '\t' << LP.cantidad() ;

	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP)
{
	double total = 0;

	os << "PVP\tCantidad\t\tArticulo\n";
	os << "===============================================================================\n";
	for(auto c : IP)
	{
		Articulo* pa = c.first;
		LineaPedido lp = c.second;

		total += pa->precio() * lp.cantidad();

		os << lp << "\t\t" << "[" << pa->referencia() << "] \"" << pa->titulo() << "\"\n";
	}

	os << "================================================================================\n";

	os << "Total\t" << total << " €" << std::endl;

	return os;

}


std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pe)
{
	int total = 0;
	double precio = 0;

	os << "[Pedidos: " << pe.size() << "]\n";
	os << "================================================================================\n";
	os << " PVP\tCantidad\tFecha de venta\n";
	os << "================================================================================\n";

	for(auto c : pe)
	{
		Pedido* pp = c.first;
		LineaPedido lp = c.second;

		precio += lp.precio_venta() * lp.cantidad();
		total += lp.cantidad(); 

		os << lp << "\t\t" << pp->fecha() << "\n";
	}

	os << "================================================================================\n";

	os << std::setprecision(2) << precio << " €\t" << total << std::endl;

	return os;

}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
	Fecha hoy;
	double total = 0; 

	for(auto c : directa_)
	{
		Pedido* pe = c.first;
		ItemsPedido IP = c.second;

		if(pe->fecha() <= hoy)
		{
			os << "Pedido núm." << pe->numero() << "\n";
			os << "Cliente: " << pe->tarjeta()->titular()->nombre() << "\t";
			os << "Fecha: " << pe->fecha() << "\n" << IP;
		}
		total += pe->total();

	}
	os <<  "TOTAL VENTAS\t "  << std::fixed << std::setprecision(2) << total << " €" << std::endl;

	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
	for(auto c : inversa_)
	{
		Articulo* pa = c.first;

		os << "Ventas de " << "[" << pa->referencia() << "] \"" << pa->titulo() << "\"\n" << c.second << "\n"; 
	}

	return os;
}
