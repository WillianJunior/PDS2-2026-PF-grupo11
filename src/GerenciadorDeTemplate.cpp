#include "GerenciadorDeTemplate.hpp"

bool GerenciadorDeTemplate::adicionarTemplate(const Template& novoTemplate) {
    return false;
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    return false;
}

Template* GerenciadorDeTemplate::buscarTemplatePorId(int id) {
    return nullptr;
}

std::vector<Template> GerenciadorDeTemplate::listarTodos() const {
    return {};
}

std::vector<Template> GerenciadorDeTemplate::filtrarPorCategoria(const FiltroDeCategoria& filtro) const {
    return {};
}

bool GerenciadorDeTemplate::validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const {
    return false;
}