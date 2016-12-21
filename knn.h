#ifndef KNN_H
#define KNN_H

class Knn{
    public:
        Knn(int K, int numeroDeAtributos, int numeroDeInstancias)
        :k(K-1),
        numAtributos(numeroDeAtributos),
        numIntancias(numeroDeInstancias){
        }
        
        void setarBanco(int **bancoDeInstancias){
            banco = bancoDeInstancias;
        }
        
        int classificar(int *instancia){
            int count, count1, dist, classif;
            int matriz[numIntancias][2];
            
            for(count=0; count<numIntancias; count++){
                //Calcular a distancia da instancia
                matriz[count][0] = 0;
                for(count1=0; count1<numAtributos; count1++){
                    matriz[count][0] += (banco[count][count1] - instancia[count1])*(banco[count][count1] - instancia[count1]);
                }
                matriz[count][1] = banco[count][9];
            }
            
            //Ordenar
            for(count=1; count<=numIntancias; count++){
                dist = matriz[count][0];
                classif = matriz[count][1];
                for(count1=count-1; count1>-1 && matriz[count1][0] > dist; count1--){
                    matriz[count1+1][0] = matriz[count1][0];
                    matriz[count1+1][1] = matriz[count1][1];
                }
                matriz[count1+1][0] = dist;
                matriz[count1+1][1] = classif;
            }
            
            int positivo = 0, negativo = 0;
            for(count=0; count < k || matriz[count][0] == matriz[k][0]; count++){
                if(2 == matriz[count][1]){
                    positivo++;
                }else{
                    negativo++;
                }
            }
            
            if(positivo >= negativo){
                return 2;
            }else{
                return 4;
            }
        }
        
        int k;
        int numAtributos;
        int numIntancias;
        int **banco;
};

#endif
