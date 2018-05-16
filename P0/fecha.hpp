#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <ctime>

using namespace std;

class Fecha
{
public:
	explicit Fecha(int dia = 0, int mes = 0, int anno = 0);	
	//explicit Fecha(const Fecha& fech);
	Fecha(const char* c);
	int dia() const;
	int mes() const;
	int anno() const;
	//Fecha& operator =(const Fecha& a);
	Fecha& operator +=(int n);
	Fecha& operator -=(int n);
	Fecha operator +(int n) const; 
	Fecha operator -(int n) const;
	Fecha operator ++(int);  //i++
	Fecha& operator ++();	 //++i
	Fecha operator --(int);
	Fecha& operator --();

	operator const char*() const; 

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
	tm* tiempo_descompuesto() const;

};


bool operator ==(const Fecha& A, const Fecha& F);
bool operator <(const Fecha& A, const Fecha& F);
bool operator !=(const Fecha& A, const Fecha& F);
bool operator >(const Fecha& A, const Fecha& F);
bool operator <=(const Fecha& A, const Fecha& F);
bool operator >=(const Fecha& A, const Fecha& F);

inline int Fecha::dia() const
{
	return d_;
}

inline int Fecha::mes() const
{
	return m_;
}

inline int Fecha::anno() const
{
	return a_;
}

#endif 