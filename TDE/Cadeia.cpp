#include "Cadeia.h"
#include <stdio.h>
#include <stdlib.h>

Cadeia *CriaCadeia(char *input, int sizeOfCadeia, char *input2, int sizeofCompatacao) {
	Cadeia *c = (Cadeia*)malloc(sizeof(Cadeia));
	c->Dna = input;
	c->SizeDna = sizeOfCadeia;
	c->Compactado = input2;
	c->SizeCompactado = sizeofCompatacao;
	int i = 0;
	return c;
}

Cadeia *CadeiaDuplaIgual(char *c,int *nextIndex) {
	/*1.	Verificar se substring contém duplas iguais. */
	if (c[0] == c[2] == c[4]) {
		if (c[1] == c[3] == c[5]) {
			nextIndex[0] += 6;
			char *stringformatada = (char*)malloc(9 * sizeof(char));
			char *stringcompactada = (char*)malloc(4 * sizeof(char));
			sprintf(stringformatada, "(%c%c)(%c%c)(%c%c)", c[0], c[1], c[2], c[3]);
			sprintf(stringcompactada, "!%c%c", c[0], c[1]);
			return CriaCadeia(stringformatada,9,stringcompactada,4);
		}
	}
	return 0;
}

Cadeia *CadeiaMetadeIgual(char *c, int *nextIndex) {
	/*2.	Verificar se metade dos caracteres são iguais e depois se a outra metade são iguais e devolver um de cada repetição.*/
	if (c[0] == c[1] == c[2]) {
		if (c[3] == c[4] == c[5]) {
			nextIndex[0] += 6;
			char *stringformatada = (char*)malloc(11 * sizeof(char));
			char *stringcompactada = (char*)malloc(4 * sizeof(char));
			sprintf(stringformatada, "(%c%c%c)(%c%c%c)", c[0], c[1], c[2], c[3],c[4],c[5]);
			sprintf(stringcompactada, "$%c%c", c[0], c[3]);
			return CriaCadeia(stringformatada, 11, stringcompactada, 4);
		}
	}
	return 0;
}

Cadeia *CadeiaTudoIgual(char *c, int *nextIndex) {
	/*3.	Verificar se o k-mer é tudo igual, devolve só um caracter:*/
	if (c[0] == c[1] == c[2] == c[3] == c[4] == c[5]) {
		nextIndex[0] += 6;
		char *stringformatada = (char*)malloc(1 * sizeof(char));
		char *stringcompactada = (char*)malloc(3 * sizeof(char));
		stringformatada[0] = '\0';
		sprintf(stringcompactada, "~%c", c[0]);
		return CriaCadeia(stringformatada, 1, stringcompactada, 3);
	}
	return 0;
}

Cadeia *CadeiaPar(char *c, int *nextIndex) {
	/*4.	Verificar se todas as sequencias são pares iguais e devolve um para cada par.*/
	if (c[0] == c[1] && c[2] == c[3] && c[2] != c[1]) {
		nextIndex[0] += 6;
		char *stringformatada = (char*)malloc(9 * sizeof(char));
		char *stringcompactada = (char*)malloc(4 * sizeof(char));
		sprintf(stringformatada, "(%c%c)(%c%c)", c[0], c[0], c[1], c[1]);
		sprintf(stringcompactada, "%%%c%c", c[0], c[3]);
		return CriaCadeia(stringformatada, 9, stringcompactada, 4);
	}
	return 0;
}

Cadeia *CadeiaUmDiferente(char *c, int *nextIndex) {
	/*5.	Verificar se  k - 1 caracteres são iguais e um diferente.*/
	int cnta = 1;
	int cntb = 0;
	char letrab = 0;;
	for (int i = 1; i < 6; i++) {
		if (c[i] == c[0]) {
			cnta++;
		}
		else {
			if (letrab == 0) {
				letrab = c[i];
			}
			else if (letrab != c[i]) {
				break;
			}
			cntb++;
		}
	}
	if (abs(cnta - cntb) == 4) {
		nextIndex[0] += 6;
		int sizeofdna = 0;
		char *stringcompactada = (char*)malloc(4 * sizeof(char));
		char *stringformatada = 0;
		/*ex: TAAAAA = (T)(AAAAA) = bTA*/
		if (c[0] != c[1] && c[1] == c[2]) {
			sizeofdna = 11;
			stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c)(%c%c%c%c%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "b%c%c", c[0], c[1]);

		}
		/*ex : ATAAAA = (A)(T)(AAAA) = dAT*/
		else if (c[0] != c[1] && c[0] == c[2]) {
			sizeofdna = 13;
			stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c)(%c)(%c%c%c%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "d%c%c", c[0], c[1]);

		}
		/*ex : AATAAA = (AA)(T)(AAA) = eAT*/
		else if (c[0] != c[2] && c[0] == c[1]) {
			sizeofdna = 13;
			stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c%c)(%c)(%c%c%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "e%c%c", c[0], c[2]);
		}
		/*ex : AAATAA = (AAA)(T)(AA) = fAT*/
		else if (c[0] != c[3] && c[0] == c[1]) {
			sizeofdna = 13;
			stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c%c%c)(%c)(%c%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "f%c%c", c[0], c[3]);
		}
		/*ex : AAAATA = (AAAA)(T)(A) = hAT*/
		else if (c[0] != c[4] && c[0] == c[1]) {
			sizeofdna = 13;
			char *stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c%c%c%c)(%c)(%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "h%c%c", c[0], c[4]);

		}
		/*ex : AAAAAT = (AAAAA)(T) = iAT*/
		else {
			sizeofdna = 11;
			stringformatada = (char*)malloc(sizeofdna * sizeof(char));
			sprintf(stringformatada, "(%c%c%c%c%c)(%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
			sprintf(stringcompactada, "i%c%c", c[0], c[5]);
		}
		return CriaCadeia(stringformatada, sizeofdna, stringcompactada, 4);
	}
	return 0;
}

Cadeia *CadeiaPrimeiroeUltimoDiferentes(char *c, int *nextIndex) {
	/*6.	Verificar se todas os caracteres depois do primeiro e antes do último são iguais e devolve o primeiro, um da repetição e o último.*/
	if (c[0] != c[1] && c[1] == c[2] && c[2] == c[3] && c[3] == c[4] && c[4] != c[5]) {
		nextIndex[0] += 6;
		char *stringformatada = (char*)malloc(13 * sizeof(char));
		char *stringcompactada = (char*)malloc(5 * sizeof(char));
		sprintf(stringformatada, "(%c)(%c%c%c%c)(%c)", c[0], c[1], c[2], c[3], c[4], c[5]);
		sprintf(stringcompactada, "&%c%c%c", c[0], c[3],c[5]);
		return CriaCadeia(stringformatada, 13, stringcompactada, 5);
	}
	return 0;
}


Cadeia *CadeiaPalindromoImpar(char *c, int i) {
	/*7.	Verifica se o primeiro (grupo 1) e o terceiro (grupo 3) de caracteres são reversos e o grupo que está no centro (grupo 2), ou seja é um palíndromo ímpar.*/
	int sizeofdna = i*2/*Grupo 1 + 2*/+1/*Grupo 2*/+ 1 /*/0*/ + 6/* ()()()*/;
	char *stringformatada = (char*)malloc(sizeofdna * sizeof(char));
	char *stringcompactada = (char*)malloc((i+3) * sizeof(char));
	int j = 0;
	stringformatada[sizeofdna - 1] = '\0';
	stringcompactada[i + 2] = '\0';
	stringcompactada[0] = '*';
	stringformatada[0] = '(';
	stringformatada[sizeofdna - 2] = ')';
	while (j < i) {
		stringcompactada[j + 1] = c[j];
		stringformatada[1 + j] = c[j];
		//já validamos o palindromo então podemos aproveitar e inverter a partir dos dados iniciais.
		stringformatada[sizeofdna - 3 - j] = c[j];
		j++;
	}
	stringformatada[1 + j] = ')';
	stringformatada[sizeofdna - 3 - j] = '(';
	stringformatada[2 + j] = '(';
	stringformatada[sizeofdna - 4 - j] = ')';
	stringformatada[3 + j] = c[j];
	stringcompactada[j + 1] = c[j];
	return CriaCadeia(stringformatada, sizeofdna, stringcompactada, i+3);
}

Cadeia *CadeiaPalindromoPar(char *c, int i) {
	/*8.	Verifica se o primeiro (grupo 1) e o segundo (grupo 2) de caracteres são reversos, ou seja, é um palíndromo par.*/
	int sizeofdna = i * 2/*Grupo 1 + 2*/ + 1 /*/0*/ + 4/* ()()*/;
	char *stringformatada = (char*)malloc(sizeofdna * sizeof(char));
	char *stringcompactada = (char*)malloc((i + 2) * sizeof(char));
	int j = 0;
	stringformatada[sizeofdna - 1] = '\0';
	stringcompactada[i + 1] = '\0';
	stringcompactada[0] = '-';
	stringformatada[0] = '(';
	stringformatada[sizeofdna - 2] = ')';
	while (j < i) {
		stringcompactada[j + 1] = c[j];
		stringformatada[1 + j] = c[j];
		//já validamos o palindromo então podemos aproveitar e inverter a partir dos dados iniciais.
		stringformatada[sizeofdna - 3 - j] = c[j];
		j++;
	}
	stringformatada[1 + j] = ')';
	stringformatada[sizeofdna - 3 - j] = '(';
	return CriaCadeia(stringformatada, sizeofdna, stringcompactada, i + 2);
}

Cadeia *CadeiaEhPalindromo(char *c, int eof,int *nextIndex, int poscheck) {
	int i = 0;
	unsigned char ehpalindromo = 0;
	//etapa 1: acha o final do palindromo
	while (i < eof - 2) {
		if (c[i] == c[i + 2] && poscheck ==0) {
			ehpalindromo = 1;//palindromo impar
			break;
		}
		if (c[i] == c[i + 1] && poscheck == 1) {
			ehpalindromo = 2;//palindromo par
			break;
		}
		i++;
	}
	if (i < eof - 2) {
		//não chegamos ao final da string, logo existe a chance de ser um palindromo impar|par.
		//checar
		int j = 0;
		if (ehpalindromo == 1) {
			while (i - j >= 0 && i + 2 + j < eof) {
				if (c[i - j] != c[i + 2 + j]) {
					break;
				}
				j++;
			}
		}
		else {
			while (i - j >= 0 && i + j < eof) {
				if (c[i - j] != c[i + 1 + j]) {
					break;
				}
				j++;
			}
		}
		if (i - j != -1) {
			ehpalindromo = 0;
		}
		if (ehpalindromo == 1) {
			nextIndex[0] += (i + 1) *2+1;
			return CadeiaPalindromoImpar(c, (i + 1));
		}
		else if (ehpalindromo == 2) {
			nextIndex[0] += (i+1)*2;
			return CadeiaPalindromoPar(c, (i + 1));
		}
	}
	return 0;
}