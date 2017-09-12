/* ========================================================================
 * MATRIZ.H
 * ========================================================================

 * ------------------------------------------------------------------------
 * DEFINICOES        - ordem da matriz (9x9)
                     - vectors
                     - funcoes de matriz
 * -------------------------------------------------------------------------- */

#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <iostream>
#include <fstream>
#include <string>

#define ORDEM 9

using namespace std;

typedef int Mat[ORDEM][ORDEM];
typedef vector<int> Vet;
typedef vector<string> Set;

inline void copiaMatriz(Mat m1, Mat m2) {
    for (int i=0; i<ORDEM; i++)
        for (int j=0; j<ORDEM; j++)
            m1[i][j] = m2[i][j];
}

inline int buscaIndice(int v[ORDEM], int n) {
    for (int i=0; i<ORDEM ; i++) {
        if (v[i]==n)
            return i;
    }
    return -1;
}

inline void imprimeMatriz(string t, Mat m) {
    cout << t << endl;
    for (int i=0; i<ORDEM ; i++) {
        for (int j=0; j<ORDEM ; j++)
            cout << m[i][j] << ' ';
        cout << endl;
    }
}

inline void converteQuadrante(Mat quad, Mat m) {
    Vet c(9,0);
    for (int i=0; i<9; i++) {
        if (i>=0 && i<3) {
            for (int j=0; j<3; j++) {
                quad[c[0]][0]=m[i][j];
                c[0]++;
            }
            for (int j=3; j<6; j++) {
                quad[c[1]][1]=m[i][j];
                c[1]++;
            }
            for (int j=6; j<9; j++) {
                quad[c[2]][2]=m[i][j];
                c[2]++;
            }
        }
        if (i>=3 && i<6) {
            for (int j=0; j<3; j++) {
                quad[c[3]][3]=m[i][j];
                c[3]++;
            }
            for (int j=3; j<6; j++) {
                quad[c[4]][4]=m[i][j];
                c[4]++;
            }
            for (int j=6; j<9; j++) {
                quad[c[5]][5]=m[i][j];
                c[5]++;
            }
        }
        if (i>=6 && i<9) {
            for (int j=0; j<3; j++) {
                quad[c[6]][6]=m[i][j];
                c[6]++;
            }
            for (int j=3; j<6; j++) {
                quad[c[7]][7]=m[i][j];
                c[7]++;
            }
            for (int j=6; j<9; j++) {
                quad[c[8]][8]=m[i][j];
                c[8]++;
            }
        }
    }
}

inline void converteColuna(Mat m, Mat quad) {
    Vet c(9,0);
    for (int i=0; i<9; i++) {
        if (i>=0 && i<3) {
            for (int j=0; j<3; j++) {
                m[i][j]=quad[c[0]][0];
                c[0]++;
            }
            for (int j=3; j<6; j++) {
                m[i][j]=quad[c[1]][1];
                c[1]++;
            }
            for (int j=6; j<9; j++) {
                m[i][j]=quad[c[2]][2];
                c[2]++;
            }
        }
        if (i>=3 && i<6) {
            for (int j=0; j<3; j++) {
                m[i][j]=quad[c[3]][3];
                c[3]++;
            }
            for (int j=3; j<6; j++) {
                m[i][j]=quad[c[4]][4];
                c[4]++;
            }
            for (int j=6; j<9; j++) {
                m[i][j]=quad[c[5]][5];
                c[5]++;
            }
        }
        if (i>=6 && i<9) {
            for (int j=0; j<3; j++) {
                m[i][j]=quad[c[6]][6];
                c[6]++;
            }
            for (int j=3; j<6; j++) {
                m[i][j]=quad[c[7]][7];
                c[7]++;
            }
            for (int j=6; j<9; j++) {
                m[i][j]=quad[c[8]][8];
                c[8]++;
            }
        }
    }
}

#endif
