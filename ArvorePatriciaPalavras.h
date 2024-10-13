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
PATRICIANODE* buscaRec(PATRICIANODE* arvore, char* x, int w);
PATRICIANODE* busca(PATRICIANODE* arvore, char* x);
PATRICIANODE* insereRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai);
void insere(PATRICIANODE** arvore, char* chave);
PATRICIANODE* removeRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai);
void remover(PATRICIANODE** arvore, char* chave);
void imprimir(PATRICIANODE* arvore);
void casoTesteInsercao6Letras(PATRICIANODE* arvore);
void casoTesteBusca6Letras(PATRICIANODE* arvore);
void casoTesteInsercao8Letras(PATRICIANODE* arvore);
void casoTesteBusca8Letras(PATRICIANODE* arvore);

#include "ArvorePatriciaPalavras.c"
#endif

