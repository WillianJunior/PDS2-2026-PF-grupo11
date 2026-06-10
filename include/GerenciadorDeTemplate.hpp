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
  */
class GerenciadorDeTemplate {
private:
    std::map<int, Template> mapaDeTemplates; 

public:
    /**
     * @brief Construtor do Gerenciador.
     */
    GerenciadorDeTemplate();

    /**
     * @brief Adiciona um novo template ao sistema.
     * @param novoTemplate O objeto da classe Template a ser armazenado.
     * @return true se adicionado com sucesso, false se o ID do template já existir no sistema.
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
     *
     * Utiliza ponteiros para evitar cópias desnecessárias e permitir a modificação
     * do template retornado (ex: adicionar novos tipos permitidos dinamicamente).
     *
     * @param id O identificador numérico do template.
     * @return Um ponteiro para o Template correspondente, ou nullptr se não for encontrado.
     */
    Template* buscarTemplatePorId(int id);

    /**
     * @brief Retorna a lista completa de todos os templates cadastrados.
     * @return Vetor contendo todos os templates do sistema.
     */
    std::vector<Template> listarTodos() const;

    /**
     * @brief Busca e lista templates aplicando uma regra de filtro de categoria.
     * @param filtro Objeto instanciado do FiltroDeCategoria contendo a regra.
     * @return Vetor contendo apenas os templates que passaram na validação do filtro.
     */
    std::vector<Template> filtrarPorCategoria(const FiltroDeCategoria& filtro) const;

    /**
     * @brief Delega a validação de um ingrediente para o template espec�fico.
     *
     * Interage com a regra de negócio da classe Template para verificar se o
     * tipo fornecido pode ser utilizado nele, sem precisar extrair o objeto inteiro.
     *
     * @param idTemplate O identificador do template a ser consultado.
     * @param tipoIngrediente A string representando a categoria/tipo do ingrediente.
     * @return true se o template existir e aceitar o ingrediente, false caso contrário.
     */
    bool validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const;

};

#endif // GERENCIADORDETEMPLATE_HPP