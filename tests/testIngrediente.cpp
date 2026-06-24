#include "../include/doctest.h"
#include "../include/Ingrediente.hpp"

TEST_CASE("Testando a entidade Ingrediente") {
    Ingrediente ingrediente("Tomate", "Fruto");

    SUBCASE("Verificando getters basicos") {
        CHECK(ingrediente.getNome() == "Tomate");
        CHECK(ingrediente.getTipo() == "Fruto");
    }

    SUBCASE("Verificando checagem de tipo") {
        CHECK(ingrediente.pertenceAoTipo("Fruto") == true);
        CHECK(ingrediente.pertenceAoTipo("Carne") == false);
    }
}