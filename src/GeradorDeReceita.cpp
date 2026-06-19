#include "GeradorDeReceita.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

GeradorDeReceita::GeradorDeReceita() {
}

Receita GeradorDeReceita::gerar(const Receita& receitaBase) const {
    if (!receitaValida(receitaBase)) {
        return Receita("", "", "", {}, {}, 0);
    }

    try {
        std::vector<EtapaDePreparo> etapasPreparo = gerarEtapasDePreparo(receitaBase);
        int tempoTotalCalculado = calcularTempoEstimado(etapasPreparo);

        return Receita(
            receitaBase.getNome(),
            receitaBase.getTemplateOrigem(),
            receitaBase.getCategoria(),
            receitaBase.getIngredientes(),
            etapasPreparo,
            tempoTotalCalculado
        );
    } catch (const std::exception& e) {
        // Se houver qualquer erro na geração (ex: path traversal ou arquivo corrompido), retorna receita vazia
        return Receita("", "", "", {}, {}, 0);
    }
}

std::vector<EtapaDePreparo> GeradorDeReceita::gerarEtapasDePreparo(const Receita& receitaBase) const {
    std::vector<EtapaDePreparo> etapas;

    std::string templateNome = receitaBase.getTemplateOrigem();
    
    // Defesa contra Path Traversal
    if (templateNome.empty() || 
        templateNome.find("..") != std::string::npos || 
        templateNome.find('/') != std::string::npos || 
        templateNome.find('\\') != std::string::npos) {
        throw std::invalid_argument("Erro: Nome do template invalido ou inseguro.");
    }

    std::transform(templateNome.begin(), templateNome.end(), templateNome.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    std::string caminhoArquivo = "data/templates/" + templateNome + ".txt";
    std::ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        return etapas;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string campoNumero, campoTempo, descricao, campoTipos;

        // Parsing dos campos separados por ';'
        if (!std::getline(ss, campoNumero, ';')) continue;
        if (!std::getline(ss, campoTempo, ';'))  continue;
        if (!std::getline(ss, descricao, ';'))   continue;
        std::getline(ss, campoTipos, ';');

        EtapaDePreparo etapa;
        
        // Defesa contra erros de conversão de tipos em std::stoi
        try {
            etapa.numero = std::stoi(campoNumero);
            etapa.tempoEstimadoMinutos = std::stoi(campoTempo);
            if (etapa.numero <= 0 || etapa.tempoEstimadoMinutos < 0) {
                continue; // Valores numéricos inválidos ou inconsistentes são ignorados
            }
        } catch (...) {
            continue; // Ignora a linha malformada defensivamente
        }
        
        etapa.descricao = descricao;

        if (!campoTipos.empty()) {
            std::stringstream ssTipos(campoTipos);
            std::string tipo;
            std::vector<std::string> tiposNecessarios;
            while (std::getline(ssTipos, tipo, ',')) {
                if (!tipo.empty()) tiposNecessarios.push_back(tipo);
            }

            for (const auto& ingReceita : receitaBase.getIngredientes()) {
                for (const auto& tipoNecessario : tiposNecessarios) {
                    if (ingReceita.getIngrediente().pertenceAoTipo(tipoNecessario)) {
                        etapa.ingredientesUsados.push_back(ingReceita);
                        break;
                    }
                }
            }
        }

        etapas.push_back(etapa);
    }

    return etapas;
}

int GeradorDeReceita::calcularTempoEstimado(const std::vector<EtapaDePreparo>& etapas) const {
    int tempoTotal = 0;
    for (const auto& etapa : etapas) {
        if (etapa.tempoEstimadoMinutos > 0) {
            tempoTotal += etapa.tempoEstimadoMinutos;
        }
    }
    return tempoTotal;
}

bool GeradorDeReceita::receitaValida(const Receita& receitaBase) const {
    if (receitaBase.getNome().empty() || receitaBase.getTemplateOrigem().empty() || receitaBase.getIngredientes().empty()) {
        return false;
    }
    return true;
}
