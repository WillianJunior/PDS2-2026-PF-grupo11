#include "doctest.h"
#include "../include/ValidadorDeIngredientes.hpp"
#include "../include/Template.hpp"
#include "../include/Ingrediente.hpp"

TEST_CASE("Testando ValidadorDeIngredientes") {
    ValidadorDeIngredientes validador;
    Template temp(1, "T", "C", "C");
    Ingrediente ing("I", "T");

    SUBCASE("Verificando validacoes") {
        CHECK(validador.validarIngrediente(ing, temp) == true);

        std::vector<Ingrediente> selecao = { ing };
        CHECK(validador.validarSelecao(selecao, temp) == true);
    }

    SUBCASE("Verificando mensagem de erro") {
        CHECK(validador.gerarMensagemErro(ing, temp) != "");
    }
}