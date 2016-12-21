#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class Perceptron{
    public:
        Perceptron(int entradas, double taxaDeAprendizagem, int epocas)
        :numEntradas(entradas),
        L(taxaDeAprendizagem),
        numDeEpocas(epocas){
            pesoEntrada = new double[numEntradas+1];//+1 para o bias
            
        }
        
        void treinar(double peso, int numInstancias, int **banco){
            for(int count=0; count<=numEntradas; count++){
                pesoEntrada[count] = peso;
            }
            int fx,erro;
            for(int epoca=0; epoca < numDeEpocas; epoca++){
//                cout << "epoca: " << epoca << "\n";
                for(int instancia=0; instancia< numInstancias; instancia++){
                    //Calcular a saida
                    fx = classificar(banco[instancia]);
                    //Erro da saída (esperado - obtido)
                    erro = ((banco[instancia][9] / 2) % 2) - fx;
                    //Atualizar os pesos
                    for(int count=0; count<numEntradas; count++){
                        pesoEntrada[count] += L * erro * banco[instancia][count];
                    }
                    pesoEntrada[numEntradas] -= L * erro;//bias
                }
//                cout << "Pesos: ";
//                for(int count=0; count<numEntradas; count++){
//                    cout << pesoEntrada[count] << " "; 
//                }
//                cout << "\n";
            }
        }
        
        int classificar(int *instancia){
            double x=0.0;
            //Entrada
            for(int count=0; count<numEntradas; count++){
                x += instancia[count]*pesoEntrada[count];
            }
            x -= pesoEntrada[numEntradas];//bias
            //Função de ativação
            if(x>0){
                return 1;
            }else{
                return 0;
            }
        }
        
        int numEntradas;
        double *pesoEntrada;
        double L;
        int numDeEpocas;
};

#endif
