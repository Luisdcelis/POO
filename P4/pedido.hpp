#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <iostream>
#include <utility>
#include <iomanip>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"


class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
	Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& us, const Tarjeta& tar, const Fecha& fp = Fecha());

	int numero() const {return num_;}
	const Tarjeta* tarjeta() const {return tarjeta_;}
	Fecha fecha() const {return fecha_;}
	double total() const {return total_;}
	static int n_total_pedidos() {return N_pedidos;}


		//Clase de excepcion VACIO

	class Vacio
	{
	public:
		Vacio(Usuario& us):up_(&us){}
		Usuario& usuario() const {return *up_;}
	private:
		Usuario* up_;
	};

		//Clase de excepcion IMPOSTOR

	class Impostor
	{
	public:
		Impostor(Usuario& us):up_(&us){}
		Usuario& usuario() const {return *up_;}
	private:
		Usuario* up_;
	};

		//Clase de excepcion SINSTOCK

	class SinStock
	{
	public:
		SinStock(Articulo& ar):ap_(&ar){}
		Articulo& articulo() const {return *ap_;}
	private:
		Articulo* ap_;
	};



private:
	static int N_pedidos;
	int num_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& pe);

#endif