#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"
#include "tarjeta.hpp"
#include <stdlib.h>
#include <ctime>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
extern "C" 
{
	#include <unistd.h>
}

class Numero;
class Tarjeta;

class Clave
{
public:
	Clave(const char* contra);
	const Cadena& clave() const;
	bool verifica(const char* contra) const;

	enum Razon {CORTA, ERROR_CRYPT};

	class Incorrecta
	{
	public: 
		Incorrecta(const Razon error):razon_(error){}
		Razon razon() const {return razon_;}
	private:
		const Razon razon_;
	};

private:
	Cadena clave_;
};

class Usuario
{
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;
	typedef std::unordered_set<Cadena> Usuarios;

	Usuario(const Cadena& id, const Cadena& nom, const Cadena& ape, const Cadena& dir, const Clave& passwd);
	Usuario(const Usuario& user) = delete;
	Usuario operator =(const Usuario& user) = delete;

	const Cadena& id() const {return id_;};
	const Cadena& nombre() const {return nombre_;};
	const Cadena& apellidos() const {return apell_;};
	const Cadena& direccion() const {return dir_;};
	const Tarjetas& tarjetas() const {return tarjetas_;};

	void es_titular_de(Tarjeta& tar);
	void no_es_titular_de(Tarjeta& tar);

	void compra(Articulo& art, unsigned int cantidad = 1);
	const Articulos& compra() const {return carrito_;}
	size_t n_articulos() const;

	friend std::ostream& operator <<(std::ostream& os, const Usuario& user);

	class Id_duplicado
	{
	public:
		Id_duplicado(const Cadena& idd):idd_(idd){}
		Cadena idd() const {return idd_;};

	private:
		Cadena idd_;
	};

	~Usuario();

private:
	Cadena id_, nombre_, apell_, dir_;
	Clave contra_;
	Tarjetas tarjetas_;
	Articulos carrito_;
	static Usuarios identificadores;
};

std::ostream& operator <<(std::ostream& os, const Usuario& user);
std::ostream& mostrar_carro(std::ostream& os, const Usuario& user);






#endif