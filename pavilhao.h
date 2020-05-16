/***********************************************************
 * TAD Pavilhao
 * .h
 **********************************************************/
 #ifndef _H_PAVILHAO
 #define _H_PAVILHAO

 #include "visitante.h"
 #include "trampolim.h"
 #include "dicionario.h"
 // #include "dicionario.h"

 typedef struct _pavilhao * pavilhao;

 pavilhao criaPavilhao(int num_visitantes, int num_trampolins, char* nomes_produtos, int* stocks, float* precos);

 void destroiPavilhao(pavilhao p);

 int existeVisitantePavilhao(pavilhao p, int cartao_cidadao);

 void entraVisitantePavilhao(pavilhao p, int cartao_cidadao, int n_contribuinte, char* nome_cliente);

 dicionario dicionarioVisitantes(pavilhao p);

 void meteNaFila(pavilhao p, int cartao_cidadao);

 int entradaVisitanteTrampolim(pavilhao p, int h_entrada, int m_entrada);

 int numeroTrampolinsPavilhao(pavilhao p);

 trampolim trampolimPav(pavilhao p, int numero_trampolim);

 void removeVisitanteTrampolim(pavilhao p, int numero_tramp, int tempo_utilizacao);

 void* bar_pavilhao(pavilhao p);

 void efetuaCompra(pavilhao p, char nome_produto, int quantidade, int cartao_cidadao);

 float saidaVisitante(pavilhao p, int cartao_cidadao);

 double caixa_pavilhao(pavilhao p);

 int pavilhaoVazio(pavilhao p);

 void tiraVisitantesPavilhao(pavilhao p);

 void * vetor_clientes_pav(pavilhao p);

 iterador iteradorPav(pavilhao p);

 #endif // _H_PAVILHAO
