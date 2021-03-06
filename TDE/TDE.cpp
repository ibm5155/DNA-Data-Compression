	// TDE.cpp : define o ponto de entrada para o aplicativo do console.
//
#include <cstdio>
#include <cstdlib>
#include <string>
#include "Texto.h"
#include "Filtro.h"
#include "Cadeia.h"

void RemoveCharAt(char *c, int pos, int len) {
	strcpy(&c[pos], &c[pos + 1]);
}

char *AddString(char *destiny, char *src) {
	int a = 0;
	int b = strlen(src);
	char *neww;
	if (destiny == 0) {
		neww = (char*)malloc((a + b + 1) * sizeof(char));
	}
	else {
		a = strlen(destiny);
		neww = (char*)realloc(destiny, (a + b + 1) * sizeof(char));
	}
	strcpy(&neww[a], src);
	return neww;
}


Cadeia **AdicionaListaCadeia(Cadeia **lista,int tamanho, Cadeia *dado) {
	lista = (Cadeia**)realloc(lista, (tamanho + 1) * sizeof(Cadeia*));
	lista[tamanho] = dado;
	return lista;
}

int main()
{
	char f[] = "fasta_example.txt";
	Texto *t = CarregaTexto(f);
	Filtro *filtro = CreateFilter("ATCG>");
	int ponteiro = 0;
	char *buffer = 0;
	char *dnafiltrado = 0;
	int i = 1;
	int j = 0;
	int sizeofbuffer = 0;
	//etapa 1: separar cabeçalho e remover caracteres que não estão contidos no filtro
	FILE *cabecalho = fopen("cabecalho", "w");
	for (; i < t->QntLinhas; i++) {
		buffer = AddString(buffer,t->Linhas[ponteiro++].Caracteres);
		if (buffer) {
			if (buffer[0] == '>') {
				fprintf(cabecalho, "%s\n", buffer);
				//achamos o outro carinha
				free(buffer);
				buffer = 0;
			}
			else {
				sizeofbuffer = strlen(buffer);
				for (j = 0; j < sizeofbuffer; j++) {
					if (false == IsInFilter(filtro, buffer[j])) {
						RemoveCharAt(buffer, j, t->Linhas[ponteiro - 1].QntCaracteres);
						j--;
						sizeofbuffer--;
					}
				}
				dnafiltrado = AddString(dnafiltrado, buffer);
				free(buffer);
				buffer = 0;
			}
		}
	}
	fclose(cabecalho);
	//etapa 2: calcular entropia

	//etapa 3: transformar
	Cadeia *cadeiatmp;
	Cadeia **listacadeias = (Cadeia**)malloc(sizeof(Cadeia*));
	int sizeoflistacadeias = 0;
	int fim = strlen(dnafiltrado);
	int debug = 0;
	i = 0;
	/* 3*8*N + 2*9*N + 82*N + 3N(N² + N) - 4N */
	/*  24N  + 18N + 82N -4N +3N(N² + N)*/
	/*  24N + 100N -4N +3N³ + 3N²*/
	/* 120N + 3N³ + 3N²*/
	/* O(n³)*/
 	while (i < fim) { // N
		cadeiatmp = CadeiaTudoIgual(&dnafiltrado[i], fim, &i);/*8*N*/
		if (!cadeiatmp) {
			cadeiatmp = CadeiaDuplaIgual(&dnafiltrado[i], fim, &i);/*9*N*/
			if (!cadeiatmp) {
				cadeiatmp = CadeiaMetadeIgual(&dnafiltrado[i], fim, &i);/*9*N*/
				if (!cadeiatmp) {
					cadeiatmp = CadeiaPar(&dnafiltrado[i], fim, &i);/*8*N*/
					if (!cadeiatmp) {
						cadeiatmp = CadeiaUmDiferente(&dnafiltrado[i], fim, &i);/*82*N*/
						if (!cadeiatmp) {
							cadeiatmp = CadeiaPrimeiroeUltimoDiferentes(&dnafiltrado[i], fim, &i); /*8*N*/
							if (!cadeiatmp) {
								cadeiatmp = CadeiaEhPalindromo(&dnafiltrado[i],fim, &i,0); /*(3(N² + N) - 4) / 2*/
								if (!cadeiatmp) {
									cadeiatmp = CadeiaEhPalindromo(&dnafiltrado[i], fim, &i, 1); /*(3(N² + N) - 4) / 2*/
									if (!cadeiatmp) {/*N-1*/
										i++;		 /*N-1*/
									}
								}
							}
						}
					}
				}
			}
		}
		if (cadeiatmp) {
			listacadeias = AdicionaListaCadeia(listacadeias, sizeoflistacadeias++, cadeiatmp);
		}
	}
	FILE *filteredoutput = fopen("filtered_out.txt", "w");
	printf("Lido: \n%s", dnafiltrado);
	printf("\n\nFiltrado: \n");
	for (j = 0; j < sizeoflistacadeias; j++) {
	//	printf("%s", listacadeias[j]->Dna);
		fprintf(filteredoutput, "%s", listacadeias[j]->Dna);
	}
	fclose(filteredoutput);
	FILE *compressedout = fopen("compressed_out.txt", "w");
	printf("\n\nCompactado: \n");
	for (j = 0; j < sizeoflistacadeias; j++) {
		//printf("%s", listacadeias[j]->Compactado);
		fprintf(compressedout, "%s", listacadeias[j]->Compactado);
	}
	fclose(compressedout);
	return 0;
}

