#include "../include/Ingrediente.hpp"
#include <stdexcept>

Ingrediente::Ingrediente(const std::string &nome, const std::string &tipo)
    : nome_(nome), tipo_(tipo) {

  if (nome.empty() || tipo.empty()) {
    throw std::invalid_argument(
        "Ingrediente inválido: nome e tipo não podem ser vazios");
  }
}

std::string Ingrediente::getNome() const { return nome_; }

std::string Ingrediente::getTipo() const { return tipo_; }

bool Ingrediente::pertenceAoTipo(const std::string &tipo) const {
  return tipo_ == tipo;
}