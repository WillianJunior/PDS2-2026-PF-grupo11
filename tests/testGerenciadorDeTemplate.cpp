#include "doctest.h"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/Template.hpp"
#include "../include/FiltroDeCategoria.hpp"

TEST_CASE("GerenciadorDeTemplate - operações básicas") {
    GerenciadorDeTemplate ger;
    Template temp(1, "Teste", "Conteudo", "Cat");

    SUBCASE("Adicionar, evitar duplicata, buscar e listar") {
        CHECK(ger.adicionarTemplate(temp) == true);
        CHECK(ger.adicionarTemplate(temp) == false); // mesmo ID não deve inserir
        CHECK(ger.buscarTemplatePorId(1) != nullptr);
        auto todos = ger.listarTodos();
        CHECK(todos.size() == 1);
    }

    SUBCASE("Remover quando não existe") {
        // sem inserir, remover deve retornar false
        CHECK(ger.removerTemplate(1) == false);
    }

    SUBCASE("Remover quando existe") {
        ger.adicionarTemplate(temp);
        CHECK(ger.removerTemplate(1) == true);
        CHECK(ger.buscarTemplatePorId(1) == nullptr);
    }

    SUBCASE("Validar ingrediente no template") {
        ger.adicionarTemplate(temp);
        Template* p = ger.buscarTemplatePorId(1);
        REQUIRE(p != nullptr);
        p->adicionarTipoPermitido("Seco");

        CHECK(ger.validarIngredienteNoTemplate(1, "Seco") == true);
        CHECK(ger.validarIngredienteNoTemplate(1, "Liquido") == false);
        // id inexistente -> false
        CHECK(ger.validarIngredienteNoTemplate(42, "Seco") == false);
    }

    SUBCASE("Filtrar por categoria") {
        Template t2(2, "Outro", "Conteudo2", "OutraCat");
        ger.adicionarTemplate(temp);
        ger.adicionarTemplate(t2);

        FiltroDeCategoria filtro("Cat");
        auto filtrados = ger.filtrarPorCategoria(filtro);
        CHECK(filtrados.size() == 1);
        CHECK(filtrados[0].getId() == 1);
    }
}