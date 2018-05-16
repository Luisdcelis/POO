#ifndef USU_PED_HPP_
#define USU_PED_HPP_

#include <set>
#include <map>
#include <utility>
#include <iostream>
#include "usuario.hpp"
#include "pedido.hpp"


class Usuario_Pedido
{
public:
	typedef set<Pedido*> Pedidos;

	void asocia(Usuario& us, Pedido& pe);
	void asocia(Pedido& pe, Usuario& us);


	Pedidos pedidos(Usuario& us) const {return directa_.at(&us);}
	Usuario* cliente(Pedido& pe) const {return inversa_.find(&pe)->second;}
	

private:
	map<Usuario*, Pedidos> directa_;
	map<Pedido*, Usuario*> inversa_;

};

inline void Usuario_Pedido::asocia(Usuario& us, Pedido& pe)
{
	directa_[&us].insert(&pe);
	inversa_[&pe] = &us;
}

inline void Usuario_Pedido::asocia(Pedido& pe, Usuario& us)
{
	asocia(us, pe);
}

/*Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& us) const
{
	return directa_.at(&us);
}

Usuario* Usuario_Pedido::cliente(Pedido& pe) const
{
	return inversa_.find(&pe)->second;
}*/	

#endif