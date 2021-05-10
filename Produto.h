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
void removerArq(char nome[]);
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
        removerArq(i->C.nome);
				lista->inicio = i->proximo;
				free((void*)i);
			}
			else{
        removerArq(i->C.nome);
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
void removerArq(char nome[]){ //metodo aux
      char aux[100];
      int tam;
      strcpy(aux,nome);
      remove(aux);
      FILE *f = fopen("produto.txt","r+");
      fscanf(f,"%d", &tam);
      for(int i=0;i<tam;i++){
        int size = ftell(f);
        fscanf(f,"%s",aux);
        if(!strcmp(nome,aux)){
          fseek(f,size,SEEK_SET);
          for(int j=0;j<=strlen(nome);j++)
          fprintf(f," ");
          break;
        }
      }
      fseek(f,0,SEEK_SET);
      fprintf(f,"%03d",tam-1);
      fclose(f);
}


void imprimir(Lista *lista){
  struct prox *i;
	i = lista->inicio;
	while(i){
    if(i->C.quantidade > 0){
      printf("---------------------------\n");
		  printf("Produto: ");
		  puts(i->C.nome);
		  printf("Quantidade em estoque: %d\nPreço: %.2f\nPreço Custo: %.2f\n",i->C.quantidade,i->C.preco,i->C.precoCusto);
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
      strcpy(aux,i->C.nome);
      FILE *f = fopen(aux,"r+");
      if(f==NULL){
        printf("Erro ao abrir\n");
        return;
      }
      item ax;
      fread(&ax,sizeof(item),1,f);
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
      strcpy(aux,i->C.nome);
      FILE *f = fopen(aux,"r+");
      if(f==NULL){
        printf("Erro ao abrir\n");
        return;
      }
      item ax;
      fread(&ax,sizeof(item),1,f);
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
//  strcat(aux,".txt");
  f = fopen(aux,"w");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  fwrite(&x,sizeof(item),1,f); //gravar em b no arquivo
  fclose(f);
}
void novo_arquivo(item x){
  FILE *f;
  char aux[100];
  strcpy(aux, x.nome);
  f = fopen(aux,"w");
  if(f == NULL){
    printf("Erro ao abrir\n");
    return;
  }
  fwrite(&x,sizeof(item),1,f);
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
  fprintf(f,"%03d\n",tam);
  fseek(f,0,SEEK_END);  //pular para o fim do arquivo
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
    FILE *file = fopen(nome,"r");
    if(file == NULL){
      printf("Erro ao abrir\n");
      return;
    }
    struct Produto x;
    fread(&x,sizeof(struct Produto),1,file);
   fclose(file);
   inserir_C(lista, x);
  }
  fclose(f);
}
