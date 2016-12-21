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
            // Gerar a ramifica��o do node;
            // percorrer o dom�nio = 1:10;
            for(int valorDoDominio=1; valorDoDominio<=10; valorDoDominio++){
                conjAnalisado = new Conjunto(valorDoDominio, nome, conjunto);
                //Identificar a situa��o
                if((conjAnalisado -> instancia.empty())){
                    //Situa��o 1: conjunto sem inst�ncias
                    if((conjunto->positivo)>(conjunto->negativo)){
                        ramificacao[valorDoDominio-1] = new Classificacao(true);
                    }else{
                        ramificacao[valorDoDominio-1] = new Classificacao(false);
                    }
                }else if((conjunto -> positivo) == (conjunto -> instancia.size())){
                    //Situa��o 2: todas as instancias pertencem a
                    //classe positiva
                    ramificacao[valorDoDominio-1] = new Classificacao(true);
                }else if((conjunto -> negativo) == (conjunto -> instancia.size())){
                    //Situa��o 2: todas as instancias pertencem a
                    //classe negativa
                    ramificacao[valorDoDominio-1] = new Classificacao(false);
                }else if(!(conjunto -> numAtributos)){
                    //Situa��o 3: conjunto sem atributos
                    if((conjAnalisado -> positivo)>(conjAnalisado -> negativo)){
                        ramificacao[valorDoDominio-1] = new Classificacao(true);
                    }else{
                        ramificacao[valorDoDominio-1] = new Classificacao(false);
                    }
                }else{//Situa��o 4
                    //Informa��o
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
                    if(2==instAnalisada[9]){//Classifica��o da instancia
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
