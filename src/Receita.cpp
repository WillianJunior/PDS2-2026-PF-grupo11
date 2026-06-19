#include "Receita.hpp"
#include <stdexcept>

Receita::Receita(const std::string& nome,
                const std::string& templateOrigem,
                const std::string& categoria,
                const std::vector<IngredienteDaReceita>& ingredientes,
                const std::vector<EtapaDePreparo>& etapasDePreparo,
                int tempoEstimadoMinutos) 
                
                :nome_(nome),
                templateOrigem_(templateOrigem),
                categoria_(categoria),
                ingredientes_(ingredientes),
                etapasDePreparo_(etapasDePreparo),
                tempoEstimadoMinutos_(tempoEstimadoMinutos)
{
    if (tempoEstimadoMinutos < 0) {
        throw std::invalid_argument("Erro: O tempo estimado de preparo nao pode ser negativo.");
    }
}

std::string Receita::getNome() const {
    return nome_;
}

std::string Receita::getTemplateOrigem() const {
    return templateOrigem_;
}

std::string Receita::getCategoria() const {
    return categoria_;
}


std::vector<IngredienteDaReceita> Receita::getIngredientes() const {
    return ingredientes_;
}

std::vector<EtapaDePreparo> Receita::getEtapasDePreparo() const {
    return etapasDePreparo_;
}

int Receita::getTempoEstimadoMinutos() const {
    return tempoEstimadoMinutos_;
}

bool Receita::estaCompleta() const {
    if( nome_.empty() || templateOrigem_.empty() || categoria_.empty() || ingredientes_.empty() || etapasDePreparo_.empty() || tempoEstimadoMinutos_ <= 0){

        return false;
    }else{
        return true;
    }

}
