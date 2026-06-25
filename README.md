# PDS2-2026-PF-grupo11

## Integrantes do grupo

Henry Dutra França, Gabriel Marques Mendonça Silva, Kaio Fernandes Ferreira Nunes e João Lucas Lima de Oliveira.

## Descrição do projeto

O Ricettario é um sistema em C++ para criação, consulta e gerenciamento de receitas inspiradas na culinária italiana.

O programa permite trabalhar com templates de pratos, como pizza, pasta e risotto, cada um com regras próprias para os tipos de ingredientes aceitos. A partir desses templates, o usuário pode selecionar ingredientes, validar se eles são compatíveis com o prato escolhido e gerar uma receita final com ingredientes, quantidades, etapas de preparo e tempo estimado.

O sistema também possui busca de receitas por nome, por ingredientes ou pelos dois critérios ao mesmo tempo, além de navegação de templates por categoria.

## Objetivos implementados

- Criar receitas personalizadas a partir de templates.
- Validar ingredientes de acordo com os tipos permitidos por cada template.
- Gerar receitas completas com nome, categoria, ingredientes, etapas de preparo e tempo estimado.
- Buscar receitas por nome.
- Buscar receitas por ingredientes.
- Buscar receitas combinando nome e ingredientes.
- Navegar e filtrar templates por categoria.
- Permitir criação e persistência de novos templates em arquivo.
- Executar testes automatizados com doctest.

## Motivação da escolha

O Ricettario surgiu como uma oportunidade de aplicar em um modelo prático a implementação orientada a objetos, aprendida ao longo desse semestre na disciplina proporcionando um ambiente inovador e de desafios para explorar o que estamos aprendendo. O catálogo da culinária italiana foi escolhido por oferecer uma estrutura, de fato, hierárquica (composta por categorias, templates, ingredientes, receitas), que se traduz de forma direta em uma modelagem orientada rica e expressiva.

Ao estudar os temas, identificamos que a maioria dos sites e aplicativos de receitas funciona como simples repositórios estáticos, em que o usuário apenas consulta receitas prontas, sem possibilidade de personalização com validação. Dessa forma, decidimos por produzir o Ricettario, que preenche essa lacuna, ao permitir que o usuário monte suas próprias combinações de ingredientes dentro de regras controladas por templates, garantindo que o resultado seja uma receita coerente e autêntica ao mesmo tempo. O projeto forneceu um ambiente inovador, recheado de desafios técnicos relevantes, como a implementação de um sistema de busca com normalização de termos, validação de regras de negócio por composição de objetos e separação de responsabilidades seguindo o princípio SRP.

## Arquitetura do projeto

O projeto foi organizado seguindo princípios de Programação Orientada a Objetos, com separação de responsabilidades entre entidades, serviços de domínio e interface.

### Classes principais

`Ingrediente`

Representa um ingrediente base, contendo nome e tipo.

`IngredienteDaReceita`

Representa um ingrediente dentro de uma receita, adicionando quantidade e unidade de medida ao ingrediente base.

`Receita`

Armazena os dados de uma receita: nome, template de origem, categoria, ingredientes, etapas de preparo e tempo estimado.

`Template`

Classe base para os modelos de receita. Armazena id, nome, conteúdo, categoria e tipos de ingredientes permitidos.

`PizzaTemplate`, `PastaTemplate` e `RisottoTemplate`

Especializações de `Template` com regras e tipos de ingredientes próprios.

`ValidadorDeIngredientes`

Valida se um ingrediente ou uma seleção de ingredientes é compatível com um template.

`SeletorDeIngredientes`

Gerencia a seleção de ingredientes feita pelo usuário.

`GeradorDeReceita`

Gera as etapas de preparo e calcula o tempo total estimado da receita com base nos arquivos de template em `data/templates`.

`BuscadorDeReceitas`

Realiza buscas no repositório de receitas por nome, por ingredientes ou pelos dois critérios combinados.

`FiltroDeCategoria`

Encapsula o critério de filtragem por categoria aplicado aos templates.

`GerenciadorDeTemplate`

Carrega, armazena, lista, filtra, adiciona, remove e salva templates.

`InterfaceTerminal`

Controla a interação com o usuário via terminal, exibindo menus e chamando as classes responsáveis pelas operações do sistema.

## Estrutura de pastas

```text
.
├── data/
│   ├── receitas.txt
│   └── templates/
│       ├── pasta.txt
│       ├── pizza.txt
│       └── risotto.txt
├── include/
│   └── arquivos de cabeçalho (.hpp)
├── src/
│   └── implementações das classes e main.cpp
├── tests/
│   └── testes automatizados com doctest
├── Makefile
├── templates.txt
└── README.md
```

## Persistência de dados

As receitas iniciais são carregadas de:

```text
data/receitas.txt
```

Os templates cadastrados são carregados e salvos em:

```text
templates.txt
```

As etapas usadas pelo `GeradorDeReceita` ficam em:

```text
data/templates/
```

## Como compilar

É necessário ter um compilador C++ com suporte a C++17 e `make`.

```bash
make
```

O executável principal é gerado em:

```text
build/main
```

No Windows, o executável pode ser gerado como:

```text
build/main.exe
```

## Como executar

```bash
make run
```

Também é possível executar diretamente o binário gerado dentro da pasta `build`.

## Como rodar os testes

```bash
make test
```

Os testes usam `doctest`, incluído no diretório `include`.

O alvo `test` também executa `gcovr` para relatório de cobertura. Portanto, para usar esse comando, o `gcovr` precisa estar instalado no ambiente.

## Observações sobre a implementação

- A busca por nome usa comparação sem diferenciar maiúsculas e minúsculas.
- A busca por ingredientes exige que todos os ingredientes informados estejam presentes na receita.
- A ordenação da busca por nome é feita por relevância em relação ao termo pesquisado.
- O filtro de categoria implementado no sistema atua sobre templates.
- O sistema usa herança e polimorfismo na hierarquia de templates.
- O sistema usa composição em classes como `Receita` e `IngredienteDaReceita`.