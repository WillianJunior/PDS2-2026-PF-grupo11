#include "../include/RisottoTemplate.hpp"

RisottoTemplate::RisottoTemplate(int id, const std::string& nome)
    : Template(id, nome, "Base de arroz arbóreo cremoso", "Arroz") {
    tiposPermitidos = {"Queijo", "Vegetal", "Proteina",
                       "Tempero", "Fruto do Mar", "Caldo"};
}

bool RisottoTemplate::aceitaTipoIngrediente(const std::string& tipo) const {
    return Template::aceitaTipoIngrediente(tipo);
}