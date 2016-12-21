#ifndef VALIDACAOCRUZADA_H
#define VALIDACAOCRUZADA_H

#include "matrizdeconfusao.h"
#include "ad.h"
#include "knn.h"
#include "perceptron.h"

class ValidacaoCruzada{
    public:
        ValidacaoCruzada(int K, int Total, int **Banco)
        :k(K),
        banco(Banco){
            numBancoTeste = Total/k;
            numBancoTreinamento = numBancoTeste*(k-1);
            bancoTeste = new int*[numBancoTeste];
            bancoTreinamento = new int *[numBancoTreinamento];
            
            grupoSelect = k;//força gerar os bancos do grupo 0
        }
        
        void atualizarBancos(){
            if(grupoSelect < (k-1)){
                int count3 = numBancoTeste*(grupoSelect++);
                int count2 = numBancoTeste*grupoSelect;
                for(int count=0; count<numBancoTeste; count++, count2++, count3++){
                    bancoTeste[count] = banco[count2];
                    bancoTreinamento[count3] = banco[count3];
                }
            }else{
                //Gerar os bancos do grupo 0
                int count;
                grupoSelect = 0;
                //Banco de Teste;
                for(count=0; count<numBancoTeste; count++){
                    bancoTeste[count] = banco[count];
                }
                //Banco de Treinamento
                int total = numBancoTreinamento+numBancoTeste;
                for(int count1=0; count<total; count++, count1++){
                    bancoTreinamento[count1] = banco[count];
                }
            }
        }
        
        MatrizDeConfusao *validarArvoreDeDecisao(){
            MatrizDeConfusao *matrizDeConfusao = new MatrizDeConfusao();
            (matrizDeConfusao -> titulo) = "Arvore de Decisao";
            Ad *ArvoreDeDecisao;
            int classificacao;
            //Esperimentos
            for(int count=0; count<k; count++){
                atualizarBancos();
                ArvoreDeDecisao = new Ad(9, numBancoTreinamento, bancoTreinamento);
                ArvoreDeDecisao -> treinar();
                //Testar
                for(int count1=0; count1<numBancoTeste; count1++){
                    classificacao = ArvoreDeDecisao -> classificar(bancoTeste[count1]);
                    if(classificacao){
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[0][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[0][1])++; 
                        }
                    }else{
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[1][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[1][1])++; 
                        }
                    }
                }
            }
            matrizDeConfusao -> imprimirAvaliacao();
            return matrizDeConfusao;
        }
        
        MatrizDeConfusao *validarKNN(){
            MatrizDeConfusao *matrizDeConfusao = new MatrizDeConfusao();
            (matrizDeConfusao -> titulo) = "KNN - K nearest neighbors";
            int kk=10;//corte
            Knn *knn = new Knn(kk, 9, numBancoTreinamento);
            
            int classificacao;
            //Esperimentos
            for(int count=0; count<k; count++){
                atualizarBancos();
                knn -> setarBanco(bancoTreinamento);
                //Testar
                for(int count1=0; count1<numBancoTeste; count1++){
                    classificacao = knn -> classificar(bancoTeste[count1]);
                    if(2 == classificacao){
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[0][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[0][1])++; 
                        }
                    }else{
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[1][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[1][1])++; 
                        }
                    }
                }
            }
            matrizDeConfusao -> imprimirAvaliacao();
            return matrizDeConfusao;
        }
        
        MatrizDeConfusao *validarPerceptron(){
            MatrizDeConfusao *matrizDeConfusao = new MatrizDeConfusao();
            (matrizDeConfusao -> titulo) = "Perceptron";
            
            Perceptron *perceptron = new Perceptron(9, 0.2, 200);
            
            int classificacao;
            //Esperimentos
            for(int count=0; count<k; count++){
                atualizarBancos();
                perceptron -> treinar( 0.5, numBancoTreinamento, bancoTreinamento);
                //Testar
                for(int count1=0; count1<numBancoTeste; count1++){
                    classificacao = perceptron -> classificar(bancoTeste[count1]);
                    if(classificacao){
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[0][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[0][1])++; 
                        }
                    }else{
                        if(2 == bancoTeste[count1][9]){
                            (matrizDeConfusao -> matriz[1][0])++; 
                        }else{
                            (matrizDeConfusao -> matriz[1][1])++; 
                        }
                    }
                }
            }
            matrizDeConfusao -> imprimirAvaliacao();
            return matrizDeConfusao;
        }
        
        int k;
        int grupoSelect;//Grupo selecionado
        int **banco;
        int numBancoTeste;//numero de instancias no banco de teste (Total/k)
        int **bancoTeste;
        int numBancoTreinamento;//numero de instancias no banco de treinamento (numBancoTeste*(k-1))
        int **bancoTreinamento;
};

#endif
