#ifndef ARVOREPATRICIAPALAVRAS_H
#define ARVOREPATRICIAPALAVRAS_H

typedef struct patricianode {
    int bit;                   // Posi��o do bit que discrimina este n�
    char *key;                  // Chave armazenada no n�, NULL para n�s intermedi�rios
    struct patricianode *left;   // Sub�rvore esquerda
    struct patricianode *right;  // Sub�rvore direita
}PATRICIANODE;

unsigned bit(char* chave, int k);
unsigned bitLetra(char chave, int k);
int calcularQuantidadeDigitoDecimalUIntMax();
char* letraParaBinario(char chave);
char* converterStringParaBinarioString(char* chave);
char* converterBinarioStringParaString(char* chave);
void inicializaArvorePatricia(PATRICIANODE** arvore);
PATRICIANODE* buscaRec(PATRICIANODE* arvore, char* x, int w, int bitsNaChave);
PATRICIANODE* busca(PATRICIANODE* arvore, char* x, int bitsNaChave);
PATRICIANODE* insereRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai, int bitsNaChave);
void insere(PATRICIANODE** arvore, char* chave, int bitsNaChave);
void imprimir(PATRICIANODE* arvore, int bitsNaChave);

#include "ArvorePatriciaPalavras.c"
#endif