//
// Created by Daniel Paiva Fernandes on 21/10/2021.
//

#ifndef PCO001_ARVORE_B_MAIN_H
#define PCO001_ARVORE_B_MAIN_H
#include<iostream>
using namespace std;

// O node da ArvoreB
class ArvoreBNode
{
    int *valores; // Um array de valores
    int grauMinimo;	 // Grau mínimo (define a largura para o número de valores)
    ArvoreBNode **ponteirosFilhos; // Um array ponteiros filhos
    int qteValores;	 // Quantidade de valores
    bool isFolha; // Verdadeiro se for node do tipo folha

public:

    ArvoreBNode(int _grauMinimo, bool _isFolha); // Constructor
    void percorre();
    ArvoreBNode *buscaValor(int valor);
    int getIndice(int valor);
    void insereEmNaoCheio(int valor);
    void divideFilho(int indice, ArvoreBNode *y);
    void remove(int valor);
    void removeDaFolha(int idx);
    void removeDoNodeNaoFolha(int idx);
    int getPredecessor(int idx);
    int getSucessor(int idx);
    void preenche(int idx);
    void emprestaValorDoAnterior(int idx);
    void emprestaValorDoSeguinte(int idx);
    void integra(int idx);

    friend class ArvoreB;
};

class ArvoreB
{
    ArvoreBNode *raiz;
    int grauMinimo;
public:

    explicit ArvoreB(int _grauMinimo)
    {
        raiz = nullptr;
        grauMinimo = _grauMinimo;
    }

    void percorre()
    {
        if (raiz != nullptr) raiz->percorre();
    }

    ArvoreBNode* buscaValor(int valor)
    {
        return (raiz == nullptr) ? nullptr : raiz->buscaValor(valor);
    }

    void insereValor(int valor);

    void removeValor(int valor);

};

ArvoreBNode::ArvoreBNode(int _grauMinimo, bool _isFolha)
{
    grauMinimo = _grauMinimo;
    isFolha = _isFolha;

    valores = new int[2 * grauMinimo - 1];
    ponteirosFilhos = new ArvoreBNode *[2 * grauMinimo];

    qteValores = 0;
}

int ArvoreBNode::getIndice(int valor)
{
    int idx=0;
    while (idx < qteValores && valores[idx] < valor)
        ++idx;
    return idx;
}

void ArvoreBNode::remove(int valor)
{
    int idx = getIndice(valor);

    if (idx < qteValores && valores[idx] == valor)
    {
        if (isFolha)
            removeDaFolha(idx);
        else
            removeDoNodeNaoFolha(idx);
    }
    else
    {
        if (isFolha)
        {
            cout << "O valor " << valor << " não existe nesta árvore\n";
            return;
        }

        bool flag = (idx == qteValores);

        if (ponteirosFilhos[idx]->qteValores < grauMinimo)
            preenche(idx);

        if (flag && idx > qteValores)
            ponteirosFilhos[idx - 1]->remove(valor);
        else
            ponteirosFilhos[idx]->remove(valor);
    }
    }

void ArvoreBNode::removeDaFolha (int idx)
{
    for (int i=idx+1; i < qteValores; ++i)
        valores[i - 1] = valores[i];

    qteValores--;
}

void ArvoreBNode::removeDoNodeNaoFolha(int idx)
{

    int valor = valores[idx];

    if (ponteirosFilhos[idx]->qteValores >= grauMinimo)
    {
        int predecessor = getPredecessor(idx);
        valores[idx] = predecessor;
        ponteirosFilhos[idx]->remove(predecessor);
    }

    else if (ponteirosFilhos[idx + 1]->qteValores >= grauMinimo)
    {
        int sucessor = getSucessor(idx);
        valores[idx] = sucessor;
        ponteirosFilhos[idx + 1]->remove(sucessor);
    }
    else
    {
        integra(idx);
        ponteirosFilhos[idx]->remove(valor);
    }
    }

int ArvoreBNode::getPredecessor(int idx)
{
    ArvoreBNode *atual=ponteirosFilhos[idx];
    while (!atual->isFolha)
        atual = atual->ponteirosFilhos[atual->qteValores];

    return atual->valores[atual->qteValores - 1];
}

int ArvoreBNode::getSucessor(int idx)
{
    ArvoreBNode *atual = ponteirosFilhos[idx + 1];
    while (!atual->isFolha)
        atual = atual->ponteirosFilhos[0];

    return atual->valores[0];
}

void ArvoreBNode::preenche(int idx)
{

    if (idx!=0 && ponteirosFilhos[idx - 1]->qteValores >= grauMinimo)
        emprestaValorDoAnterior(idx);

    else if (idx != qteValores && ponteirosFilhos[idx + 1]->qteValores >= grauMinimo)
        emprestaValorDoSeguinte(idx);

    else
    {
        if (idx != qteValores)
            integra(idx);
        else
            integra(idx - 1);
    }
    }

void ArvoreBNode::emprestaValorDoAnterior(int idx)
{

    ArvoreBNode *filho=ponteirosFilhos[idx];
    ArvoreBNode *irmao=ponteirosFilhos[idx - 1];

    for (int i= filho->qteValores - 1; i >= 0; --i)
        filho->valores[i + 1] = filho->valores[i];

    if (!filho->isFolha)
    {
        for(int i=filho->qteValores; i >= 0; --i)
            filho->ponteirosFilhos[i + 1] = filho->ponteirosFilhos[i];
    }

    filho->valores[0] = valores[idx - 1];

    if(!filho->isFolha)
        filho->ponteirosFilhos[0] = irmao->ponteirosFilhos[irmao->qteValores];

    valores[idx - 1] = irmao->valores[irmao->qteValores - 1];

    filho->qteValores += 1;
    irmao->qteValores -= 1;
}

void ArvoreBNode::emprestaValorDoSeguinte(int idx)
{

    ArvoreBNode *filho=ponteirosFilhos[idx];
    ArvoreBNode *irmao=ponteirosFilhos[idx + 1];

    filho->valores[(filho->qteValores)] = valores[idx];

    if (!(filho->isFolha))
        filho->ponteirosFilhos[(filho->qteValores) + 1] = irmao->ponteirosFilhos[0];

    valores[idx] = irmao->valores[0];

    for (int i=1; i < irmao->qteValores; ++i)
        irmao->valores[i - 1] = irmao->valores[i];

    if (!irmao->isFolha)
    {
        for(int i=1; i <= irmao->qteValores; ++i)
            irmao->ponteirosFilhos[i - 1] = irmao->ponteirosFilhos[i];
    }

    filho->qteValores += 1;
    irmao->qteValores -= 1;
}

void ArvoreBNode::integra(int idx)
{
    ArvoreBNode *filho = ponteirosFilhos[idx];
    ArvoreBNode *irmao = ponteirosFilhos[idx + 1];

    filho->valores[grauMinimo - 1] = valores[idx];

    for (int i=0; i < irmao->qteValores; ++i)
        filho->valores[i + grauMinimo] = irmao->valores[i];

    if (!filho->isFolha)
    {
        for(int i=0; i <= irmao->qteValores; ++i)
            filho->ponteirosFilhos[i + grauMinimo] = irmao->ponteirosFilhos[i];
    }

    for (int i=idx+1; i < qteValores; ++i)
        valores[i - 1] = valores[i];

    for (int i=idx+2; i <= qteValores; ++i)
        ponteirosFilhos[i - 1] = ponteirosFilhos[i];

    filho->qteValores += irmao->qteValores + 1;
    qteValores--;

    delete(irmao);
}

void ArvoreB::insereValor(int valor)
{
    if (raiz == nullptr)
    {
        raiz = new ArvoreBNode(grauMinimo, true);
        raiz->valores[0] = valor;
        raiz->qteValores = 1;
    }
    else
    {
        if (raiz->qteValores == 2 * grauMinimo - 1)
        {
            auto *s = new ArvoreBNode(grauMinimo, false);

            s->ponteirosFilhos[0] = raiz;

            s->divideFilho(0, raiz);

            int i = 0;
            if (s->valores[0] < valor)
                i++;
            s->ponteirosFilhos[i]->insereEmNaoCheio(valor);

            raiz = s;
        }
        else
            raiz->insereEmNaoCheio(valor);
    }
}

void ArvoreBNode::insereEmNaoCheio(int valor)
{
    int i = qteValores - 1;

    if (isFolha)
    {
        while (i >= 0 && valores[i] > valor)
        {
            valores[i + 1] = valores[i];
            i--;
        }

        valores[i + 1] = valor;
        qteValores = qteValores + 1;
    }
    else
    {
        while (i >= 0 && valores[i] > valor)
            i--;

        if (ponteirosFilhos[i + 1]->qteValores == 2 * grauMinimo - 1)
        {
            divideFilho(i + 1, ponteirosFilhos[i + 1]);

            if (valores[i + 1] < valor)
                i++;
        }
        ponteirosFilhos[i + 1]->insereEmNaoCheio(valor);
    }
}

void ArvoreBNode::divideFilho(int indice, ArvoreBNode *y)
{

    auto *z = new ArvoreBNode(y->grauMinimo, y->isFolha);
    z->qteValores = grauMinimo - 1;

    for (int j = 0; j < grauMinimo - 1; j++)
        z->valores[j] = y->valores[j + grauMinimo];

    if (!y->isFolha)
    {
        for (int j = 0; j < grauMinimo; j++)
            z->ponteirosFilhos[j] = y->ponteirosFilhos[j + grauMinimo];
    }

    y->qteValores = grauMinimo - 1;

    for (int j = qteValores; j >= indice + 1; j--)
        ponteirosFilhos[j + 1] = ponteirosFilhos[j];

    ponteirosFilhos[indice + 1] = z;

    for (int j = qteValores - 1; j >= indice; j--)
        valores[j + 1] = valores[j];

    valores[indice] = y->valores[grauMinimo - 1];

    qteValores = qteValores + 1;
}

void ArvoreBNode::percorre()
{
    int i;
    for (i = 0; i < qteValores; i++)
    {
        if (!isFolha)
            ponteirosFilhos[i]->percorre();
        cout << " " << valores[i];
    }

    if (!isFolha)
        ponteirosFilhos[i]->percorre();
}

ArvoreBNode *ArvoreBNode::buscaValor(int valor)
{
    int i = 0;
    while (i < qteValores && valor > valores[i])
        i++;

    if (valores[i] == valor)
        return this;

    if (isFolha)
        return nullptr;

    return ponteirosFilhos[i]->buscaValor(valor);
}

void ArvoreB::removeValor(int valor)
{
    if (!raiz)
    {
        cout << "A árvore está vazia" << endl;
        return;
    }

    raiz->remove(valor);

    if (raiz->qteValores == 0)
    {
        ArvoreBNode *tmp = raiz;
        if (raiz->isFolha)
            raiz = nullptr;
        else
            raiz = raiz->ponteirosFilhos[0];

        delete tmp;
    }
    }

#endif //PCO001_ARVORE_B_MAIN_H
