#include "Produto.h"

void modificar_arquivo(item x){
  FILE *f;
  f = fopen(x.nome".txt","w");
  fprintf(f,"%d %.2f %.2f %s",x.quantidade,x.preco,x.precoCusto,x.nome);
  fclose(f);
}
