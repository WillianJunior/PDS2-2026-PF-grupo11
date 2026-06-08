#include "BuscadorDeReceita.hpp"
#include <algorithm>
#include <cctype>

// Converte o termo de busca para minúsculo
std::string BuscadorDeReceitas::normalizarTermo(const std::string& termo) const {
    std::string termoNormalizado = termo;
    std::transform(termoNormalizado.begin(), termoNormalizado.end(), termoNormalizado.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return termoNormalizado;
}
//**************************************** */

BuscadorDeReceitas::BuscadorDeReceitas(const std::vector<Receita>& repositorio) : repositorio_(repositorio) {
}

// Busca receitas pelo nome
std::vector<Receita> BuscadorDeReceitas::buscarPorNome(const std::string& nome) const {
    std::vector<Receita> resultados;
    std::string termoNormalizado = normalizarTermo(nome);

    for(const auto& receita : repositorio_){

        std::string nomeReceitaNormalizado = normalizarTermo(receita.getNome());
    
        // Verifica se o termo digitado é uma sub-string do nome da receita
        // Ex: "carb" é substring de "spaghetti alla carbonara"
        if (nomeReceitaNormalizado.find(termoNormalizado) != std::string::npos) { 
            resultados.push_back(receita);
        }
    }
    return resultados;
}


std::vector<Receita> BuscadorDeReceitas::buscarPorIngredientes(const std::vector<std::string>& ingredientes) const {
                std::vector<Receita> resultados;

                for(const auto& receita : repositorio_){
                    bool possuiTodosIngredientes = true;
                
                // 1. Loop nos termos que o usuário digitou para buscar
                for(const auto& termoBuscar : ingredientes){
                    std::string termoNormalizado = normalizarTermo(termoBuscar);
                    bool encontrouEsteTermo = false;

                     // 2. Loop nos ingredientes reais da receita
                    for(const auto& ingReceita : receita.getIngredientes()){
                        // Puxa o nome do ingrediente base e normaliza
                        std::string nomeIngrediente = normalizarTermo(ingReceita.getIngrediente().getNome());
 
                        // Verifica se o termo está contido no nome do ingrediente
                        if (nomeIngrediente.find(termoNormalizado) != std::string::npos) {

                            encontrouEsteTermo = true;
                            break; // Achou este termo, passa para o próximo ingrediente da 
                        }
                    }
                    // Se o usuário buscou por um ingrediente que NÃO existe nessa receita
                    if (!encontrouEsteTermo) {
                      possuiTodosIngredientes = false;
                      break; // Descarta esta receita e vai para a próxima do repositório
                }
            }
            if (possuiTodosIngredientes) {
                resultados.push_back(receita);
            }
        }
        return resultados;
    }

std::vector<Receita> BuscadorDeReceitas::buscarPorNomeIngredientes(const std::string& nome, const std::vector<std::string>& ingredientes) const {
                return {};
            }

bool BuscadorDeReceitas::nenhumaReceitaEncontrada(const std::vector<Receita>& resultados) const {
    return false;
}

std::vector<Receita> BuscadorDeReceitas::ordenarPorRelevancia(
    const std::vector<Receita>& resultados, const std::string& termo) const {
        return {};
}

