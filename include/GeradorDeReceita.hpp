/**
 * @file GeradorDeReceita.hpp
 * @brief Definição da classe GeradorDeReceita.
 *
 * Responsável por gerar a receita final a partir de um template
 * e de ingredientes previamente validados.
 */

#ifndef GERADORDERECEITA_HPP
#define GERADORDERECEITA_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include "Receita.hpp"

/**
 * @class GeradorDeReceita
 * @brief Orquestra a geração da receita final.
 *
 * Recebe os dados necessários para compor a receita,
 * gera as etapas de preparo e calcula o tempo estimado total.
 */
class GeradorDeReceita {
public:
    /**
     * @brief Construtor da classe GeradorDeReceita.
     */
    GeradorDeReceita();

    /**
     * @brief Gera a receita final a partir de uma receita base.
     *
     * @param receitaBase Receita contendo template, nome, categoria e ingredientes válidos.
     * @return Receita final com etapas e tempo estimado definidos.
     * @throws std::runtime_error Se a receita base não estiver pronta para geração.
     */
    Receita gerar(const Receita& receitaBase) const;

    /**
     * @brief Gera as etapas de preparo da receita.
     * @param receitaBase Receita contendo os dados necessários.
     * @return Vetor ordenado de EtapaDePreparo.
     */
    std::vector<EtapaDePreparo> gerarEtapasDePreparo(const Receita& receitaBase) const;

    /**
     * @brief Calcula o tempo total estimado da receita.
     * @param etapas Lista de etapas geradas.
     * @return Tempo total estimado em minutos.
     */
    int calcularTempoEstimado(const std::vector<EtapaDePreparo>& etapas) const;

private:
    /**
     * @brief Verifica se a receita base possui os dados mínimos para geração.
     * @param receitaBase Receita a ser validada.
     * @return true se a receita puder ser processada; false caso contrário.
     */
    bool receitaValida(const Receita& receitaBase) const;
};

#endif