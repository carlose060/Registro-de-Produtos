//#include "Produto.h"

void Carregar(Lista *lista);
void novo_arquivo(item x);
void modificar_arquivo(item x);


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
  fprintf(f,"%03d\n",tam);
  fclose(f);
  f = fopen("produto.txt", "a+");
  fprintf(f,"%s",x.nome);
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
