#include "../include/InterfaceTerminal.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cctype>
#include <fstream>

struct IngredienteCatalogo {
    std::string nome;
    std::string tipo;
};

// Catálogo pré-definido de ingredientes sugeridos para facilitar a escolha do usuário
const std::vector<IngredienteCatalogo> CATALOGO_INGREDIENTES = {
    {"Sal", "Tempero"},
    {"Manteiga", "Tempero"},
    {"Azeite de Oliva", "Tempero"},
    {"Oregano", "Tempero"},

    {"Molho de Tomate", "Molho"},

    {"Queijo Mozzarella", "Queijo"},
    {"Queijo Parmesao", "Queijo"},

    {"Pepperoni", "Proteina"},
    {"Pancetta", "Proteina"},
    {"Presunto", "Proteina"},
    {"Frango Desfiado", "Proteina"},
    {"Bacon", "Proteina"},
    {"Carne de Sol","Proteina"},

    {"Manjericao", "Vegetal"},
    {"Cogumelos", "Vegetal"},
    {"Cebola", "Vegetal"},
    {"Alho", "Vegetal"},
    {"Tomate Seco", "Vegetal"},

    {"Caldo de Legumes", "Caldo"},

    {"Camarões", "Fruto do Mar"},
    {"Vongole", "Fruto do Mar"},
    {"Polvo", "Fruto do Mar"},
	{"Lula", "Fruto do Mar"}
};

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

InterfaceTerminal::InterfaceTerminal(BuscadorDeReceitas& buscador,
                                     GerenciadorDeTemplate& gerenciador,
                                     GeradorDeReceita& gerador)
    : buscador_{buscador}
    , gerenciador_{gerenciador}
    , gerador_{gerador}
{
}

void InterfaceTerminal::iniciar() {
    limparTela();
    std::cout << "=========================================================\n";
    std::cout << "              R I C E T T A R I O\n";
    std::cout << "    Sistema de Receitas Italianas Personalizadas\n";
    std::cout << "=========================================================\n";
    
    bool continuar = true;
    while (continuar) {
        int opcao = exibirMenuPrincipal();
        continuar = processarOpcao(opcao);
    }

    std::cout << "\nGrazie! Arrivederci!\n\n";
}

int InterfaceTerminal::exibirMenuPrincipal() const {
    exibirSeparador();
    std::cout << "MENU PRINCIPAL:\n";
    std::cout << "  1. Criar Nova Receita Personalizada\n";
    std::cout << "  2. Buscar Receitas no Acervo\n";
    std::cout << "  3. Navegar Templates por Categoria\n";
    std::cout << "  4. Listar Todos os Templates Disponiveis\n";
    std::cout << "  5. Criar Novo Template\n";
    std::cout << "  6. Sair\n";
    return lerInteiro("Escolha uma opcao: ");
}

bool InterfaceTerminal::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            fluxoCriarReceita();
            break;
        case 2:
            fluxoBuscarReceita();
            break;
        case 3:
            fluxoNavegaPorCategoria();
            break;
        case 4:
            exibirListaTemplates(gerenciador_.listarTodosRefs());
            break;
        case 5:
            fluxoCriarTemplate();
			break;
        case 6:
            return false;
        default:
            std::cout << "\nOpcao invalida. Tente novamente.\n";
            break;
    }
    return true;
}

void InterfaceTerminal::fluxoBuscarReceita() {
    bool emSubmenu = true;
    while (emSubmenu) {
        int opcao = exibirSubMenuBusca();
        switch (opcao) {
            case 1:
                buscarPorNome();
                break;
            case 2:
                buscarPorIngredientes();
                break;
            case 3:
                buscarPorNomeEIngredientes();
                break;
            case 4: {
                exibirSeparador();
                auto resultados = buscador_.obterTodasAsReceitas();
                if (resultados.empty()) {
                    std::cout << "Nenhuma receita encontrada no acervo.\n";
                    aguardarEnter();
                } else {
                    exibirListaReceitas(resultados);
                }
                break;
            }
            case 5:
                emSubmenu = false;
                break;
            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }
    }
}

int InterfaceTerminal::exibirSubMenuBusca() const {
    exibirSeparador();
    std::cout << "MENU DE BUSCA:\n";
    std::cout << "  1. Buscar por Nome do Prato\n";
    std::cout << "  2. Buscar por Ingredientes\n";
    std::cout << "  3. Buscar por Nome e Ingredientes\n";
    std::cout << "  4. Listar todas as receitas cadastradas\n";
    std::cout << "  5. Voltar ao Menu Principal\n";
    return lerInteiro("Escolha uma opcao: ");
}

void InterfaceTerminal::buscarPorNome() {
    exibirSeparador();
    std::string nome = lerString("Digite o nome ou parte dele para busca: ");
    try {
        auto resultados = buscador_.buscarPorNome(nome);
        exibirListaReceitas(resultados);
    } catch (const std::exception& e) {
        std::cout << "\nErro na busca: " << e.what() << "\n";
        aguardarEnter();
    }
}

void InterfaceTerminal::buscarPorIngredientes() {
    exibirSeparador();
    auto ingredientes = lerListaCSV("Digite os ingredientes separados por virgula (ex: Sal, Queijo): ");
    try {
        auto resultados = buscador_.buscarPorIngredientes(ingredientes);
        exibirListaReceitas(resultados);
    } catch (const std::exception& e) {
        std::cout << "\nErro na busca: " << e.what() << "\n";
        aguardarEnter();
    }
}

void InterfaceTerminal::buscarPorNomeEIngredientes() {
    exibirSeparador();
    std::string nome = lerString("Digite o nome do prato: ");
    auto ingredientes = lerListaCSV("Digite os ingredientes separados por virgula: ");
    try {
        auto resultados = buscador_.buscarPorNomeIngredientes(nome, ingredientes);
        exibirListaReceitas(resultados);
    } catch (const std::exception& e) {
        std::cout << "\nErro na busca: " << e.what() << "\n";
        aguardarEnter();
    }
}

void InterfaceTerminal::fluxoNavegaPorCategoria() {
    exibirSeparador();
    auto todos = gerenciador_.listarTodosRefs();
    if (todos.empty()) {
        std::cout << "Nenhum template cadastrado no sistema.\n";
        aguardarEnter();
        return;
    }

    // Coleta categorias únicas
    std::vector<std::string> categorias;
    for (const auto& tRef : todos) {
        const Template& t = tRef.get();
        if (std::find(categorias.begin(), categorias.end(), t.getCategoria()) == categorias.end()) {
            categorias.push_back(t.getCategoria());
        }
    }

    std::cout << "CATEGORIAS DISPONIVEIS:\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << categorias[i] << "\n";
    }

    int opcao = lerInteiro("Escolha uma categoria: ");
    if (opcao > 0 && opcao <= static_cast<int>(categorias.size())) {
        FiltroDeCategoria filtro(categorias[opcao - 1]);
        auto templatesFiltrados = gerenciador_.filtrarPorCategoriaRefs(filtro);
        exibirListaTemplates(templatesFiltrados);
    } else {
        std::cout << "\nOpcao invalida.\n";
        aguardarEnter();
    }
}

void InterfaceTerminal::fluxoCriarReceita() {
    exibirSeparador();
    std::cout << "CRIACAO DE RECEITA PERSONALIZADA\n\n";
    auto todosTemplates = gerenciador_.listarTodosRefs();
    if (todosTemplates.empty()) {
        std::cout << "Erro: Nao ha templates cadastrados no sistema. Nao e possivel criar receitas.\n";
        aguardarEnter();
        return;
    }

    std::cout << "Escolha um template base:\n";
    for (const auto& tRef : todosTemplates) {
        const Template& t = tRef.get();
        std::cout << "  ID: " << t.getId() << " - " << t.getNome() << " (" << t.getCategoria() << ")\n";
    }

    int idTmpl = lerInteiro("Digite o ID do template escolhido (ou 0 para voltar): ");
    if (idTmpl == 0) {
        return;
    }

    auto tmplEncontrado = gerenciador_.buscarTemplatePorIdRef(idTmpl);
    if (!tmplEncontrado) {
        std::cout << "\nErro: Template com ID " << idTmpl << " nao encontrado.\n";
        aguardarEnter();
        return;
    }
    const Template& tmpl = tmplEncontrado.value().get();

    exibirTemplate(tmpl);
    
    // Inicia a seleção interativa de ingredientes
    auto seletorOpcional = selecionarIngredientes(tmpl);
    if (!seletorOpcional) {
        return;
    }
    SeletorDeIngredientes seletor = seletorOpcional.value();
    auto selecionados = seletor.getIngredientesSelecionados();

    std::string nomeReceita = lerString("Digite o nome da sua receita (ou 0 para voltar): ");
    if (nomeReceita == "0") {
        return;
    }

    std::string categoriaReceita = lerString("Digite a categoria da receita (ex: Massas, Sobremesas) [Enter para usar a do template, 0 para voltar]: ");
    if (categoriaReceita == "0") {
        return;
    }
    if (trim(categoriaReceita).empty()) {
        categoriaReceita = tmpl.getCategoria();
    }

    // Solicita as quantidades e unidades de medida para os ingredientes selecionados
    std::vector<IngredienteDaReceita> ingredientesDaReceita;
    std::cout << "\n=== Informar Quantidades dos Ingredientes ===\n";
    for (const auto& ing : selecionados) {
        std::cout << "\nIngrediente: " << ing.getNome() << " (" << ing.getTipo() << ")\n";
        double qtd = 0;
        while (true) {
            std::cout << "  Digite a quantidade (maior que 0, ou 0 para voltar): ";
            std::string entrada = lerString("");
            if (entrada == "0") {
                return;
            }
            try {
                size_t idx;
                qtd = std::stod(entrada, &idx);
                if (qtd > 0 && idx == entrada.size()) {
                    break;
                }
            } catch (...) {}
            std::cout << "  Quantidade invalida. Deve ser um numero positivo.\n";
        }
        std::string unidade = "";
        while (true) {
            unidade = lerString("  Digite a unidade de medida (ex: g, ml, colheres, unidades, ou 0 para voltar): ");
            if (unidade == "0") {
                return;
            }
            if (!unidade.empty()) {
                break;
            }
            std::cout << "  A unidade de medida nao pode ser vazia.\n";
        }

        ingredientesDaReceita.push_back(IngredienteDaReceita(ing, qtd, unidade));
    }

    // Cria a receita base para enviar ao Gerador
    Receita receitaBase(nomeReceita, tmpl.getNome(), categoriaReceita, ingredientesDaReceita, {}, 0);

    std::cout << "\nGerando receita culinaria final...\n";
    Receita receitaFinal = gerador_.gerar(receitaBase);

    if (receitaFinal.estaCompleta()) {
        std::cout << "\nReceita '" << receitaFinal.getNome() << "' criada com sucesso!\n";
        exibirReceita(receitaFinal);
        buscador_.adicionarReceita(receitaFinal);

        // Salva a receita no arquivo para persistência
        std::ofstream arquivo("data/receitas.txt", std::ios::app);
        if (arquivo.is_open()) {
            arquivo << receitaFinal.getNome() << "|" 
                    << receitaFinal.getTemplateOrigem() << "|" 
                    << receitaFinal.getCategoria() << "|";
            auto ings = receitaFinal.getIngredientes();
            for (size_t i = 0; i < ings.size(); ++i) {
                arquivo << ings[i].getIngrediente().getNome() << "," 
                        << ings[i].getIngrediente().getTipo() << "," 
                        << ings[i].getQuantidade() << "," 
                        << ings[i].getUnidadeDeMedida();
                if (i < ings.size() - 1) arquivo << "|";
            }
            arquivo << "\n";
        }
    } else {
        std::cout << "\nErro na geracao da receita. Verifique se o arquivo do template está disponivel.\n";
    }
    aguardarEnter();
}


void InterfaceTerminal::fluxoCriarTemplate() 
{
    exibirSeparador();
    std::cout << "CRIACAO DE NOVO TEMPLATE PERSONALIZADO\n\n";  

    std::cout << "Deseja utilizar um template existente como base para o novo template? (S/N)\n";
    std::string resposta = lerString("Digite S para sim ou N para nao: ");
    std::unique_ptr<Template> novoTemplate;
    int novoId = static_cast<int>(gerenciador_.listarTodosRefs().size()) + 1;
    while (gerenciador_.buscarTemplatePorId(novoId) != nullptr) {
        ++novoId;
    }

    if (resposta == "S" || resposta == "s") {
        std::cout << "  TODOS OS TEMPLATES JA EXISTENTES    \n\n";

        auto todosTemplates = gerenciador_.listarTodosRefs();
        if (todosTemplates.empty()) {
            std::cout << "Erro: Nao ha templates cadastrados no sistema para usar como base.\n";
            aguardarEnter();
            return;
        }
        for (const auto& tRef : todosTemplates) {
            const Template& t = tRef.get();
            std::cout << "  ID: " << t.getId() << " - " << t.getNome() << " (" << t.getCategoria() << ")\n";
        }

        int idTmpl = lerInteiro("Digite o ID do template escolhido (ou 0 para voltar): ");
        if (idTmpl == 0) {
            return;
        }

        auto tmplEncontrado = gerenciador_.buscarTemplatePorIdRef(idTmpl);
        if (!tmplEncontrado) {
            std::cout << "\nErro: Template com ID " << idTmpl << " nao encontrado.\n";
            aguardarEnter();
            return;
        }
        const Template& tmpl = tmplEncontrado.value().get();

        exibirTemplate(tmpl);

        std::cout << "Deseja prosseguir com este template ?";
        std::string resposta = lerString("Digite S para sim ou N para nao: ");
        if (resposta != "S" && resposta != "s") {
            return;
        }

        novoTemplate = std::make_unique<Template>(novoId, tmpl.getNome(), tmpl.getConteudo(), tmpl.getCategoria());
        novoTemplate->setTiposPermitidos(tmpl.getTiposPermitidos());
    } else if (resposta == "N" || resposta == "n") {
        std::string categoria = lerString("Digite a categoria do template: ");
        if (categoria.empty()) {
            std::cout << "\nErro: Categoria nao pode ser vazia.\n";
            aguardarEnter();
            return;
        }
        novoTemplate = std::make_unique<Template>(novoId, "", "", categoria);
    } else {
        std::cout << "\nOpcao invalida.\n";
        aguardarEnter();
        return;
    }

    std::string nome = lerString("Digite o nome do novo template: ");
    if (nome.empty()) {
        std::cout << "\nErro: Nome nao pode ser vazio.\n";
        aguardarEnter();
        return;
    }
    novoTemplate->setNome(nome);

    std::string conteudo = lerString("Digite o conteudo/descricao do template: ");
    novoTemplate->setConteudo(conteudo);

    novoTemplate->setTiposPermitidos(editarTiposPermitidos(novoTemplate->getTiposPermitidos()));

    if (gerenciador_.adicionarTemplate(std::move(novoTemplate))) {
        std::cout << "\nTemplate salvo com sucesso no arquivo templates.txt.\n";
    } else {
        std::cout << "\nErro: Nao foi possivel salvar o template.\n";
    }
    aguardarEnter();
}

std::vector<std::string> InterfaceTerminal::editarTiposPermitidos(std::vector<std::string> tipos) {
    while (true) {
        exibirSeparador();
        std::cout << "TIPOS PERMITIDOS DO TEMPLATE:\n";
        if (tipos.empty()) {
            std::cout << "  (Nenhum tipo cadastrado)\n";
        } else {
            for (size_t i = 0; i < tipos.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << tipos[i] << "\n";
            }
        }

        std::cout << "\nOpcoes:\n";
        std::cout << "  1. Adicionar tipo(s)\n";
        std::cout << "  2. Remover tipo\n";
        std::cout << "  3. Finalizar lista\n";

        int opcao = lerInteiro("Escolha uma opcao: ");
        if (opcao == 1) {
            auto novosTipos = lerListaCSV("Digite os tipos para adicionar separados por virgula: ");
            for (const auto& tipo : novosTipos) {
                if (std::find(tipos.begin(), tipos.end(), tipo) == tipos.end()) {
                    tipos.push_back(tipo);
                }
            }
        } else if (opcao == 2) {
            if (tipos.empty()) {
                std::cout << "\nNao ha tipos para remover.\n";
                aguardarEnter();
                continue;
            }

            int indice = lerInteiro("Digite o numero do tipo para remover (ou 0 para cancelar): ");
            if (indice > 0 && indice <= static_cast<int>(tipos.size())) {
                tipos.erase(tipos.begin() + indice - 1);
                std::cout << "\nTipo removido.\n";
            } else if (indice != 0) {
                std::cout << "\nOpcao invalida.\n";
                aguardarEnter();
            }
        } else if (opcao == 3) {
            return tipos;
        } else {
            std::cout << "\nOpcao invalida.\n";
            aguardarEnter();
        }
    }
}

std::optional<SeletorDeIngredientes> InterfaceTerminal::selecionarIngredientes(const Template& templateEscolhido) {
    SeletorDeIngredientes seletor;
    ValidadorDeIngredientes validador;

    while (true) {
        exibirSeparador();
        std::cout << "\n=== SELECAO DE INGREDIENTES PARA: " << templateEscolhido.getNome() << " ===\n";
        
        auto selecionados = seletor.getIngredientesSelecionados();
        std::cout << "Ingredientes selecionados ate o momento (" << selecionados.size() << "):\n";
        if (selecionados.empty()) {
            std::cout << "  (Nenhum ingrediente selecionado)\n";
        } else {
            for (size_t i = 0; i < selecionados.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << selecionados[i].getNome() 
                          << " (tipo: " << selecionados[i].getTipo() << ")\n";
            }
        }

        std::cout << "\nTipos de ingredientes exigidos pelo template:\n";
        auto tiposTmpl = templateEscolhido.getTiposPermitidos();
        for (const auto& tipo : tiposTmpl) {
            bool preenchido = false;
            for (const auto& sel : selecionados) {
                if (sel.pertenceAoTipo(tipo)) {
                    preenchido = true;
                    break;
                }
            }
            std::cout << "  - [" << (preenchido ? "X" : " ") << "] " << tipo << "\n";
        }

        std::cout << "\nOpcoes:\n";
        std::cout << "  1. Selecionar ingrediente sugerido\n";
        std::cout << "  2. Adicionar ingrediente customizado\n";
        std::cout << "  3. Remover ingrediente selecionado\n";
        std::cout << "  4. Finalizar selecao\n";
        std::cout << "  0. Voltar ao Menu Principal\n";
        
        int opcao = lerInteiro("Escolha uma opcao: ");
        if (opcao == 0) {
            return std::nullopt;
        }
        else if (opcao == 1) {
            std::cout << "\nIngredientes sugeridos no catalogo:\n";
            std::vector<IngredienteCatalogo> permitidos;
            for (const auto& ing : CATALOGO_INGREDIENTES) {
                if (templateEscolhido.aceitaTipoIngrediente(ing.tipo)) {
                    permitidos.push_back(ing);
                }
            }

            if (permitidos.empty()) {
                std::cout << "Nenhum ingrediente compativel no catalogo pre-definido.\n";
            } else {
                for (size_t i = 0; i < permitidos.size(); ++i) {
                    std::cout << "  " << (i + 1) << ". " << permitidos[i].nome 
                              << " (tipo: " << permitidos[i].tipo << ")\n";
                }
                int ingOpcao = lerInteiro("Escolha o numero do ingrediente para adicionar (ou 0 para cancelar): ");
                if (ingOpcao > 0 && ingOpcao <= static_cast<int>(permitidos.size())) {
                    Ingrediente ing(permitidos[ingOpcao - 1].nome, permitidos[ingOpcao - 1].tipo);
                    if (validador.validarIngrediente(ing, templateEscolhido)) {
                        seletor.adicionarIngrediente(ing);
                        std::cout << "\nIngrediente '" << ing.getNome() << "' adicionado!\n";
                    } else {
                        std::cout << "\nErro: " << validador.gerarMensagemErro(ing, templateEscolhido) << "\n";
                        aguardarEnter();
                    }
                }
            }
        }
        else if (opcao == 2) {
            std::string nomeIng = lerString("Digite o nome do ingrediente (ou 0 para voltar): ");
            if (nomeIng == "0") {
                return std::nullopt;
            }

            std::string tipoIng = lerString("Digite o tipo do ingrediente (ou 0 para voltar): ");
            if (tipoIng == "0") {
                return std::nullopt;
            }
            if (!nomeIng.empty() && !tipoIng.empty()) {
                try {
                    Ingrediente ing(nomeIng, tipoIng);
                    if (validador.validarIngrediente(ing, templateEscolhido)) {
                        seletor.adicionarIngrediente(ing);
                        std::cout << "\nIngrediente customizado '" << ing.getNome() << "' adicionado!\n";
                    } else {
                        std::cout << "\nErro: " << validador.gerarMensagemErro(ing, templateEscolhido) << "\n";
                        aguardarEnter();
                    }
                } catch (const std::exception& e) {
                    std::cout << "\nErro de validacao: " << e.what() << "\n";
                    aguardarEnter();
                }
            } else {
                std::cout << "\nErro: Nome ou tipo nao podem ser vazios.\n";
                aguardarEnter();
            }
        }
        else if (opcao == 3) {
            if (selecionados.empty()) {
                std::cout << "\nNenhum ingrediente selecionado para remover.\n";
                aguardarEnter();
            } else {
                int remOpcao = lerInteiro("Digite o numero do ingrediente para remover (ou 0 para cancelar): ");
                if (remOpcao > 0 && remOpcao <= static_cast<int>(selecionados.size())) {
                    seletor.removerIngrediente(selecionados[remOpcao - 1]);
                    std::cout << "\nIngrediente removido!\n";
                }
            }
        }
        else if (opcao == 4) {
            if (seletor.slotsObrigatoriosPreenchidos(templateEscolhido)) {
                std::cout << "\nSlots preenchidos com sucesso!\n";
                return seletor;
            } else {
                std::cout << "\nErro: Nem todos os slots permitidos e exigidos foram preenchidos!\n";
                aguardarEnter();
            }
        }
    }
}

void InterfaceTerminal::exibirReceita(const Receita& receita) const {
    exibirSeparador();
    std::cout << "NOME:      " << receita.getNome() << "\n";
    std::cout << "CATEGORIA: " << receita.getCategoria() << "\n";
    std::cout << "BASEADO EM: " << receita.getTemplateOrigem() << "\n";
    std::cout << "TEMPO ESTIMADO TOTAL: " << receita.getTempoEstimadoMinutos() << " minutos\n";
    
    std::cout << "\nINGREDIENTES:\n";
    for (const auto& ing : receita.getIngredientes()) {
        std::cout << "  - " << ing.getIngrediente().getNome() << " (" << ing.getIngrediente().getTipo() << "): " 
                  << std::fixed << std::setprecision(1) << ing.getQuantidade() << " " << ing.getUnidadeDeMedida() << "\n";
    }

    std::cout << "\nETAPAS DE PREPARO:\n";
    for (const auto& etapa : receita.getEtapasDePreparo()) {
        std::cout << "  Passo " << etapa.numero << " (" << etapa.tempoEstimadoMinutos << " min):\n";
        std::cout << "    Instrucoes: " << etapa.descricao << "\n";
        if (!etapa.ingredientesUsados.empty()) {
            std::cout << "    Ingredientes envolvidos: ";
            for (size_t i = 0; i < etapa.ingredientesUsados.size(); ++i) {
                std::cout << etapa.ingredientesUsados[i].getIngrediente().getNome();
                if (i + 1 < etapa.ingredientesUsados.size()) std::cout << ", ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void InterfaceTerminal::exibirListaTemplates(const std::vector<InterfaceTerminal::TemplateConstRef>& templates) const {
    if (templates.empty()) {
        std::cout << "\nNenhum template cadastrado no sistema.\n";
        aguardarEnter();
        return;
    }

    std::cout << "\nTEMPLATES CADASTRADOS:\n";
    for (const auto& tRef : templates) {
        const Template& t = tRef.get();
        std::cout << "  - ID: " << t.getId() << " | " << t.getNome() << " (" << t.getCategoria() << ")\n";
    }

    int opcao = lerInteiro("\nDigite o ID de um template para ver detalhes (ou 0 para voltar): ");
    if (opcao > 0) {
        // Encontra o template por ID
        auto it = std::find_if(templates.begin(), templates.end(), [opcao](const TemplateConstRef& tRef){
            return tRef.get().getId() == opcao;
        });
        if (it != templates.end()) {
            exibirTemplate((*it).get());
        } else {
            std::cout << "\nID nao encontrado.\n";
        }
        aguardarEnter();
    }
}

void InterfaceTerminal::exibirTemplate(const Template& t) const {
    exibirSeparador();
    std::cout << "TEMPLATE:  " << t.getNome() << "\n";
    std::cout << "CATEGORIA: " << t.getCategoria() << "\n";
    std::cout << "CONTEUDO:  " << t.getConteudo() << "\n";
    std::cout << "TIPOS DE INGREDIENTES ACEITOS: ";
    auto tipos = t.getTiposPermitidos();
    for (size_t i = 0; i < tipos.size(); ++i) {
        std::cout << tipos[i];
        if (i + 1 < tipos.size()) std::cout << ", ";
    }
    std::cout << "\n";
}


void InterfaceTerminal::exibirListaReceitas(const std::vector<Receita>& receitas) const {
    if (receitas.empty()) {
        std::cout << "\nNenhuma receita encontrada.\n";
        aguardarEnter();
        return;
    }

    std::cout << "\nRECEITAS ENCONTRADAS (" << receitas.size() << "):\n";
    for (size_t i = 0; i < receitas.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << receitas[i].getNome()
                  << " (" << receitas[i].getCategoria() << ")\n";
    }

    int opcao = lerInteiro("\nDigite o numero de uma receita para ver detalhes (ou 0 para voltar): ");
    if (opcao > 0 && opcao <= static_cast<int>(receitas.size())) {
        exibirReceita(receitas[opcao - 1]);
    }
    aguardarEnter();
}


std::string InterfaceTerminal::lerString(const std::string& prompt) const {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::string s;
    std::getline(std::cin, s);
    return trim(s);
}

int InterfaceTerminal::lerInteiro(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string entrada;
        std::getline(std::cin, entrada);
        try {
            size_t idx;
            int valor = std::stoi(entrada, &idx);
            // Verifica se a conversão consumiu toda a string
            if (idx == entrada.size()) {
                return valor;
            }
        } catch (...) {}
        std::cout << "Entrada invalida. Digite um numero inteiro valido.\n";
    }
}

std::vector<std::string> InterfaceTerminal::lerListaCSV(const std::string& prompt) const {
    std::string linha = lerString(prompt);
    std::vector<std::string> itens;
    std::stringstream ss(linha);
    std::string item;
    while (std::getline(ss, item, ',')) {
        std::string limpo = trim(item);
        if (!limpo.empty()) {
            itens.push_back(limpo);
        }
    }
    return itens;
}

void InterfaceTerminal::exibirSeparador() const {
    std::cout << "\n---------------------------------------------------------\n";
}

void InterfaceTerminal::aguardarEnter() const {
    std::cout << "\nPressione Enter para continuar...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

void InterfaceTerminal::limparTela() const {
    // Código ANSI para limpar a tela
    std::cout << "\033[2J\033[1;1H";
}
