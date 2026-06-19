#include "PizzaTemplate.hpp"

PizzaTemplate::PizzaTemplate(int id, const std::string& nome)
    : Template(id, nome, "Base de pizza com molho e queijo", "Massas") {
    tiposPermitidos = {"Queijo", "Molho", "Embutido", "Vegetal", "Tempero"};
}

bool PizzaTemplate::aceitaTipoIngrediente(const std::string& tipo) const {
    if (tipo == "Fruta") {
        return false;
    }
    return Template::aceitaTipoIngrediente(tipo);
}