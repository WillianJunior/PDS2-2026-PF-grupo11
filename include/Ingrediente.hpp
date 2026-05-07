#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <string>

/**
 * @brief Representa um ingrediente base do sistema.
 *
 * A classe Ingrediente armazena o nome e o tipo do ingrediente,
 * servindo como entidade central para validação e composição de receitas.
 */
class Ingrediente {
public:
  /**
   * @brief Cria um ingrediente com nome e tipo.
   * @param nome Nome do ingrediente.
   * @param tipo Tipo ao qual o ingrediente pertence.
   * @throw std::invalid_argument se o nome ou o tipo forem vazios.
   */
  Ingrediente(const std::string &nome, const std::string &tipo);

  /**
   * @brief Retorna o nome do ingrediente.
   * @return Nome do ingrediente.
   */
  std::string getNome() const;

  /**
   * @brief Retorna o tipo do ingrediente.
   * @return Tipo associado ao ingrediente.
   */
  std::string getTipo() const;

  /**
   * @brief Verifica se o ingrediente pertence ao tipo informado.
   * @param tipo Tipo a ser comparado.
   * @return true se o ingrediente pertencer ao tipo informado; false caso
   * contrário.
   */
  bool pertenceAoTipo(const std::string &tipo) const;

private:
  std::string nome_;
  std::string tipo_;
};

#endif