#ifndef PIZZA_TEMPLATE_HPP
#define PIZZA_TEMPLATE_HPP

#include "Template.hpp"

class PizzaTemplate : public Template {
public:
    PizzaTemplate(int id, const std::string& nome);

    bool aceitaTipoIngrediente(const std::string& tipo) const override;
};

#endif