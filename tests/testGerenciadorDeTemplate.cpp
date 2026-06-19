#include "doctest.h"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/PizzaTemplate.hpp"

TEST_CASE("Testando GerenciadorDeTemplate") {
    GerenciadorDeTemplate gerenciador;

    SUBCASE("Adicionar e buscar template") {
        auto temp = std::make_unique<PizzaTemplate>(1, "Marguerita");
        CHECK(gerenciador.adicionarTemplate(std::move(temp)) == true);
        CHECK(gerenciador.buscarTemplatePorId(1) != nullptr);
        CHECK(gerenciador.listarTodos().size() >= 1);
    }

    SUBCASE("Remover template") {
        CHECK(gerenciador.removerTemplate(999) == false);
    }

    SUBCASE("Validar ingrediente no template") {
        
        auto temp = std::make_unique<PizzaTemplate>(2, "Quatro Queijos");
        gerenciador.adicionarTemplate(std::move(temp));
        
       
        auto tipos = gerenciador.buscarTemplatePorId(2)->getTiposPermitidos();
        if(!tipos.empty()) {
            CHECK(gerenciador.validarIngredienteNoTemplate(2, tipos[0]) == true);
        }
    }
}