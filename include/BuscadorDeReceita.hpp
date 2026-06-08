/**
 * @brief Definição da classe BuscadorDeReceitas.
 *
 * Responsável por localizar receitas no repositório com base em
 * critérios de busca como nome do prato e ingredientes.
 */

#ifndef BUSCADORDERECEITAS_HPP
#define BUSCADORDERECEITAS_HPP

#include <string>
#include <vector>
#include "Receita.hpp"

/**
 * @class BuscadorDeReceitas
 * @brief Localiza receitas compatíveis com os critérios informados pelo usuário.
 *
 * Atua como intermediário entre o usuário e o RepositorioDeReceitas,
 * normalizando termos, combinando critérios e ordenando resultados.
 */
class BuscadorDeReceitas {
public:

    /**
     * @brief Construtor da classe BuscadorDeReceitas.
     * @param repositorio Lista de receitas disponíveis no sistema.
     */
    BuscadorDeReceitas(const std::vector<Receita>& repositorio);

    /** @name Buscas (US5) */
    ///@{

    /**
     * @brief Busca receitas pelo nome do prato.
     * @param nome Nome ou parte do nome do prato (ex: "Carbonara").
     * @return Lista de receitas compatíveis com o nome informado.
     */
    std::vector<Receita> buscarPorNome(const std::string& nome) const;

    /**
     * @brief Busca receitas que contenham um ou mais ingredientes.
     * @param ingredientes Lista de ingredientes informados pelo usuário.
     * @return Lista de receitas compatíveis com os ingredientes.
     */
    std::vector<Receita> buscarPorIngredientes(
            const std::vector<std::string>& ingredientes) const;

    /**
     * @brief Combina busca por nome e ingredientes simultaneamente.
     * @param nome Nome ou parte do nome do prato.
     * @param ingredientes Lista de ingredientes desejados.
     * @return Lista de receitas que satisfazem ambos os critérios.
     */
    std::vector<Receita> buscarPorNomeIngredientes(
            const std::string& nome,
            const std::vector<std::string>& ingredientes) const;

    ///@}

    /** @name Resultados */
    ///@{

    /**
     * @brief Verifica se uma busca retornou resultados.
     * @param resultados Lista retornada por qualquer método de busca.
     * @return true Se a lista estiver vazia — nenhuma receita encontrada.
     */
    bool nenhumaReceitaEncontrada(const std::vector<Receita>& resultados) const;

    /**
     * @brief Ordena a lista de receitas por relevância em relação ao termo buscado.
     * @param resultados Lista de receitas a ordenar.
     * @param termo Termo usado como referência para ordenação.
     * @return Lista ordenada por relevância.
     */
    std::vector<Receita> ordenarPorRelevancia(
            const std::vector<Receita>& resultados,
            const std::string& termo) const;

    ///@}

private:

    ///< Repositório de receitas fornecido ao construtor.
    std::vector<Receita> repositorio_;

    /**
     * @brief Normaliza um termo de busca para comparação.
     *
     * Converte para minúsculas e remove acentos,
     * garantindo que "Carbonara" e "carbonara" sejam equivalentes.
     *
     * @param termo Termo original informado pelo usuário.
     * @return Termo normalizado para comparação.
     */
    std::string normalizarTermo(const std::string& termo) const;
};

#endif