#pragma once
#include "Filtro.h"
#include <cstdlib>
#include <string>


Filtro *CreateFilter(const char *filter) {
	Filtro *f = (Filtro*)malloc(sizeof(Filtro));
	f->Caracteres = (char*)filter;
	f->Lenght = strlen(filter);
	return f;
}
int IsInFilter(Filtro * filter, char letter) {
	for (int i = 0; i < filter->Lenght; i++) {
		if (filter->Caracteres[i] == letter) {
			return true;
		}
	}
	return false;
}