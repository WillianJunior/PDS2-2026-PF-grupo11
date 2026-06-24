#include "../include/doctest.h"
#include "../include/InterfaceTerminal.hpp"
#include "../include/BuscadorDeReceita.hpp"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/GeradorDeReceita.hpp"

TEST_CASE("Testando InterfaceTerminal") {
    std::vector<Receita> repo;
    BuscadorDeReceitas b(repo);
    GerenciadorDeTemplate gt;
    GeradorDeReceita gr;

    SUBCASE("Verificando instanciacao da interface") {
      
        InterfaceTerminal it(b, gt, gr);
        CHECK(true);
    }
}