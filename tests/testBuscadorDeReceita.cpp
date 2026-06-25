#include "../include/doctest.h"
#include "../include/BuscadorDeReceita.hpp"

TEST_CASE("Testando BuscadorDeReceitas") {
    std::vector<IngredienteDaReceita> ings = {
        IngredienteDaReceita(Ingrediente("Farinha", "Seco"), 100, "g"),
        IngredienteDaReceita(Ingrediente("Ovo", "Proteina"), 2, "un")
    };
    std::vector<EtapaDePreparo> etapas;
    Receita rec1("Bolo de Chocolate", "Bolo", "Sobremesas", ings, etapas, 60);
    Receita rec2("Torta de Limao", "Torta", "Sobremesas", {}, etapas, 40);

    std::vector<Receita> repo = {rec1, rec2};
    BuscadorDeReceitas buscador(repo);

    SUBCASE("Verificando buscas vazias e sem match") {
        CHECK(buscador.buscarPorNome("Pizza").empty() == true);

        std::vector<std::string> ingsBusca = { "Sal" };
        CHECK(buscador.buscarPorIngredientes(ingsBusca).empty() == true);
        CHECK(buscador.buscarPorNomeIngredientes("Bolo", ingsBusca).empty() == true);
    }

    SUBCASE("Verificando busca por nome com matches (case-insensitive)") {
        auto res = buscador.buscarPorNome("bolo");
        CHECK(res.size() == 1);
        CHECK(res[0].getNome() == "Bolo de Chocolate");

        auto res2 = buscador.buscarPorNome("LiMaO");
        CHECK(res2.size() == 1);
        CHECK(res2[0].getNome() == "Torta de Limao");
    }

    SUBCASE("Verificando busca por ingredientes com matches") {
        std::vector<std::string> buscaIngs = {"Ovo"};
        auto res = buscador.buscarPorIngredientes(buscaIngs);
        CHECK(res.size() == 1);
        CHECK(res[0].getNome() == "Bolo de Chocolate");

        std::vector<std::string> buscaIngs2 = {"Farinha", "Ovo"};
        auto res2 = buscador.buscarPorIngredientes(buscaIngs2);
        CHECK(res2.size() == 1);
    }

    SUBCASE("Verificando busca por nome e ingredientes") {
        std::vector<std::string> buscaIngs = {"Farinha"};
        auto res = buscador.buscarPorNomeIngredientes("Bolo", buscaIngs);
        CHECK(res.size() == 1);
        CHECK(res[0].getNome() == "Bolo de Chocolate");

        auto res2 = buscador.buscarPorNomeIngredientes("Torta", buscaIngs);
        CHECK(res2.empty() == true);
    }

    SUBCASE("Adicionar receita dinamicamente") {
        Receita rec3("Pudim", "Pudim", "Sobremesas", {}, etapas, 30);
        buscador.adicionarReceita(rec3);
        auto res = buscador.buscarPorNome("Pudim");
        CHECK(res.size() == 1);
    }

    SUBCASE("Obter todas as receitas") {
        auto res = buscador.obterTodasAsReceitas();
        CHECK(res.size() == 2);
    }

    SUBCASE("Verificando nenhuma receita encontrada (helper)") {
        std::vector<Receita> resultados;
        CHECK(buscador.nenhumaReceitaEncontrada(resultados) == true);
    }
}