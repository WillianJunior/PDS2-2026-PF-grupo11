/**
 * @file InterfaceTerminal.hpp
 * @brief Definição da classe InterfaceTerminal.
 *
 * Responsável por toda a interação com o usuário via terminal,
 * orquestrando as chamadas às classes de negócio do sistema.
 */

#ifndef INTERFACETERMINAL_HPP
#define INTERFACETERMINAL_HPP

#include <string>
#include <vector>
#include <functional>
#include <optional>
#include "BuscadorDeReceita.hpp"
#include "GerenciadorDeTemplate.hpp"
#include "GeradorDeReceita.hpp"
#include "SeletorDeIngredientes.hpp"
#include "ValidadorDeIngredientes.hpp"
#include "FiltroDeCategoria.hpp"
#include "Receita.hpp"
#include "Template.hpp"
#include "Ingrediente.hpp"

/**
 * @class InterfaceTerminal
 * @brief Camada de apresentação do sistema via linha de comando.
 *
 * Centraliza a exibição de menus, leitura de entradas do usuário
 * e delegação de operações às classes de negócio correspondentes.
 * Não contém lógica de domínio — apenas orquestra e exibe resultados.
 */
class InterfaceTerminal {
public:
    using TemplateConstRef = std::reference_wrapper<const Template>;

    /**
     * @brief Construtor da InterfaceTerminal.
     * @param buscador      Instância do BuscadorDeReceitas para consultas.
     * @param gerenciador   Instância do GerenciadorDeTemplate para navegação de templates.
     * @param gerador       Instância do GeradorDeReceita para criação de receitas.
     */
    InterfaceTerminal(BuscadorDeReceitas& buscador,
        GerenciadorDeTemplate& gerenciador,
        GeradorDeReceita& gerador);

    /**
     * @brief Inicia o loop principal da aplicação.
     *
     * Exibe o menu principal e mantém a execução até que o usuário
     * escolha a opção de sair.
     */
    void iniciar();

private:

    // ---------------------------------------------------------------
    // Dependências (injetadas pelo construtor)
    // ---------------------------------------------------------------

    BuscadorDeReceitas&    buscador_;    ///< Serviço de busca de receitas.
    GerenciadorDeTemplate& gerenciador_; ///< Serviço de gerenciamento de templates.
    GeradorDeReceita&      gerador_;     ///< Serviço de geração de receitas.

    // ---------------------------------------------------------------
    // Menu principal
    // ---------------------------------------------------------------

    /**
     * @brief Exibe o menu principal e retorna a opção escolhida.
     * @return Inteiro correspondente à opção selecionada pelo usuário.
     */
    int exibirMenuPrincipal() const;

    /**
     * @brief Processa a opção selecionada no menu principal.
     * @param opcao Opção escolhida pelo usuário.
     * @return false se o usuário escolheu sair; true caso contrário.
     */
    bool processarOpcao(int opcao);

    // ---------------------------------------------------------------
    // Fluxo: Buscar receita (US5)
    // ---------------------------------------------------------------

    /**
     * @brief Conduz o fluxo de busca de receitas pelo usuário.
     *
     * Permite buscar por nome, por ingredientes ou por ambos,
     * exibindo os resultados ordenados por relevância.
     */
    void fluxoBuscarReceita();

    /**
     * @brief Exibe o submenu de busca e retorna a opção escolhida.
     * @return Inteiro correspondente ao critério de busca selecionado.
     */
    int exibirSubMenuBusca() const;

    /**
     * @brief Lê e exibe os resultados de uma busca por nome.
     */
    void buscarPorNome();

    /**
     * @brief Lê e exibe os resultados de uma busca por ingredientes.
     */
    void buscarPorIngredientes();

    /**
     * @brief Lê e exibe os resultados de uma busca combinada (nome + ingredientes).
     */
    void buscarPorNomeEIngredientes();

    // ---------------------------------------------------------------
    // Fluxo: Navegar por categoria
    // ---------------------------------------------------------------

    /**
     * @brief Conduz o fluxo de navegação de templates por categoria.
     *
     * Lista as categorias disponíveis, aplica o FiltroDeCategoria
     * e exibe os templates correspondentes.
     */
    void fluxoNavegaPorCategoria();

    // ---------------------------------------------------------------
    // Fluxo: Criar receita
    // ---------------------------------------------------------------

    /**
     * @brief Conduz o fluxo completo de criação de uma nova receita.
     *
     * Solicita template, ingredientes (com validação em tempo real)
     * e gera a receita final via GeradorDeReceita.
     */
    void fluxoCriarReceita();



    /**
     * @brief Conduz o fluxo completo de criação de um novo Template.
     *
     * Solicita solicita os dados para o novo template.
     */
    void fluxoCriarTemplate();

    /**
     * @brief Permite editar a lista de tipos permitidos de um template.
     * @param tipos Lista inicial de tipos permitidos.
     * @return Lista editada pelo usuario.
     */
    std::vector<std::string> editarTiposPermitidos(std::vector<std::string> tipos);

    /**
     * @brief Conduz a seleção interativa de ingredientes para um template.
     * @param templateEscolhido Template selecionado pelo usuário.
     * @return SeletorDeIngredientes com a seleção final validada.
     */
    std::optional<SeletorDeIngredientes> selecionarIngredientes(const Template& templateEscolhido);

    // ---------------------------------------------------------------
    // Exibição de entidades
    // ---------------------------------------------------------------

    /**
     * @brief Exibe os dados de uma receita formatados no terminal.
     * @param receita Receita a ser exibida.
     */
    void exibirReceita(const Receita& receita) const;

    /**
     * @brief Exibe uma lista de receitas numeradas.
     * @param receitas Lista de receitas a exibir.
     */
    void exibirListaReceitas(const std::vector<Receita>& receitas) const;

    /**
     * @brief Exibe os dados de um template formatados no terminal.
     * @param t Template a ser exibido.
     */
    void exibirTemplate(const Template& t) const;

    /**
     * @brief Exibe uma lista de templates numerados.
     * @param templates Lista de templates a exibir.
     */
    void exibirListaTemplates(const std::vector<TemplateConstRef>& templates) const;

    // ---------------------------------------------------------------
    // Utilitários de I/O
    // ---------------------------------------------------------------

    /**
     * @brief Lê uma string do terminal após exibir um prompt.
     * @param prompt Mensagem exibida antes da leitura.
     * @return String digitada pelo usuário (sem espaços extras).
     */
    std::string lerString(const std::string& prompt) const;

    /**
     * @brief Lê um inteiro do terminal após exibir um prompt.
     *
     * Repete a leitura enquanto a entrada for inválida.
     *
     * @param prompt Mensagem exibida antes da leitura.
     * @return Inteiro digitado pelo usuário.
     */
    int lerInteiro(const std::string& prompt) const;

    /**
     * @brief Lê uma lista de itens separados por vírgula.
     * @param prompt Mensagem exibida antes da leitura.
     * @return Vetor de strings com os itens informados.
     */
    std::vector<std::string> lerListaCSV(const std::string& prompt) const;

    /**
     * @brief Exibe uma linha separadora no terminal.
     */
    void exibirSeparador() const;

    /**
     * @brief Pausa a execução até o usuário pressionar Enter.
     */
    void aguardarEnter() const;

    /**
     * @brief Limpa a tela do terminal.
     */
    void limparTela() const;
};

#endif // INTERFACETERMINAL_HPP
