#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <cstring>
#include <ctime>
#include <stdexcept>
#include <cstdio>

using namespace std;

class Fecha
{
public:
	explicit Fecha(int dia = 0, int mes = 0, int anno = 0);	
	Fecha(const Fecha& fech) = default;
	Fecha& operator =(const Fecha& fech) = default;
	Fecha(const char* c);
	int dia() const noexcept;
	int mes() const noexcept;
	int anno() const noexcept;
	//Fecha& operator =(const Fecha& a);
	Fecha& operator +=(int n);
	Fecha& operator -=(int n);
	Fecha operator +(int n) const ; 
	Fecha operator -(int n) const ; 
	Fecha operator ++(int);  //i++
	Fecha& operator ++();	 //++i
	Fecha operator --(int);
	Fecha& operator --();

	//operator const char*() const;
	const char* cadena() const;

	//friend std::istream& operator >>(std::istream& is, Fecha& f);
	//friend std::ostream& operator <<(std::ostream& os, const Fecha& f);

	static const int AnnoMaximo = 2037;
	static const int AnnoMinimo = 1902;

	class Invalida{
	public:
		Invalida(const char* c);
		const char* por_que() const;
	private:
		const char* error;
	};

private:
	int d_, m_, a_;
	void comprobaciones(int d, int m, int a);
	tm* tiempo_descompuesto() const noexcept;

};


bool operator ==(const Fecha& A, const Fecha& F) noexcept;
bool operator <(const Fecha& A, const Fecha& F) noexcept;
bool operator !=(const Fecha& A, const Fecha& F) noexcept;
bool operator >(const Fecha& A, const Fecha& F) noexcept;
bool operator <=(const Fecha& A, const Fecha& F) noexcept;
bool operator >=(const Fecha& A, const Fecha& F) noexcept;

std::istream& operator >>(std::istream& is, Fecha& f);
std::ostream& operator <<(std::ostream& os, const Fecha& f);

inline int Fecha::dia() const noexcept
{
	return d_;
}

inline int Fecha::mes() const noexcept
{
	return m_;
}

inline int Fecha::anno() const noexcept
{
	return a_;
}

#endif 