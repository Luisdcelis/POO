#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iterator>

using namespace std;

class Cadena
{
public:
	explicit Cadena(size_t t = 0, char s = ' ') noexcept;
	Cadena(const Cadena& cad) noexcept;
	Cadena(Cadena&& cad) noexcept;
	Cadena(const char* s) noexcept;
	~Cadena() noexcept;
	Cadena& operator =(const Cadena& cad) noexcept;
	Cadena& operator =(Cadena&& cad) noexcept;
	Cadena& operator =(const char* cad) noexcept;

	const char* c_str() const noexcept;

	typedef	 char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin()  noexcept{return s_;};
	iterator end()  noexcept{return s_ + tam_;};
	const_iterator begin() const  noexcept{return s_;};
	const_iterator end() const  noexcept{return s_ + tam_;};
	const_iterator cbegin() const  noexcept{return begin();};
	const_iterator cend() const  noexcept{return end();};
	reverse_iterator rbegin()  noexcept{return reverse_iterator(end());};
	reverse_iterator rend()  noexcept{return reverse_iterator(begin());};
	const_reverse_iterator rbegin() const  noexcept{return const_reverse_iterator(end());};
	const_reverse_iterator rend() const  noexcept{return const_reverse_iterator(begin());};
	const_reverse_iterator crbegin() const  noexcept{return  const_reverse_iterator(end());};
	const_reverse_iterator crend() const  noexcept{return const_reverse_iterator(begin());};

	size_t length() const noexcept;
	Cadena& operator +=(const Cadena& cad) noexcept;
	Cadena& operator +=(const char* cad) noexcept;

	char& operator [](size_t indice) noexcept;
	char operator [](size_t indice) const noexcept;
	char& at(size_t indice);
	char at(size_t indice) const;

	Cadena substr(size_t indice, size_t tam) const;


private:
	char* s_;  //terminado con caracter terminador
	size_t tam_;
};

Cadena operator +(const Cadena& A, const Cadena& B) noexcept;

bool operator ==(const Cadena& A, const Cadena& B) noexcept;
bool operator !=(const Cadena& A, const Cadena& B) noexcept;
bool operator <(const Cadena& A, const Cadena& B) noexcept;
bool operator >(const Cadena& A, const Cadena& B) noexcept;
bool operator <=(const Cadena& A, const Cadena& B) noexcept;
bool operator >=(const Cadena& A, const Cadena& B) noexcept;

std::istream& operator >>(std::istream& is, Cadena& cad) noexcept;
std::ostream& operator <<(std::ostream& os, const Cadena& cad) noexcept;

inline size_t Cadena::length() const  noexcept{return tam_;}
inline char& Cadena::operator [](size_t indice)  noexcept{return s_[indice];}
inline char Cadena::operator [](size_t indice) const  noexcept{return s_[indice];}

namespace std {
	template <> struct hash<Cadena> {
		size_t operator()(const Cadena& cad) const
		{ // conversión const char* ->string
			return hash<string>{}(cad.c_str());
		}
	};
}


#endif