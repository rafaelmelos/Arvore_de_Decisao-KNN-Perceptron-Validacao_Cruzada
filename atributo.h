#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <iostream>
using std::cin;

#include "node.h"
#include "conjunto.h"
#include "ad.h"
#include "classificacao.h"

class Atributo : public Node{
    public:
        Atributo(int indiceDoAtributo, Conjunto *conjuntoDoAtributo)
        :conjunto(conjuntoDoAtributo){
            nome = indiceDoAtributo;
            Conjunto *conjAnalisado;
            // Gerar a ramificação do node;
            // percorrer o domínio = 1:10;
            for(int valorDoDominio=1; valorDoDominio<=10; valorDoDominio++){
                conjAnalisado = new Conjunto(valorDoDominio, nome, conjunto);
                //Identificar a situação
                if((conjAnalisado -> instancia.empty())){
                    //Situação 1: conjunto sem instâncias
                    if((conjunto->positivo)>(conjunto->negativo)){
                        ramificacao[valorDoDominio-1] = new Classificacao(true);
                    }else{
                        ramificacao[valorDoDominio-1] = new Classificacao(false);
                    }
                }else if((conjunto -> positivo) == (conjunto -> instancia.size())){
                    //Situação 2: todas as instancias pertencem a
                    //classe positiva
                    ramificacao[valorDoDominio-1] = new Classificacao(true);
                }else if((conjunto -> negativo) == (conjunto -> instancia.size())){
                    //Situação 2: todas as instancias pertencem a
                    //classe negativa
                    ramificacao[valorDoDominio-1] = new Classificacao(false);
                }else if(!(conjunto -> numAtributos)){
                    //Situação 3: conjunto sem atributos
                    if((conjAnalisado -> positivo)>(conjAnalisado -> negativo)){
                        ramificacao[valorDoDominio-1] = new Classificacao(true);
                    }else{
                        ramificacao[valorDoDominio-1] = new Classificacao(false);
                    }
                }else{//Situação 4
                    //Informação
                    int P=(conjunto -> positivo);
                    int N=(conjunto -> negativo);
                    double info = informacao((double) P/(P+N), (double) N/(P+N));
                    //Escolher o melhor atributo
                    int atributo = conjAnalisado -> atributo[0];
                     double maiorGanho, testGanho;
                    maiorGanho = info - entropia(atributo);//Ganho do primeiro atributo
                    int numAtributos = (conjAnalisado -> numAtributos);
                    for(int count=1; count < numAtributos; count++){
                        testGanho = info - entropia(conjAnalisado -> atributo[count]);//Ganho
                        if(maiorGanho < testGanho){
                            maiorGanho = testGanho;
                            atributo = conjAnalisado -> atributo[count];
                        }
                    }
                    ramificacao[valorDoDominio-1] = new Atributo(atributo, conjAnalisado);
                }
            }
        }
        
        double informacao(double X, double Y){
            return -X * log2(X) -Y * log2(Y);
        }
        
        double entropia(int atributo){
            double entro = R(atributo, 1);
            for(int count=2; count<=10; count++){
                entro += R(atributo, count);
            }
            
            return entro;
        }
        
        double R(int atributo, int valor){
            int Patv=0, Natv=0;
            int numInstancias = conjunto -> instancia.size();
            int *instAnalisada;
            for(int count=0; count<numInstancias; count++){
                instAnalisada = conjunto -> instancia[count];
                if(instAnalisada[atributo] == valor){
                    if(2==instAnalisada[9]){//Classificação da instancia
                        Patv++;
                    }else{
                        Natv++;
                    }
                }
            }
            return ((Patv + Natv)/((conjunto -> positivo)+(conjunto -> negativo)))*informacao(Patv, Patv + Natv);
        }
        
        Node *ramificacao[10];
        Conjunto *conjunto;
};

#endif
