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

Cadena::operator const char*() const
{
	return s_;
}

size_t Cadena::length()
{
	return tam_;
}

Cadena& Cadena::operator +=(const Cadena& cad)
{

	Cadena aux = *this;
	delete[] s_;
	tam_ += cad.tam_;
	s_ = new char[cad.tam_ + 1];

	strcpy(s_, aux.s_);
	strcat(s_, cad.s_);

	return *this;
}

Cadena Cadena::operator +(const Cadena& cad)
{
	Cadena aux{*this};
	aux += cad;
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
	if(indice >= 0 && indice < tam_)
		return s_[indice];
	else
		throw out_of_range("indice fuera de rango");
}

char Cadena::at(size_t indice) const 
{
	if(indice >= 0 && indice < tam_)
		return s_[indice];
	else
		throw out_of_range("indice fuera de rango");
}

Cadena Cadena::substr(size_t indice, size_t tam)
{
	size_t j = 0;
	Cadena aux(indice);

	for(size_t i = indice; i < (tam + indice); i++)
	{
		aux[j] = this->at(i);
		j++;
	}

	return aux;
}


