#include "ValidadorDeIngredientes.hpp"

bool ValidadorDeIngredientes::validarIngrediente(const Ingrediente &ingrediente,
    const Template &templateReceita) const {
        return false;
}

bool ValidadorDeIngredientes::validarSelecao(const std::vector<Ingrediente> &selecaoIngredientes,
    const Template &templateReceita) const {
        return false;
}

std::string ValidadorDeIngredientes::gerarMensagemErro(const Ingrediente &ingrediente,
    const Template &templateReceita) const {
        return "";
}