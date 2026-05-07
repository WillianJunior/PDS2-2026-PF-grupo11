#ifndef GERENCIADORDETEMPLATE_HPP
#define GERENCIADORDETEMPLATE_HPP

#include <vector>
#include <string>
#include <map>
#include "Template.hpp"
#include "FiltroDeCategoria.hpp"

 /**
  * @class GerenciadorDeTemplate
  * @brief Controla o ciclo de vida dos templates e centraliza as operações do sistema.
  *
  * Atua como a classe controladora (Controller), gerenciando a coleção de
  * templates. Fornece métodos para criação, exclusão, busca e delega a
  * validação de ingredientes diretamente para a classe Template.
  */
class GerenciadorDeTemplate {
private:
    std::map<int, Template> mapaDeTemplates; ///< Armazena os templates usando o ID como chave para busca rápida.

public:
    /**
     * @brief Construtor padrão do Gerenciador.
     */
    GerenciadorDeTemplate() = default;

    /**
     * @brief Adiciona um novo template ao sistema.
     * @param novoTemplate O objeto da classe Template a ser armazenado.
     * @return true se adicionado com sucesso, false se o ID do template já existir.
     */
    bool adicionarTemplate(const Template& novoTemplate);

    /**
     * @brief Remove um template do sistema pelo seu identificador.
     * @param id O identificador numérico do template a ser removido.
     * @return true se o template foi encontrado e removido, false caso contrário.
     */
    bool removerTemplate(int id);

    /**
     * @brief Busca um template específico no sistema através do seu ID.
     * @param id O identificador numérico do template.
     * @return Um ponteiro para o Template correspondente, ou nullptr se não for encontrado.
     */
    Template* buscarTemplatePorId(int id);

    /**
     * @brief Retorna a lista completa de todos os templates cadastrados.
     * @return Vetor contendo todos os templates armazenados no gerenciador.
     */
    std::vector<Template> listarTodos() const;

    /**
     * @brief Busca e lista templates aplicando uma regra de filtro de categoria.
     * @param filtro Objeto instanciado do FiltroDeCategoria contendo a regra.
     * @return Vetor contendo apenas os templates que passaram na validação do filtro.
     */
    std::vector<Template> buscarPorCategoria(const FiltroDeCategoria& filtro) const;

    /**
     * @brief Valida se um tipo de ingrediente é aceito por um template específico.
     *
     * Este método busca o template pelo ID e chama internamente a função
     * aceitaTipoIngrediente() do próprio template, respeitando o encapsulamento.
     *
     * @param idTemplate O identificador numérico do template a ser consultado.
     * @param tipoIngrediente A string representando o tipo do ingrediente a ser testado.
     * @return true se o template existir e aceitar o ingrediente, false caso contrário.
     */
    bool validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const;

    /**
     * @brief Destrutor padrão.
     */
    ~GerenciadorDeTemplate() = default;
};

#endif // GERENCIADORDETEMPLATE_HPP