#include "BuscadorDeReceita.hpp"
#include <algorithm>
#include <cctype>

std::string BuscadorDeReceitas::normalizarTermo(const std::string& termo) const {
    std::string termoNormalizado = termo;
    std::transform(termoNormalizado.begin(), termoNormalizado.end(), termoNormalizado.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return termoNormalizado;
}

BuscadorDeReceitas::BuscadorDeReceitas(const std::vector<Receita>& repositorio) : repositorio_(repositorio) {
}

std::vector<Receita> BuscadorDeReceitas::buscarPorNome(const std::string& nome) const {
    std::vector<Receita> resultados;
    std::string termoNormalizado = normalizarTermo(nome);

    for (const auto& receita : repositorio_) {
        std::string nomeReceitaNormalizado = normalizarTermo(receita.getNome());
        if (nomeReceitaNormalizado.find(termoNormalizado) != std::string::npos) {
            resultados.push_back(receita);
        }
    }

    return ordenarPorRelevancia(resultados, nome);
}

std::vector<Receita> BuscadorDeReceitas::buscarPorIngredientes(const std::vector<std::string>& ingredientes) const {
    std::vector<Receita> resultados;

    for (const auto& receita : repositorio_) {
        bool possuiTodosIngredientes = true;

        for (const auto& termoBuscar : ingredientes) {
            std::string termoNormalizado = normalizarTermo(termoBuscar);
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
    std::vector<Receita> porNome = buscarPorNome(nome);
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