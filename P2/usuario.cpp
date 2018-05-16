#include <random>
#include <iomanip>
#include "usuario.hpp"
/*
class SNA 
{
public:
	SNA() {std::srand(std::time(nullptr));}
};

SNA sna;

Clave::Clave(const char* contra)
{
	Cadena contrasena{contra};
	if(contrasena.length() < 5)
		throw Incorrecta(CORTA);
	else
	{
		static const char *const seedchars ="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		char* seed = nullptr;

		seed[0] = seedchars[std::rand() % 64];
		seed[1] = seedchars[std::rand() % 64]; 

		const char* const pcc = crypt(contrasena.c_str(), seed);
		
		if(const char* const pcc = crypt(contrasena, seed))
			clave_ = pcc;
		else
			throw Incorrecta(ERROR_CRYPT)
		

		contrasena.~Cadena();
	}
}
*/

Clave::Clave(const char* key)
{
	if(std::strlen(key) < 5) throw Incorrecta(CORTA);				
	
  	static const char *const cv = "./0123456789"
  	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  	static const size_t longtd = sizeof(cv) - 1;					

  	static std::random_device r;
  	static std::uniform_int_distribution<size_t> distribucion(0, longtd - 1);		
  	const char salt[] = {cv[distribucion(r)], cv[distribucion(r)]};
  		
  	if(const char *const pcc = crypt(key, salt)) clave_ = pcc;  		
	else throw Incorrecta(ERROR_CRYPT);
}

const Cadena& Clave::clave() const{return clave_;};

bool Clave::verifica(const char* contra) const
{
	if(const char *const pcc = crypt(contra, clave_.c_str())) 
		return (clave_ == pcc);
	throw Incorrecta(ERROR_CRYPT);		
}

Usuario::Usuarios Usuario::identificadores;


Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& ape, const Cadena& dir, const Clave& passwd):
				 id_(id), nombre_(nom), apell_(ape), dir_(dir), contra_(passwd)
{
	if(!identificadores.insert(id).second)
	{
		throw Id_duplicado(id_);
	}

}

void Usuario::es_titular_de(Tarjeta& tar)
{
	if(this == tar.titular())
		tarjetas_.insert(make_pair(tar.numero(), &tar));
}

void Usuario::no_es_titular_de(Tarjeta& tar)
{
	tar.anula_titular();
	tarjetas_.erase(tar.numero());
}

void Usuario::compra(Articulo& art, unsigned int cantidad)
{
	if(cantidad == 0)
		carrito_.erase(&art);
	else
		carrito[&art] = cantidad;
}


size_t Usuario::n_articulos() const
{
	return carrito_.size();
}

std::ostream& operator <<(std::ostream& os, const Usuario& user)
{
	os << user.id() << " [" << user.contra_.clave() << "] " << user.nombre().c_str() << " " << user.apellidos() << "\n" << user.direccion() << "\nTarjetas:\n";

	

	for(auto it = user.tarjetas().begin(); it != user.tarjetas().end(); it++)
	{
		os << *it->second << "\n";	
	}

	return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
  os << "Carrito de compra de " << user.id() << " [Artículos: "<< user.n_articulos() << "]" << "\n"
  		<< "Cant.Artículo"<< std::endl
  		<< std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');

  		int stock = user.n_articulos() ;

  		while( stock > 0 )
  		{
  			for(auto const& pos : user.compra())  //for each
  			{
  				os << std::setw(4) << pos.second << "    "
  					<< " [" << (*pos.first).referencia() << "] " << "\""
  					<< (*pos.first).titulo() << "\", "
					<< (*pos.first).f_publi().anno()
					<< ". " << std::fixed << std::setprecision(2) << (*pos.first).precio() << " €" << std::endl;
  				--stock;
  			}

  		}

  	return os ;
}



Usuario::~Usuario()
{
	Tarjetas::iterator it;

	for(it = tarjetas_.begin(); it != tarjetas_.end(); it++)
	{
		it->second->anula_titular();	
	}

	identificadores.erase(id_);
}



