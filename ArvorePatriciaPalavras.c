#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ArvorePatriciaPalavras.h"
#include <math.h>

unsigned bit(char* chave, int k, int bitsNaChave){
    unsigned int chaveDecimal = 0;
    for(int i = 0; chave[i] != '\0'; i++){
        chaveDecimal = chaveDecimal + (int) chave[i];
    }
    return chaveDecimal >> (bitsNaChave - 1 - k) & 1;
}

unsigned bitLetra(char chave, int k){
    return (chave >> (7 - k)) & 1;
}

int calcularQuantidadeDigitoDecimalUIntMax(){
    int quantidade = 0;
    unsigned int numero = UINT_MAX;
    while(numero > 0){
        quantidade++;
        numero >>=1;
    }
    return quantidade;
}

//Converte um decimal que esta em string para a representacao em binario em string
char* letraParaBinario(char chave){
    char* binario = (char*) malloc((9) * sizeof(char));

    for(int i = 0; i < 8; i++){
        binario[i] = bitLetra(chave, i) + '0';
    }

    binario[8] = '\0';
    return binario;
}

//Converte string de letras para string de binario
char* converterStringParaBinarioString(char* chave){
    char* chaveBinaria = (char*) malloc((strlen(chave) * 8 + 1) * sizeof(char));
    chaveBinaria[0] = '\0';
    char* letraEmBinario;
    int tamanhoChave = strlen(chave);
    for(int i = 0; i < tamanhoChave; i++){
        letraEmBinario = letraParaBinario(chave[i]);
        //strcpy(letraEmBinario, letraParaBinario(chave[i], 8));
        strcat(chaveBinaria, letraEmBinario);
        free(letraEmBinario);
    }
    return chaveBinaria;
}

//Converte binario armazenado como string para string de letras
char* converterBinarioStringParaString(char* chave){
    int contador = 0, tamanho = strlen(chave);
    for(int i = 0; i < tamanho; i++){
        contador++;
    }

    printf("Contador: %d\t", contador);

    char* chaveString = (char*) malloc(((strlen(chave) / 8) + 1) * sizeof(char));
    unsigned int letraDecimal;
    int i = 0;

    int tamanhoChave = strlen(chave);
    for(int c = 0; c < tamanhoChave/8; c++){
        letraDecimal = 0;
        
        for(int j = 0; j < 8; j++){
            if(chave[i] == '1'){
                letraDecimal = letraDecimal + (1 << (7 - j));
            }
            i++;
        }
        chaveString[c] = (char) letraDecimal;
    }

    chaveString[strlen(chave) / 8] = '\0';
    return chaveString;
}

void inicializaArvorePatricia(PATRICIANODE** arvore){
    *arvore = malloc(sizeof(PATRICIANODE));

    (*arvore)->key = (char*) malloc((40 * 8 + 1) * sizeof(char));
    char* chaveString = (char*) malloc(41 * sizeof(char));
    for(int i = 0; i < 40; i++){
        chaveString[i] = '}';
    }

    chaveString[40] = '\0';

    strncpy((*arvore)->key, converterStringParaBinarioString(chaveString), (40 * 8));
    (*arvore)->key[40 * 8] = '\0';

    (*arvore)->left = (*arvore);
    (*arvore)->right = (*arvore);
    (*arvore)->bit = -1;

}

PATRICIANODE* buscaRec(PATRICIANODE* arvore, char* x, int w, int bitsNaChave){
    if(arvore->bit <= w){
        return arvore;
    }
    if(bit(x, arvore->bit, bitsNaChave) == 0){
        return buscaRec(arvore->left, x, arvore->bit, bitsNaChave);
    }
    else{
        return buscaRec(arvore->right, x, arvore->bit, bitsNaChave);
    }
}

PATRICIANODE* busca(PATRICIANODE* arvore, char* x, int bitsNaChave){
    PATRICIANODE* t = buscaRec(arvore->left, x, -1, bitsNaChave);
    if(strcmp(t->key, x) == 0){
        return t;
    }
    else{
        return NULL;
    }
}

PATRICIANODE* insereRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai, int bitsNaChave){
    PATRICIANODE *novo;
    if((arvore->bit >= w) || (arvore->bit) <= pai->bit){
        novo = malloc(sizeof(PATRICIANODE));
        novo->key = (char*) malloc(((strlen(chave) * 8) + 1) * sizeof(char));
        strncpy(novo->key, converterStringParaBinarioString(chave), strlen(chave) * 8 + 1);
        novo->bit = w;
        if(bit(chave, novo->bit, bitsNaChave) == 1){
            novo->left = arvore;
            novo->right = novo;
        }
        else{
            novo->left = novo;
            novo->right = arvore;
        }
        return novo;
    }
    if(bit(chave, arvore->bit, bitsNaChave) == 0){
        arvore->left = insereRec(arvore->left, chave, w, arvore, bitsNaChave);
    }
    else{
        arvore->right = insereRec(arvore->right, chave, w, arvore, bitsNaChave);
    }
    return arvore;
}

void insere(PATRICIANODE** arvore, char* chave, int bitsNaChave){
    int i;
    PATRICIANODE* t = buscaRec((*arvore)->left, chave, -1, bitsNaChave);
    char* tKeyString = malloc((strlen(t->key)/8) * sizeof(char));
    strncpy(tKeyString, converterBinarioStringParaString(t->key), strlen(t->key)/8);

    if(strcmp(chave, tKeyString) == 0){
        return;
    }


    for(i = 0; bit(chave, i, bitsNaChave) == bit(t->key, i, bitsNaChave); i++);
    (*arvore)->left = insereRec((*arvore)->left, chave, i, *arvore, bitsNaChave);
    free(tKeyString);
}

/*PATRICIANODE* removeRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai, int bitsNaChave){
    //Caso seja o no dummy
    if(arvore->bit == -1 && strcmp(chave, arvore->key) == 0){
        arvore->left = NULL;
        arvore->right = NULL;
        return NULL;
    }

    //Caso possua o apontador esquerdo apontando para si proprio, verificar se está a esquerda ou direita do pai e depois apontar do pai para o filho
    if(arvore->left == arvore && bit(chave, pai->bit ,bitsNaChave) == 0 && strcmp(chave, arvore->key) == 0){
        pai->left = arvore->right;
        free(arvore);
        return NULL;
    }
    if(arvore->left == arvore && bit(chave, pai->bit, bitsNaChave && strcmp(chave, arvore->key) == 0)){
        pai->right = arvore->right;
        free(arvore);
        return NULL;
    }

    //Quase mesma coisa que o caso anterior, no entanto caso possua o apontador direito apontando para si proprio
    if(arvore->right == arvore && bit(chave, pai->bit, bitsNaChave) == 0 && strcmp(chave, arvore->key) == 0){
        pai->left = arvore->left;
        free(arvore);
        return NULL;
    }
    if(arvore->right == arvore && bit(chave, pai->bit, bitsNaChave) && strcmp(chave, arvore->key) == 0){
        pai->right = arvore->left;
        free(arvore);
        return NULL;
    }

    //Se o apontador esquerdo apontar para o no que possui a chave
    //Objetivo e passar o conteudo do no arvore para o noarvore->esquerda e depois excluir o no arvore
    if(arvore->left->bit <= arvore->bit && strcmp(chave, arvore->left->key) == 0){
        PATRICIANODE* r = arvore;
        while(r->left != arvore || r->right != arvore){
            if(bit(arvore->key, r->bit, bitsNaChave) == 0){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }

        strcpy(arvore->left->key, arvore->key);

        if(r->left == arvore){
            r->left = arvore->left;
        }
        else{
            r->right = arvore->left;
        }

        //Se o no arvore a ser removido estava a esquerda do pai, apontar o pai esquerda para o mais a direita dos filhos de arvore
        if(pai->left == arvore){
            while(arvore != NULL){
                arvore = arvore->right;
            }
            pai->left = arvore;
            return NULL;
        }

        //Se o no arvore a ser removido estava a direita do pai, apontar o pai direita para o mais a esquerda dos filhos de arvore
        else{
            while(arvore != NULL){
                arvore = arvore->left;
            }
            pai->right = arvore;
            return NULL;
        }
    }

    //Se o apontador direito apontar para o no que possui a chave
    //Objetivo e passar o conteudo do no arvore para o noarvore->direita e depois excluir o no arvore
    if(arvore->right->bit <= arvore->bit && strcmp(chave, arvore->right->key) == 0){
        PATRICIANODE* r = arvore;
        while(r->left != arvore || r->right != arvore){
            if(bit(arvore->key, r->bit, bitsNaChave) == 0){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }

        strcpy(arvore->right->key, arvore->key);

        if(r->left == arvore){
            r->left = arvore->right;
        }
        else{
            r->right = arvore->right;
        }

        //Se o no arvore a ser removido estava a esquerda do pai, apontar o pai esquerda para o mais a direita dos filhos de arvore
        if(pai->left == arvore){
            while(arvore != NULL){
                arvore = arvore->right;
            }
            pai->left = arvore;
            return NULL;
        }

        //Se o no arvore a ser removido estava a direita do pai, apontar o pai direita para o mais a esquerda dos filhos de arvore
        else{
            while(arvore != NULL){
                arvore = arvore->left;
            }
            pai->right = arvore;
            return NULL;
        }
    }

    if(bit(chave, arvore->bit, bitsNaChave) == 0){
        arvore->left = removeRec(arvore->left, chave, w, arvore, bitsNaChave);
    }
    else{
        arvore->right = removeRec(arvore->right, chave, w, arvore, bitsNaChave);
    }
    return arvore;
}

void remove(PATRICIANODE** arvore, char* chave, int bitsNaChave){
    if(busca((*arvore), chave, bitsNaChave) == NULL){
        return NULL;
    }
    else{
        removeRec((*arvore), chave, -1, NULL, bitsNaChave);
    }
}*/

void imprimir(PATRICIANODE* arvore, int bitsNaChave){
    if (arvore == NULL){
        return;
    }

    printf("Chave: %s\t", arvore->key);
    printf("Chave em palavra: %s\t", converterBinarioStringParaString(arvore->key));
    printf("Bit: %d\n", arvore->bit);

    if(arvore->left != arvore && arvore->left->bit > arvore->bit){
        printf("Subarvore esquerda:\n");
        imprimir(arvore->left, bitsNaChave);
    }

    if(arvore->right != arvore && arvore->right->bit > arvore->bit){
        printf("Subarvore direita:\n");
        imprimir(arvore->right, bitsNaChave);
    }
}

/*void printTree(PATRICIANODE* no, PATRICIANODE* arvore, int level){
    if(no->bit == arvore->bit){
        return;
    }
    if(no->bit <= level){
        return;
    }
    printTree(no->right, arvore, no->bit);
    if(no->bit == 0){
        printf()
    }
}*/





