#include "../include/PastaTemplate.hpp"

PastaTemplate::PastaTemplate(int id, const std::string& nome)
    : Template(id, nome, "Base de massa italiana", "Pasta",
               {"Queijo", "Molho", "Proteina", "Vegetal", "Tempero", "Fruto do Mar"}) {
}