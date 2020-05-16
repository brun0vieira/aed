/***********************************************************
 * TAD Visitante
 * .c
 **********************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "visitante.h"

 struct _visitante {

    int cartao_cidadao, contribuinte;
    char *nome;
    int localizacao;
    int tempo_trampolim;
    float consumoBar;

 };

 visitante criaVisitante(int cartao_cidadao, int contribuinte, char* nome) {

    visitante v = (visitante) malloc(sizeof(struct _visitante));

    if(v==NULL)
        return NULL;

    v->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));

    strcpy(v->nome, nome);

    if(v->nome == NULL)
        return NULL;

    v->cartao_cidadao = cartao_cidadao;
    v->contribuinte = contribuinte;
    v->localizacao = -1;
    v->consumoBar = 0;
    v->tempo_trampolim = 0;

    return v;

 }

 void destroiVisitante(visitante v) {

    free(v->nome);
    free(v);

 }

 float devolveConsumoBar(visitante v) {

    return v->consumoBar;
}

 int devolveLocalizacao(visitante v) {

    return v->localizacao;

 }

 int devolveTempoTrampolim(visitante v) {

    return v->tempo_trampolim;

 }

 void alteraLocal(visitante v, int nova_loc){
     v->localizacao=nova_loc;
 }

 char* devolveNome(visitante v) {

    return v->nome;

 }

 void aumentaTempoTramp(visitante v, int tempo) {

    v->tempo_trampolim = v->tempo_trampolim + tempo;

 }

 void visitanteCompra(visitante v, int quantidade, float preco) {

    v->consumoBar = v->consumoBar + (preco*quantidade);
 }

 float pagamento(visitante v) {

    float valor_pagar, valorTrampolim;

    if(devolveConsumoBar(v)==0 && devolveTempoTrampolim(v)==0)
        return 5;

    valorTrampolim = ((devolveTempoTrampolim(v))/30)*5;

    valor_pagar = devolveConsumoBar(v) + valorTrampolim;

    if(devolveTempoTrampolim(v)%30)
        valor_pagar = valor_pagar + 5;

    return valor_pagar;
 }

 int devolveCC(visitante v) {

    return v->cartao_cidadao;

 }
