#ifndef RISOTTO_TEMPLATE_HPP
#define RISOTTO_TEMPLATE_HPP

#include "Template.hpp"

class RisottoTemplate : public Template {
public:
    RisottoTemplate(int id, const std::string& nome);
    bool aceitaTipoIngrediente(const std::string& tipo) const override;
};

#endif