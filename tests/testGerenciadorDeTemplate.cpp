#include "doctest.h"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/Template.hpp"

TEST_CASE("Testando GerenciadorDeTemplate") {
    GerenciadorDeTemplate gerenciador;
    Template temp(1, "Teste", "Conteudo", "Cat");

    SUBCASE("Adicionar e buscar template") {
        CHECK(gerenciador.adicionarTemplate(temp) == true);
        CHECK(gerenciador.buscarTemplatePorId(1) != nullptr);
        CHECK(gerenciador.listarTodos().size() == 1);
    }

    SUBCASE("Remover template") {
        CHECK(gerenciador.removerTemplate(1) == false);
    }

    SUBCASE("Validar ingrediente no template") {
        CHECK(gerenciador.validarIngredienteNoTemplate(1, "Seco") == true);
    }
}