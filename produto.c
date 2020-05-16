/***********************************************************
 * TAD Produto
 * .c
 **********************************************************/
 #include <stdlib.h>
 #include <stdio.h>

 #include "produto.h"

 struct _produto {

    char nome_produto;
    int stock;
    float preco;

 };

 produto criaProduto(float preco, char nome_produto, int stock) {

    produto pr = (produto) malloc(sizeof(struct _produto));

    if(pr==NULL)
        return NULL;

    pr->nome_produto=nome_produto;
    pr->stock=stock;
    pr->preco=preco;

    return pr;

 }

 void destroiProduto(produto pr) {

    free(pr);

 }

 char devolveNomeProduto(produto pr) {

    return pr->nome_produto;

 }

 int devolveStockProduto(produto pr) {

    return pr->stock;

 }

 float devolvePrecoProduto(produto pr) {

    return pr->preco;

 }

 void decrementaStock(produto pr, int quantidade) {
    pr->stock = pr->stock - quantidade;
 }
