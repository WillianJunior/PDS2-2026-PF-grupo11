#include "GerenciadorDeTemplate.hpp"
#include "PizzaTemplate.hpp"
#include "PastaTemplate.hpp"    
#include "RisottoTemplate.hpp"
#include "FiltroDeCategoria.hpp" 
#include <algorithm>
#include <fstream>
#include <sstream>

namespace {
    const std::string ARQUIVO_TEMPLATES = "templates.txt";

    bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream f(nomeArquivo);
        return f.good();
    }

    void salvarTemplatesEmArquivo(const std::vector<Template*>& templates) {
        std::ofstream arquivo(ARQUIVO_TEMPLATES);
        if (!arquivo.is_open()) return;

        for (const auto* tmpl : templates) {
            arquivo << tmpl->getId() << "|"
                    << tmpl->getNome() << "|"
                    << "" << "|" 
                    << tmpl->getCategoria() << "|";

            auto tipos = tmpl->getTiposPermitidos();
            for (size_t i = 0; i < tipos.size(); ++i) {
                arquivo << tipos[i];
                if (i + 1 < tipos.size()) arquivo << ",";
            }
            arquivo << '\n';
        }
    }

    std::vector<std::unique_ptr<Template>> carregarTemplatesDoArquivo() {
        std::vector<std::unique_ptr<Template>> templates;
        if (!arquivoExiste(ARQUIVO_TEMPLATES)) return templates;

        std::ifstream arquivo(ARQUIVO_TEMPLATES);
        if (!arquivo.is_open()) return templates;

        std::string linha;
        while (std::getline(arquivo, linha)) {
            if (linha.empty()) continue;
            std::istringstream iss(linha);
            std::string idStr, nome, conteudo, categoria, tiposStr;

            if (!std::getline(iss, idStr, '|')) continue;
            if (!std::getline(iss, nome, '|')) continue;
            if (!std::getline(iss, conteudo, '|')) continue;
            if (!std::getline(iss, categoria, '|')) continue;
            if (!std::getline(iss, tiposStr)) tiposStr = "";

            try {
                int id = std::stoi(idStr);
                std::unique_ptr<Template> tmpl;

                if (categoria == "Pizza") {
                    tmpl = std::make_unique<PizzaTemplate>(id, nome);
                } else if (categoria == "Pasta" || categoria == "Massas") {
                    tmpl = std::make_unique<PastaTemplate>(id, nome);
                } else if (categoria == "Risotto" || categoria == "Arroz") {
                    tmpl = std::make_unique<RisottoTemplate>(id, nome);
                } else {
                    tmpl = std::make_unique<Template>(id, nome, "", categoria);
                }

                (void)tiposStr; 
                templates.push_back(std::move(tmpl));   
            } catch (...) {
                continue; 
            }
        }

        return templates;
    }
} 

GerenciadorDeTemplate::GerenciadorDeTemplate() {
    auto todos = carregarTemplatesDoArquivo();
    for (auto& t : todos) {
        mapaDeTemplates.emplace(t->getId(), std::move(t));
    }
}

bool GerenciadorDeTemplate::adicionarTemplate(std::unique_ptr<Template> novoTemplate) {
    if (!novoTemplate) return false; 
    int id = novoTemplate->getId();
    auto res = mapaDeTemplates.emplace(id, std::move(novoTemplate));
    if (res.second) {
        salvarTemplatesEmArquivo(listarTodos());
    }
    return res.second;
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    bool removed = mapaDeTemplates.erase(id) > 0;
    if (removed) {
        salvarTemplatesEmArquivo(listarTodos());
    }
    return removed;
}

Template* GerenciadorDeTemplate::buscarTemplatePorId(int id) {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return nullptr;
    return it->second.get();
}

std::optional<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::buscarTemplatePorIdRef(int id) const {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return std::nullopt;
    return std::cref(*it->second);
}

std::vector<Template*> GerenciadorDeTemplate::listarTodos() const {
    std::vector<Template*> lista;
    lista.reserve(mapaDeTemplates.size());
    for (const auto& par : mapaDeTemplates) {
        lista.push_back(par.second.get());
    }
    return lista;
}

std::vector<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::listarTodosRefs() const {
    std::vector<TemplateConstRef> lista;
    lista.reserve(mapaDeTemplates.size());
    for (const auto& par : mapaDeTemplates) {
        lista.push_back(std::cref(*par.second));
    }
    return lista;
}

std::vector<Template*> GerenciadorDeTemplate::filtrarPorCategoria(const FiltroDeCategoria& filtro) const {
    std::vector<Template*> filtrados;
    for (const auto& par : mapaDeTemplates) {
        Template* tmpl = par.second.get();
        if (filtro.satisfazFiltro(*tmpl)) {
            filtrados.push_back(tmpl);
        }
    }
    return filtrados;
}

std::vector<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::filtrarPorCategoriaRefs(const FiltroDeCategoria& filtro) const {
    std::vector<TemplateConstRef> filtrados;
    for (const auto& par : mapaDeTemplates) {
        const Template& tmpl = *par.second;
        if (filtro.satisfazFiltro(tmpl)) {
            filtrados.push_back(std::cref(tmpl));
        }
    }
    return filtrados;
}

bool GerenciadorDeTemplate::validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const {
    auto it = mapaDeTemplates.find(idTemplate);
    if (it == mapaDeTemplates.end()) return false;
    return it->second->aceitaTipoIngrediente(tipoIngrediente);
}
