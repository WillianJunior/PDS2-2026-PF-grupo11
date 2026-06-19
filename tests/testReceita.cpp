#include "doctest.h"
#include "../include/Receita.hpp"

TEST_CASE("Testando Receita") {
    std::vector<IngredienteDaReceita> ingredientes;
    std::vector<EtapaDePreparo> etapas;
    Receita receita("Bolo", "TempBolo", "Sobremesa", ingredientes, etapas, 40);

    SUBCASE("Verificando getters") {
        CHECK(receita.getNome() == "Bolo");
        CHECK(receita.getTemplateOrigem() == "TempBolo");
        CHECK(receita.getCategoria() == "Sobremesa");
        CHECK(receita.getTempoEstimadoMinutos() == 40);
        CHECK(receita.getIngredientes().empty() == true);
        CHECK(receita.getEtapasDePreparo().empty() == true);
    }

    SUBCASE("Verificando estaCompleta") {
        CHECK(receita.estaCompleta() == true);
    }
}