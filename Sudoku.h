/* ========================================================================
 * ALGORITMO.H
 * ========================================================================

 * ------------------------------------------------------------------------
 * FORMA DA SOLUCAO  - matriz
 * INICIALIZACAO     - cruzar matriz com valores fixos dado pelo usuario e
                       matriz com solucao inicial valida e aleatoria
 * CUSTO DA SOLUCAO  - quantidade de numeros repetidos por coluna e por
                       quadrante
 * FUNCAO OBJETIVO   - calcular e reduzir custo de coluna
 * FUNCAO VIZINHANCA - troca aleatoria de numeros na mesma linha e em
                       colunas diferentes qual haja custo
 * SOLUCAO FINAL     - matriz preenchida com numeros de 1-9 sem repeticao
                       por linha, coluna e quadrante
 * -------------------------------------------------------------------------- */

#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdio.h>
#include <sys/time.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Random.h"
#include "Matriz.h"

#define DECR_TEMP 0.9
#define CONST_E 2.71828
#define DEBUG 0
#define DISPLAY 0

using namespace std;

// -----------------------------------------------------------------------
// - Classe Sudoku
// -----------------------------------------------------------------------
class Sudoku {

    public:
        // - Construtor
        Sudoku(Mat matEspelho, int tamTabu, int limTempo, int temperatura);

        // - Funcoes de inicializacao
        void inicializaMatrizSolucao();
        void criaMatrizBase();
        void cruzaMatrizes();

        // - Funcoes passo da Solucao
        int funcaoObjetivo(Vet vetor);
        void funcaoIncremento(Mat vizinho, Mat atual, Vet custo);

        // - Funcoes do Tabu Search
        string converteSolucaoTabu(Mat matriz);
        bool insereTabu(string tabu);

        // - Funcao do Simulated Annealing
        double calculaSimAnn(Vet vizinho, Vet atual);

        // - Funcoes auxiliares
        bool procuraElemento(int vetor[ORDEM], int elemento);
        int menorCusto(Vet vetor);
        int maiorCusto(Vet vetor);
        int custoTotal(Vet custo);
        int custoColuna(Mat matriz, int coluna);
        Vet calculaCustoColunas(Mat matriz);
        void converteFormato(Mat matriz);
        void imprimeVetor(string texto, Vet vetor);
        void imprimeResultado();

        // - Funcoes Debug
        void imprimeMatrizSaida(Mat matriz);
        void display_info_exec();
        void display_info(string t);
        void display_info(string t, int i);
        void display_info(string t, Vet v);
        void display_info(string t, Mat m);
        void display_info(string t, Mat m, Mat e);
        void debug_info(string texto);
        void debug_info(string texto, int i);
        void debug_info(string texto, Mat matriz);
        void debug_info(string texto, Vet vetor);
        void debug_info(string texto, int vetor[ORDEM]);

        // - Funcao principal do algoritmo - EXECUCAO
        void executa();

    private:
        Mat _matIni;         // matriz inicial (base)
        Mat _matSol;         // matriz solucao (atual)
        Mat _matSolQ;        // matriz solucao (formato quadrante)
        Mat _matEsp;         // matriz espelho (contendo fixos)
        Mat _matEspQ;        // matriz espelho (formato quadrante)
        Set _tabLin;         // vetor de string Tabu (linhas)
        int _tabItr;         // iterador de controle do tabu
        int _cusSol;         // custo atual da solucao
        int _tamTabu;        // tamanho do vetor Tabu
        bool _quadrante;     // formato da solucao (coluna/quadrante)
        int _limTempo;       // lim. de iteracoes (cong. da solucao)
        float _temperatura;  // controle do simulated annealing
        double _tExec;       // tempo de execucao do algoritmo
};

#endif
