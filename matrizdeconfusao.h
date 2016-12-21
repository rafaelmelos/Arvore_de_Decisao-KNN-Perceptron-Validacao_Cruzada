#ifndef MATRIZDECONFUSAO_H
#define MATRIZDECONFUSAO_H

#include <string>
using std::string;

class MatrizDeConfusao{
    public:
        MatrizDeConfusao(){
            matriz[0][0] = matriz[0][1] = matriz[1][0] = matriz[1][1] = 0;
        }
        
        void imprimirAvaliacao(){
            cout << "matriz de confusao:\n";
            cout << matriz[0][0] << "\t" << matriz[0][1] << "\n";
            cout << matriz[1][0] << "\t" << matriz[1][1] << "\n";
            cout << "Taxa de acerto total: ";
            taxa[0] = matriz[0][0]+matriz[0][1]+matriz[1][0]+matriz[1][1];
            taxa[0] = ((matriz[0][0]+matriz[1][1])/taxa[0])*100.0;
            cout << taxa[0];
            cout << "\nTaxa de acerto benigno: ";
            taxa[1] = (matriz[0][0]+matriz[1][0]);
            taxa[1] = ((matriz[0][0])/taxa[1])*100.0;
            cout << taxa[1];
            cout << "\nTaxa de acerto maligno: ";
            taxa[2] = (matriz[0][1]+matriz[1][1]);
            taxa[2] = ((matriz[1][1])/taxa[2])*100.0;
            cout << taxa[2];
            cout << "\n";
        }
        int matriz[2][2];
        double taxa[3];
        string titulo;
};

#endif
