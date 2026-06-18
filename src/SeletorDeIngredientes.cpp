#include "SeletorDeIngredientes.hpp"
#include <algorithm>

SeletorDeIngredientes::SeletorDeIngredientes() {}

void SeletorDeIngredientes::adicionarIngrediente(
    const Ingrediente &ingrediente) {
  ingredientesSelecionados_.push_back(ingrediente);
}

void SeletorDeIngredientes::removerIngrediente(const Ingrediente &ingrediente) {
  auto it = std::find_if(ingredientesSelecionados_.begin(),
                         ingredientesSelecionados_.end(),
                         [&ingrediente](const Ingrediente &i) {
                           return i.getNome() == ingrediente.getNome();
                         });

  if (it != ingredientesSelecionados_.end()) {
    ingredientesSelecionados_.erase(it);
  }
}

void SeletorDeIngredientes::limparSelecao() {
  ingredientesSelecionados_.clear();
}
std::vector<Ingrediente>
SeletorDeIngredientes::getIngredientesSelecionados() const {
  return ingredientesSelecionados_;
}

bool SeletorDeIngredientes::slotsObrigatoriosPreenchidos(
    const Template &templateReceita) const {

  std::vector<std::string> tiposExigidos = templateReceita.getTiposPermitidos();

  for (const std::string &tipo : tiposExigidos) {
    bool encontrou = std::any_of(
        ingredientesSelecionados_.begin(), ingredientesSelecionados_.end(),
        [&tipo](const Ingrediente &ing) { return ing.pertenceAoTipo(tipo); });

    if (!encontrou) {
      return false;
    }
  }

  return true;
}