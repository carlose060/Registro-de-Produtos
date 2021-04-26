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

typedef struct Lista{
	struct prox *inicio;
	struct prox *final;
}Lista;



void criar(Lista *lista){
	lista->inicio = NULL;
	lista->final = NULL;
}

int tamanho(Lista *lista){
	struct prox *i;
	int tam = 0;

	i = lista->inicio;
	while(i){
		tam++;
		i = i->proximo;
	}
	return tam;
}

void inserir(Lista *lista, item x){
	struct prox *i;
	i = lista->inicio;
	while(i){
		if(strcmp(i->C.nome,x.nome)==0){
			i->C.quantidade = i->C.quantidade + x.quantidade;
      modificar_arquivo(x);
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
  novo_arquivo(x);
}
void inserir_C(Lista *lista, item x){
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
}

void remover(Lista *lista, char name[], int retirar){
	struct prox *i;
	struct prox *j = NULL;
	i = lista->inicio;
	int a = 1;
	while(i && a){
		if(strcmp(i->C.nome,name) == 0){ //função de comparar string
			if(i->C.quantidade - retirar > 0){
				i->C.quantidade = i->C.quantidade - retirar;
        modificar_arquivo(i->C);
      }
			else if(j==NULL){
        remove(i->C.nome".txt");
				lista->inicio = i->proximo;
				free((void*)i);

			}
			else{
        remove(i->C.nome".txt");
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
}

void imprimir(Lista *lista){
	i = lista->inicio;
	while(i){
		printf("Produto:");
		puts(i->C.nome);
		printf("Quantidade em estoque: %d\nPreço: %f\n",i->C.quantidade,i->C.preco);
		i = i->proximo;
	}
	printf("\n");
}
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
