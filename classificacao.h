#ifndef CLASSIFICACAO_H
#define CLASSIFICACAO_H

#include "node.h"

class Classificacao: public Node{
    public:
        Classificacao(bool posit)
        :positiva(posit){
            nome = 9;
        }
        bool positiva;
};

#endif
