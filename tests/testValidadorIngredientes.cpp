#include "doctest.h"
#include "../include/ValidadorDeIngredientes.hpp"
#include "../include/PizzaTemplate.hpp"
#include "../include/Ingrediente.hpp"

TEST_CASE("Testando ValidadorDeIngredientes") {
    ValidadorDeIngredientes validador;
    PizzaTemplate temp(1, "Calabresa");
    

    auto tiposAceitos = temp.getTiposPermitidos();
    std::string tipoValido = "Invalido";
    if(!tiposAceitos.empty()) tipoValido = tiposAceitos[0];

    Ingrediente ing("IngredienteTeste", tipoValido);

    SUBCASE("Verificando validacoes") {
        CHECK(validador.validarIngrediente(ing, temp) == true);

        std::vector<Ingrediente> selecao = { ing };
        CHECK(validador.validarSelecao(selecao, temp) == true);
    }

    SUBCASE("Verificando mensagem de erro") {
        Ingrediente ingErrado("Errado", "TipoInexistente");
        CHECK(validador.gerarMensagemErro(ingErrado, temp) != "");
    }
}