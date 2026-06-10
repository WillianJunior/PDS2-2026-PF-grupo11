#include "ValidadorDeIngredientes.hpp"

bool ValidadorDeIngredientes::validarIngrediente(
    const Ingrediente &ingrediente, const Template &templateReceita) const {
  return templateReceita.aceitaTipoIngrediente(ingrediente.getTipo());
}

bool ValidadorDeIngredientes::validarSelecao(
    const std::vector<Ingrediente> &selecaoIngredientes,
    const Template &templateReceita) const {

  if (selecaoIngredientes.empty()) {
    return false;
  }

  for (const Ingrediente &ingrediente : selecaoIngredientes) {
    if (!validarIngrediente(ingrediente, templateReceita)) {
      return false;
    }
  }

  return true;
}

// Gera uma mensagem explicando POR QUE o ingrediente foi rejeitado
std::string ValidadorDeIngredientes::gerarMensagemErro(
    const Ingrediente &ingrediente, const Template &templateReceita) const {

  if (validarIngrediente(ingrediente, templateReceita)) {
    return "";
  }

  std::string mensagem = "O ingrediente '" + ingrediente.getNome() +
                         "' (tipo: " + ingrediente.getTipo() +
                         ") não é permitido no template '" +
                         templateReceita.getNome() + "'.\nTipos aceitos: ";

  std::vector<std::string> permitidos = templateReceita.getTiposPermitidos();
  for (size_t i = 0; i < permitidos.size(); i++) {
    mensagem += permitidos[i];
    if (i < permitidos.size() - 1) {
      mensagem += ", ";
    }
  }
  mensagem += ".";

  return mensagem;
}