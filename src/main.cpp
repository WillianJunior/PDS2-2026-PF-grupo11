#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/GeradorDeReceita.hpp"
#include "../include/BuscadorDeReceita.hpp"
#include "../include/InterfaceTerminal.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    try {
        // Inicializa serviços do sistema
        GerenciadorDeTemplate gerenciador;
        GeradorDeReceita gerador;

        std::vector<Receita> repositorio;

        // Carrega as receitas do arquivo de persistencia
        try {
            std::ifstream arquivo("data/receitas.txt");
            if (arquivo.is_open()) {
                std::string linha;
                while (std::getline(arquivo, linha)) {
                    if (linha.empty()) continue;
                    std::stringstream ss(linha);
                    std::string nome, tmpl, cat;
                    if (!std::getline(ss, nome, '|')) continue;
                    if (!std::getline(ss, tmpl, '|')) continue;
                    if (!std::getline(ss, cat, '|')) continue;
                    
                    std::vector<IngredienteDaReceita> ings;
                    std::string ingStr;
                    while (std::getline(ss, ingStr, '|')) {
                        if (ingStr.empty()) continue;
                        std::stringstream ssIng(ingStr);
                        std::string ingNome, ingTipo, qtdStr, unid;
                        if (!std::getline(ssIng, ingNome, ',')) continue;
                        if (!std::getline(ssIng, ingTipo, ',')) continue;
                        if (!std::getline(ssIng, qtdStr, ',')) continue;
                        if (!std::getline(ssIng, unid, ',')) continue;
                        
                        try {
                            double qtd = std::stod(qtdStr);
                            ings.push_back(IngredienteDaReceita(Ingrediente(ingNome, ingTipo), qtd, unid));
                        } catch (...) {}
                    }
                    
                    Receita base(nome, tmpl, cat, ings, {}, 0);
                    Receita gerada = gerador.gerar(base);
                    if (gerada.estaCompleta()) {
                        repositorio.push_back(gerada);
                    }
                }
            }
        } catch (...) {
            // Ignora silenciosamente se houver problemas de leitura das receitas na carga inicial
        }

        BuscadorDeReceitas buscador(repositorio);

        // Inicializa e executa a interface com o usuário
        InterfaceTerminal terminal(buscador, gerenciador, gerador);
        terminal.iniciar();

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal na inicializacao do sistema: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}