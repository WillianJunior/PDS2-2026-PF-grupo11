#ifndef FILTRODECATEGORIA_HPP
#define FILTRODECATEGORIA_HPP

#include <string>
#include <vector>
#include "Template.hpp"

 /**
  * @class FiltroDeCategoria
  * @brief Responsável por encapsular o critério de busca por categoria.
  *
  * Esta classe aplica o Princípio da Responsabilidade Única (SRP),
  * separando a lógica de validação do filtro da lógica de armazenamento
  * e controle do GerenciadorDeTemplate.
  */
class FiltroDeCategoria {
private:
    std::string categoriaAlvo; 

public:
    /**
     * @brief Construtor da classe FiltroDeCategoria.
     * @param _categoriaAlvo A string exata da categoria que servirá como critério de busca.
     */
    explicit FiltroDeCategoria(const std::string& _categoriaAlvo);

    /**
     * @brief Obtém a categoria alvo configurada no filtro.
     * @return Uma string constante com a categoria alvo.
     */
    std::string getCategoriaAlvo() const;

    /**
     * @brief Filtra uma coleção de templates com base na categoria alvo.
     *
     * Itera sobre a lista fornecida, utilizando o método getCategoria() de cada
     * objeto Template para verificar se ele corresponde ao critério estabelecido.
     *
     * @param templates Lista de templates a serem avaliados.
     * @return Um vetor contendo apenas os templates que correspondem à categoria procurada.
     */
    std::vector<Template> aplicarFiltro(const std::vector<Template>& templates) const;

    /**
     * @brief Avalia individualmente se um template satisfaz o critério do filtro.
     * @param t O template a ser avaliado.
     * @return true se a categoria do template for igual à categoria alvo, false caso contrário.
     */
    bool satisfazFiltro(const Template& t) const;

    /**
     * @brief Destrutor padrão.
     */
    ~FiltroDeCategoria() = default;
};

#endif // FILTRODECATEGORIA_HPP