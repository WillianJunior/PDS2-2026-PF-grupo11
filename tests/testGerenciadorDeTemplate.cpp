#include "../include/doctest.h"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/FiltroDeCategoria.hpp"
#include "../include/PizzaTemplate.hpp"
#include "../include/PastaTemplate.hpp"
#include "../include/RisottoTemplate.hpp"
#include <cstdio>

TEST_CASE("Testando GerenciadorDeTemplate") {
    // Remove o arquivo de teste temporário antigo para garantir isolamento
    std::remove("templates_test_tmp.txt");
    // Instancia o gerenciador de forma isolada
    GerenciadorDeTemplate gerenciador("templates_test_tmp.txt");

    SUBCASE("Adicionar template nulo retorna false") {
        CHECK(gerenciador.adicionarTemplate(nullptr) == false);
    }

    SUBCASE("Adicionar, buscar por ID e listar todos") {
        auto t1 = std::make_unique<PizzaTemplate>(100, "Pizza Teste");
        CHECK(gerenciador.adicionarTemplate(std::move(t1)) == true);

        CHECK(gerenciador.buscarTemplatePorId(100).has_value());
        CHECK(gerenciador.buscarTemplatePorId(999).has_value() == false);

        auto lista = gerenciador.listarTodosRefs();
        bool achou = false;
        for (const auto& t : lista) {
            if (t.get().getId() == 100) achou = true;
        }
        CHECK(achou == true);
    }

    SUBCASE("Adicionar template duplicado retorna false") {
        auto t1 = std::make_unique<PizzaTemplate>(200, "Pizza A");
        auto t2 = std::make_unique<PizzaTemplate>(200, "Pizza B");
        CHECK(gerenciador.adicionarTemplate(std::move(t1)) == true);
        CHECK(gerenciador.adicionarTemplate(std::move(t2)) == false);
    }

    SUBCASE("Remover template existente e inexistente") {
        auto t1 = std::make_unique<PastaTemplate>(300, "Pasta Teste");
        gerenciador.adicionarTemplate(std::move(t1));
        CHECK(gerenciador.removerTemplate(300) == true);
        CHECK(gerenciador.removerTemplate(300) == false);
        CHECK(gerenciador.removerTemplate(999) == false);
    }

    SUBCASE("Buscar template por ID como referencia opcional") {
        auto t1 = std::make_unique<RisottoTemplate>(400, "Risotto Teste");
        gerenciador.adicionarTemplate(std::move(t1));

        auto ref = gerenciador.buscarTemplatePorIdRef(400);
        CHECK(ref.has_value() == true);
        CHECK(ref->get().getNome() == "Risotto Teste");

        auto refNone = gerenciador.buscarTemplatePorIdRef(999);
        CHECK(refNone.has_value() == false);
    }

    SUBCASE("Listar todos como referencias constantes") {
        auto t1 = std::make_unique<PizzaTemplate>(500, "Pizza Refs");
        gerenciador.adicionarTemplate(std::move(t1));

        auto refs = gerenciador.listarTodosRefs();
        bool achou = false;
        for (const auto& r : refs) {
            if (r.get().getId() == 500) achou = true;
        }
        CHECK(achou == true);
    }

    SUBCASE("Filtrar por categoria e por refs") {
        auto t1 = std::make_unique<PizzaTemplate>(600, "Pizza Filtro");
        auto t2 = std::make_unique<PastaTemplate>(601, "Pasta Filtro");
        gerenciador.adicionarTemplate(std::move(t1));
        gerenciador.adicionarTemplate(std::move(t2));

        FiltroDeCategoria filtroPizza("Pizza");
        auto filtrados = gerenciador.filtrarPorCategoriaRefs(filtroPizza);
        bool achouPizza = false;
        for (const auto& t : filtrados) {
            if (t.get().getId() == 600) achouPizza = true;
        }
        CHECK(achouPizza == true);

        auto filtradosRefs = gerenciador.filtrarPorCategoriaRefs(filtroPizza);
        bool achouRef = false;
        for (const auto& r : filtradosRefs) {
            if (r.get().getId() == 600) achouRef = true;
        }
        CHECK(achouRef == true);
    }

    SUBCASE("Validar ingrediente no template por ID") {
        auto t1 = std::make_unique<PizzaTemplate>(700, "Pizza Validar");
        gerenciador.adicionarTemplate(std::move(t1));

        CHECK(gerenciador.validarIngredienteNoTemplate(700, "Queijo") == true);
        CHECK(gerenciador.validarIngredienteNoTemplate(700, "Fruta") == false);
        CHECK(gerenciador.validarIngredienteNoTemplate(999, "Queijo") == false);
    }

        SUBCASE("Salvar templates em arquivo") {
        auto t1 = std::make_unique<PizzaTemplate>(800, "Pizza Salvar");
        gerenciador.adicionarTemplate(std::move(t1));
        CHECK(gerenciador.salvarTemplatesEmArquivo("templates_test_tmp.txt") == true);
    }

    // Limpa o arquivo temporário ao finalizar o ciclo de testes
    std::remove("templates_test_tmp.txt");
}