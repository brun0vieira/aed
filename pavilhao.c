/***********************************************************
 * TAD Pavilhao
 * .c
 **********************************************************/
 #define NUMPRODUTOS 3
 #include <stdio.h>
 #include <stdlib.h>

 #include "pavilhao.h"
 #include "bar.h"
 #include "visitante.h"
 #include "fila.h"
 #include "dicionario.h"


 struct _pavilhao {

    trampolim* trampolins;
    int numero_trampolins;
    double caixa;
    bar bar;
    dicionario visitantes;
    fila filaEspera;

 };

 pavilhao criaPavilhao(int num_visitantes, int num_trampolins, char* nomes_produtos, int* stocks, float* precos) {

    int i;

    pavilhao p = (pavilhao) malloc(sizeof(struct _pavilhao));

    if(p==NULL)
        return NULL;

    p->trampolins = (trampolim*) malloc(sizeof(trampolim*)*num_trampolins);

    for(i=0; i<num_trampolins; i++)
        p->trampolins[i] = criaTrampolim();

    p->numero_trampolins=num_trampolins;
    p->caixa=0;
    p->bar=criaBar(NUMPRODUTOS, nomes_produtos, stocks, precos);
    p->visitantes = criaDicionario(num_visitantes, 0);
    p->filaEspera=criaFila(num_visitantes);

    return p;

 }

 void destroiPavilhao(pavilhao p) {

    int i;
    for(i=0; i<p->numero_trampolins; i++)
        destroiTrampolim(p->trampolins[i]);

    free(p);

 }

 int existeVisitantePavilhao(pavilhao p, int cartao_cidadao){
    if(existeElemDicionario(p->visitantes, &cartao_cidadao))
        return 1;
    else
        return 0;
 }

 void entraVisitantePavilhao(pavilhao p, int cartao_cidadao, int n_contribuinte, char* nome_cliente){
    adicionaElemDicionario(p->visitantes, &cartao_cidadao, criaVisitante(cartao_cidadao,n_contribuinte,nome_cliente));
 }

 dicionario dicionarioVisitantes(pavilhao p){
    return p->visitantes;
 }

void meteNaFila(pavilhao p, int cartao_cidadao){
    adicionaElemFila(p->filaEspera, elementoDicionario(p->visitantes, &cartao_cidadao));
    alteraLocal(elementoDicionario(p->visitantes,&cartao_cidadao),0);
}

int entradaVisitanteTrampolim(pavilhao p, int h_entrada, int m_entrada) {
    int contador=0;
    int i=0;

    visitante v;

    if(vaziaFila(p->filaEspera))
        return -1;

    while( i < p->numero_trampolins && !vaziaFila(p->filaEspera)) {

        if(disponibilidadeTrampolim(p->trampolins[i]) == 1) {
            v = removeElemFila(p->filaEspera);
            colocaNoTrampolim(p->trampolins[i], v, h_entrada, m_entrada);
            alteraLocal(v, i+1);
            contador++;
        } i++;
    } return contador;
}

int numeroTrampolinsPavilhao(pavilhao p) {

    return p->numero_trampolins;

}

trampolim trampolimPav(pavilhao p, int numero_trampolim) {

    return p->trampolins[numero_trampolim-1];

}

void removeVisitanteTrampolim(pavilhao p, int numero_tramp, int tempo_utilizacao) {

    visitante v = saidaTrampolim(p->trampolins[numero_tramp-1]);
    alteraLocal(v, -1);
    aumentaTempoTramp(v, tempo_utilizacao);

}

void removeVisitanteFila(pavilhao p) {

     visitante v = removeElemFila(p->filaEspera);
     alteraLocal(v, -1);

}

void* bar_pavilhao(pavilhao p) {

    return p->bar;

}

void efetuaCompra(pavilhao p, char nome_produto, int quantidade, int cartao_cidadao) {

    decrementaStockBar(bar_pavilhao(p), nome_produto, quantidade);
    visitanteCompra(elementoDicionario(p->visitantes, &cartao_cidadao), quantidade, devolvePrecoProduto(produtos(bar_pavilhao(p), nome_produto)));

}

float saidaVisitante(pavilhao p, int cartao_cidadao) {

    visitante v = removeElemDicionario(p->visitantes, &cartao_cidadao);
    float valor_pagar = pagamento(v);

    p->caixa = p->caixa + valor_pagar;
    return valor_pagar;

}

double caixa_pavilhao(pavilhao p) {

    return p->caixa;

}

int pavilhaoVazio(pavilhao p) {

    if(vazioDicionario(p->visitantes))
        return 1;

    return 0;
}

void tiraVisitantesPavilhao(pavilhao p) {
    void **vetor_clientes;
    int quantidade_clientes, i, local;

    quantidade_clientes = tamanhoDicionario(p->visitantes);
    vetor_clientes = vetor_clientes_pav(p);

    for(i=0; i < quantidade_clientes; i++) {

        local = devolveLocalizacao(vetor_clientes[i]);

        if(local > 0)
            removeVisitanteTrampolim(p, local, 24*30);

        else {

            if(local==0) {

                while(!(vaziaFila(p->filaEspera))) {

                    removeVisitanteFila(p);

                }
            }
        }
        saidaVisitante(p, devolveCC(vetor_clientes[i]));

    }

}

void * vetor_clientes_pav(pavilhao p) {

    iterador itera;
    int i;
    itera = iteradorPav(p);

    void **vetor;

    vetor = (void*) malloc(sizeof(void*)*tamanhoDicionario(p->visitantes));

    for(i=0 ; i< tamanhoDicionario(p->visitantes); i++){

        vetor[i]=seguinteIterador(itera);

    }

    return vetor;

}

iterador iteradorPav(pavilhao p) {

    iterador itera;
    itera= iteradorDicionario(p->visitantes);
    return itera;

}

