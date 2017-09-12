/* ========================================================================
 * PROGRAMA PRINCIPAL
 * ========================================================================

 * ------------------------------------------------------------------------
 * Universidade Tuiuti do Parana
 * Bacharelado em Ciencia da Computacao
 * Inteligencia Artificial
 * Prof. Chaua Queirolo
 * Aluno Bruno Luiz Zani
 * ------------------------------------------------------------------------

 * ------------------------------------------------------------------------
 * Sudoku - Simulated Annealing + Tabu Search
 * ------------------------------------------------------------------------

 * -------------------------------------------------------------------------- */

#include "Sudoku.h"

bool readInFile(const char* arquivo, Mat m) {
    string line;
    ifstream inFile(arquivo);
    if (inFile.is_open()) {
        int i=0;
        while (!inFile.eof() && i<9) {
            getline(inFile,line);
            int tamLinha = (line.size() > 0) ? line.size() : 30;
            int k=0,j=0;
            char ch;
            do {
                if (isdigit(line[k])) {
                    ch = line[k];
                    m[i][j] = ch - '0';
                    j++;
                }
                k++;
            } while (k<line.size() && j<9);
            i++;
        }
        inFile.close();
    } else return false;
    return true;
}

int main(int argc, const char **argv) {

    /* ------------------------------------------------------------------------
     * TESTE
     * ------------------------------------------------------------------------
     * JOGO INICIAL   =========================
                      | 5 3 ' | ' 7 ' | ' ' ' |
                      | 6 ' ' | 1 9 5 | ' ' ' |
                      | ' 9 8 | ' ' ' | ' 6 ' |
                      =========================
                      | 8 ' ' | ' 6 ' | ' ' 3 |
                      | 4 ' ' | 8 ' 3 | ' ' 1 |
                      | 7 ' ' | ' 2 ' | ' ' 6 |
                      =========================
                      | ' 6 ' | ' ' ' | 2 8 ' |
                      | ' ' ' | 4 1 9 | ' ' 5 |
                      | ' ' ' | ' 8 ' | ' 7 9 |
                      =========================
    * ------------------------------------------------------------------------*/

    // - inicializa valores fixos da matriz

    // -------------------------------------------------- SOLUCAO =>
    // - copia valores para matriz do problema
    Mat matriz;
    if (!readInFile(argv[1],matriz)) {
        cerr << "Nao foi possivel abrir o arquivo: " << argv[1] << endl;
        cout << endl;
        return -1;
    }

    // - inicializa construtor da solucao
    // - (matriz, tamTabu, maxTempo, temperaturaIni)
    Sudoku sudoku(matriz, 200, 1000000, 1000000000);

    // - Executa o algoritmo : Simulated Annealing + Tabu Search
    sudoku.executa();

    // - Imprime solucao final
    sudoku.imprimeResultado();
    // -------------------------------------------------- <= SOLUCAO

    // - fim -
    return 0;
}

