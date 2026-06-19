#ifndef INGREDIENTE_DA_RECEITA_HPP
#define INGREDIENTE_DA_RECEITA_HPP

#include "Ingrediente.hpp"
#include <string>

/**
 * @brief Representa um ingrediente concreto dentro de uma receita.
 *
 * Essa classe associa um Ingrediente base à sua quantidade e unidade de medida
 * no contexto de uma receita específica.
 */
class IngredienteDaReceita {
public:
  /**
   * @brief Cria um ingrediente concreto da receita.
   * @param ingrediente Ingrediente base.
   * @param quantidade Quantidade utilizada na receita.
   * @param unidadeDeMedida Unidade de medida da quantidade.
   */
  IngredienteDaReceita(const Ingrediente &ingrediente, double quantidade,
                       const std::string &unidadeDeMedida);

  /**
   * @brief Retorna o ingrediente base associado.
   * @return Ingrediente base.
   */
  Ingrediente getIngrediente() const;

  /**
   * @brief Retorna a quantidade utilizada na receita.
   * @return Quantidade do ingrediente.
   */
  double getQuantidade() const;

  /**
   * @brief Retorna a unidade de medida utilizada.
   * @return Unidade de medida do ingrediente.
   */
  std::string getUnidadeDeMedida() const;

private:
  Ingrediente ingrediente_;
  double quantidade_;
  std::string unidadeDeMedida_;
  static constexpr double QUANTIDADE_MAXIMA = 10000.0;

};

#endif