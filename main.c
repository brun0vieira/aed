#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "pavilhao.h"
#include "bar.h"
#include "trampolim.h"
#include "visitante.h"
#include "iterador.h"
#include "produto.h"
#include "dicionario.h"

#define NUMERO_VISITANTES 1500
#define NUM_PRODUTOS 3
#define MAX_LINHA 50

// Protótipos

void interpretador(pavilhao p);
void tratarE(pavilhao p, char * l);
void tratarF(pavilhao p, char * l);
void tratarL(pavilhao p, char * l);
void tratarT(pavilhao p, char * l);
void tratarS(pavilhao p, char * l);
void tratarV(pavilhao p, char * l);
void tratarQ(pavilhao p, char * l);
void tratarC(pavilhao p);
void tratarP(pavilhao p);
void tratarX(pavilhao p);

int main() {

    int numero_trampolins, stocks[NUM_PRODUTOS];
    float precos[NUM_PRODUTOS];
    char nomes_produtos[NUM_PRODUTOS] = {'C','S','B'};
    pavilhao p;

    char linha_comando1[MAX_LINHA], linha_comando2[MAX_LINHA], linha_comando3[MAX_LINHA], linha_comando4[MAX_LINHA];

    fgets(linha_comando1, MAX_LINHA, stdin);

    if(sscanf(linha_comando1, "%d", &numero_trampolins)==1 && numero_trampolins <= 500 && numero_trampolins>0) {

        fgets(linha_comando2, MAX_LINHA, stdin);

        if(sscanf(linha_comando2, "%d %f", &stocks[0], &precos[0])==2) {

            fgets(linha_comando3, MAX_LINHA, stdin);

            if(sscanf(linha_comando3, "%d %f", &stocks[1], &precos[1])==2) {

                fgets(linha_comando4, MAX_LINHA, stdin);

                if(sscanf(linha_comando4, "%d %f", &stocks[2], &precos[2])==2) {

                    p = criaPavilhao(NUMERO_VISITANTES, numero_trampolins, nomes_produtos, stocks, precos);
                    printf("Abertura pavilhao.\n");
                    interpretador(p);
                }
            }
        }
    }

}

void interpretador(pavilhao p) {

    char linha_comando[MAX_LINHA], comando;

    fflush(stdin);

    fgets(linha_comando, MAX_LINHA, stdin);

    comando = toupper(linha_comando[0]);

    while(comando != 'X') {

        switch(comando) {

            case 'E': tratarE(p, &linha_comando[2]); break;
            case 'F': tratarF(p, &linha_comando[2]); break;
            case 'L': tratarL(p, &linha_comando[2]); break;
            case 'T': tratarT(p, &linha_comando[2]); break;
            case 'S': tratarS(p, &linha_comando[2]); break;
            case 'V': tratarV(p, &linha_comando[2]); break;
            case 'Q': tratarQ(p, &linha_comando[2]); break;
            case 'C': tratarC(p); break;
            case 'P': tratarP(p); break;
            default : printf("Comando invalido.\n");

        }
        fgets(linha_comando, MAX_LINHA, stdin);
        comando = toupper(linha_comando[0]);
    }

    tratarX(p);

}

// Codigo das funcoes para tratar dos comandos...

void tratarE(pavilhao p, char* l) {

    int cartao_cidadao, n_contribuinte;
    char nome_visitante[50];

    if(sscanf(l, "%d %d", &cartao_cidadao, &n_contribuinte) != 2){
        printf("Dados invalidos.\n");
    }

    else {

        fgets(nome_visitante, 50, stdin);
        nome_visitante[strlen(nome_visitante)-1]= '\0';

        if(nome_visitante[0]== '\0' || n_contribuinte<=0 || cartao_cidadao<=0)
            printf("Dados invalidos.\n");

        else {

            if(existeVisitantePavilhao(p, cartao_cidadao)==1)
                printf("Visitante ja no pavilhao.\n");

            else {

                entraVisitantePavilhao(p,cartao_cidadao,n_contribuinte,nome_visitante);
                printf("Entrada autorizada.\n");

            }

        }
    }
}

void tratarF(pavilhao p, char * l) {
    int cartao_cidadao;

    if(sscanf(l, "%d", &cartao_cidadao) !=1)
        printf("Dados invalidos.\n");

    else {

        if(cartao_cidadao<=0)
            printf("Dados invalidos.\n");

        else {

            if(existeVisitantePavilhao(p, cartao_cidadao)==0)
                printf("Visitante nao esta no pavilhao.\n");

            else {

                if((devolveLocalizacao(elementoDicionario(dicionarioVisitantes(p),&cartao_cidadao))) != -1 )
                    printf("Chegada nao autorizada a fila.\n");

                else {

                    meteNaFila(p,cartao_cidadao);
                    printf("Chegada autorizada a fila.\n");


                }
            }
        }
    }
}

void tratarL(pavilhao p, char * l) {

    int h_entrada, m_entrada, entrada;

    if(sscanf(l, "%d:%d", &h_entrada, &m_entrada) != 2)
        printf("Dados invalidos.\n");

    else {
            if(h_entrada < 0 || m_entrada < 0 || h_entrada > 24 || m_entrada > 60)
                printf("Dados invalidos.\n");

            else {
                entrada = entradaVisitanteTrampolim(p, h_entrada, m_entrada);
                if(entrada == -1)
                    printf("Fila vazia.\n");

                else {

                    if(entrada == 0)
                        printf("Trampolins ocupados.\n");

                    else
                        printf("Entrada de %d visitantes nos trampolins.\n", entrada);
                }

            }

    }

}

void tratarT(pavilhao p, char * l) {

    int numero_trampolim;

    if(sscanf(l, "%d", &numero_trampolim) != 1)
        printf("Dados invalidos.\n");

    else {

        if(numero_trampolim < 1 || numero_trampolim > numeroTrampolinsPavilhao(p) )
            printf("Trampolim inexistente.\n");

        else {

            if(disponibilidadeTrampolim(trampolimPav(p, numero_trampolim)))
                printf("Trampolim %d vazio.\n", numero_trampolim);

            else {
                printf("%s esta no trampolim %d.\n", devolveNome(visitanteTrampolim(trampolimPav(p, numero_trampolim))), numero_trampolim);
            }
        }
    }

}

void tratarS(pavilhao p, char * l) {

    int cartao_cidadao, h_saida, m_saida, dados_introduzidos, tempo_utilizacao, localizacao;

    dados_introduzidos=sscanf(l, "%d %d:%d", &cartao_cidadao, &h_saida, &m_saida);

    if(dados_introduzidos!=3 || cartao_cidadao <=0)
        printf("Dados invalidos.\n");

        else {

           if(existeVisitantePavilhao(p, cartao_cidadao) == 0)
                printf("Visitante nao esta no pavilhao.\n");

           else {

                localizacao = devolveLocalizacao(elementoDicionario(dicionarioVisitantes(p), &cartao_cidadao));
                if(localizacao == -1 || localizacao == 0) {

                    printf("Saida trampolim nao autorizada.\n");

                }

                else {

                    tempo_utilizacao = (h_saida*60) + m_saida;
                    if(tempo_utilizacao <= tempoEntradaTrampolim(trampolimPav(p, localizacao)))
                        printf("Hora errada.\n");

                    else {
                        tempo_utilizacao = tempo_utilizacao - tempoEntradaTrampolim(trampolimPav(p, localizacao));
                        removeVisitanteTrampolim(p, localizacao, tempo_utilizacao);
                        printf("Saida trampolim autorizada.\n");

                    }
                }
           }

        }
    }





void tratarV(pavilhao p, char * l) {

    char tipo_produto;
    int quantidade, cartao_cidadao, local;
    int valido;

    valido = sscanf(l, "%c %d %d", &tipo_produto, &quantidade, &cartao_cidadao);

    if( (valido != 3) || (cartao_cidadao <= 0)  )
        printf("Dados invalidos.\n");

    else {

        tipo_produto = toupper(l[0]);

        if(tipo_produto != 'C' && tipo_produto !='S' && tipo_produto != 'B')
            printf("Dados invalidos.\n");

        else {

            if(existeVisitantePavilhao(p, cartao_cidadao) == 0)
                printf("Visitante nao esta no pavilhao.\n");

            else {
                local = devolveLocalizacao(elementoDicionario(dicionarioVisitantes(p), &cartao_cidadao));
                if(local != -1) // nao esta no bar
                    printf("Venda nao autorizada.\n");

                else {

                    if(quantidade > devolveStockProduto(produtos(bar_pavilhao(p), tipo_produto))){

                        printf("Produto %c esgotado.\n", tipo_produto);
                    }

                    else {

                        efetuaCompra(p, tipo_produto, quantidade, cartao_cidadao);
                        printf("Venda autorizada.\n");

                    }

                }

            }
        }
    }
}

void tratarQ(pavilhao p, char * l) {

   int cartao_cidadao, local;

   if((sscanf(l, "%d", &cartao_cidadao) != 1) || cartao_cidadao <= 0)
        printf("Dados invalidos.\n");

   else {

        if(existeVisitantePavilhao(p, cartao_cidadao) == 0)
            printf("Visitante nao esta no pavilhao.\n");

        else {
            local = devolveLocalizacao(elementoDicionario(dicionarioVisitantes(p), &cartao_cidadao));

            if(local != -1)
                printf("Saida nao autorizada.\n");

            else
                printf("Saida autorizada, valor a pagar %.2f euros.\n", saidaVisitante(p, cartao_cidadao));
        }

   }



}

void tratarC(pavilhao p) {

    printf("Caixa: %.2f euros.\n", caixa_pavilhao(p));

}

void tratarP(pavilhao p) {
/*
    void **vetor_visitantes;

    int i, local, num_visitantes;
*/
    if(pavilhaoVazio(p) == 1)
        printf("Sem visitantes no pavilhao.\n");
/*
    else {
         // ORDENA
         num_visitantes = tamanhoDicionario(dicionarioVisitantes(p));
         for(i=0; i<num_visitantes; i++) {

            local=devolveLocalizacao(/*ordenados);

            printf("%s esta em ", devolveNome(/*ORDENADOS));

            if(local == -1)
                printf("bar.\n");

            else {

                if(local == 0)
                    printf("fila de trampolins.\n");

                else
                    printf("trampolim %d.\n", local);

            }

            }

    }*/
}

void tratarX(pavilhao p) {

    if(pavilhaoVazio(p) != 1)
        tiraVisitantesPavilhao(p);

    printf("Caixa: %.2f euros.\n",  caixa_pavilhao(p));
    printf("Stock cafe: %d.\n", devolveStockProduto(produtos(bar_pavilhao(p), 'C')));
    printf("Stock sumo: %d.\n", devolveStockProduto(produtos(bar_pavilhao(p), 'S')));
    printf("Stock bolo: %d.\n", devolveStockProduto(produtos(bar_pavilhao(p), 'B')));

}
