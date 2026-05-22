#include "doctest.h"
#include "../include/SeletorDeIngredientes.hpp"
#include "../include/Ingrediente.hpp"
#include "../include/Template.hpp"

TEST_CASE("Testando SeletorDeIngredientes") {
    SeletorDeIngredientes seletor;
    Ingrediente ing("Sal", "Tempero");
    Template temp(1, "Temp", "Cont", "Cat");

    SUBCASE("Adicionar e limpar ingredientes") {
        seletor.adicionarIngrediente(ing);
        CHECK(seletor.getIngredientesSelecionados().size() == 1);

        seletor.removerIngrediente(ing);
        CHECK(seletor.getIngredientesSelecionados().empty() == true);

        seletor.adicionarIngrediente(ing);
        seletor.limparSelecao();
        CHECK(seletor.getIngredientesSelecionados().empty() == true);
    }

    SUBCASE("Verificando preenchimento de slots") {
        CHECK(seletor.slotsObrigatoriosPreenchidos(temp) == true);
    }
}