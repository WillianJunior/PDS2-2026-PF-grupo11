#include "Template.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <utility>

namespace {
    std::string removerEspacosExternos(const std::string& texto) {
        auto inicio = std::find_if_not(texto.begin(), texto.end(), [](unsigned char c) {
            return std::isspace(c);
        });

        auto fim = std::find_if_not(texto.rbegin(), texto.rend(), [](unsigned char c) {
            return std::isspace(c);
        }).base();

        if (inicio >= fim) {
            return "";
        }

        return std::string(inicio, fim);
    }

    void validarTextoObrigatorio(const std::string& valor, const char* campo) {
        if (removerEspacosExternos(valor).empty()) {
            throw std::invalid_argument(std::string("Template: campo obrigatorio vazio: ") + campo);
        }
    }
}

Template::Template(int _id, std::string _nome, std::string _conteudo, std::string _categoria)
    : id(_id),
      nome(removerEspacosExternos(_nome)),
      conteudo(std::move(_conteudo)),
      categoria(removerEspacosExternos(_categoria)) {
    if (id <= 0) {
        throw std::invalid_argument("Template: id deve ser positivo");
    }

    validarTextoObrigatorio(nome, "nome");
    validarTextoObrigatorio(categoria, "categoria");
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
    const std::string tipoNormalizado = removerEspacosExternos(tipo);
    if (tipoNormalizado.empty()) {
        throw std::invalid_argument("Template: tipo permitido nao pode ser vazio");
    }

    if (std::find(tiposPermitidos.begin(), tiposPermitidos.end(), tipoNormalizado) == tiposPermitidos.end()) {
        tiposPermitidos.push_back(tipoNormalizado);
    }
}

std::vector<std::string> Template::getTiposPermitidos() const {
    return tiposPermitidos;
}

bool Template::aceitaTipoIngrediente(const std::string& tipo) const {
    const std::string tipoNormalizado = removerEspacosExternos(tipo);
    if (tipoNormalizado.empty()) {
        return false;
    }

    return std::find(tiposPermitidos.begin(), tiposPermitidos.end(), tipoNormalizado) != tiposPermitidos.end();
}
