//
// Created by Daniel Paiva Fernandes on 21/10/2021.
//
#include <iostream>
#include "main.h"

int main()
{
    // Criação de uma nova
    ArvoreB arvoreB(3);

    // Inserção
    arvoreB.insereValor(1);
    arvoreB.insereValor(3);
    arvoreB.insereValor(7);
    arvoreB.insereValor(10);
    arvoreB.insereValor(11);
    arvoreB.insereValor(13);
    arvoreB.insereValor(14);
    arvoreB.insereValor(15);
    arvoreB.insereValor(18);
    arvoreB.insereValor(16);
    arvoreB.insereValor(19);
    arvoreB.insereValor(24);
    arvoreB.insereValor(25);
    arvoreB.insereValor(26);
    arvoreB.insereValor(21);
    arvoreB.insereValor(4);

    // Impressão da árvore
    cout << "Percorre a árvore construída" << endl;
    arvoreB.percorre();
    cout << endl;

    //Busca se o item está ou não presente
    ArvoreBNode *result = arvoreB.buscaValor(21);
    cout << "Percorre o nó onde o valor 21 está armazenado no nó" << endl;
    result->percorre();
    cout << endl;

    // Remoção
    arvoreB.removeValor(6);
    cout << "Percorre a árvore após remover 6" << endl;
    arvoreB.percorre();
    cout << endl;

    // Remoção
    arvoreB.removeValor(13);
    cout << "Percorre a árvore após remover 13" << endl;
    arvoreB.percorre();
    cout << endl;

    // Remoção
    arvoreB.removeValor(16);
    cout << "Percorre a árvore após remover 16" << endl;
    arvoreB.percorre();
    cout << endl;

    return 0;
}
