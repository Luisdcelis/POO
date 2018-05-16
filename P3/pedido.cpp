#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos = 0; 	//contador de pedidos

Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& u, const Tarjeta& t, const Fecha& fp)
	:num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
	if(u.n_articulos() == 0)
		throw Vacio(u); 							//Carrito vacio

	if(t.titular() != &u)
		throw Impostor(u); 							//Tarjeta robada

	if(t.caducidad() < fp)
		throw Tarjeta::Caducada(t.caducidad()); 	//Tarjeta caducada


	for(auto c : u.compra()) //c es pair<Articulo*, unsigned (cantidad)>   	Este for es para mirar si hay stock de todos los articulos 
	{
		if(c.first->stock() < c.second) //no hay bastante stock en el armasén
		{
			const_cast<Usuario::Articulos&>(u.compra()).clear(); //necesitamos quitar el const que nos devuelve u.compra()
			throw SinStock(*c.first);				//Sin stock, c.first es el Articulo*; *c.first es el Articulo
		}
	}

	Usuario::Articulos carroAux = u.compra(); //Hacemos esto pq si leemos y borramos en el mismo contenedor, al borrar elementos
											  //Los iteradores fallan entonces nos creamos este carro auxiliar para leer y borramos
											  //En el nuestro

	for(auto c : carroAux) //												Este for es para restar la cantidad de articulos que nos llevamos
	{
		Articulo* pa = c.first;
		unsigned int cantidad = c.second;
		double precio = pa->precio();

		pa->stock() -= cantidad; 

		pe_art.pedir(*this, *pa, precio, cantidad);
		total_ += precio * cantidad;
		u.compra(*pa, 0);
	}
	us_pe.asocia(u, *this);
	++N_pedidos;
}

std::ostream& operator <<(std::ostream& os, const Pedido& pe)
{
	os << "Núm. pedido: " << pe.numero() << "\n";
	os << "Fecha:       " << pe.fecha() << "\n";
	os << "Pagado con:  " << *pe.tarjeta() << "\n";
	os << "Importe:" << std::fixed << std::setprecision(2) << pe.total() << " €";
	return os;

}