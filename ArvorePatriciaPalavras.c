//Rodrigo Isao Goto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ArvorePatriciaPalavras.h"
#include <math.h>

/*
@brief Extrai o bit duma posicao numa palavra

@param chave Chave em palavra que será convertida para string binaria
@return bit de diferenciacao
*/

unsigned bit(char* chave, int k){
    char* chaveBinario = converterStringParaBinarioString(chave);
    int tamanho = strlen(chaveBinario);

    if (k < 0 || k >= tamanho) {
        printf("Bit fora de range");
        free(chaveBinario);  
        return NULL;
    }

    unsigned result = chaveBinario[k] - '0';

    free(chaveBinario);

    return result;
}

/*
@brief Extrai o bit duma posicao numa letra

@param chave Letra em caracter
@param k deslocamento na cadeia de bits
@return bit
*/
unsigned bitLetra(char chave, int k){
    return (chave >> (7 - k)) & 1;
}

/*
@brief Converte um decimal que esta em string para a representacao em binario em string

@param chave Letra em caracter
@return String com representacao binaria da letra
*/
char* letraParaBinario(char chave){
    char* binario = (char*) malloc((9) * sizeof(char));

    for(int i = 0; i < 8; i++){
        binario[i] = bitLetra(chave, i) + '0';
    }

    binario[8] = '\0';
    return binario;
}

/*
@brief Converte string de letras para string de binario

@param chave palavra em string
@return String com representacao binaria da palavra
*/
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

/*@brief Converte binario armazenado como string para string de letras

@param chave representacao binaria em string
@return palavra em string
*/

char* converterBinarioStringParaString(char* chave){
    int contador = 0, tamanho = strlen(chave);
    for(int i = 0; i < tamanho; i++){
        contador++;
    }

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

/*@brief Inicializa a arvore patricia com 40 * "}" e bit = -1

@param arvore raiz da arvore
@return none
*/

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

/*@brief Parte recursiva da busca por uma chave

@param arvore raiz da arvore
@param x chave a ser buscada
@param w bit discriminante

@return PATRICIANODE
*/

PATRICIANODE* buscaRec(PATRICIANODE* arvore, char* x, int w){
    if(arvore->bit <= w){
        return arvore;
    }
    if(bit(x, arvore->bit) == 0){
        return buscaRec(arvore->left, x, arvore->bit);
    }
    else{
        return buscaRec(arvore->right, x, arvore->bit);
    }
}

/*@brief Parte chamada da busca por uma chave

@param arvore raiz da arvore
@param x chave a ser buscada em string de palavra

@return PATRICIANODE ou NULL
*/

PATRICIANODE* busca(PATRICIANODE* arvore, char* x){
    int tamanhoStringBinario = strlen(x) * 8;
    char* xBinario = (char*) malloc((tamanhoStringBinario + 1) * sizeof(char));
    strncpy(xBinario, converterStringParaBinarioString(x), tamanhoStringBinario);
    xBinario[tamanhoStringBinario] = '\0';
    PATRICIANODE* t = buscaRec(arvore->left, x, -1);
    if(strcmp(t->key, xBinario) == 0){
        return t;
    }
    else{
        return NULL;
    }
}

/*@brif Parte recursiva da insercao de uma chave

@param arvore raiz da arvore
@param chave chave a ser inserida em string de palavra
@param w bit discriminante
@param pai no anterior ao no em trabalho

@return PATRICIANODE
*/

PATRICIANODE* insereRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai){
    PATRICIANODE *novo;
    if((arvore->bit >= w) || (arvore->bit) <= pai->bit){
        novo = malloc(sizeof(PATRICIANODE));
        novo->key = (char*) malloc(((strlen(chave) * 8) + 1) * sizeof(char));
        strncpy(novo->key, converterStringParaBinarioString(chave), strlen(chave) * 8);
        novo->key[strlen(chave) * 8] = '\0';
        novo->bit = w;
        if(bit(chave, novo->bit) == 1){
            novo->left = arvore;
            novo->right = novo;
        }
        else{
            novo->left = novo;
            novo->right = arvore;
        }
        return novo;
    }
    if(bit(chave, arvore->bit) == 0){
        arvore->left = insereRec(arvore->left, chave, w, arvore);
    }
    else{
        arvore->right = insereRec(arvore->right, chave, w, arvore);
    }
    return arvore;
}

/*@brief Parte chamada da insercao de uma chave

@param arvore raiz da arvore
@param chave chave a ser inserida em string de palavra

@return none
*/

void insere(PATRICIANODE** arvore, char* chave){
    int i;
    PATRICIANODE* t = buscaRec((*arvore)->left, chave, -1);
    char* tKeyString = (char*) malloc((strlen(t->key)/8) + 1 * sizeof(char));
    strncpy(tKeyString, converterBinarioStringParaString(t->key), strlen(t->key)/8);
    tKeyString[strlen(t->key)/8] = '\0';

    if(strcmp(chave, tKeyString) == 0){
        return;
    }

    for(i = 0; bit(chave, i) == bit(tKeyString, i); i++);
    (*arvore)->left = insereRec((*arvore)->left, chave, i, *arvore);
    free(tKeyString);
}

/*@brief Parte recursiva da remocao de uma chave

@param arvore raiz da arvore
@param chave chave a ser removida em string binaria
@param w bit discriminante
@param pai no anterior ao no em trabalho

@return NULL ou PATRICIANODE
*/

PATRICIANODE* removeRec(PATRICIANODE* arvore, char* chave, int w, PATRICIANODE* pai){
    //Caso seja o no dummy
    if(arvore->bit == -1 && strcmp(chave, arvore->key) == 0){
        arvore->left = NULL;
        arvore->right = NULL;
        free(arvore);
        return NULL;
    }
    printf("Checou pra ver se nn e dummy\n");
    //Caso possua o apontador esquerdo apontando para si proprio, verificar se está a esquerda ou a direita do pai e depois apontar do pai para o filho
    if(arvore->bit != - 1 && arvore->left == arvore && bit(chave, pai->bit) == 0 && strcmp(chave, arvore->key) == 0){
        printf("Chegou apontador esquerdo\n");
        pai->left = arvore->right;
        free(arvore);
        return arvore->right;
    }
    if(arvore->bit != - 1 && arvore->left == arvore && bit(chave, pai->bit) && strcmp(chave, arvore->key) == 0){
        printf("Chegou apontador esquerdo\n");
        pai->right = arvore->right;
        free(arvore);
        return arvore->right;
    }
    printf("Checou pra ver se nn tem ponteiro esquerda pra ele msm\n");

    //Quase mesma coisa que o caso anterior, no entanto caso possua o apontador direito apontando para si proprio
    if(arvore->bit != - 1 && arvore->right == arvore && bit(chave, pai->bit) == 0 && strcmp(chave, arvore->key) == 0){
        printf("Chegou apontador direito\n");
        pai->left = arvore->left;
        free(arvore);
        return arvore->left;
    }
    if(arvore->bit != - 1 && arvore->right == arvore && bit(chave, pai->bit) && strcmp(chave, arvore->key) == 0){
        printf("Chegou apontador direito\n");
        pai->right = arvore->left;
        free(arvore);
        return arvore->left;
    }
    printf("Checou pra ver se nn tem ponteiro direita pra ele msm\n");

    //Caso nao possua apontador para si mesmo
    if(arvore->bit != - 1 && arvore->left != arvore && arvore->right != arvore && strcmp(chave, arvore->key) == 0){
        PATRICIANODE* q = arvore;
        PATRICIANODE* pai = arvore;
        //Encontrando no q
        while((q->left != arvore || q->right != arvore) && q->bit <= arvore->bit){
            if(bit(chave, q->bit) == 0){
                q = q->left;
            }
            else{
                q = q->right;
            }
        }
        printf("Chave q: %s\n", q->key);

        //Encontrando no pai de no q
        while((pai->left != q || pai->right != q) && pai->bit <=arvore->bit){
            if(bit(chave, pai->bit) == 0){
                pai = pai->left;
            }
            else{
                pai = pai->right;
            }
        }
        printf("Chave pai: %s\n", pai->key);

        PATRICIANODE* r = q;
        //Encontrando no r que aponta para q
        while((r->left != q || r->right != q) && r->bit <= q->bit){
            if(bit(q->key, r->bit) == 0){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }
        printf("Chave r: %s\n", r->key);

        //Copiando para no p o conteudo de no q
        strcpy(arvore->key, q->key);
        printf("Chave p: %s\n", arvore->key);

        //Apontando de no r para no p
        if(r->left == q){
            r->left = arvore;
        }
        else{
            r->right = arvore;
        }
        
        //Apontando do no pai de no q para no filho de no q
        if(pai->left == q){
            if(q->left == arvore){
                pai->left = q->right;
            }
            else{
                pai->left = q->left;
            }
        }
        else{
            if(q->left == arvore){
                pai->right = q->right;
            }
            else{
                pai->right = q->left;
            }
        }

        free(q);
        return arvore;
    }

    /*//Se o apontador esquerdo apontar para o no que possui a chave
    //Objetivo e passar o conteudo do no arvore para o noarvore->esquerda e depois excluir o no arvore
    if(arvore->left->bit <= arvore->bit && strcmp(chave, arvore->left->key) == 0){
        PATRICIANODE* r = arvore;
        while(r->left != arvore || r->right != arvore){
            if(bit(arvore->key, r->bit) == 0){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }

        strcpy(arvore->left->key, arvore->key);

        //Apontando de r para arvore->esquerda
        if(r->left == arvore){
            r->left = arvore->left;
        }
        else{
            r->right = arvore->left;
        }

        if(pai->left == arvore){
            pai->left = arvore->right;
        }
        else{
            pai->right = arvore->right;
        }

        free(arvore);
        return arvore->right;
    }
    printf("Checou pra ver se nn possui apontador esquerda pro no que contem a chave\n");

    //Se o apontador direito apontar para o no que possui a chave
    //Objetivo e passar o conteudo do no arvore para o noarvore->direita e depois excluir o no arvore
    if(arvore->right->bit <= arvore->bit && strcmp(chave, arvore->right->key) == 0){
        PATRICIANODE* r = arvore;
        while(r->left != arvore || r->right != arvore){
            if(bit(arvore->key, r->bit) == 0){
                r = r->left;
            }
            else{
                r = r->right;
            }
        }

        strcpy(arvore->right->key, arvore->key);

        //Apontando de r para arvore->direita
        if(r->left == arvore){
            r->left = arvore->right;
        }
        else{
            r->right = arvore->right;
        }

        if(pai->left == arvore){
            pai->left = arvore->left;
        }
        else{
            pai->right = arvore->left;
        }

        free(arvore);
        return arvore->left;
    }
    printf("Checou pra ver se nn possui apontador direita pro no que contem a chave\n");*/


    if(bit(chave, arvore->bit) == 0){
        printf("Foi pra esquerda\n");
        arvore->left = removeRec(arvore->left, chave, w, arvore);
    }
    else{
        printf("Foi pra direita\n");
        arvore->right = removeRec(arvore->right, chave, w, arvore);
    }
    return arvore;
}

/*@brief Parte chamada da remocao de uma chave

@param arvore raiz da arvore
@chave chave em string de palavras

@return none
*/

void remover(PATRICIANODE** arvore, char* chave){
    if(busca((*arvore), chave) == NULL){
        return;
    }
    else{
        char* chaveBinario = (char*) malloc(((strlen(chave) * 8) + 1) * sizeof(char));
        strncpy(chaveBinario, converterStringParaBinarioString(chave), strlen(chave) * 8);
        chaveBinario[strlen(chave) * 8] = '\0';
        (*arvore)->left = removeRec((*arvore)->left, chaveBinario, -1, (*arvore));
        free(chaveBinario);
    }
}

/*@brif Impressao da arvore

@param arvore raiz da arvore
@return none
*/

void imprimir(PATRICIANODE* arvore){
    if (arvore == NULL){
        return;
    }

    printf("Chave: %s\t", arvore->key);
    printf("Chave em palavra: %s\t", converterBinarioStringParaString(arvore->key));
    printf("Bit: %d\n", arvore->bit);
    if(arvore->key == arvore->left->key){
        printf("Esquerda: Ele mesmo\n");
    }
    else{
        printf("Esquerda: %s\n", arvore->left->key);
    }
    if(arvore->key == arvore->right->key){
        printf("Direita: Ele mesmo\n");
    }
    else{
        printf("Direita: %s\n", arvore->right->key);
    }

    if(arvore->left != arvore && arvore->left->bit > arvore->bit){
        printf("Subarvore esquerda de %s:\n", arvore->key);
        imprimir(arvore->left);
    }

    if(arvore->right != arvore && arvore->right->bit > arvore->bit){
        printf("Subarvore direita de %s:\n", arvore->key);
        imprimir(arvore->right);
    }
}



void casoTesteInsercao6Letras(PATRICIANODE* arvore){
    insere(&arvore, "Banana");
    imprimir(arvore);

    insere(&arvore, "utopia");
    system("cls");
    imprimir(arvore);

    insere(&arvore, "legado");
    system("cls");
    imprimir(arvore);

    insere(&arvore, "Aferir");
    system("cls");
    imprimir(arvore);

    insere(&arvore, "papiro");
    system("cls");
    imprimir(arvore);
}

void casoTesteBusca6Letras(PATRICIANODE* arvore){
    if(busca(arvore, "papiro") != NULL){
        printf("Chave papiro encontrada\n");
    }
    
    if(busca(arvore, "Banana") != NULL){
        printf("Chave Banana encontrada\n");
    }

    if(busca(arvore, "utopia") != NULL){
        printf("Chave utopia encontrada\n");
    }
}

void casoTesteInsercao8Letras(PATRICIANODE* arvore){
    insere(&arvore, "Genocida");
    imprimir(arvore);

    insere(&arvore, "pandemia");
    system("cls");
    imprimir(arvore);

    insere(&arvore, "Ardiloso");
    system("cls");
    imprimir(arvore);

    insere(&arvore, "prudente");
    system("cls");
    imprimir(arvore);
}

void casoTesteBusca8Letras(PATRICIANODE* arvore){
    if(busca(arvore, "pandemia") != NULL){
        printf("Chave pandemia encontrada\n");
    }
    
    if(busca(arvore, "Banana") != NULL){
        printf("Chave Banana encontrada\n");
    }

    if(busca(arvore, "Ardiloso") != NULL){
        printf("Chave Ardiloso encontrada\n");
    }
}

void casoTesteRemocao6Letras(PATRICIANODE* arvore){
    inicializaArvorePatricia(&arvore);
    insere(&arvore, "Banana");
    insere(&arvore, "utopia");
    remover(&arvore, "Banana");
    remover(&arvore, "utopia");
    removerDummyNode(&arvore);
}

void casoTesteRemocao8Letras(PATRICIANODE* arvore){
    remover(&arvore, "pandemia");
}

/*@brief Selecao da remocao do no dummy

@param arvore raiz da arvore
@return none
*/
void removerDummyNode(PATRICIANODE **arvore){
    remover(arvore, "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}");
}
