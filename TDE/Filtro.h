#pragma once
#include <cstdio>
#include <cstdlib>


struct Filtro {
	char * Caracteres;
	int Lenght;
};


Filtro *CreateFilter(const char *filter);
int IsInFilter(Filtro * filter, char letter);