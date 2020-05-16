/***********************************************************
 * TAD Visitante
 * .h
 **********************************************************/

 #ifndef _H_VISITANTE
 #define _H_VISITANTE

 typedef struct _visitante *visitante;

 visitante criaVisitante(int cartao_cidadao, int contribuinte, char * nome);

 void destroiVisitante(visitante v);

 float devolveConsumoBar(visitante v);

 int devolveLocalizacao(visitante v);

 int devolveTempoTrampolim(visitante v);

 void alteraLocal(visitante v, int nova_loc);

 char* devolveNome(visitante v);

 void aumentaTempoTramp(visitante v, int tempo);

 void visitanteCompra(visitante v, int quantidade, float preco);

 float pagamento(visitante v);

 int devolveCC(visitante v);

 #endif // _H_VISITANTE
