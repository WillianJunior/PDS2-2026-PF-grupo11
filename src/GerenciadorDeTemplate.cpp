#include "GerenciadorDeTemplate.hpp"

bool GerenciadorDeTemplate::adicionarTemplate(const Template& novoTemplate) {
    int id = novoTemplate.getId();
    auto res = mapaDeTemplates.emplace(id, novoTemplate);
    return res.second; // true se inserido, false se já existia o id
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    return mapaDeTemplates.erase(id) > 0;
}

Template* GerenciadorDeTemplate::buscarTemplatePorId(int id) {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return nullptr;
    return &it->second;
}

std::vector<Template> GerenciadorDeTemplate::listarTodos() const {
    std::vector<Template> lista;
    lista.reserve(mapaDeTemplates.size());
    for (const auto& par : mapaDeTemplates) {
        lista.push_back(par.second);
    }
    return lista;
}

std::vector<Template> GerenciadorDeTemplate::filtrarPorCategoria(const FiltroDeCategoria& filtro) const {
    std::vector<Template> todos = listarTodos();
    return filtro.aplicarFiltro(todos);
}

bool GerenciadorDeTemplate::validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const {
    auto it = mapaDeTemplates.find(idTemplate);
    if (it == mapaDeTemplates.end()) return false;
    return it->second.aceitaTipoIngrediente(tipoIngrediente);
}