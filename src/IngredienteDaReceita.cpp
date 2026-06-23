#include "IngredienteDaReceita.hpp"
#include <stdexcept>

IngredienteDaReceita::IngredienteDaReceita(const Ingrediente &ingrediente,
                                           double quantidade,
                                           const std::string &unidadeDeMedida)

    : ingrediente_(ingrediente), quantidade_(quantidade),
      unidadeDeMedida_(unidadeDeMedida) {
  
  if (quantidade <= 0) {
    throw std::invalid_argument("Quantidade inválida: deve ser maior que zero");
  }
  
  if (quantidade > QUANTIDADE_MAXIMA) {
    throw std::invalid_argument("Quantidade inválida: excede o limite máximo");
  }

  if (unidadeDeMedida.empty()) {
    throw std::invalid_argument("Unidade de medida inválida: não pode ser vazia");
  }
}

Ingrediente IngredienteDaReceita::getIngrediente() const {
  return ingrediente_;
}

double IngredienteDaReceita::getQuantidade() const { return quantidade_; }

std::string IngredienteDaReceita::getUnidadeDeMedida() const {
  return unidadeDeMedida_;
}