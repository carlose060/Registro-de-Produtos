#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Produto{
  char nome[100];
  float preco;
  float precoCusto;
  int quantidade;
}item;

typedef struct prox{
	item C;
	struct prox *proximo;
}Node;

typedef struct Lista_en{
	struct prox *inicio;
	struct prox *final;
}Lista;

void criar(Lista *lista){
	lista->inicio = NULL;
	lista->final = NULL;
}

int tamanho(Lista *lista){ //ex2
	struct prox *i;
	int tam = 0;

	i = lista->inicio;
	while(i){
		tam++;
		i = i->proximo;
	}
	return tam;
}	//fim



void inserir(Lista *lista, item x){ //ex3
	struct prox *i;
	i = lista->inicio;
	while(i){
		if(strcmp(i->C.nome,x.nome)==0){
			i->C.quantidade = i->C.quantidade + x.quantidade;
			return;
		}
		i = i->proximo;
	} //checar se ja existe o item para nao repetir
	struct prox* caixa = (struct prox*) malloc(sizeof(struct prox));
	strcpy (caixa->C.nome,x.nome);
	caixa->C.preco = x.preco;
	caixa->C.precoCusto = x.precoCusto;
	caixa->C.quantidade = x.quantidade;

	caixa->proximo = NULL;

	if(lista->inicio==NULL){
		lista->inicio = caixa;
		lista->final = caixa;
	}
	else{
	lista->final->proximo = caixa;
	lista->final = caixa;
	}
}//fim

void remover(Lista *lista, char name[], int retirar){		//ex4
	struct prox *i;
	struct prox *j = NULL;
	i = lista->inicio;
	int a = 1;
	while(i && a){
		if(strcmp(i->C.nome,name) == 0){ //função de comparar string
			if(i->C.quantidade - retirar > 0)
				i->C.quantidade = i->C.quantidade - retirar;
			else if(j==NULL){
				lista->inicio = i->proximo;
				free((void*)i);
			}
			else{
				j->proximo = i->proximo;
				free((void*)i);
			}
			a = 0;
		}
		else{
			j = i;
			i = i->proximo;
		}
	}
} //fim

void imprimir(Lista *lista){	//ex5
	struct prox *i;
	i = lista->inicio;
	while(i){
		printf("Produto:");
		puts(i->C.nome);
		printf("Quantidade em estoque: %d\nPreço: %f\n",i->C.quantidade,i->C.preco);
		i = i->proximo;
	}
	printf("\n");
} //fim
void alterarPreco(Lista *lista,char x[], float new_p){
	struct prox* i;
	i = lista->inicio;
	while(i){
		if(strcmp(i->C.nome,x)==0){
			i->C.preco = new_p;
			return;
		}
		i = i->proximo;
	}
}
void alterarPrecoCusto(Lista *lista,char x[], float new_p){

	struct prox* i;
	i = lista->inicio;
	while(i){
		if(strcmp(i->C.nome,x)==0){
			i->C.precoCusto = new_p;
			return;
		}
		i = i->proximo;
	}
}
