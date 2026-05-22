#include "doctest.h"
#include "../include/GeradorDeReceita.hpp"
#include "../include/Receita.hpp"

TEST_CASE("Testando GeradorDeReceita") {
    GeradorDeReceita gerador;
    std::vector<IngredienteDaReceita> ingredientes;
    std::vector<EtapaDePreparo> etapas;
    Receita rec("Base", "T", "C", ingredientes, etapas, 10);

    SUBCASE("Verificando tempo estimado e etapas") {
        // Verifica os stubs publicos
        CHECK(gerador.calcularTempoEstimado(etapas) == 0);
        CHECK(gerador.gerarEtapasDePreparo(rec).size() == 0);
    }

    SUBCASE("Verificando geracao") {
        CHECK(gerador.gerar(rec).getNome() == "");
    }
}