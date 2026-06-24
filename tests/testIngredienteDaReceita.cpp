#include "../include/doctest.h"
#include "../include/IngredienteDaReceita.hpp"

TEST_CASE("Testando IngredienteDaReceita") {
    Ingrediente ingBase("Farinha", "Seco");
    IngredienteDaReceita ingReceita(ingBase, 2.5, "Xicaras");

    SUBCASE("Verificando getters") {
        CHECK(ingReceita.getQuantidade() == doctest::Approx(2.5));
        CHECK(ingReceita.getUnidadeDeMedida() == "Xicaras");
        CHECK(ingReceita.getIngrediente().getNome() == "Farinha");
    }
}