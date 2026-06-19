#include "BuscadorDeReceita.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace {
    std::string trim(const std::string& str) {
        auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) {
            return std::isspace(ch);
        });
        auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) {
            return std::isspace(ch);
        }).base();
        return (start < end ? std::string(start, end) : "");
    }
}

std::string BuscadorDeReceitas::normalizarTermo(const std::string& termo) const {
    std::string termoNormalizado = trim(termo);
    std::transform(termoNormalizado.begin(), termoNormalizado.end(), termoNormalizado.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return termoNormalizado;
}

BuscadorDeReceitas::BuscadorDeReceitas(const std::vector<Receita>& repositorio) : repositorio_(repositorio) {
}

std::vector<Receita> BuscadorDeReceitas::buscarPorNome(const std::string& nome) const {
    std::string termoTrimmed = trim(nome);
    if (termoTrimmed.empty()) {
        throw std::invalid_argument("Erro: O nome para busca nao pode estar vazio ou conter apenas espacos.");
    }

    std::vector<Receita> resultados;
    std::string termoNormalizado = normalizarTermo(termoTrimmed);

    for (const auto& receita : repositorio_) {
        std::string nomeReceitaNormalizado = normalizarTermo(receita.getNome());
        if (nomeReceitaNormalizado.find(termoNormalizado) != std::string::npos) {
            resultados.push_back(receita);
        }
    }

    return ordenarPorRelevancia(resultados, termoTrimmed);
}

// Busca receitas que contenham TODOS os ingredientes informados
std::vector<Receita> BuscadorDeReceitas::buscarPorIngredientes(const std::vector<std::string>& ingredientes) const {
    if (ingredientes.empty()) {
        throw std::invalid_argument("Erro: A lista de ingredientes para busca nao pode estar vazia.");
    }

    std::vector<Receita> resultados;

    // Valida e trimma todos os ingredientes de busca
    std::vector<std::string> ingredientesNormalizados;
    ingredientesNormalizados.reserve(ingredientes.size());
    for (const auto& ing : ingredientes) {
        std::string ingTrimmed = trim(ing);
        if (ingTrimmed.empty()) {
            throw std::invalid_argument("Erro: Um ingrediente de busca nao pode estar vazio ou conter apenas espacos.");
        }
        ingredientesNormalizados.push_back(normalizarTermo(ingTrimmed));
    }

    for (const auto& receita : repositorio_) {
        bool possuiTodosIngredientes = true;

        for (const auto& termoNormalizado : ingredientesNormalizados) {
            bool encontrouEsteTermo = false;

            for (const auto& ingReceita : receita.getIngredientes()) {
                std::string nomeIngrediente = normalizarTermo(ingReceita.getIngrediente().getNome());
                if (nomeIngrediente.find(termoNormalizado) != std::string::npos) {
                    encontrouEsteTermo = true;
                    break;
                }
            }

            if (!encontrouEsteTermo) {
                possuiTodosIngredientes = false;
                break;
            }
        }

        if (possuiTodosIngredientes) {
            resultados.push_back(receita);
        }
    }

    return resultados;
}

// Delega para buscarPorNome e filtra pelo resultado usando buscarPorIngredientes
std::vector<Receita> BuscadorDeReceitas::buscarPorNomeIngredientes(const std::string& nome, const std::vector<std::string>& ingredientes) const {
    std::string nomeTrimmed = trim(nome);
    if (nomeTrimmed.empty()) {
        throw std::invalid_argument("Erro: O nome para busca combinada nao pode estar vazio.");
    }
    if (ingredientes.empty()) {
        throw std::invalid_argument("Erro: A lista de ingredientes para busca combinada nao pode estar vazia.");
    }

    std::vector<Receita> porNome = buscarPorNome(nomeTrimmed);
    BuscadorDeReceitas buscadorParcial(porNome);
    return buscadorParcial.buscarPorIngredientes(ingredientes);
}

bool BuscadorDeReceitas::nenhumaReceitaEncontrada(const std::vector<Receita>& resultados) const {
    return resultados.empty();
}

std::vector<Receita> BuscadorDeReceitas::ordenarPorRelevancia(
    const std::vector<Receita>& resultados, const std::string& termo) const {

    std::vector<Receita> ordenados = resultados;
    std::string termoNormalizado = normalizarTermo(termo);

    std::sort(ordenados.begin(), ordenados.end(),
        [&](const Receita& a, const Receita& b) {
            std::string nomeA = normalizarTermo(a.getNome());
            std::string nomeB = normalizarTermo(b.getNome());
            size_t posA = nomeA.find(termoNormalizado);
            size_t posB = nomeB.find(termoNormalizado);
            return posA < posB;
        }
    );

    return ordenados;
}

void BuscadorDeReceitas::adicionarReceita(const Receita& receita) {
    repositorio_.push_back(receita);
}
