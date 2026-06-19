#include "FiltroDeCategoria.hpp"

FiltroDeCategoria::FiltroDeCategoria(const std::string& _categoriaAlvo)
    : categoriaAlvo(_categoriaAlvo) {
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
    return t.getCategoria() == categoriaAlvo;
}
