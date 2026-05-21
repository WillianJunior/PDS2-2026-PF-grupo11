#include "Receita.hpp"

Receita::Receita(const std::string& nome,
                const std::string& templateOrigem,
                const std::string& categoria,
                const std::vector<IngredienteDaReceita>& ingredientes,
                const std::vector<EtapaDePreparo>& etapasDePreparo,
                int tempoEstimadoMinutos) {

}

std::string Receita::getNome() const {
    return "";
}

std::string Receita::getTemplateOrigem() const {
    return "";
}

std::string Receita::getCategoria() const {
    return "";
}


std::vector<IngredienteDaReceita> Receita::getIngredientes() const {
    return {};
}

std::vector<EtapaDePreparo> Receita::getEtapasDePreparo() const {
    return {};
}

int Receita::getTempoEstimadoMinutos() const {
    return 0;
}

bool Receita::estaCompleta() const {
    return false;
}
