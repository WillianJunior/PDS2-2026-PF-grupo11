#ifndef SELETOR_DE_INGREDIENTES_HPP
#define SELETOR_DE_INGREDIENTES_HPP

#include "Ingrediente.hpp"
#include "Template.hpp"
#include <string>
#include <vector>

/**
 * @brief Gerencia os ingredientes selecionados pelo usuário.
 *
 * Essa classe mantém o estado da seleção atual de ingredientes,
 * permitindo adição, remoção, limpeza e consulta da seleção.
 */
class SeletorDeIngredientes {
public:
  /**
   * @brief Cria um seletor de ingredientes vazio.
   */
  SeletorDeIngredientes();

  /**
   * @brief Adiciona um ingrediente à seleção.
   * @param ingrediente Ingrediente a ser adicionado.
   */
  void adicionarIngrediente(const Ingrediente &ingrediente);

  /**
   * @brief Remove um ingrediente da seleção.
   * @param ingrediente Ingrediente a ser removido.
   */
  void removerIngrediente(const Ingrediente &ingrediente);

  /**
   * @brief Limpa toda a seleção atual.
   */
  void limparSelecao();

  /**
   * @brief Retorna a lista atual de ingredientes selecionados.
   * @return Vetor com os ingredientes selecionados.
   */
  std::vector<Ingrediente> getIngredientesSelecionados() const;

  /**
   * @brief Verifica se os slots obrigatórios do template foram preenchidos.
   * @param templateReceita Template atualmente selecionado.
   * @return true se os slots obrigatórios estiverem preenchidos; false caso
   * contrário.
   */
  bool slotsObrigatoriosPreenchidos(const Template &templateReceita) const;

private:
  std::vector<Ingrediente> ingredientesSelecionados_;
};

#endif