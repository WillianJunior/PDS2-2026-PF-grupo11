#include "../include/doctest.h"
#include "../include/GeradorDeReceita.hpp"
#include "../include/Receita.hpp"

TEST_CASE("Testando GeradorDeReceita") {
    GeradorDeReceita gerador;

    std::vector<IngredienteDaReceita> ingredientes = {
        IngredienteDaReceita(Ingrediente("Farinha", "Farinha"), 300, "g"),
        IngredienteDaReceita(Ingrediente("Agua", "Liquido"), 150, "ml"),
        IngredienteDaReceita(Ingrediente("Queijo", "Queijo"), 100, "g")
    };
    std::vector<EtapaDePreparo> etapas;
    
    SUBCASE("Verificando geracao de receita com template real (Pizza)") {
        Receita recValida("Minha Pizza", "Pizza", "Massas", ingredientes, etapas, 0);
        Receita gerada = gerador.gerar(recValida);
        
        CHECK(gerada.getNome() == "Minha Pizza");
        CHECK(gerada.getTemplateOrigem() == "Pizza");
        // Verifica se conseguiu extrair etapas do arquivo
        CHECK(gerada.getEtapasDePreparo().size() > 0);
        CHECK(gerada.getTempoEstimadoMinutos() > 0);
        CHECK(gerada.estaCompleta() == true);
    }

    SUBCASE("Verificando geracao de receita com template inexistente") {
        Receita recInexistente("Ghost", "TemplateFantasma", "Desconhecido", ingredientes, etapas, 0);
        Receita gerada = gerador.gerar(recInexistente);
        
        CHECK(gerada.getNome() == "Ghost");
        CHECK(gerada.getEtapasDePreparo().size() == 0);
        CHECK(gerada.estaCompleta() == false);
    }

    SUBCASE("Verificando defesa contra Path Traversal") {
        Receita recTraversal("Ataque", "../Pizza", "Hacker", ingredientes, etapas, 0);
        
        // O gerador captura a excecao e retorna Receita vazia
        Receita gerada = gerador.gerar(recTraversal);
        CHECK(gerada.getNome() == "");
        CHECK(gerada.estaCompleta() == false);
    }

    SUBCASE("Verificando receita inicial incompleta") {
        Receita recInvalida("", "", "", {}, {}, 0);
        Receita gerada = gerador.gerar(recInvalida);
        CHECK(gerada.getNome() == "");
    }
}