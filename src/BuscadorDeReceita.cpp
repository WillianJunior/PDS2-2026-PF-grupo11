#include "BuscadorDeReceita.hpp"

BuscadorDeReceitas::BuscadorDeReceitas(const std::vector<Receita>& repositorio) {

}

std::vector<Receita> BuscadorDeReceitas::buscarPorNome(const std::string& nome) const {
    return {};
}

std::vector<Receita> BuscadorDeReceitas::buscarPorIngredientes(
            const std::vector<std::string>& ingredientes) const {
                return {};
            }

std::vector<Receita> BuscadorDeReceitas::buscarPorNomeEIngredientes(
            const std::string& nome,
            const std::vector<std::string>& ingredientes) const {
                return {};
            }

bool BuscadorDeReceitas::nenhumaReceitaEncontrada(const std::vector<Receita>& resultados) const {
    return false;
}

std::vector<Receita> BuscadorDeReceitas::ordenarPorRelevancia(
    const std::vector<Receita>& resultados,const std::string& termo) const {
        return {};
}

std::string BuscadorDeReceitas::normalizarTermo(const std::string& termo) const {
    return "";
}