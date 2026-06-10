#include "doctest.h"
#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/Template.hpp"
#include "../include/FiltroDeCategoria.hpp"
#include <cstdio>

// Helper: remove o arquivo de persistência para garantir isolamento entre testes
static void removerArquivoTemplates() {
    std::remove("templates.txt");
}

struct LimpadorTemplates {
    LimpadorTemplates() { removerArquivoTemplates(); }
    ~LimpadorTemplates() { removerArquivoTemplates(); }
};

TEST_CASE("GerenciadorDeTemplate - adicionar e listar") {
    LimpadorTemplates limpador;
    GerenciadorDeTemplate ger;

    Template t1(1, "Teste", "Conteudo", "Cat");

    CHECK(ger.adicionarTemplate(t1) == true);
    // tentativa de duplicata deve falhar
    CHECK(ger.adicionarTemplate(t1) == false);

    Template* p = ger.buscarTemplatePorId(1);
    REQUIRE(p != nullptr);
    CHECK(p->getId() == 1);
    CHECK(p->getNome() == "Teste");

    auto todos = ger.listarTodos();
    CHECK(todos.size() == 1);
    CHECK(todos[0].getId() == 1);
}

TEST_CASE("GerenciadorDeTemplate - remover") {
    LimpadorTemplates limpador;
    GerenciadorDeTemplate ger;

    // remover inexistente
    CHECK(ger.removerTemplate(42) == false);

    Template t1(5, "A", "C", "CatA");
    ger.adicionarTemplate(t1);
    CHECK(ger.removerTemplate(5) == true);
    CHECK(ger.buscarTemplatePorId(5) == nullptr);
}

TEST_CASE("GerenciadorDeTemplate - validar ingredientes") {
    LimpadorTemplates limpador;
    GerenciadorDeTemplate ger;

    Template t1(10, "Pizza", "Receita", "Italiana");
    ger.adicionarTemplate(t1);

    // template existe, mas tipos permitidos ainda vazios
    CHECK(ger.validarIngredienteNoTemplate(10, "Seco") == false);

    // adicionar tipo permitido via ponteiro retornado
    Template* p = ger.buscarTemplatePorId(10);
    REQUIRE(p != nullptr);
    p->adicionarTipoPermitido("Seco");

    CHECK(ger.validarIngredienteNoTemplate(10, "Seco") == true);
    CHECK(ger.validarIngredienteNoTemplate(10, "Liquido") == false);

    // id inexistente sempre retorna false
    CHECK(ger.validarIngredienteNoTemplate(999, "Seco") == false);
}

TEST_CASE("GerenciadorDeTemplate - filtrar por categoria") {
    LimpadorTemplates limpador;
    GerenciadorDeTemplate ger;

    Template t1(1, "T1", "C1", "CatX");
    Template t2(2, "T2", "C2", "CatY");
    Template t3(3, "T3", "C3", "CatX");

    ger.adicionarTemplate(t1);
    ger.adicionarTemplate(t2);
    ger.adicionarTemplate(t3);

    FiltroDeCategoria filtro("CatX");
    auto filtrados = ger.filtrarPorCategoria(filtro);

    CHECK(filtrados.size() == 2);
    // Como o gerenciador usa map, a ordem é por ID
    CHECK(filtrados[0].getId() == 1);
    CHECK(filtrados[1].getId() == 3);
}

TEST_CASE("GerenciadorDeTemplate - persistencia: salvar e carregar") {
    LimpadorTemplates limpador;

    // criar gerenciador, adicionar templates e deixar sair de escopo para forcar salvamento
    {
        GerenciadorDeTemplate ger1;
        Template t1(21, "Persist1", "C", "Pcat");
        Template t2(22, "Persist2", "C", "Pcat");
        ger1.adicionarTemplate(t1);
        ger1.adicionarTemplate(t2);
        // ao final deste bloco, os templates devem ter sido salvos no arquivo
    }

    // novo gerenciador deve carregar os templates do arquivo
    GerenciadorDeTemplate ger2;
    auto todos = ger2.listarTodos();
    CHECK(todos.size() == 2);
    CHECK(ger2.buscarTemplatePorId(21) != nullptr);
    CHECK(ger2.buscarTemplatePorId(22) != nullptr);

    // remover e verificar persistência
    ger2.removerTemplate(21);
    // criar novo gerenciador para recarregar do arquivo
    GerenciadorDeTemplate ger3;
    auto todos2 = ger3.listarTodos();
    CHECK(todos2.size() == 1);
    CHECK(ger3.buscarTemplatePorId(21) == nullptr);
    CHECK(ger3.buscarTemplatePorId(22) != nullptr);
}

TEST_CASE("GerenciadorDeTemplate - não sobrescreve ao adicionar com mesmo id") {
    LimpadorTemplates limpador;
    GerenciadorDeTemplate ger;

    Template t1(30, "Nome1", "C1", "CatA");
    Template t2(30, "Nome2", "C2", "CatB");

    CHECK(ger.adicionarTemplate(t1) == true);
    // tentar adicionar outro com mesmo id deve retornar false e não sobrescrever
    CHECK(ger.adicionarTemplate(t2) == false);

    Template* p = ger.buscarTemplatePorId(30);
    REQUIRE(p != nullptr);
    CHECK(p->getNome() == "Nome1");
    CHECK(p->getCategoria() == "CatA");
}