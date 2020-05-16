/***********************************************************
 * TAD Bar
 * .c
 **********************************************************/
 #include <stdio.h>
 #include <stdlib.h>

 #include "bar.h"
 #include "produto.h"

 struct _bar {

    produto * produtos;
    int numero_produtos;
    double caixa;

 };

 bar criaBar(int numero_produtos, char* nomes_produtos, int* stock, float* precos) {

    int i;
    bar b = (bar) malloc(sizeof(struct _bar));

    if(b==NULL)
        return NULL;

    b->produtos = (produto*)malloc(sizeof(produto)*numero_produtos);

    if(b->produtos == NULL) {
        free(b);
        return NULL;
    }

    b->numero_produtos=numero_produtos;
    b->caixa=0;

    for(i=0; i<numero_produtos; i++) {
        b->produtos[i] = criaProduto(precos[i], nomes_produtos[i], stock[i]);
    }

    return b;
 }

 void destroiBar(bar b) {

   int i;

   for(i=0; i<b->numero_produtos; i++)
        destroiProduto(b->produtos[i]);

   free(b->produtos);
   free(b);

 }

 produto produtos(bar b, char nome_produto) {

    int i;

    for(i=0; i < b->numero_produtos; i++){
        if(devolveNomeProduto(b->produtos[i]) == nome_produto){
            return b->produtos[i];
        }
    }

    return NULL;

 }

 void decrementaStockBar(bar b, char nome_produto, int quantidade) {

    decrementaStock(produtos(b, nome_produto), quantidade);

 }
