#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvorePatriciaPalavras.h"

int main(){
    PATRICIANODE* raiz;
    inicializaArvorePatricia(&raiz);
    int preoOpcao = 0, opcao = 0, letrasNaChave;
    do{
        printf("1 - Caso Teste Insercao 6 Letras\n2 - Caso Teste Busca 6 Letras\n4 - Inserir manualmente\nDigite uma opcao:");
        scanf("%d", &preoOpcao);

        switch(preoOpcao){
            case 1:
                casoTesteInsercao6Letras(raiz);
                break;

            case 2:
                casoTesteBusca6Letras(raiz);
                break;    

            case 4:
                printf("Insercao manual selecionado!\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while(preoOpcao != 4);

    inicializaArvorePatricia(&raiz);
    
    printf("Digite quantidade de letras na chave: ");
    scanf("%d", &letrasNaChave);
    char* chave = malloc(letrasNaChave * sizeof(char));
        
    do{
        printf("1 - Buscar chave\n2 - Inserir chave\n3 - Remover chave\n4 - Imprimir arvore\n5 - Sair\nDigite uma opcao:\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite chave a ser buscada com maximo %d letras: \n", letrasNaChave);
                scanf("%s", chave);
                if(busca(raiz, chave) != NULL){
                    printf("Chave %s encontrada\n", chave);
                }
                break;

            case 2:
                printf("Digite chave a ser inserida com maximo %d letras:\n", letrasNaChave);
                scanf("%s", chave);
                insere(&raiz, chave);
                break;

            case 3:
                printf("Digite chave a ser removida com maximo %d letras:\n", letrasNaChave);
                scanf("%s", chave);
                remover(&raiz, chave);
                break;

            case 4:
                system("cls");
                imprimir(raiz);
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while(opcao != 5);

}
