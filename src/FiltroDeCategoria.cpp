#include "FiltroDeCategoria.hpp"

FiltroDeCategoria::FiltroDeCategoria(const std::string& _categoriaAlvo) {

}

std::string FiltroDeCategoria::getCategoriaAlvo() const {
    return "";
}

std::vector<Template> FiltroDeCategoria::aplicarFiltro(const std::vector<Template>& templates) const {
    return {};
}

bool FiltroDeCategoria::satisfazFiltro(const Template& t) const {
    return false;
}
