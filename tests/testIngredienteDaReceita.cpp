#include "doctest.h"
#include "../include/IngredienteDaReceita.hpp"
#include <stdexcept>

TEST_CASE("Testando IngredienteDaReceita") {
    Ingrediente ingBase("Farinha", "Seco");
    IngredienteDaReceita ingReceita(ingBase, 2.5, "Xicaras");

    SUBCASE("Verificando getters") {
        CHECK(ingReceita.getQuantidade() == doctest::Approx(2.5));
        CHECK(ingReceita.getUnidadeDeMedida() == "Xicaras");
        CHECK(ingReceita.getIngrediente().getNome() == "Farinha");
    }
}

TEST_CASE("Testando exceções em IngredienteDaReceita") {
    Ingrediente ingBase("Farinha", "Seco");
    SUBCASE("Quantidade negativa deve lancar exceção") {
        CHECK_THROWS_AS(
            IngredienteDaReceita(ingBase, -1.0, "Gramas"),
            std::invalid_argument
        );
    }
    SUBCASE("Quantidade zero deve lancar exceção") {
        CHECK_THROWS_AS(
            IngredienteDaReceita(ingBase, 0.0, "Gramas"),
            std::invalid_argument
        );
    }
    SUBCASE("Quantidade acima do limite deve lancar exceção") {
        CHECK_THROWS_AS(
            IngredienteDaReceita(ingBase, 99999.9, "Gramas"),
            std::invalid_argument
        );
    }
    SUBCASE("Unidade de medida vazia deve lancar exceção") {
        CHECK_THROWS_AS(
            IngredienteDaReceita(ingBase, 100.0, ""),
            std::invalid_argument
        );
    }
    SUBCASE("Ingrediente válido nao deve lancar exceção") {
        CHECK_NOTHROW(
            IngredienteDaReceita(ingBase, 100.0, "Gramas")
        );
    }
}