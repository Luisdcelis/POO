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


	Usuario::Articulos carroAux = u.compra(); //Hacemos esto pq si leemos y borramos en el mismo contenedor, al borrar elementos
											  //Los iteradores fallan entonces nos creamos este carro auxiliar para leer y borramos
											  //En el nuestro

	bool pedido_final_vacio = true;

	for(auto c : carroAux) //Este for es para restar la cantidad de articulos que nos llevamos
	{
		Articulo* pa = c.first;
		unsigned int cantidad = c.second;
		if(ArticuloAlmacenable* const aa = dynamic_cast<ArticuloAlmacenable* const>(pa))  //es un articulo almacenable?
		{
			if(aa->stock() < cantidad)
			{
				const_cast<Usuario::Articulos&>(u.compra()).clear(); 
				throw SinStock(*c.first);
			}
			else
			{
				double precio = aa->precio();

				aa->stock() -= cantidad; 

				pe_art.pedir(*this, *aa, precio, cantidad);
				total_ += precio * cantidad;

				pedido_final_vacio = false;
			}

		}
		else
		{
			if(LibroDigital* const ld = dynamic_cast<LibroDigital* const>(pa))
			{
				if(ld->f_expir() > fp)
				{
					total_ += ld->precio() * cantidad;
					pe_art.pedir(*this, *ld, ld->precio(), cantidad);

					pedido_final_vacio = false;
				}
			}
			else 
			{
				throw std::logic_error("Pedido::Pedido error, tipo de Articulo desconocido");
			}
		}

		u.compra(*(c.first), 0);
	}

	if(pedido_final_vacio)
		throw Vacio(u);

	us_pe.asocia(u, *this);
	++N_pedidos;
}

std::ostream& operator <<(std::ostream& os, const Pedido& pe)
{
	os << "Núm. pedido: " << pe.numero() << "\n";
	os << "Fecha:       " << std::setfill(' ') << std::setw(6) << pe.fecha() << "\n";
	os << "Pagado con:  " << pe.tarjeta()->tipo() << " n.º: " << pe.tarjeta()->numero() << "\n";
	os << "Importe:" << std::setfill(' ') << std::setw(4) << pe.total() << " €";
	return os;

}

 