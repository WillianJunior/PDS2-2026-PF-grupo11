#include "Template.hpp"
#include <algorithm>

Template::Template(int _id, std::string _nome, std::string _conteudo, std::string _categoria)
    : id(_id), nome(std::move(_nome)), conteudo(std::move(_conteudo)), categoria(std::move(_categoria)) {
}

int Template::getId() const {
    return id;
}

std::string Template::getNome() const {
    return nome;
}

std::string Template::getCategoria() const {
    return categoria;
}

void Template::adicionarTipoPermitido(const std::string& tipo) {
    // Evita duplicatas
    if (std::find(tiposPermitidos.begin(), tiposPermitidos.end(), tipo) == tiposPermitidos.end()) {
        tiposPermitidos.push_back(tipo);
    }
}

std::vector<std::string> Template::getTiposPermitidos() const {
    return tiposPermitidos;
}

bool Template::aceitaTipoIngrediente(const std::string& tipo) const {
    return std::find(tiposPermitidos.begin(), tiposPermitidos.end(), tipo) != tiposPermitidos.end();
}
