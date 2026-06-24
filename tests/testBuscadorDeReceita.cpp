#include "../include/doctest.h"
#include "../include/BuscadorDeReceita.hpp"

TEST_CASE("Testando BuscadorDeReceitas") {
    std::vector<Receita> repo;
    BuscadorDeReceitas buscador(repo);

    SUBCASE("Verificando buscas vazias") {
        CHECK(buscador.buscarPorNome("Bolo").empty() == true);

        std::vector<std::string> ings = { "Ovo" };
        CHECK(buscador.buscarPorIngredientes(ings).empty() == true);
        CHECK(buscador.buscarPorNomeIngredientes("Bolo", ings).empty() == true);
    }

    SUBCASE("Verificando nenhuma receita encontrada") {
        std::vector<Receita> resultados;
        CHECK(buscador.nenhumaReceitaEncontrada(resultados) == true);
    }
}