#include "IngredienteDaReceita.hpp"

IngredienteDaReceita::IngredienteDaReceita(const Ingrediente &ingrediente,
                                           double quantidade,
                                           const std::string &unidadeDeMedida)

    : ingrediente_(ingrediente), quantidade_(quantidade),
      unidadeDeMedida_(unidadeDeMedida) {}

Ingrediente IngredienteDaReceita::getIngrediente() const {
  return ingrediente_;
}

double IngredienteDaReceita::getQuantidade() const { return quantidade_; }

std::string IngredienteDaReceita::getUnidadeDeMedida() const {
  return unidadeDeMedida_;
}
