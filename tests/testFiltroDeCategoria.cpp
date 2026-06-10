#include "../include/doctest.h"
#include "../include/FiltroDeCategoria.hpp"
#include "../include/Template.hpp"
#include <vector>

TEST_CASE("Testando FiltroDeCategoria") {
    FiltroDeCategoria filtro("Sobremesa");
    Template t1(1, "Bolo", "Conteudo", "Sobremesa");

    SUBCASE("Verificando atributos e validacoes") {
        CHECK(filtro.getCategoriaAlvo() == "Sobremesa");
        CHECK(filtro.satisfazFiltro(t1) == true);
    }

    SUBCASE("Verificando aplicarFiltro") {
        std::vector<Template> templates = { t1 };
        auto res = filtro.aplicarFiltro(templates);
        CHECK(res.size() == 1);
        CHECK(res[0].getId() == 1);
    }
}