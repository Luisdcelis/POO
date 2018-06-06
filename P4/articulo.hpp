#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"

class Autor;

class Articulo
{
public:

	typedef std::set<Autor*> Autores;

	class Autores_vacios{};

	Articulo(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre);

	Cadena referencia() const {return cod_;};
	Cadena titulo() const {return titulo_;};
	Fecha f_publi() const {return publicacion_;};
	double precio() const {return precio_;};
	double& precio() {return precio_;};

	const Autores& autores() const {return autores_;};

	virtual void impresion_especifica(std::ostream& os) const = 0;

	virtual ~Articulo(){}
	
private:
	Cadena cod_;
	Cadena titulo_;	
	Fecha publicacion_; 	
	double precio_;

	const Autores autores_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& A);

class Autor
{
public:
	Autor(const Cadena& nom, const Cadena& ape, const Cadena& dir)noexcept :nombre_(nom), apellidos_(ape), direccion_(dir){}

	Cadena nombre() const noexcept{return nombre_;}
	Cadena apellidos() const noexcept{return apellidos_;}
	Cadena direccion() const noexcept{return direccion_;}

private:
	Cadena nombre_, apellidos_, direccion_;
};

class LibroDigital: public Articulo
{
public:
	LibroDigital(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre, const Fecha& f_expir): 
				Articulo(aut, cod, tit, pub, pre), f_expir_(f_expir){}
	Fecha f_expir() const {return f_expir_;}
	void impresion_especifica(std::ostream&) const;

private:
	const Fecha f_expir_;

};


class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre, unsigned stk = 0): 
						Articulo(aut, cod, tit, pub, pre), stock_(stk){}
	unsigned stock() const {return stock_;};
	unsigned& stock() {return stock_;};

	virtual ~ArticuloAlmacenable(){}

protected:
	unsigned stock_;
	
};


class Libro: public ArticuloAlmacenable
{
public:
	Libro(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre, unsigned n_pag, unsigned stock = 0):ArticuloAlmacenable(aut, cod, tit, pub, pre, stock), n_pag_(n_pag){}
	const unsigned n_pag() const{return n_pag_;}
	void impresion_especifica(std::ostream&) const;


protected:
	const unsigned n_pag_;
};


class Cederron: public ArticuloAlmacenable
{
public:
	Cederron(const Autores& aut, const Cadena& cod, const Cadena& tit, const Fecha& pub, double pre, unsigned tam, unsigned stock = 0):ArticuloAlmacenable(aut, cod, tit, pub, pre, stock), tam_(tam){}
	const unsigned tam() const{return tam_;}
	void impresion_especifica(std::ostream&) const;


protected:
	const unsigned tam_;
};

#endif
