#include <iostream>
#include <string.h>
#include <stdio.h>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(size_t t, char s)
{
	s_ = new char[t+1];
	tam_ = t;
	for(int i = 0; i < tam_; i++)
	{
		s_[i] = s;
	}
	s_[tam_] = '\0';

}

Cadena::Cadena(const Cadena& cad)
{
	tam_ = cad.tam_;
	s_ = new char[cad.tam_ + 1];
	int i;
	for(i = 0; i < cad.tam_; i++)
	{
		s_[i] = cad.s_[i];
	}
	s_[i] = '\0';
}

Cadena::Cadena(const char* s)
{
	tam_ = strlen(s);
	s_ = new char[strlen(s) + 1];
	int i;
	for(i = 0; i < strlen(s); i++)
	{
		s_[i] = s[i];
	}
	s_[i] = '\0';
}

Cadena::~Cadena()
{
	delete[] s_;
}

Cadena& Cadena::operator =(const Cadena& cad)
{
	if(this != &cad){
		tam_ = cad.tam_;
		delete[] s_;
		s_ = new char[cad.tam_ + 1];
		int i;
		for(i = 0; i < strlen(cad); i++)
		{
			s_[i] = cad[i];
		}
		s_[i] = '\0';
	}
	
	return *this;	
}

Cadena& Cadena::operator =(const char* cad)
{

	tam_ = strlen(cad);
	delete[] s_;
	s_ = new char[tam_ + 1];
	int i;
	for(i = 0; i < strlen(cad); i++)
	{
		s_[i] = cad[i];
	}
	s_[i] = '\0';

	return *this;

}

Cadena::operator const char*() const
{
	return s_;
}

size_t Cadena::length() const
{
	return tam_;
}

Cadena& Cadena::operator +=(const Cadena& cad)
{

	Cadena aux(*this);
	delete[] s_;
	tam_ += cad.tam_;
	s_ = new char[tam_ + 1];

	strcpy(s_, aux.s_);
	strcat(s_, cad.s_);

	return *this;
}

Cadena& Cadena::operator +=(const char* cad)
{
	Cadena aux(cad);
	return *this += aux;
}


Cadena operator +(const Cadena& A, const Cadena& B)
{
	Cadena aux{A};
	aux += B;
	return aux;
}

bool operator ==(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) == 0);
}

bool operator !=(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) != 0);
}

bool operator <(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) < 0);
}

bool operator >(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) > 0);
}

bool operator <=(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) <= 0);
}

bool operator >=(const Cadena& A, const Cadena& B)
{
	return (strcmp(A, B) >= 0);
}

char& Cadena::operator [](size_t indice)
{
	return s_[indice];
}

char Cadena::operator [](size_t indice) const
{
	return s_[indice];
}

char& Cadena::at(size_t indice)
{
	if(indice < tam_ && indice >= 0)
		return this->s_[indice];
	else
		throw out_of_range{"indice fuera de rango"};
}

char Cadena::at(size_t indice) const 
{
	if(indice < tam_ && indice >= 0)
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

