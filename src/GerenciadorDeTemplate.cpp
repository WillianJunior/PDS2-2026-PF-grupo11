#include "GerenciadorDeTemplate.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>


namespace {
    const std::string ARQUIVO_TEMPLATES = "templates.txt";

    bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream f(nomeArquivo);
        return f.good();
    }

    // Formato por linha: ID|Nome|Conteudo|Categoria|Tipo1,Tipo2,...
    void salvarTemplatesEmArquivo(const std::vector<Template>& templates) {
        std::ofstream arquivo(ARQUIVO_TEMPLATES);
        if (!arquivo.is_open()) return; // falha silenciosa

        for (const auto& tmpl : templates) {
            arquivo << tmpl.getId() << "|"
                    << tmpl.getNome() << "|"
                    << /* conteudo */ "" << "|"
                    << tmpl.getCategoria() << "|";

            auto tipos = tmpl.getTiposPermitidos();
            for (size_t i = 0; i < tipos.size(); ++i) {
                arquivo << tipos[i];
                if (i + 1 < tipos.size()) arquivo << ",";
            }
            arquivo << '\n';
        }
    }

    std::vector<Template> carregarTemplatesDoArquivo() {
        std::vector<Template> templates;
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
                Template tmpl(id, nome, conteudo, categoria);

                if (!tiposStr.empty()) {
                    std::istringstream ts(tiposStr);
                    std::string tipo;
                    while (std::getline(ts, tipo, ',')) {
                        if (!tipo.empty()) tmpl.adicionarTipoPermitido(tipo);
                    }
                }
                templates.push_back(tmpl);
            } catch (...) {
                continue; 
            }
        }

        return templates;
    }
} 


GerenciadorDeTemplate::GerenciadorDeTemplate() {
    // Ao construir, carregar do arquivo
    auto todos = carregarTemplatesDoArquivo();
    for (auto& t : todos) {
        mapaDeTemplates.emplace(t.getId(), std::move(t));
    }
}

bool GerenciadorDeTemplate::adicionarTemplate(const Template& novoTemplate) {
    int id = novoTemplate.getId();
    auto res = mapaDeTemplates.emplace(id, novoTemplate);
    if (res.second) {
        // salvar
        std::vector<Template> todos = listarTodos();
        salvarTemplatesEmArquivo(todos);
    }
    return res.second; // true se inserido, false se já existia o id
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    bool removed = mapaDeTemplates.erase(id) > 0;
    if (removed) {
        std::vector<Template> todos = listarTodos();
        salvarTemplatesEmArquivo(todos);
    }
    return removed;
}

Template* GerenciadorDeTemplate::buscarTemplatePorId(int id) {
    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) return nullptr;
    return &it->second;
}

std::vector<Template> GerenciadorDeTemplate::listarTodos() const {
    std::vector<Template> lista;
    lista.reserve(mapaDeTemplates.size());
    for (const auto& par : mapaDeTemplates) {
        lista.push_back(par.second);
    }
    return lista;
}

std::vector<Template> GerenciadorDeTemplate::filtrarPorCategoria(const FiltroDeCategoria& filtro) const {
    std::vector<Template> todos = listarTodos();
    return filtro.aplicarFiltro(todos);
}

bool GerenciadorDeTemplate::validarIngredienteNoTemplate(int idTemplate, const std::string& tipoIngrediente) const {
    auto it = mapaDeTemplates.find(idTemplate);
    if (it == mapaDeTemplates.end()) return false;
    return it->second.aceitaTipoIngrediente(tipoIngrediente);
}