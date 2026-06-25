#include "../include/GerenciadorDeTemplate.hpp"
#include "../include/PizzaTemplate.hpp"
#include "../include/PastaTemplate.hpp"    
#include "../include/RisottoTemplate.hpp"
#include "../include/FiltroDeCategoria.hpp" 
#include <algorithm>
#include <fstream>
#include <sstream>

namespace {
    const std::string ARQUIVO_TEMPLATES = "templates.txt";

    bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream f(nomeArquivo);
        return f.good();
    }

    std::string escaparCampo(const std::string& valor) {
        std::string resultado;
        resultado.reserve(valor.size());
        for (char ch : valor) {
            if (ch == '\\' || ch == '|' || ch == ',' || ch == '\n') {
                resultado += '\\';
            }
            if (ch == '\n') {
                resultado += 'n';
            } else {
                resultado += ch;
            }
        }
        return resultado;
    }

    std::string desescaparCampo(const std::string& valor) {
        std::string resultado;
        resultado.reserve(valor.size());
        bool escapado = false;
        for (char ch : valor) {
            if (escapado) {
                resultado += (ch == 'n') ? '\n' : ch;
                escapado = false;
            } else if (ch == '\\') {
                escapado = true;
            } else {
                resultado += ch;
            }
        }
        if (escapado) {
            resultado += '\\';
        }
        return resultado;
    }

    std::vector<std::string> dividirCamposEscapados(const std::string& linha, char delimitador) {
        std::vector<std::string> campos;
        std::string atual;
        bool escapado = false;

        for (char ch : linha) {
            if (escapado) {
                atual += '\\';
                atual += ch;
                escapado = false;
            } else if (ch == '\\') {
                escapado = true;
            } else if (ch == delimitador) {
                campos.push_back(desescaparCampo(atual));
                atual.clear();
            } else {
                atual += ch;
            }
        }

        if (escapado) {
            atual += '\\';
        }
        campos.push_back(desescaparCampo(atual));
        return campos;
    }

    std::vector<std::unique_ptr<Template>> carregarTemplatesDoArquivo(const std::string& caminhoArquivo) {
        std::vector<std::unique_ptr<Template>> templates;
        if (!arquivoExiste(caminhoArquivo)) return templates;

        std::ifstream arquivo(caminhoArquivo);
        if (!arquivo.is_open()) return templates;

        std::string linha;
        while (std::getline(arquivo, linha)) {
            if (linha.empty()) continue;
            auto campos = dividirCamposEscapados(linha, '|');
            if (campos.size() < 4) continue;

            const std::string& idStr = campos[0];
            const std::string& nome = campos[1];
            const std::string& conteudo = campos[2];
            const std::string& categoria = campos[3];
            const std::string tiposStr = campos.size() > 4 ? campos[4] : "";

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
                    std::vector<std::string> tipos = tiposStr.empty() ? std::vector<std::string>{} : dividirCamposEscapados(tiposStr, ',');
                    tmpl = std::make_unique<Template>(id, nome, conteudo, categoria, tipos);
                }
                tmpl->setConteudo(conteudo);
                templates.push_back(std::move(tmpl));   
            } catch (...) {
                continue; 
            }
        }

        return templates;
    }
} 

GerenciadorDeTemplate::GerenciadorDeTemplate() : caminhoArquivo_("templates.txt") {
    auto todos = carregarTemplatesDoArquivo(caminhoArquivo_);
    for (auto& t : todos) {
        mapaDeTemplates.emplace(t->getId(), std::move(t));
    }
}

GerenciadorDeTemplate::GerenciadorDeTemplate(const std::string& caminhoArquivo) : caminhoArquivo_(caminhoArquivo) {
    auto todos = carregarTemplatesDoArquivo(caminhoArquivo_);
    for (auto& t : todos) {
        mapaDeTemplates.emplace(t->getId(), std::move(t));
    }
}

bool GerenciadorDeTemplate::adicionarTemplate(std::unique_ptr<Template> novoTemplate) {
    if (!novoTemplate) return false; 
    int id = novoTemplate->getId();
    auto res = mapaDeTemplates.emplace(id, std::move(novoTemplate));
    if (res.second) {
        salvarTemplatesEmArquivo();
    }
    return res.second;
}

bool GerenciadorDeTemplate::salvarTemplatesEmArquivo() const {
    return salvarTemplatesEmArquivo(caminhoArquivo_);
}

bool GerenciadorDeTemplate::salvarTemplatesEmArquivo(const std::string& caminhoArquivo) const {
    std::ofstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) return false;

    for (const auto& par : mapaDeTemplates) {
        const Template& tmpl = *par.second;
        arquivo << tmpl.getId() << "|"
                << escaparCampo(tmpl.getNome()) << "|"
                << escaparCampo(tmpl.getConteudo()) << "|"
                << escaparCampo(tmpl.getCategoria()) << "|";

        auto tipos = tmpl.getTiposPermitidos();
        for (size_t i = 0; i < tipos.size(); ++i) {
            arquivo << escaparCampo(tipos[i]);
            if (i + 1 < tipos.size()) arquivo << ",";
        }
        arquivo << '\n';
    }

    return arquivo.good();
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    bool removed = mapaDeTemplates.erase(id) > 0;
    if (removed) {
        salvarTemplatesEmArquivo();
    }
    return removed;
}

std::optional<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::buscarTemplatePorId(int id) const {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return std::nullopt;
    return std::cref(*it->second);
}

std::optional<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::buscarTemplatePorIdRef(int id) const {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return std::nullopt;
    return std::cref(*it->second);
}

std::vector<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::listarTodos() const {
    std::vector<TemplateConstRef> lista;
    lista.reserve(mapaDeTemplates.size());
    for (const auto& par : mapaDeTemplates) {
        lista.push_back(std::cref(*par.second));
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

std::vector<GerenciadorDeTemplate::TemplateConstRef> GerenciadorDeTemplate::filtrarPorCategoria(const FiltroDeCategoria& filtro) const {
    std::vector<TemplateConstRef> filtrados;
    for (const auto& par : mapaDeTemplates) {
        const Template& tmpl = *par.second;
        if (filtro.satisfazFiltro(tmpl)) {
            filtrados.push_back(std::cref(tmpl));
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
