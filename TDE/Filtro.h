#pragma once
#include <stdio.h>
#include <stdlib.h>

struct Filtro {
	char * Caracteres;
	int Lenght;
};


Filtro *CreateFilter(const char *filter);
int IsInFilter(Filtro * filter, char letter);