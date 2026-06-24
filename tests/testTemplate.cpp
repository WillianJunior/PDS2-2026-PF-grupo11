#include "../include/doctest.h"
#include "../include/Template.hpp"
#include "../include/PizzaTemplate.hpp"
#include "../include/PastaTemplate.hpp"
#include "../include/RisottoTemplate.hpp"

TEST_CASE("Testando a hierarquia de Classes Template") {
    
    SUBCASE("Classe Base Template") {
        Template temp(1, "Teste Base", "Conteudo", "Generico");
        CHECK(temp.getId() == 1);
        CHECK(temp.getNome() == "Teste Base");
        CHECK(temp.getCategoria() == "Generico");
        CHECK(temp.aceitaTipoIngrediente("Qualquer") == false);

        temp.setId(2);
        temp.setNome("Novo Nome");
        temp.setCategoria("Nova Categoria");
        temp.setConteudo("Novo Conteudo");
        temp.setTiposPermitidos({"Queijo", "Molho"});

        CHECK(temp.getId() == 2);
        CHECK(temp.getNome() == "Novo Nome");
        CHECK(temp.getCategoria() == "Nova Categoria");
        CHECK(temp.getTiposPermitidos().size() == 2);
        CHECK(temp.aceitaTipoIngrediente("Queijo") == true);
    }

    SUBCASE("Subclasse PizzaTemplate") {
        PizzaTemplate pizza(10, "Moda da Casa");
        CHECK(pizza.getId() == 10);
        CHECK(pizza.getCategoria() == "Pizza");
        auto tipos = pizza.getTiposPermitidos();
        CHECK(tipos.empty() == false); 
        CHECK(pizza.aceitaTipoIngrediente(tipos[0]) == true);
    }

    SUBCASE("Subclasse PastaTemplate") {
        PastaTemplate pasta(20, "Fettuccine");
        CHECK(pasta.getId() == 20);
        CHECK(pasta.getCategoria() == "Pasta");
        auto tipos = pasta.getTiposPermitidos();
        CHECK(tipos.empty() == false);
        CHECK(pasta.aceitaTipoIngrediente(tipos[0]) == true);
    }

    SUBCASE("Subclasse RisottoTemplate") {
        RisottoTemplate risotto(30, "Funghi");
        CHECK(risotto.getId() == 30);
        CHECK(risotto.getCategoria() == "Risotto");
        auto tipos = risotto.getTiposPermitidos();
        CHECK(tipos.empty() == false);
        CHECK(risotto.aceitaTipoIngrediente(tipos[0]) == true);
    }
}
