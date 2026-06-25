#include "../include/Template.hpp"
#include <algorithm>
#include <utility>

Template::Template(int _id, std::string _nome, std::string _conteudo, std::string _categoria, std::vector<std::string> _tiposPermitidos)
    : id(_id), nome(std::move(_nome)), conteudo(std::move(_conteudo)), 
    categoria(std::move(_categoria)), tiposPermitidos(std::move(_tiposPermitidos)) {
}

int Template::getId() const {
    return id;
}

std::string Template::getNome() const {
    return nome;
}

void Template::setNome(std::string _nome) {
    nome = std::move(_nome);
}

std::string Template::getCategoria() const {
    return categoria;
}

std::string Template::getConteudo() const {
    return conteudo;
}

void Template::setCategoria(std::string _categoria) {
    categoria = std::move(_categoria);
}

void Template::setConteudo(std::string _conteudo) {
    conteudo = std::move(_conteudo);
}

std::vector<std::string> Template::getTiposPermitidos() const {
    return tiposPermitidos;
}

bool Template::aceitaTipoIngrediente(const std::string& tipo) const {
    return std::find(tiposPermitidos.begin(), tiposPermitidos.end(), tipo) != tiposPermitidos.end();
}
