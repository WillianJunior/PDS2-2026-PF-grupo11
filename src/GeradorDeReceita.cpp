#include "GeradorDeReceita.hpp"

GeradorDeReceita::GeradorDeReceita() {

}

Receita GeradorDeReceita::gerar(const Receita& receitaBase) const {
    return Receita("", "", "", {}, {}, 0);
}

std::vector<EtapaDePreparo> GeradorDeReceita::gerarEtapasDePreparo(const Receita& receitaBase) const {
    return {};
}

int GeradorDeReceita::calcularTempoEstimado(const std::vector<EtapaDePreparo>& etapas) const {
    return 0;
}

bool GeradorDeReceita::receitaValida(const Receita& receitaBase) const {
    return false;
}