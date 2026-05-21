#include "Template.hpp"

Template::Template(int _id, std::string _nome, std::string _conteudo, std::string _categoria) {

}

int Template::getId() const {
    return 0;
}

std::string Template::getNome() const {
    return "";
}

std::string Template::getCategoria() const {
    return "";
}


void Template::adicionarTipoPermitido(const std::string& tipo) {
}

std::vector<std::string> Template::getTiposPermitidos() const {
    return {};
}

bool Template::aceitaTipoIngrediente(const std::string& tipo) const {
    return false;
}
