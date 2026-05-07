#ifndef VALIDADOR_DE_INGREDIENTES_HPP
#define VALIDADOR_DE_INGREDIENTES_HPP

#include "Ingrediente.hpp"
#include "Template.hpp"
#include <string>
#include <vector>

/**
 * @brief Valida ingredientes e seleções com base nas regras do template.
 *
 * Essa classe verifica se os ingredientes escolhidos respeitam os tipos
 * permitidos e as restrições associadas ao template selecionado.
 */
class ValidadorDeIngredientes {
public:
  /**
   * @brief Valida se um ingrediente pode ser adicionado a uma seleção.
   * @param ingrediente Ingrediente a ser validado.
   * @param templateReceita Template para o qual a validação será feita.
   * @return true se o ingrediente puder ser adicionado; false caso contrário.
   */
  bool validarIngrediente(const Ingrediente &ingrediente,
                          const Template &templateReceita) const;

  /**
   * @brief Valida a seleção completa de ingredientes.
   * @param selecaoIngredientes Seleção atual de ingredientes.
   * @param templateReceita Template para o qual a validação será feita.
   * @return true se a seleção completa for válida; false caso contrário.
   */
  bool validarSelecao(const std::vector<Ingrediente> &selecaoIngredientes,
                      const Template &templateReceita) const;

  /**
   * @brief Gera uma mensagem explicando a rejeição de um ingrediente.
   * @param ingrediente Ingrediente rejeitado na validação.
   * @param templateReceita Template usado na validação.
   * @return Mensagem de erro com o motivo da rejeição.
   */
  std::string gerarMensagemErro(const Ingrediente &ingrediente,
                                const Template &templateReceita) const;
};

#endif