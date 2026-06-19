#include "PastaTemplate.hpp"

PastaTemplate::PastaTemplate(int id, const std::string& nome)
    : Template(id, nome, "Base de massa italiana", "Massas") {
    tiposPermitidos = {"Queijo", "Molho", "Proteína", "Vegetal",
                       "Tempero", "Embutido", "Fruto do Mar"};
}