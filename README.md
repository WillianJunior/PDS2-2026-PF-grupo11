# PDS2-2026-PF-grupo11

# Integrantes do grupo: 
Henry Dutra França, Gabriel Marques Mendonça Silva, Kaio Fernandes Ferreira Nunes & João Lucas Lima de Oliveira.

# Descrição do projeto 
O tema do nosso projeto final é o "Ricettario", uma coleção de receitas italianas, que foi implementado em um sistema de criação e gerenciamento dessa culinária. O programa permite ao usuário montar receitas personalizadas a partir de templates predefinidos (como Pizza, Pasta, Risotto), onde cada template define quais tipos de ingredientes são permitidos — garantindo combinações coerentes e autênticas.

O usuário pode selecionar ingredientes de forma interativa, e o sistema valida automaticamente se cada escolha é compatível com o template selecionado. Após a seleção, o GeradorDeReceita monta a receita final com etapas de preparo ordenadas, tempo estimado e lista detalhada de ingredientes com quantidades e unidades de medida. O sistema também oferece mecanismos de busca por nome ou ingrediente e filtragem por categoria gastronômica.

# Objetivos Principais
- Fornecer uma experiência agradável e intuitiva ao usuário.
- Permitir a criação de receitas personalizadas a partir de templates predefinidos para cada tipo de prato italiano.
- Validar a compatibilidade dos ingredientes selecionados com o template escolhido, rejeitando combinações incoerentes e informando o motivo da rejeição.
- Gerar receitas completas com nome, categoria, lista de ingredientes (com quantidade e unidade de medida), etapas de preparo ordenadas e tempo estimado total.
- Oferecer busca de receitas por nome, por ingredientes ou por ambos os critérios simultaneamente, com resultado seguindo ordem alfabética.
- Filtrar templates e receitas por categoria gastronômica (ex: Massas, Carnes, Sobremesas).

# Motivação da escolha
O Ricettario surgiu como uma oportunidade de aplicar em um modelo prático a implementação orientada a objetos, aprendida ao longo desse semestre na disciplina proporcionando um ambiente inovador e de desafios para explorar o que estamos aprendendo. O catálogo da culinária italiana foi escolhido por oferecer uma estrutura, de fato, hierárquica (composta por categorias, templates, ingredientes, receitas), que se traduz de forma direta em uma modelagem orientada rica e expressiva.

Ao estudar os temas, identificamos que a maioria dos sites e aplicativos de receitas funciona como simples repositórios estáticos, em que o usuário apenas consulta receitas prontas, sem possibilidade de personalização com validação. Dessa forma, decidimos por produzir o Ricettario, que preenche essa lacuna, ao permitir que o usuário monte suas próprias combinações de ingredientes dentro de regras controladas por templates, garantindo que o resultado seja uma receita coerente e autêntica ao mesmo tempo. O projeto forneceu um ambiente inovador, recheado de desafios técnicos relevantes, como a implementação de um sistema de busca com normalização de termos, validação de regras de negócio por composição de objetos e separação de responsabilidades seguindo o princípio SRP.

# Arquitetura do Projeto
O projeto segue os princípios da Programação Orientada a Objetos com as seguintes classes:

`Receita` -> Armazena dados estruturais da receita (nome, categoria, ingredientes, etapas).

`Template` -> Define modelos reutilizáveis com regras de tipos de ingredientes permitidos.

`Ingrediente` -> Representa um ingrediente genérico do sistema. 

`IngredienteDaReceita` -> Especialização do ingrediente com quantidade e unidade específica. 

`GeradorDeReceita` -> Responsável por montar a receita a partir do template e ingredientes.

`BuscadorDeReceita` -> Realiza buscas por nome ou ingrediente no acervo.

`FiltroDeCategoria` -> Filtra receitas por categoria gastronômica.

`GerenciadorDeTemplate` -> Gerencia o ciclo de vida dos templates disponíveis.

`SeletorDeIngredientes` -> Interface para seleção de ingredientes pelo usuário.

`ValidadorDeIngredientes` -> Valida compatibilidade dos ingredientes com o template.