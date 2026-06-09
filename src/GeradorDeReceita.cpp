#include "GeradorDeReceita.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
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
    std::vector<EtapaDePreparo> etapas;

    // Converte o nome do template para minúsculas para montar o caminho do arquivo
    // Ex: "Pizza" -> "data/templates/pizza.txt"
    std::string templateNome = receitaBase.getTemplateOrigem();
    std::transform(templateNome.begin(), templateNome.end(), templateNome.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    std::string caminhoArquivo = "data/templates/" + templateNome + ".txt";
    std::ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: nao foi possivel abrir o arquivo do template: " + caminhoArquivo);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string campoNumero, campoTempo, descricao, campoTipos;

        // Parsing dos campos separados por ';'
        // Formato: numero;tempoMinutos;descricao;Tipo1,Tipo2,...
        if (!std::getline(ss, campoNumero, ';')) continue;
        if (!std::getline(ss, campoTempo, ';'))  continue;
        if (!std::getline(ss, descricao, ';'))   continue;
        std::getline(ss, campoTipos, ';'); // Pode ser vazio (etapa sem ingredientes)

        EtapaDePreparo etapa;
        etapa.numero = std::stoi(campoNumero);
        etapa.tempoEstimadoMinutos = std::stoi(campoTempo);
        etapa.descricao = descricao;

        // Vincula os ingredientes da receita que pertencem a algum tipo exigido pela etapa
        if (!campoTipos.empty()) {
            // Separa os tipos: "Molho,Queijo,Proteina" -> ["Molho", "Queijo", "Proteina"]
            std::stringstream ssTipos(campoTipos);
            std::string tipo;
            std::vector<std::string> tiposNecessarios;
            while (std::getline(ssTipos, tipo, ',')) {
                if (!tipo.empty()) tiposNecessarios.push_back(tipo);
            }

            // Para cada ingrediente concreto da receita, verifica se pertence a algum tipo da etapa
            for (const auto& ingReceita : receitaBase.getIngredientes()) {
                for (const auto& tipoNecessario : tiposNecessarios) {
                    if (ingReceita.getIngrediente().pertenceAoTipo(tipoNecessario)) {
                        etapa.ingredientesUsados.push_back(ingReceita);
                        break; // Evita duplicar o mesmo ingrediente
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