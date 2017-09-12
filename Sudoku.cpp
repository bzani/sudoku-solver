#include "Sudoku.h"

// -----------------------------------------------------------------------
// - Construtor
// -----------------------------------------------------------------------
Sudoku::Sudoku(Mat me, int tt, int lt, int t) {
    copiaMatriz(_matEsp, me);
    converteQuadrante(_matEspQ, _matEsp);
    _tamTabu = tt;
    _limTempo = lt;
    _temperatura = t;
    _quadrante = false;
    _tabItr = 0;
    _cusSol = 0;
    _tabLin = Set(_tamTabu,"");

}

// -----------------------------------------------------------------------
// - Funcoes de inicializacao
// -----------------------------------------------------------------------

void Sudoku::inicializaMatrizSolucao() {
    criaMatrizBase();
    cruzaMatrizes();
}

void Sudoku::criaMatrizBase() {

    int k=(int)rnd(ORDEM);
    int i=0,j=0;
    while (i<ORDEM) {
        if (j>=ORDEM) {
            j=0;
            i++;
            k+=((i==3)||(i==6))?5:4;
        } else k++;
        if (k>ORDEM) k-=ORDEM;
        _matIni[i][j]=k;
        j++;
    }
}

void Sudoku::cruzaMatrizes() {
    int x;

    // copia
    copiaMatriz(_matSol,_matIni);

    // cruza matriz inicial com espelho para sol. inicial
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (_matEsp[i][j] != 0) {
                x = buscaIndice(_matSol[i], _matEsp[i][j]);
                if (x < 0)
                    _matSol[i][j]=_matIni[i][j];
                else {
                    _matSol[i][x]=_matSol[i][j];
                    _matSol[i][j]=_matEsp[i][j];
                }
            }
        }
    }
}

// -----------------------------------------------------------------------
// - Funcoes passo da Solucao
// -----------------------------------------------------------------------

// - Define a funcao objetivo
int Sudoku::funcaoObjetivo(Vet v) {
    int soma=0;
    for (int i=0; i<ORDEM; i++)
        soma+=v[i];
    return soma;
}

// - Define a funcao de incremento
void Sudoku::funcaoIncremento(Mat v, Mat a, Vet c) {

//    int pos1 = maiorCusto(c);
//    int pos2 = menorCusto(c);
    int pos1,pos2,lin;

    Mat esp;
    if (_quadrante) copiaMatriz(esp,_matEspQ);
    else copiaMatriz(esp,_matEsp);

    do {
        pos1 = (int) rnd(ORDEM);
        pos2 = (int) rnd(ORDEM);
        lin  = (int) rnd(ORDEM);
    } while ((esp[lin][pos1] > 0) ||
             (esp[lin][pos2] > 0) ||
             (c[pos1] == 0)       ||
             (pos2 == pos1));
    copiaMatriz(v,a);
    int aux = v[lin][pos1];
    v[lin][pos1] = v[lin][pos2];
    v[lin][pos2] = aux;
    //debug_info("pos1 : ",pos1);
    //debug_info("pos2 : ",pos2);
    //debug_info("linha: ",lin);
}


// -----------------------------------------------------------------------
// - Funcoes do Tabu Search
// -----------------------------------------------------------------------

// - Converte vector(int) em string para armazenar no vetor Tabu
string Sudoku::converteSolucaoTabu(Mat m) {
    stringstream ss;
    for(int i=0; i<ORDEM; i++)
        for(int j=0; j<ORDEM; j++)
            ss << m[i][j];
    return ss.str();
}

// - Verifica se solucao ja esta armazenada no vetor Tabu
bool Sudoku::insereTabu(string tabu) {
    if (find(_tabLin.begin(), _tabLin.end(), tabu) != _tabLin.end())
        return false;
    _tabLin[_tabItr] = tabu;
    _tabItr = (_tabItr < (_tamTabu-1)) ? _tabItr+1 : 0;
    return true;
}


// -----------------------------------------------------------------------
// - Funcoes do Simulated Annealing
// -----------------------------------------------------------------------
double Sudoku::calculaSimAnn(Vet v, Vet a) {
    return pow (CONST_E,
        ( ( funcaoObjetivo(v) - funcaoObjetivo(a) )
            / _temperatura ) );
}


// -----------------------------------------------------------------------
// - Funcoes auxiliares
// -----------------------------------------------------------------------
bool Sudoku::procuraElemento(int v[ORDEM], int e) {
    int *p;
    p = find (v, v+4, 2);
    if (p != v+4)
        return true;
    return false;
}

int Sudoku::maiorCusto(Vet v) {
    int maior=0;
    for (int i=0; i<ORDEM; i++)
        if (v[i] > maior)
            maior = v[i];
    return maior;
}

int Sudoku::menorCusto(Vet v) {
    int menor=99;
    for (int i=0; i<ORDEM; i++)
        if (v[i] < menor)
            menor = v[i];
    return menor;
}

int Sudoku::custoTotal(Vet v) {
    int soma=0;
    for (int i=0; i<ORDEM; i++)
        soma+=v[i];
    return soma;
}

int Sudoku::custoColuna(Mat m, int c) {
    int v[ORDEM];
    for (int i=0; i<ORDEM; i++) {
        v[i] = m[i][c];
    }
    int custo=0;
    int* end = v+ORDEM;
    sort(v, end);
    for(int i=1; i<ORDEM; i++) {
        if (v[i] == v[i-1]) {
            custo++;
        }
    }
    return custo;
}

Vet Sudoku::calculaCustoColunas(Mat m) {
    Vet custo(ORDEM,0);
    for (int i=0; i<ORDEM; i++)
        custo[i]=custoColuna(m,i);
    return custo;
}

void Sudoku::converteFormato(Mat m) {
    Mat ma;
    if (_quadrante) {
        converteColuna(ma, m);
        _quadrante=false;
    } else {
        converteQuadrante(ma, m);
        _quadrante=true;
    }
    copiaMatriz(m,ma);
}

void Sudoku::imprimeResultado() {

    display_info("-----------------");
    display_info("  RESULTADO      ");
    display_info("-----------------");

    //display_info("Inicial",_matIni);
    display_info("Espelho",_matEsp, _matEsp);
    display_info("Matriz Final",_matSol, _matEsp);
    imprimeMatrizSaida(_matSol);

    // - Verifica formato final do problema
    if (_quadrante)
        display_info("Custo final: [Q] ",funcaoObjetivo(calculaCustoColunas(_matSol)));
    else
        display_info("Custo final: ",funcaoObjetivo(calculaCustoColunas(_matSol)));

    // - Verifica se problema foi solucionado
    if (_cusSol == 0)
        display_info("\n--Achou solucao!");
    else
        display_info("\n--NAO achou solucao!");

    // - Informacoes da execucao
    display_info_exec();
}

// -----------------------------------------------------------------------
// - Funcao de Debug e Display
// -----------------------------------------------------------------------
void Sudoku::imprimeMatrizSaida(Mat m) {
    for (int i=0; i<ORDEM; i++) {
        for (int j=0; j<ORDEM; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::display_info_exec() {
    if (!DISPLAY) return;
    cout << "--iteracoes: " << _limTempo << endl;
    printf("--temperatura: %.3f ms\n", _temperatura);
    printf("-tempo decorrido: %.3f ms\n\n", _tExec);
}

void Sudoku::display_info(string t) {
    if (!DISPLAY) return;
    cout << t << endl;
}

void Sudoku::display_info(string t, int i) {
    if (!DISPLAY) return;
    cout << t << i << endl;
}

void Sudoku::display_info(string t, Vet v) {
    if (!DISPLAY) return;
    cout << t << ' ';
    for (int i=0; i<ORDEM; i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
}

void Sudoku::display_info(string t, Mat m) {
    if (!DISPLAY) return;
    cout << t << endl;
    for (int i=0; i<ORDEM; i++) {
        for (int j=0; j<ORDEM; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::display_info(string t, Mat m, Mat e) {
    if (!DISPLAY) return;
    cout << t << endl;
    for (int i=0; i<ORDEM; i++) {
        for (int j=0; j<ORDEM; j++) {
            if (e[i][j]>0)
                cout << " [" << m[i][j] << "] ";
            else
                cout << "  " << m[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::debug_info(string t) {
    if (!DEBUG) return;
    cout << "[DEBUG]" << t << endl;
}

void Sudoku::debug_info(string t, int i) {
    if (!DEBUG) return;
    cout << "[DEBUG]" << t << i << endl;
}

void Sudoku::debug_info(string t, Mat m) {
    if (!DEBUG) return;
    cout << "[DEBUG]" << t << endl;
    for (int i=0; i<ORDEM; i++) {
        for (int j=0; j<ORDEM; j++) {
            cout << m[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::debug_info(string t, Vet v) {
    if (!DEBUG) return;
    cout << "[DEBUG]" << t;
    Vet::iterator it;
    for (it=v.begin(); it!=v.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
}

void Sudoku::debug_info(string t, int v[ORDEM]) {
    if (!DEBUG) return;
    cout << "[DEBUG]" << t << endl;
    for (int i=0; i<ORDEM; i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
}


// -----------------------------------------------------------------------
// - Funcao principal do algoritmo - EXECUCAO
// -----------------------------------------------------------------------

void Sudoku::executa() {

    // - tempo decorrido da execucao
    timeval tIni, tFim;
    double ti=0, tf=0;
    gettimeofday(&tIni, NULL);

    // - inicializa funcao randomica
    randomize();

    // - Variaveis auxiliares
    bool saida = false;                     // Condicao de termino do algoritmo
    int objetivo = 0;                       // Temporaria de valor de solucao
    int melhor = 99;                        // Reserva melhor valor da solucao
    int _tabItr = 0;                         // Iterador do Tabu
    int tempo = 0;                          // Iterador do tempo
    int iteracoes = 0;                      // Iterador temporario
    float congelamento = 1/_temperatura;    // Iterador de congelamento

    // - Matrizes da heuristica
    Mat atual;
    Mat vizinho;

    // - Variaveis de Custo da Heuristica
    Vet cusAtual(ORDEM,0);
    Vet cusVizinho(ORDEM,0);

    // - Inicializacao vetores das iteracoes
    display_info("\nInicializando solucao base...");
    inicializaMatrizSolucao();
    copiaMatriz(atual, _matSol);

    display_info("\nCusto inicial: ",funcaoObjetivo(calculaCustoColunas(atual)));
    //debug_info("atual",atual);
    //debug_info("custo atual: ",cusAtual);
    //debug_info("total atual: ",funcaoObjetivo(cusAtual));

    // - Executa iteracoes
    display_info("\nProcessando solucoes...");
    do {

        if (melhor < 5) {
            //debug_info("melhor: ",melhor);
            //converteFormato(atual);
        }
        cusAtual = calculaCustoColunas(atual);
        do {
            funcaoIncremento(vizinho, atual, cusAtual);
            cusVizinho = calculaCustoColunas(vizinho);
            iteracoes++;
        } while ( (funcaoObjetivo(cusVizinho) > funcaoObjetivo(cusAtual)) && (iteracoes < 100) );
        //debug_info("*sai ", iteracoes);
        iteracoes = 0;

        //debug_info("vizinho",vizinho);
        //debug_info("custo vizinho: ",cusVizinho);
        //debug_info("total vizinho: ",funcaoObjetivo(cusVizinho));

        // - testa objetivo
        if (
             ( insereTabu(converteSolucaoTabu(vizinho)) ) &&                 // tabu search
             ( ( funcaoObjetivo(cusVizinho) > funcaoObjetivo(cusAtual) ) ||  // qualidade
                 (rnd(1) < calculaSimAnn(cusVizinho, cusAtual)) )            // simulating annealing
        ) {
            //debug_info("**vizinho melhor**");
            copiaMatriz(atual, vizinho);
            cusAtual = calculaCustoColunas(atual);
            tempo = 0;
        }

        // - Valor objetivo fixado para evitar custo com chamadas de funcao
        objetivo = funcaoObjetivo(cusAtual);
        if (objetivo < melhor) {
            melhor = objetivo;
        }

        // - Verifica a condicao de parada
        if ( (objetivo == 0)      ||         // achou solucao ideal
             (tempo == _limTempo) ||         // atingiu limite de tempo
             (_temperatura < congelamento)   // temperatura congelou
        ) {
            _cusSol = melhor;
            copiaMatriz(_matSol,atual);
            saida = true;
        }

        // - Atualiza variaveis de controle
        _temperatura *= DECR_TEMP;
        iteracoes++;
        tempo++;

        //debug_info("tempo: ", tempo);
        //debug_info("melhor: ", melhor);
        //debug_info("objetivo: ", objetivo);
        //debug_info("_temperatura: ", _temperatura);
        //debug_info("\n");

    } while (!saida);

    // - Imprime tempo decorrido
    gettimeofday(&tFim, NULL);
    tf = (double) tFim.tv_usec + ((double) tFim.tv_sec * (1000000.0));
    ti = (double) tIni.tv_usec + ((double) tIni.tv_sec * (1000000.0));
    _tExec = (tf - ti) / 1000;

}


