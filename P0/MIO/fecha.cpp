#include <iostream>
#include <ctime>
#include <stdio.h>
#include "Fecha.hpp"

using namespace std;

tm* Fecha::tiempo_descompuesto() const
{
	tm* t = {0};
	time_t tiempo_calendario = time(nullptr); 
	t = localtime(&tiempo_calendario);
 	return t;
}

int bisiesto(int a)
{
	return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobaciones(int day, int month, int year)
{

	static int diames[13] = {0, 31, 28 + bisiesto(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

	if(day > diames[month] || day < 0)
		throw Invalida("DIA INVALIDO");

	if(month < 1 || month > 12)
		throw Invalida("MES INVALIDO"); 

	if(year < Fecha::AnnoMinimo || year > Fecha::AnnoMaximo)
		throw Invalida("ANNO INVALIDO"); 
}




Fecha::Fecha(int dia, int mes, int anno):d_(dia), m_(mes), a_(anno){

	if(d_ == 0 || m_ == 0 || a_ == 0)
		tm* tiempo_descompuesto = Fecha::tiempo_descompuesto();

	if(d_ == 0)
		d_ = tiempo_descompuesto->tm_mday;
	
	if(m_ == 0)
		m_ = tiempo_descompuesto->tm_mon + 1;

	if(a_ == 0)
		a_ = tiempo_descompuesto->tm_year + 1900;

	comprobaciones(d_, m_, a_);	
}


Fecha& Fecha::operator =(const Fecha& a){
	if(this != &a){
		d_ = a.d_;
		m_ = a.m_;
		a_ = a.a_;
	}
	return *this;
}

Fecha::Fecha(const char* c){
	int dia, mes, anno;

	sscanf(c, "%d/%d/%d", &dia, &mes, &anno);

	Fecha aux(dia, mes, anno);

	d_ = aux.d_;
	m_ = aux.m_;
	a_ = aux.a_;	
}

Fecha::Invalida::Invalida(const char* c):error(c){}

const char* Fecha::Invalida::por_que() const
{
	return error;
}

Fecha& Fecha::operator +=(int n)
{
	tm f = {0};
	f.tm_mday = d_ + n;
	f.tm_mon = m_ - 1;
	f.tm_year = a_ - 1900;

	mktime(&f);

	d_ = f.tm_mday;
	m_ = f.tm_mon + 1;
	a_ = f.tm_year + 1900;

	return *this;

}

Fecha& Fecha::operator -=(int n)
{
	return *this += (-n);
}

Fecha Fecha::operator +(int n) const 
{
	Fecha aux{*this};
	return (aux += n);
}

Fecha Fecha::operator -(int n) const 
{
	Fecha aux{*this};
	return (aux += (-n));
}

Fecha Fecha::operator ++(int)
{
	Fecha aux{*this};
	*this += 1;
	return aux;
}

Fecha& Fecha::operator ++()
{
	return *this += 1;
}

Fecha Fecha::operator --(int)
{
	Fecha aux{*this};
	*this += (-1);
	return aux;
}

Fecha& Fecha::operator --()
{
	return *this += (-1);
}


bool operator ==(const Fecha& A, const Fecha& F)
{
	return (A.dia() == F.dia() && A.mes() == F.mes() && A.anno() == F.anno());
}

bool operator <(const Fecha& A, const Fecha& F)
{
	if(A.anno() < F.anno())
		return true;
	else
	{
		if(A.anno() > F.anno())
			return false;
		else
		{
			if(A.mes() < F.mes())
				return true;
			else
			{
				if(A.mes() > F.mes())
					return false;
				else
				{
					if(A.dia() < F.dia())
						return true;
					else
						return false;
				}
			}
		}
	}
}

bool operator !=(const Fecha& A, const Fecha& F)
{
	return !(A == F);
}

bool operator >(const Fecha& A, const Fecha& F)
{
	return (F < A);
}

bool operator <=(const Fecha& A, const Fecha& F)
{
 	return !(F < A);
}

bool operator >=(const Fecha& A, const Fecha& F)
{
	return !(A < F);
}

Fecha::operator const char*() const
{
	static char s[40];

	const char* diasem[7] = {
		"domingo",
		"lunes",
		"martes", 
		"miercoles", 
		"jueves",
		"viernes",
		"sabado"
	};

	const char* meses[12] = { 
		"enero",
		"febrero", 
		"marzo",
		"abril",
		"mayo", 
		"junio", 
		"julio", 
		"agosto",
		"septiembre",
		"octubre",
		"noviembre",
		"diciembre"
	};

	tm f = {0};
	f.tm_mday = d_;
	f.tm_mon = m_ - 1;
	f.tm_year = a_ - 1900;

	mktime(&f);

	sprintf(s, "%s %d de %s de %d", diasem[f.tm_wday], d_, meses[f.tm_mon], a_);

	return s;
}



