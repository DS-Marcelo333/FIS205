#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TApplication.h>

class Caminos {
public:
    Caminos(int n, double inf = -1000, double max = 1000) {
        GenerarNodos(n, inf, max);
    }

    double DistanciaTotal(const std::vector<int>& camino) const {
        double distancia = 0.0;
        int nc = camino.size();
        for (int i = 0; i < nc; ++i) {
            auto inodo = nodos[camino[i]];
            auto fnodo = nodos[camino[(i + 1) % nc]];
            distancia += CalcularDistancia(inodo, fnodo);
        }
        return distancia;
    }

    void ImprimirNodos() const {
        std::cout << "Ubicaciones de los nodos:" << std::endl;
        for (const auto& nodo : nodos) {
            std::cout << "(" << nodo.first << ", " << nodo.second << ")" << std::endl;
        }
    }

    double CalcularTemperaturaInicial(double P_aceptacion = 0.95) const {
        double distanciaMedia = CalcularDistanciaMedia();
        return -distanciaMedia / std::log(P_aceptacion);
    }

    std::vector<int> GenerarCaminoInicial() const {
        std::vector<int> camino(nodos.size());
        std::iota(camino.begin(), camino.end(), 0);
        std::shuffle(camino.begin(), camino.end(), std::mt19937{std::random_device{}()});
        return camino;
    }

    void CaminoGenerado(double T_inicial, double r) {
        std::vector<int> camino = GenerarCaminoInicial();
        double T = T_inicial;
        double D_actual = DistanciaTotal(camino);
	cout<< " Distancia primer camino: "<<D_actual<<"       ";
	cout<<"   ";
        std::vector<int> mejor_camino = camino;
        double mejor_distancia = D_actual;

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        int iter = 0;
        int imagen_contador = 0;
        std::vector<double> distancias;
        while (T > 1e-6) {
            std::vector<int> nuevo_camino = camino;
            std::swap(nuevo_camino[std::uniform_int_distribution<>(0, nuevo_camino.size() - 1)(gen)],
                      nuevo_camino[std::uniform_int_distribution<>(0, nuevo_camino.size() - 1)(gen)]);

            double D_nuevo = DistanciaTotal(nuevo_camino);
            double delta = D_nuevo - D_actual;

            if (delta < 0 || dis(gen) < std::exp(-delta / T)) {
                camino = nuevo_camino;
                D_actual = D_nuevo;
                if (D_nuevo < mejor_distancia) {
                    mejor_camino = camino;
                    mejor_distancia = D_nuevo;
                    GraficarCamino(mejor_camino, imagen_contador++);
                }
            }

            distancias.push_back(D_actual);

            T *= r;

            iter++;
        }

        std::cout << "Mejor distancia encontrada: " << mejor_distancia << std::endl;
        std::cout << "Mejor camino encontrado: ";
        for (int ciudad : mejor_camino) {
        //    std::cout << ciudad << " ";
        }
        std::cout << std::endl;
        std::cout << "Iteraciones realizadas: " << iter << std::endl;

        GraficarEvolucionDistancia(distancias);
    }

private:
    std::vector<std::pair<double, double>> nodos;

    void GenerarNodos(int n, double inf, double max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(inf, max);
        nodos.clear();
        for (int i = 0; i < n; ++i) {
            double x = dis(gen);
            double y = dis(gen);
            nodos.emplace_back(x, y);
        }
    }

    double CalcularDistancia(const std::pair<double, double>& nodo1, const std::pair<double, double>& nodo2) const {
        return std::sqrt(std::pow(nodo2.first - nodo1.first, 2) + std::pow(nodo2.second - nodo1.second, 2));
    }

    double CalcularDistanciaMedia() const {
        double distanciaTotal = 0.0;
        int numComparaciones = 0;
        for (size_t i = 0; i < nodos.size(); ++i) {
            for (size_t j = i + 1; j < nodos.size(); ++j) {
                distanciaTotal += CalcularDistancia(nodos[i], nodos[j]);
                numComparaciones++;
            }
        }
        return distanciaTotal / numComparaciones;
    }

    void GraficarCamino(const std::vector<int>& camino, int imagen_contador) const {
        TCanvas* c1 = new TCanvas("c1", "Camino", 800, 600);
        TGraph* g = new TGraph(camino.size() + 1);

        for (size_t i = 0; i < camino.size(); ++i) {
            g->SetPoint(i, nodos[camino[i]].first, nodos[camino[i]].second);
        }
        g->SetPoint(camino.size(), nodos[camino[0]].first, nodos[camino[0]].second);

        g->SetTitle("Camino;X;Y");
        g->Draw("AL*");
        c1->Update();

 c1->SaveAs(Form("camino_%d.png", imagen_contador));
        delete g;
        delete c1;
    }

    void GraficarEvolucionDistancia(const std::vector<double>& distancias) const {
        TCanvas* c2 = new TCanvas("c2", "Evolución de la Distancia", 800, 600);
        TGraph* g = new TGraph(distancias.size());

        for (size_t i = 0; i < distancias.size(); ++i) {
            g->SetPoint(i, i, distancias[i]);
        }

        g->SetTitle("Evolucion de la Distancia;Iteracion;Distancia");
        g->Draw("AL");
        c2->Update();

        std::string filename = "evolucion_distancia.png";
        c2->SaveAs(filename.c_str());

        delete g;
        delete c2;
    }
};

int tsp9() {
    int n;
    std::cout << "Ingrese número de nodos: ";
    std::cin >> n;
    double inf = -1000;
    double max = 1000;

    TApplication theApp("App", nullptr, nullptr);
    Caminos caminos(n, inf, max);

//    caminos.ImprimirNodos();

    double T_inicial = caminos.CalcularTemperaturaInicial();
    std::cout << "Temperatura inicial: " << T_inicial << std::endl;

    double tasa_enfriamiento = 0.98;
    std::cout << "\n Tasa de enfriamiento: " << tasa_enfriamiento << std::endl;
    caminos.CaminoGenerado(T_inicial, tasa_enfriamiento);

    theApp.Run();
    return 0;
}

