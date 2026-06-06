#include "GeradorDeReceita.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>

GeradorDeReceita::GeradorDeReceita() {

}

Receita GeradorDeReceita::gerar(const Receita& receitaBase) const {
    if(!receitaValida(receitaBase)){
        throw std::runtime_error("Erro: receita base possui dados insuficientes para a geracao.");
    }
   
    std::vector<EtapaDePreparo> etapasPreparo = gerarEtapasDePreparo(receitaBase);

    int tempoTotalCalculado = calcularTempoEstimado(etapasPreparo);

    Receita receitaFinal(
     receitaBase.getNome(),
     receitaBase.getTemplateOrigem(),
     receitaBase.getCategoria(),
     receitaBase.getIngredientes(),
     etapasPreparo,
     tempoTotalCalculado
    );

    return receitaFinal;
}

std::vector<EtapaDePreparo> GeradorDeReceita::gerarEtapasDePreparo(const Receita& receitaBase) const {
    return {};
}

int GeradorDeReceita::calcularTempoEstimado(const std::vector<EtapaDePreparo>& etapas) const {
    int tempoTotal = 0;

    for (const auto& etapa : etapas){
        tempoTotal += etapa.tempoEstimadoMinutos;
    }

    return tempoTotal;
}

bool GeradorDeReceita::receitaValida(const Receita& receitaBase) const {
    if (receitaBase.getNome().empty() ||  receitaBase.getTemplateOrigem().empty() ||  receitaBase.getIngredientes().empty()) {
        return false;
    }
    return true;
}