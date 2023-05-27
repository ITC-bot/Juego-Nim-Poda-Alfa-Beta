/*Hecho por Marcos Abaroa para la materia de Inteligencia Artificial I
Programa basado en el juego Nim de 2 jugadores: Maquina vs Jugador*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;
const int INF = numeric_limits<int>::max(); // valor infinito
const int MAX_PROF = 15;  // Si se requiere mas precision, aumente la profundidad maxima

struct Estado {
    int palitos;
    int jugadorActual;
};

// Variable global para llevar la cuenta de los nodos visitados
long long contadorNodos = 0; // contador de nodos que visita la función Minimax

// Funcion que genera los sucesores de un estado
vector<Estado> generarSucesores(Estado estado) {
    vector<Estado> sucesores;
    for (int i = 1; i <= 3; i++) {
        if (i <= estado.palitos) {
            Estado sucesor = {estado.palitos - i, estado.jugadorActual == 1 ? 2 : 1};
            sucesores.push_back(sucesor);
        }
    }
    return sucesores;
}

// Funcion minimax
int MiniMax(Estado u, int Prof, int alpha, int beta, bool Mano) {
    contadorNodos++; // incrementamos el contador de nodos
    if (u.palitos == 1) {
        return Mano ? -1 : 1;
    }
    if (Prof == 0) {
        return 0;
    }
    int m = Mano ? -1 : 1;
    vector<Estado> sucesores = generarSucesores(u);
    for (Estado v : sucesores) {
        int t = MiniMax(v, Prof - 1, alpha, beta, !Mano);
        if (Mano) {
            m = max(m, t);
            alpha = max(alpha, m);
        } else {
            m = min(m, t);
            beta = min(beta, m);
        }
        if (alpha >= beta) {
            break;
        }
    }
    return m;
}

//Funcion que controla los movimientos de la "Maquina inteligente"
int maquina(int palos) {
    int m = -2;
    int mejorMovimiento = 1;
    int alpha = -INF;
    int beta = INF;
    vector<Estado> sucesores = generarSucesores({palos, 1});
    for (Estado v : sucesores) {
        int t = MiniMax(v, MAX_PROF, alpha, beta, false);
        if (t > m) {
            m = t;
            mejorMovimiento = palos - v.palitos;
        }
        alpha = max(alpha, m);
    }
    return mejorMovimiento;
}

//Funcion para que el jugador haga su jugada"
int jugador(int palos) {
    int movimiento;
    do {
        cout << "Ingrese la cantidad de palitos que desea quitar (1-3): ";
        cin >> movimiento;
    } while (movimiento < 1 || movimiento > 3 || movimiento > palos);
    return movimiento;
}

//Funcion principal
int main() {
    srand(time(0));
    int palitos;
    cout << "Ingrese la cantidad de palitos para el juego: ";
    cin >> palitos;
    int jugadorActual = rand() % 2 + 1;
    cout << "Juego de los Palitos" << endl;
    cout << "=====================" << endl;
    while (palitos > 1) {
        cout << "Palitos restantes: ";
        for (int i = 0; i < palitos; i++) {
            cout << "|";
        }
        cout << endl;
        if (jugadorActual == 1) {
            int palitosQuitados = maquina(palitos);
            palitos -= palitosQuitados;
            cout << "La maquina quita " << palitosQuitados << " palitos." << endl;
            jugadorActual = 2;
        } else {
            int palitosQuitadosJugador = jugador(palitos);
            palitos -= palitosQuitadosJugador;
            cout << "El jugador quita " << palitosQuitadosJugador << " palitos." << endl;
            jugadorActual = 1;
        }
    }
    cout << "Palos restantes: ";
    for (int i = 0; i < palitos; i++) {
        cout << "|";
    }
    cout << endl;
    if (jugadorActual == 1) {
        cout << "El jugador gana" << endl;
    } else {
        cout << "La maquina gana" << endl;
    }
    cout << "Nodos visitados: " << contadorNodos << endl; // imprimir el número de nodos visitados
    return 0;
}
