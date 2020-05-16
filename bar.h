/***********************************************************
 * TAD Bar
 * .h
 **********************************************************/
 #ifndef _H_BAR
 #define _H_BAR

 #include "visitante.h"
 #include "trampolim.h"
 #include "dicionario.h"
 #include "produto.h"

 typedef struct _bar * bar;

 bar criaBar(int numero_produtos, char* nomes_produtos, int* stock, float* preco);

 void destroiBar(bar b);

 produto produtos(bar b, char nome_produto);

 void decrementaStockBar(bar b, char nome_produto, int quantidade);


 #endif // _H_BAR

