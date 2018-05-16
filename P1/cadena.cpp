#include "cadena.hpp"

using namespace std;

Cadena::Cadena(size_t t, char s) noexcept
{
	s_ = new char[t+1];
	tam_ = t;
	for(size_t i = 0; i < tam_; i++)
	{
		s_[i] = s;
	}
	s_[tam_] = '\0';

}

Cadena::Cadena(const Cadena& cad) noexcept
{
	tam_ = cad.tam_;
	s_ = new char[cad.tam_ + 1];
	size_t i;
	for(i = 0; i < cad.tam_; i++)
	{
		s_[i] = cad.s_[i];
	}
	s_[i] = '\0';
}

Cadena::Cadena(Cadena&& cad) noexcept:s_(cad.s_), tam_(cad.tam_)
{
	cad.s_ = nullptr;
	cad.tam_ = 0;

}

Cadena::Cadena(const char* s) noexcept
{ 
	tam_ = strlen(s);
	s_ = new char[strlen(s) + 1];
	size_t i;
	for(i = 0; i < strlen(s); i++)
	{
		s_[i] = s[i];
	}
	s_[i] = '\0';
}


Cadena::~Cadena() noexcept
{
	delete[] s_;
}

Cadena& Cadena::operator =(const Cadena& cad) noexcept
{ 
	if(this != &cad){
		tam_ = cad.tam_;
		delete[] s_;
		s_ = new char[cad.tam_ + 1];
		size_t i;
		for(i = 0; i < strlen(cad.c_str()); i++)
		{
			s_[i] = cad[i];
		}
		s_[i] = '\0';
	}
	
	return *this;	
}

Cadena& Cadena::operator =(Cadena&& cad) noexcept
{
	if(this != &cad){
		delete[] s_;

		s_ = cad.s_;
		tam_ = cad.tam_;

		cad.s_ = nullptr;
		cad.tam_ = 0;
	}
	
	return *this;
}

Cadena& Cadena::operator =(const char* cad) noexcept
{

	tam_ = strlen(cad);
	delete[] s_;
	s_ = new char[tam_ + 1];
	size_t i;
	for(i = 0; i < strlen(cad); i++)
	{
		s_[i] = cad[i];
	}
	s_[i] = '\0';

	return *this;

}

const char* Cadena::c_str() const noexcept
{
	return s_;

}

std::istream& operator >>(std::istream& is, Cadena& cad)  noexcept
{
	char* aux = new char[31];
	int i = 0;
	while(isspace(is.get()) && is.good()){}
	is.unget();
	
	while(i < 32 && !isspace(is.peek()) && is.good())
		aux[i++] = is.get();

	aux[i] = '\0';

	if(i != 0)
		cad = Cadena(aux);
	else
		cad = Cadena();

	delete[] aux;

 	return is;	
}

std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept
{
	os << cad.c_str();
	return os;
}


Cadena& Cadena::operator +=(const Cadena& cad) noexcept
{

	Cadena aux(*this);
	delete[] s_;
	tam_ += cad.tam_;
	s_ = new char[tam_ + 1];

	strcpy(s_, aux.s_);
	strcat(s_, cad.s_);

	return *this;
}

Cadena& Cadena::operator +=(const char* cad) noexcept
{
	Cadena aux(cad);
	return *this += aux;
}


Cadena operator +(const Cadena& A, const Cadena& B) noexcept
{
	Cadena aux{A};
	aux += B;
	return aux;
}

bool operator ==(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) == 0);
}

bool operator !=(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) != 0);
}

bool operator <(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) < 0);
}

bool operator >(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) > 0);
}

bool operator <=(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) <= 0);
}

bool operator >=(const Cadena& A, const Cadena& B) noexcept
{
	return (strcmp(A.c_str(), B.c_str()) >= 0);
}


char& Cadena::at(size_t indice)
{
	if(indice < tam_)
		return this->s_[indice];
	else
		throw out_of_range{"indice fuera de rango"};
}

char Cadena::at(size_t indice) const 
{
	if(indice < tam_)
		return this->s_[indice];
	else
		throw out_of_range{"indice fuera de rango"};
}

Cadena Cadena::substr(size_t indice, size_t tam) const
{
	if(indice < tam_)
	{
		if(tam_ - indice >= tam)
		{
			Cadena aux{tam};
			unsigned j;
			
			for(j = 0; j < tam; j++)
			{
				aux.s_[j] = s_[indice + j];
			}
			aux.s_[j] = '\0';

			return aux;
		}
		else
			throw out_of_range{"Error. La subcadena pedida se sale de los limites de la cadena."};
	}
	else
		throw out_of_range{"Error. Posicion inicial despues del ultimo caracter."};
}

