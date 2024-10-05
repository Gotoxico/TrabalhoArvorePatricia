#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvorePatriciaPalavras.h"

int main(){
    PATRICIANODE* raiz;
    inicializaArvorePatricia(&raiz);
    int opcao = 0, letrasNaChave, bitsNaChave;
    printf("Digite quantidade de letras na chave: ");
    scanf("%d", &letrasNaChave);
    char* chave = malloc(letrasNaChave * sizeof(char));
    bitsNaChave = letrasNaChave * 8;
    
    do{
        printf("1 - Buscar chave\n2 - Inserir chave\n3 - Remover chave\n4 - Imprimir arvore\n5 - Sair\nDigite uma opcao:\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite chave a ser buscada com maximo %d letras: \n", letrasNaChave);
                scanf("%s", chave);
                if(busca(raiz, chave, bitsNaChave) != NULL){
                    printf("Chave %s encontrada\n", chave);
                }
                break;

            case 2:
                printf("Digite chave a ser inserida com maximo %d letras:\n", letrasNaChave);
                scanf("%s", chave);
                insere(&raiz, chave, bitsNaChave);
                break;

            case 3:
                printf("Digite chave a ser removida com maximo %d letras:\n", letrasNaChave);
                scanf("%s", chave);
                //remove(&raiz, chave, bitsNaChave);
                break;

            case 4:
                imprimir(raiz, bitsNaChave);
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while(opcao != 5);
}
