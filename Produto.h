#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

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

void criar(Lista *lista);
int tamanho(Lista *lista);
void inserir(Lista *lista, item x);
void inserir_C(Lista *lista, item x);
void remover(Lista *lista, char name[], int retirar);
void imprimir(Lista *lista);
void alterarPreco(Lista *lista,char x[], float new_p0);
void alterarPrecoCusto(Lista *lista,char x[], float new_p);
//escopo parte de arquivos
void Carregar(Lista *lista);
void novo_arquivo(item x);
void modificar_arquivo(item x);



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
      x.quantidade = i->C.quantidade;
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
    /*    char aux[100];
        strcpy(aux, i->C.nome);
        strcat(aux,".txt");
        remove(aux);*/
        i->C.quantidade = 0;
        modificar_arquivo(i->C); //so para colocar 0 no arquivo
				lista->inicio = i->proximo;
				free((void*)i);
			}
			else{
        /*char aux[100];
        strcpy(aux, i->C.nome);
        strcat(aux,".txt");
        remove(aux);
        remove(aux);*/
        i->C.quantidade = 0;
        modificar_arquivo(i->C); // so para colocar 0 no arquivo
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
/*void removerArq(char nome[]){ //metodo aux
      char aux[100];
      int tam;
      strcpy(aux,nome);
      strcat(aux,".txt");
      remove(aux);
      FILE *f = fopen("produto.txt","r");
      fscanf(f,"%d", &tam);
      for(int i=0;i< tam;i++){

      }
      fclose(f);
}*/

void imprimir(Lista *lista){
  struct prox *i;
	i = lista->inicio;
	while(i){
    if(i->C.quantidade > 0){
      printf("---------------------------\n");
		  printf("Produto: ");
		  puts(i->C.nome);
		  printf("Quantidade em estoque: %d\nPreço: %f\n",i->C.quantidade,i->C.preco);
      printf("---------------------------\n");
    }
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
      char aux[100];
      item ax;
      strcpy(aux,i->C.nome);
      strcat(aux,".txt");
      FILE *f = fopen(aux,"r+");
      if(f==NULL){
        printf("Erro ao abrir\n");
        return;
      }
      fscanf(f,"%d", &ax.quantidade);
      fscanf(f,"%f", &ax.preco);
      fscanf(f,"%f", &ax.precoCusto);
      strcpy(ax.nome, x);
      ax.preco = new_p;
      fclose(f);
      modificar_arquivo(ax);
			return;
		}
		i = i->proximo;
	}
  printf("\n\n\nO Produto não se encontra em estoque\n");
}
void alterarPrecoCusto(Lista *lista,char x[], float new_p){

	struct prox* i;
	i = lista->inicio;
	while(i){
		if(strcmp(i->C.nome,x)==0){
			i->C.precoCusto = new_p;
      char aux[100];
      item ax;
      strcpy(aux,i->C.nome);
      strcat(aux,".txt");
      FILE *f = fopen(aux,"r+");
      if(f==NULL){
        printf("Erro ao abrir\n");
        return;
      }
      fscanf(f,"%d", &ax.quantidade);
      fscanf(f,"%f", &ax.preco);
      strcpy(ax.nome, x);
      ax.precoCusto = new_p;
      fclose(f);
      modificar_arquivo(ax);
			return;
		}
		i = i->proximo;
	}
  printf("\n\n\nO Produto não se encontra em estoque\n");
}
//funções de arquivo
void modificar_arquivo(item x){
  FILE *f;
  char aux[100];
  strcpy(aux, x.nome);
  strcat(aux,".txt");
  f = fopen(aux,"w");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  fprintf(f,"%03d\n%.5f\n%.5f\n%s",x.quantidade,x.preco,x.precoCusto,x.nome);
  fclose(f);
}
void novo_arquivo(item x){
  FILE *f;
  char aux[100];
  strcpy(aux, x.nome);
  strcat(aux,".txt");
  f = fopen(aux,"w");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  fprintf(f,"%03d\n%.5f\n%.5f\n%s",x.quantidade,x.preco,x.precoCusto,x.nome);
  fclose(f);
  f = fopen("produto.txt", "r+");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  int tam;
  fscanf(f,"%d",&tam);
  tam++;
  rewind(f);
  fprintf(f,"%03d",tam);
  fclose(f);
  f = fopen("produto.txt","a");
  fprintf(f,"%s\n",x.nome);
  fclose(f);
}
void Carregar(Lista *lista){
  FILE *f;
  int qt;
  f = fopen("produto.txt", "r");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  fscanf(f,"%d", &qt);
  for(int i=0;i < qt;i++){
    char nome[100];
    fscanf(f,"%s", nome);
    strcat(nome,".txt");
    FILE *file = fopen(nome,"r");
    if(file == NULL){
      printf("Erro ao abrir\n");
      return;
    }
    struct Produto x;
   fscanf(file,"%d",&x.quantidade);
   fscanf(file,"%f",&x.preco);
   fscanf(file,"%f",&x.precoCusto);
   fscanf(file,"%s",x.nome);
   fclose(file);
   inserir_C(lista, x);
  }
  fclose(f);
}
