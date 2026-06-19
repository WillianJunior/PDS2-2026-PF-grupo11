#include "doctest.h"
#include "../include/Receita.hpp"
#include "../include/IngredienteDaReceita.hpp"
#include <vector>
#include <string>

TEST_CASE("Testando Receita") {
    
    
    Receita receita("Bolo", "TempBolo", "Sobremesa", {}, {}, 40);

    SUBCASE("Verificando getters") {
        CHECK(receita.getNome() == "Bolo");
        CHECK(receita.getTemplateOrigem() == "TempBolo");
        CHECK(receita.getCategoria() == "Sobremesa");
        CHECK(receita.getTempoEstimadoMinutos() == 40);
        CHECK(receita.getIngredientes().empty() == true);
        CHECK(receita.getEtapasDePreparo().empty() == true);
    }

    SUBCASE("Verificando estaCompleta") {
        CHECK(receita.estaCompleta() == false);
    }
}