/**
 * @file InterfaceTerminal.cpp
 * @brief Implementação da classe InterfaceTerminal.
 *
 * Corpo vazio para todas as funções: apenas stubs para compilação.
 */

#include "InterfaceTerminal.hpp"

#include <iostream>
#include <limits>


// Construtor
InterfaceTerminal::InterfaceTerminal(BuscadorDeReceitas& buscador,
                                     GerenciadorDeTemplate& gerenciador,
                                     GeradorDeReceita& gerador)
    : buscador_{buscador}
    , gerenciador_{gerenciador}
    , gerador_{gerador}
{
    
}


// Inicia o loop principal da aplicação
void InterfaceTerminal::iniciar()
{
    
}


// Menu principal

int InterfaceTerminal::exibirMenuPrincipal() const
{
    
    return 0;
}

bool InterfaceTerminal::processarOpcao(int /*opcao*/)
{
    
    return true;
}


// Fluxo: Buscar receita (US5)

void InterfaceTerminal::fluxoBuscarReceita()
{
    
}

int InterfaceTerminal::exibirSubMenuBusca() const
{
    
    return 0;
}

void InterfaceTerminal::buscarPorNome()
{
    
}

void InterfaceTerminal::buscarPorIngredientes()
{
    
}

void InterfaceTerminal::buscarPorNomeEIngredientes()
{
    
}


// Fluxo: Navegar por categoria

void InterfaceTerminal::fluxoNavegaPorCategoria()
{
    
}


// Fluxo: Criar receita

void InterfaceTerminal::fluxoCriarReceita()
{
    
}

SeletorDeIngredientes InterfaceTerminal::selecionarIngredientes(const Template& /*templateEscolhido*/)
{
    
    return SeletorDeIngredientes{};
}


// Exibição de entidades

void InterfaceTerminal::exibirReceita(const Receita& /*receita*/) const
{
    
}

void InterfaceTerminal::exibirListaReceitas(const std::vector<Receita>& /*receitas*/) const
{
    
}

void InterfaceTerminal::exibirTemplate(const Template& /*t*/) const
{
    
}

void InterfaceTerminal::exibirListaTemplates(const std::vector<Template>& /*templates*/) const
{
    
}


// Utilitários de I/O

std::string InterfaceTerminal::lerString(const std::string& /*prompt*/) const
{
    
    return "";
}

int InterfaceTerminal::lerInteiro(const std::string& /*prompt*/) const
{
    
    return 0;
}

std::vector<std::string> InterfaceTerminal::lerListaCSV(const std::string& /*prompt*/) const
{
    
    return {};
}

void InterfaceTerminal::exibirSeparador() const
{
    
}

void InterfaceTerminal::aguardarEnter() const
{
   
}

void InterfaceTerminal::limparTela() const
{
    
}