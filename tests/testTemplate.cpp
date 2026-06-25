#include "../include/doctest.h"
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

    SUBCASE("Verificando validacoes com ingrediente valido") {
        CHECK(validador.validarIngrediente(ing, temp) == true);

        std::vector<Ingrediente> selecao = { ing };
        CHECK(validador.validarSelecao(selecao, temp) == true);
    }

    SUBCASE("Verificando selecao vazia retorna false") {
        std::vector<Ingrediente> selecaoVazia;
        CHECK(validador.validarSelecao(selecaoVazia, temp) == false);
    }

    SUBCASE("Selecao com ingrediente invalido retorna false") {
        Ingrediente ingInvalido("Invalido", "TipoNaoAceito");
        std::vector<Ingrediente> selecaoInvalida = { ingInvalido };
        CHECK(validador.validarSelecao(selecaoInvalida, temp) == false);
    }

    SUBCASE("Verificando mensagem de erro para ingrediente invalido") {
        Ingrediente ingErrado("Errado", "TipoInexistente");
        std::string msg = validador.gerarMensagemErro(ingErrado, temp);
        CHECK(msg != "");
        CHECK(msg.find("Errado") != std::string::npos);
    }

    SUBCASE("Mensagem de erro para ingrediente valido retorna string vazia") {
        std::string msg = validador.gerarMensagemErro(ing, temp);
        CHECK(msg == "");
    }
}
