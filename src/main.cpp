#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/GeradorDeReceita.hpp"
#include "../include/BuscadorDeReceita.hpp"
#include "../include/InterfaceTerminal.hpp"
#include <vector>
#include <iostream>

int main() {
    try {
        // Inicializa serviços do sistema
        GerenciadorDeTemplate gerenciador;
        GeradorDeReceita gerador;

        std::vector<Receita> repositorio;

        // Tenta pré-popular algumas receitas italianas clássicas no acervo inicial
        try {
            std::vector<IngredienteDaReceita> ingPizza = {
                IngredienteDaReceita(Ingrediente("Farinha de Trigo", "Farinha"), 300, "g"),
                IngredienteDaReceita(Ingrediente("Agua", "Liquido"), 150, "ml"),
                IngredienteDaReceita(Ingrediente("Sal", "Sal"), 5, "g"),
                IngredienteDaReceita(Ingrediente("Molho de Tomate", "Molho"), 100, "g"),
                IngredienteDaReceita(Ingrediente("Queijo Mozzarella", "Queijo"), 150, "g"),
                IngredienteDaReceita(Ingrediente("Manjericao", "Vegetal"), 10, "g")
            };
            Receita basePizza("Pizza Margherita", "Pizza", "Massas", ingPizza, {}, 0);
            Receita pizza = gerador.gerar(basePizza);
            if (pizza.estaCompleta()) {
                repositorio.push_back(pizza);
            }

            std::vector<IngredienteDaReceita> ingPasta = {
                IngredienteDaReceita(Ingrediente("Sal", "Sal"), 10, "g"),
                IngredienteDaReceita(Ingrediente("Espaguete", "Massa"), 200, "g"),
                IngredienteDaReceita(Ingrediente("Gema de Ovo", "Molho"), 3, "unidades"),
                IngredienteDaReceita(Ingrediente("Queijo Parmesao", "Queijo"), 50, "g")
            };
            Receita basePasta("Pasta Carbonara", "Pasta", "Massas", ingPasta, {}, 0);
            Receita pasta = gerador.gerar(basePasta);
            if (pasta.estaCompleta()) {
                repositorio.push_back(pasta);
            }
        } catch (...) {
            // Ignora silenciosamente se houver problemas de leitura de templates na carga inicial
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