#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <string>
#include <vector>

/**
 * @file Template.hpp
 * @brief Definição da classe Template.
 */

 /**
  * @class Template
  * @brief Representa um modelo ou padrão reutilizável no sistema.
  *
  * Esta classe armazena as informações do template e gerencia as regras
  * de negócio referentes aos tipos de ingredientes que ele permite receber.
  */
class Template {
private:
    int id;                                   ///< Identificador único do template.
    std::string nome;                         ///< Nome descritivo do template.
    std::string conteudo;                     ///< O conteúdo ou estrutura do template.
    std::string categoria;                    ///< Categoria para fins de organização e filtragem.
    std::vector<std::string> tiposPermitidos; ///< Lista que guarda os tipos de ingredientes permitidos.

public:
    /**
     * @brief Construtor da classe Template.
     * @param _id Identificador único.
     * @param _nome Nome do template.
     * @param _conteudo Corpo principal do template.
     * @param _categoria Categoria associada.
     */
    //// Novo construtor que aceita a lista de tipos permitidos (com valor padrão vazio)
    Template(int _id, std::string _nome, std::string _conteudo, 
        std::string _categoria, std::vector<std::string> _tiposPermitidos = {});

    /**
     * @brief Obtém o ID do template.
     * @return O valor inteiro do ID.
     */
    int getId() const;

    /**
     * @brief Obtém o nome do template.
     * @return Uma string com o nome.
     */
    std::string getNome() const;

    /**
     * @brief Atualiza o nome do template.
     * @param _nome Novo nome.
     */
    void setNome(std::string _nome);

    /**
     * @brief Obtém a categoria do template.
     * @return Uma string com a categoria.
     */
    std::string getCategoria() const;

    /**
     * @brief Obtem o conteudo do template.
     * @return Uma string com o conteudo.
     */
    std::string getConteudo() const;

    /**
     * @brief Atualiza a categoria do template.
     * @param _categoria Nova categoria.
     */
    void setCategoria(std::string _categoria);

    /**
     * @brief Atualiza o conteúdo do template.
     * @param _conteudo Novo conteúdo.
     */
    void setConteudo(std::string _conteudo);

    //adicionarTipoPermitido foi substituido pela hierarquia, cada classe filha ja possui regras específicas.

    /**
     * @brief Expõe os tipos permitidos.
     * @return Um vetor contendo todas as strings de tipos de ingredientes aceitos.
     */
    virtual std::vector<std::string> getTiposPermitidos() const;

    /**
     * @brief Regra de aceitação: verifica se o template aceita um determinado tipo de ingrediente.
     *
     * Este método busca o tipo passado como parâmetro dentro da lista
     * interna de tipos permitidos.
     *
     * @param tipo O tipo de ingrediente que se deseja testar.
     * @return true se o tipo é permitido, false se for rejeitado.
     */
    virtual bool aceitaTipoIngrediente(const std::string& tipo) const;

    /**
     * @brief Destrutor padr�o.
     */
    virtual ~Template() = default;
};

#endif // TEMPLATE_HPP
