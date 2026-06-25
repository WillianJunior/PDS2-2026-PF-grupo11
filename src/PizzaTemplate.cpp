#include "../include/PizzaTemplate.hpp"

PizzaTemplate::PizzaTemplate(int id, const std::string& nome)
    : Template(id, nome, "Base de pizza com molho e queijo", "Pizza",
               {"Queijo", "Molho", "Vegetal", "Tempero", "Proteina"}) {
}

bool PizzaTemplate::aceitaTipoIngrediente(const std::string& tipo) const {
    if (tipo == "Fruta") {
        return false;
    }
    return Template::aceitaTipoIngrediente(tipo);
}