/**
 * @brief Definição da classe Receita e da estrutura EtapaDePreparo.
 *
 * Este arquivo contém a lógica para representação de uma receita culinária,
 * permitindo a gestão de ingredientes, etapas e validação de integridade.
 */

#ifndef RECEITA_HPP
#define RECEITA_HPP

#include <string>
#include <vector>
#include "IngredienteDaReceita.hpp"

/**
 * @brief Representa uma unidade lógica no processo de confecção da receita.
 */
struct EtapaDePreparo {
    int numero;                                  ///< Ordem da etapa no processo.
    std::string descricao;                       ///< Instruções detalhadas do que fazer.
    std::vector<IngredienteDaReceita> ingredientesUsados; ///< Ingredientes utilizados nesta fase.
    int tempoEstimadoMinutos;                    ///< Duração prevista para concluir esta etapa.
};

/**
 * @class Receita
 * @brief Entidade que armazena os dados de uma receita culinária.
 *
 * A classe é responsável por armazenar informações estruturais (nome, categoria,
 * template) e fornecer seus dados para as classes colaboradoras.
 */
class Receita {
public:
    /**
     * @brief Construtor da classe Receita.
     * @param nome Nome do prato (ex: "Pizza Margherita").
     * @param templateOrigem Base culinária (ex: "Pizza", "Pasta").
     * @param categoria Classificação do prato (ex: "Massas", "Vegano").
     * @param ingredientes Lista dos ingredientes contretos usados na  receita.
     * @param etapasDePreparo Etapas de preparo da receita. 
     */
    Receita(const std::string& nome,
            const std::string& templateOrigem,
            const std::string& categoria,
            const std::vector<IngredienteDaReceita>& ingredientes,
            const std::vector<EtapaDePreparo>& etapasDePreparo,
            int tempoEstimadoMinutos   
        );

    /** @name Getters (Contrato de Leitura) */
    ///@{

    /**
     * @brief Retorna o nome do prato.
     * @return Nome da receita.
     */
    std::string getNome() const;

    /**
     * @brief Retorna o template de origem da receita.
     * @return Nome do template (ex: "Pizza", "Pasta").
     */
    std::string getTemplateOrigem() const;

    /**
     * @brief Retorna a categoria gastronômica da receita.
     * @return Nome da categoria (ex: "Massas", "Carnes").
     */
    std::string getCategoria() const;

    /**
     * @brief Retorna a lista de ingredientes selecionados.
     * @return Vetor com os nomes dos ingredientes.
     */
    std::vector<IngredienteDaReceita> getIngredientes() const;

    /**
     * @brief Retorna as etapas de preparo para o GeradorDeReceita.
     * @return Vetor ordenado de EtapaDePreparo.
     */
    std::vector<EtapaDePreparo> getEtapasDePreparo() const;

    /**
     * @brief Retorna o tempo estimado total de preparo.
     * @return Tempo em minutos.
     */
    int getTempoEstimadoMinutos() const;

    ///@}

    

    /**
     * @brief Valida se a receita possui os dados mínimos necessários, para exibição, armazenamento ou recuperação do sistema.
     *
     * Verifica se há template, ingredientes e nome definidos,
     * permitindo que o GeradorDeReceita prossiga com a geração.
     *
     * @return true Se a receita estiver consistente com os requisitos.
     * @return false Caso falte alguma informação essencial.
     */
    bool estaCompleta() const;

private:
    std::string nome_;                           ///< Nome identificador da receita.
    std::string templateOrigem_;                 ///< Tipo base da receita.
    std::string categoria_;                      ///< Categoria gastronômica.
    std::vector<IngredienteDaReceita> ingredientes_;      ///< Coleção de ingredientes selecionados.
    std::vector<EtapaDePreparo> etapasDePreparo_; ///< Lista ordenada de passos.
    int tempoEstimadoMinutos_;                   ///< Somatório do tempo de todas as etapas.
};

#endif