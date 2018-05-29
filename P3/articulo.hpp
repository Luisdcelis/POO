#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo
{
public:

	Articulo(const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre, unsigned stk):cod_(cod), titulo_(tit), publicacion_(pub), precio_(pre), stock_(stk){};

	Cadena referencia() const {return cod_;};
	Cadena titulo() const {return titulo_;};
	Fecha f_publi() const {return publicacion_;};
	double precio() const {return precio_;};
	double& precio() {return precio_;};
	unsigned stock() const {return stock_;};
	unsigned& stock() {return stock_;};

	
private:
	Cadena cod_;
	Cadena titulo_;	
	Fecha publicacion_; 	
	double precio_;
	unsigned stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& A);




#endif