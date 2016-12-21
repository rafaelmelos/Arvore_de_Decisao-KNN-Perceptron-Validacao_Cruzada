#ifndef AD_H
#define AD_H

#include <math.h>

#include "node.h"
#include "conjunto.h"
#include "atributo.h"

class Ad{
    public:
        Ad(int numeroDeAtributos, int numeroDeInstancias, int **bancoDeInstancias)
        :numAtributos(numeroDeAtributos),
        numInstancia(numeroDeInstancias),
        banco(bancoDeInstancias){
        }
        
        void treinar(){
            conjuntoInicial = new Conjunto(numInstancia, numAtributos, banco);
            //Informação
            int P=(conjuntoInicial -> positivo);
            int N=(conjuntoInicial -> negativo);
                    
            double info = informacao((double) P/(P+N), (double) N/(P+N));
            //Escolher o melhor atributo
            int atributo = 0; 
            double maiorGanho, testGanho;
            maiorGanho = info - entropia(atributo);//Ganho do primeiro atributo
            for(int count=1; count < numAtributos; count++){
                testGanho = info - entropia(count);//Ganho
                 if(maiorGanho < testGanho){
                    maiorGanho = testGanho;
                    atributo = count;
                }
            }
            raiz = new Atributo(atributo, conjuntoInicial);
        }
        
        int classificar(int *instancia){
            Node *node = raiz;
            while((node -> nome) != numAtributos){
                Atributo *atributo = static_cast< Atributo * >(node);
                node = (atributo -> ramificacao[instancia[(node -> nome)]-1]);
            }
            Classificacao *classificacao = static_cast< Classificacao * >(node);
            if(classificacao -> positiva){
                return 1;
            }else{
                return 0;
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
            //Setar as instancias;
            int *instAnalisada;
            for(int count=0; count<numInstancia; count++){
                instAnalisada = conjuntoInicial -> instancia[count];
                if(instAnalisada[atributo] == valor){
                    if(2==instAnalisada[numAtributos]){//Classificação da instancia
                        Patv++;
                    }else{
                        Natv++;
                    }
                }
            }
            return ((Patv + Natv)/((conjuntoInicial -> positivo)+(conjuntoInicial -> negativo)))*informacao(Patv, Patv + Natv);
        }
        
        int **banco;
        Node *raiz;
        int numInstancia;
        int numAtributos;
        Conjunto *conjuntoInicial;
};

#endif
