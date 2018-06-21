#pragma once

struct Cadeia {
	char *Dna;
	char *Compactado;
	int SizeDna;
	int SizeCompactado;
};


Cadeia *CriaCadeia(char *input, int index);

Cadeia *CadeiaPrimeiroeUltimoDiferentes(char *c, int eofindex, int *nextIndex);
Cadeia *CadeiaEhPalindromo(char *c, int eof, int *nextIndex, int poscheck);
Cadeia *CadeiaUmDiferente(char *c, int eofindex, int *nextIndex);
Cadeia *CadeiaPar(char *c, int eofindex, int *nextIndex);
Cadeia *CadeiaTudoIgual(char *c, int eofindex, int *nextIndex);
Cadeia *CadeiaMetadeIgual(char *c, int eofindex, int *nextIndex);
Cadeia *CadeiaDuplaIgual(char *c, int eofindex, int *nextIndex);