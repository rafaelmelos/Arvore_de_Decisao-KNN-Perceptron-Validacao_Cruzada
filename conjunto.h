#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <vector>
using std::vector;

class Conjunto{
    public:
        Conjunto(int numInstancias, int numDeAtributos, int **banco)
        :numAtributos(numDeAtributos){
            int count;
            positivo = negativo = 0;
            atributo = new int[numAtributos];
            //setar os atributos;
            for(count=0; count<numAtributos; count++){
                atributo[count] = count;
            }
            for(count=0; count<numInstancias; count++){
                instancia.push_back(banco[count]);
                if(2==banco[count][9]){//Classificação da instancia
                    positivo++;
                }else{
                    negativo++;
                }
            }
        }
        
        Conjunto(int valorDoDominio, int indiceDoAtributo, Conjunto *conjuntoDoPai){
            int count, count2, count3;
            positivo = negativo = 0;
            numAtributos = (conjuntoDoPai->numAtributos) - 1;
            atributo = new int[numAtributos];
            //setar os atributos;
            for(count=0, count2=0; count<numAtributos; count2++){
                count3 = conjuntoDoPai -> atributo[count2];
                if(count3 != indiceDoAtributo){
                    atributo[count++] = count3;
                }
            }
            //Setar as instancias;
            int numInstanciasDoPai = conjuntoDoPai -> instancia.size();
            int *instAnalisada;
            for(count=0; count<numInstanciasDoPai; count++){
                instAnalisada = conjuntoDoPai -> instancia[count];
                if(instAnalisada[indiceDoAtributo] == valorDoDominio){
                    instancia.push_back(instAnalisada);
                    if(2==instAnalisada[9]){//Classificação da instancia
                        positivo++;
                    }else{
                        negativo++;
                    }
                }
            }
        }
        
        vector< int * > instancia;
        int numAtributos;
        int *atributo;
        int positivo;
        int negativo;
};

#endif
