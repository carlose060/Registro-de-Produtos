//#include "Arquivo.h"
#include "Produto.h"
#include <stdio.h>


int main(){

  Lista lista;
  criar(&lista);
  Carregar(&lista);
  int op=1;
  do{
    imprimir(&lista);
    printf("\n---------------Menu principal-------------\n\n");
    printf("1.Inserir produto\n");
    printf("2.Remover produto\n");
    printf("3.Alterar valor do produto\n");
    printf("0.Para fechar o programa\n\n");
    printf("Digite uma opção: ");
    scanf("%d", &op);
    switch(op){
      case 0:
        break;
      case 1:
        system("clear");
        imprimir(&lista);
        item x;
        printf("Digite o nome do produto: ");
        scanf("%s", x.nome);
        printf("Digite o valor do produto: ");
        scanf("%f",&x.preco);
        printf("Digite o valor de custo do produto: ");
        scanf("%f", &x.precoCusto);
        printf("Quantidade em estoque: ");
        scanf("%d", &x.quantidade);
        inserir(&lista,x);
        break;
      case 2:
        system("clear");
        imprimir(&lista);
        printf("Digite o nome do produto: ");
        scanf("%s", x.nome);
        //fgets(x.nome,100,stdin);
        printf("Digite a quantidade que foi vendida: ");
        scanf("%d",&x.quantidade);
        remover(&lista,x.nome,x.quantidade);
        break;
      case 3:
        system("clear");
        imprimir(&lista);
        int alt;
        float new_p;
        printf("Qual produto deseja alterar o preço: ");
        scanf("%s", x.nome);
        //fgets(x.nome,100,stdin);
        printf("Digite o novo valor para o produto: ");
        scanf("%f",&new_p);
        printf("Qual preço deseja alterar? (0.Preço de venda/1.Preço de custo) = ");
        scanf("%d", &alt);
        if(alt==0)
          alterarPreco(&lista,x.nome,new_p);
        else if(alt == 1)
          alterarPrecoCusto(&lista,x.nome,new_p);
        else
          printf("\n*****Opção invalida******\n\n");
        break;
      default:
        printf("\n*****Opção invalida******\n\n");
    }
  }while(op!=0);
}
