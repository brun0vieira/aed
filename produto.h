/***********************************************************
 * TAD Produto
 * .h
 **********************************************************/

 #ifndef _H_PRODUTO
 #define _H_PRODUTO

 typedef struct _produto *produto;

 produto criaProduto(float preco, char nome_produto, int stock);

 void destroiProduto(produto pr);

 char devolveNomeProduto(produto pr);

 int devolveStockProduto(produto pr);

 float devolvePrecoProduto(produto pr);

 void decrementaStock(produto pr, int quantidade);

 #endif // _H_PRODUTO

