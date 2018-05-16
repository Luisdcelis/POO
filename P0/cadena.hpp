#ifndef CADENA_HPP_
#define CADENA_HPP_

using namespace std;

class Cadena
{
public:
	explicit Cadena(size_t t = 0, char s = ' ');
	Cadena(const char* s);
	Cadena(const Cadena& cad);
	~Cadena();
	Cadena& operator =(const Cadena& cad);
	Cadena& operator =(const char* cad);

	operator const char*() const; 

	size_t length() const;
	Cadena& operator +=(const Cadena& cad);

	Cadena& operator +=(const char* cad);

	char& operator [](size_t indice);
	char operator [](size_t indice) const;
	char& at(size_t indice);
	char at(size_t indice) const;

	Cadena substr(size_t indice, size_t tam) const;


private:
	char* s_;  //terminado con caracter terminador
	size_t tam_;
};

Cadena operator +(const Cadena& A, const Cadena& B);

bool operator ==(const Cadena& A, const Cadena& B);
bool operator !=(const Cadena& A, const Cadena& B);
bool operator <(const Cadena& A, const Cadena& B);
bool operator >(const Cadena& A, const Cadena& B);
bool operator <=(const Cadena& A, const Cadena& B);
bool operator >=(const Cadena& A, const Cadena& B);


#endif