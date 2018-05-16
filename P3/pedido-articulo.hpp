#ifndef PED_AR_HPP_
#define PED_AR_HPP_

#include <iostream>
#include <map>
#include <utility>

#include "pedido.hpp"
#include "articulo.hpp"

class LineaPedido;
class Pedido;

struct OrdenaPedidos: public std::binary_function <Pedido*,Pedido*,bool>
{
	bool operator()(const Pedido* ped1, const Pedido* ped2) const { return ped1->numero() < ped2->numero() ;};
};

struct OrdenaArticulos: public std::binary_function<Articulo*,Articulo*,bool>
{
	bool operator()(const Articulo* art1, const Articulo* art2) const { return art1->referencia() < art2->referencia() ;};
};


class Pedido_Articulo
{
public:
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;


	void pedir(Pedido& pe, Articulo& ar, double precio, unsigned cantidad = 1);
	void pedir(Articulo& ar, Pedido& pe, double precio, unsigned cantidad = 1);

	ItemsPedido& detalle(Pedido& pe); 
	Pedidos ventas(Articulo& ar); 
	
	std::ostream& mostrarDetallePedidos(std::ostream& os);
	std::ostream& mostrarVentasArticulos(std::ostream& os);


private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa_;
	std::map<Articulo*, Pedidos, OrdenaArticulos> inversa_;
};

class LineaPedido
{
public:
	explicit LineaPedido(double p, unsigned int cant = 1):p_vnt_(p), cant_vnt_(cant){}
	double precio_venta() const {return p_vnt_;}
	size_t cantidad() const {return cant_vnt_;}

private:
	double p_vnt_;
	unsigned cant_vnt_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& LP);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pe);


#endif