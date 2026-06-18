#include "FiltroDeCategoria.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>

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
}

FiltroDeCategoria::FiltroDeCategoria(const std::string& _categoriaAlvo)
    : categoriaAlvo(removerEspacosExternos(_categoriaAlvo)) {
    if (categoriaAlvo.empty()) {
        throw std::invalid_argument("FiltroDeCategoria: categoria alvo nao pode ser vazia");
    }
}

std::string FiltroDeCategoria::getCategoriaAlvo() const {
    return categoriaAlvo;
}

std::vector<Template> FiltroDeCategoria::aplicarFiltro(const std::vector<Template>& templates) const {
    std::vector<Template> resultados;
    resultados.reserve(templates.size());
    for (const auto& t : templates) {
        if (satisfazFiltro(t)) {
            resultados.push_back(t);
        }
    }
    return resultados;
}

bool FiltroDeCategoria::satisfazFiltro(const Template& t) const {
    return removerEspacosExternos(t.getCategoria()) == categoriaAlvo;
}
