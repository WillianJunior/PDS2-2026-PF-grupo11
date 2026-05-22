#include "doctest.h"
#include "../include/Template.hpp"

TEST_CASE("Testando Template") {
    Template temp(1, "Massa Base", "Conteudo massa", "Massa");

    SUBCASE("Verificando getters") {
        CHECK(temp.getId() == 1);
        CHECK(temp.getNome() == "Massa Base");
        CHECK(temp.getCategoria() == "Massa");
    }

    SUBCASE("Verificando tipos permitidos") {
        temp.adicionarTipoPermitido("Farinha");
        CHECK(temp.getTiposPermitidos().size() == 1);
        CHECK(temp.aceitaTipoIngrediente("Farinha") == true);
        CHECK(temp.aceitaTipoIngrediente("Liquido") == false);
    }
}