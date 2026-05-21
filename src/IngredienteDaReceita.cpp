#include "IngredienteDaReceita.hpp"

IngredienteDaReceita::IngredienteDaReceita(const Ingrediente &ingrediente, 
    double quantidade,const std::string &unidadeDeMedida) 
        :ingrediente_("","") {

}

Ingrediente IngredienteDaReceita::getIngrediente() const {
    return Ingrediente("", "");
}

double IngredienteDaReceita::getQuantidade() const {
    return 0.0;
}

std::string IngredienteDaReceita::getUnidadeDeMedida() const {
    return "";
}

