#include "../include/doctest.h"
#include "../include/SeletorDeIngredientes.hpp"
#include "../include/Ingrediente.hpp"
#include "../include/Template.hpp"
#include "../include/PizzaTemplate.hpp"

TEST_CASE("Testando SeletorDeIngredientes") {
    SeletorDeIngredientes seletor;
    Ingrediente ing("Sal", "Tempero");
    Template temp(1, "Temp", "Cont", "Cat");

    SUBCASE("Adicionar e limpar ingredientes") {
        seletor.adicionarIngrediente(ing);
        CHECK(seletor.getIngredientesSelecionados().size() == 1);

        seletor.removerIngrediente(ing);
        CHECK(seletor.getIngredientesSelecionados().empty() == true);

        // Remover ingrediente que nao existe (cobre o if sem erase)
        seletor.removerIngrediente(ing);
        CHECK(seletor.getIngredientesSelecionados().empty() == true);

        seletor.adicionarIngrediente(ing);
        seletor.limparSelecao();
        CHECK(seletor.getIngredientesSelecionados().empty() == true);
    }

    SUBCASE("Verificando preenchimento de slots com template sem tipos") {
        CHECK(seletor.slotsObrigatoriosPreenchidos(temp) == true);
    }

    SUBCASE("Verificando slot nao preenchido com PizzaTemplate") {
        PizzaTemplate pizzaTemp(1, "TestePizza");
        // Nenhum ingrediente adicionado: deve falhar pois Pizza exige tipos
        CHECK(seletor.slotsObrigatoriosPreenchidos(pizzaTemp) == false);
    }

    SUBCASE("Slot preenchido com PizzaTemplate") {
        PizzaTemplate pizzaTemp(1, "TestePizza");
        auto tipos = pizzaTemp.getTiposPermitidos();
        for (const auto& tipo : tipos) {
            seletor.adicionarIngrediente(Ingrediente("Ing" + tipo, tipo));
        }
        CHECK(seletor.slotsObrigatoriosPreenchidos(pizzaTemp) == true);
    }
}