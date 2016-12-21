#include <iostream>
using std::cout;
using std::cerr;

#include <fstream>
using std::ifstream;

#include "validacaocruzada.h"
#include "matrizdeconfusao.h"

int main(){
    int const numInstancia=680;
    int const numAtributos=9;
    int const K = 10;//Numero de dobras da validação cruzada
    
    // Abrir arquivo com o conjunto de treinamento
    // em modo leitura;
    ifstream arquivo("banco.txt");
    if(!arquivo){
        cerr << "Arquivo nao pode ser aberto\n";
        system("PAUSE");
        exit(1);
    }
    
    //Gerar banco
    int **banco = new int*[numInstancia];
    for(int count=0; count<numInstancia; count++){
        banco[count] = new int[numAtributos+1];
        for(int count1=0; count1<=numAtributos; count1++){
            arquivo >>  banco[count][count1];
        }
    }
    
    
    ValidacaoCruzada *validacaoCruzada = new ValidacaoCruzada(K, numInstancia, banco);
    
    MatrizDeConfusao *matrizDeConfusao[3];
    
    //Arvore de Decisão
    cout << "Validacao da Arvore de Decisao:\n";
    matrizDeConfusao[0] = validacaoCruzada -> validarArvoreDeDecisao();
    
    cout << "\n////////////////////////\n\n";
    
    //KNN - K nearest neighbors
    cout << "Validacao da KNN:\n";
    matrizDeConfusao[1] = validacaoCruzada -> validarKNN();
    
    cout << "\n////////////////////////\n\n";
    
    //RNA perceptron
    cout << "Validacao da Perceptron:\n";
    matrizDeConfusao[2] = validacaoCruzada -> validarPerceptron();
    
    cout << "\n////////////////////////\n\n";
    cout << "O melhor algoritmo para:\n";
    double melhor;
    int indice;
    char *mesagem[3]= {"Taxa de acerto total: ",
                        "Taxa de acerto benigno: ",
                        "Taxa de acerto maligno: "};
    for(int count=0; count < 3; count++){
        melhor = matrizDeConfusao[0] -> taxa[count];
        indice = 0;
        for(int matriz = 1; matriz < 3; matriz++){
            if((matrizDeConfusao[matriz]->taxa[count]) > melhor){
                melhor = matrizDeConfusao[matriz] -> taxa[count];
                indice = matriz;
            }
        }
        cout << mesagem[count] << (matrizDeConfusao[indice] -> titulo) << "\n";
    }
    
    getchar();
    getchar();
    return 0;
}
