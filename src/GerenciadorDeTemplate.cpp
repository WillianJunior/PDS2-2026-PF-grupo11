#include "GerenciadorDeTemplate.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace {
    const std::string ARQUIVO_TEMPLATES = "templates.txt";

    std::string removerEspacosExternos(const std::string& texto) {
        auto inicio = std::find_if_not(texto.begin(), texto.end(), [](unsigned char c) {
            return std::isspace(c);
        });

        auto fim = std::find_if_not(texto.rbegin(), texto.rend(), [](unsigned char c) {
            return std::isspace(c);
        }).base();

        if (inicio >= fim) {
            return "";
        }

        return std::string(inicio, fim);
    }

    bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream f(nomeArquivo);
        return f.good();
    }

    bool inteiroValido(const std::string& texto, int& valor) {
        const std::string normalizado = removerEspacosExternos(texto);
        if (normalizado.empty()) {
            return false;
        }

        std::size_t posicaoFinal = 0;
        try {
            long convertido = std::stol(normalizado, &posicaoFinal);
            if (posicaoFinal != normalizado.size()) {
                return false;
            }
            if (convertido < std::numeric_limits<int>::min() ||
                convertido > std::numeric_limits<int>::max()) {
                return false;
            }
            valor = static_cast<int>(convertido);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    // Formato por linha: ID|Nome|Conteudo|Categoria|Tipo1,Tipo2,...
    void salvarTemplatesEmArquivo(const std::vector<Template>& templates) {
        std::ofstream arquivo(ARQUIVO_TEMPLATES);
        if (!arquivo.is_open()) {
            throw std::runtime_error("Nao foi possivel abrir o arquivo de templates para escrita");
        }

        for (const auto& tmpl : templates) {
            arquivo << tmpl.getId() << "|"
                    << tmpl.getNome() << "|"
                    << "" << "|"
                    << tmpl.getCategoria() << "|";

            auto tipos = tmpl.getTiposPermitidos();
            for (size_t i = 0; i < tipos.size(); ++i) {
                arquivo << tipos[i];
                if (i + 1 < tipos.size()) {
                    arquivo << ",";
                }
            }
            arquivo << '\n';
        }

        if (!arquivo.good()) {
            throw std::runtime_error("Falha ao gravar templates no arquivo");
        }
    }

    std::vector<Template> carregarTemplatesDoArquivo() {
        std::vector<Template> templates;
        if (!arquivoExiste(ARQUIVO_TEMPLATES)) {
            return templates;
        }

        std::ifstream arquivo(ARQUIVO_TEMPLATES);
        if (!arquivo.is_open()) {
            throw std::runtime_error("Nao foi possivel abrir o arquivo de templates para leitura");
        }

        std::string linha;
        while (std::getline(arquivo, linha)) {
            if (removerEspacosExternos(linha).empty()) {
                continue;
            }

            std::istringstream iss(linha);
            std::string idStr, nome, conteudo, categoria, tiposStr;

            if (!std::getline(iss, idStr, '|')) continue;
            if (!std::getline(iss, nome, '|')) continue;
            if (!std::getline(iss, conteudo, '|')) continue;
            if (!std::getline(iss, categoria, '|')) continue;
            if (!std::getline(iss, tiposStr)) tiposStr = "";

            int id = 0;
            if (!inteiroValido(idStr, id)) {
                continue;
            }

            try {
                Template tmpl(id, nome, conteudo, categoria);

                if (!tiposStr.empty()) {
                    std::istringstream ts(tiposStr);
                    std::string tipo;
                    while (std::getline(ts, tipo, ',')) {
                        if (!removerEspacosExternos(tipo).empty()) {
                            tmpl.adicionarTipoPermitido(tipo);
                        }
                    }
                }
                templates.push_back(tmpl);
            } catch (const std::invalid_argument&) {
                continue;
            }
        }

        if (arquivo.bad()) {
            throw std::runtime_error("Falha ao ler o arquivo de templates");
        }

        return templates;
    }
}

GerenciadorDeTemplate::GerenciadorDeTemplate() {
    auto todos = carregarTemplatesDoArquivo();
    for (auto& t : todos) {
        mapaDeTemplates.emplace(t.getId(), std::move(t));
    }
}

bool GerenciadorDeTemplate::adicionarTemplate(const Template& novoTemplate) {
    const int id = novoTemplate.getId();
    if (id <= 0) {
        throw std::invalid_argument("GerenciadorDeTemplate: id do template deve ser positivo");
    }

    auto res = mapaDeTemplates.emplace(id, novoTemplate);
    if (res.second) {
        try {
            std::vector<Template> todos = listarTodos();
            salvarTemplatesEmArquivo(todos);
        } catch (...) {
            mapaDeTemplates.erase(id);
            throw;
        }
    }
    return res.second;
}

bool GerenciadorDeTemplate::removerTemplate(int id) {
    if (id <= 0) {
        return false;
    }

    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) {
        return false;
    }

    Template removido = it->second;
    mapaDeTemplates.erase(it);
    try {
        std::vector<Template> todos = listarTodos();
        salvarTemplatesEmArquivo(todos);
    } catch (...) {
        mapaDeTemplates.emplace(id, std::move(removido));
        throw;
    }

    return true;
}

Template* GerenciadorDeTemplate::buscarTemplatePorId(int id) {
    if (id <= 0) {
        return nullptr;
    }

    auto it = mapaDeTemplates.find(id);
    if (it == mapaDeTemplates.end()) {
        return nullptr;
    }
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
    if (idTemplate <= 0 || removerEspacosExternos(tipoIngrediente).empty()) {
        return false;
    }

    auto it = mapaDeTemplates.find(idTemplate);
    if (it == mapaDeTemplates.end()) {
        return false;
    }
    return it->second.aceitaTipoIngrediente(tipoIngrediente);
}
