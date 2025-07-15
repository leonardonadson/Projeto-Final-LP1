#include "Prontuario.h"
#include <iostream>

int Prontuario::proximoId_ = 1;

Prontuario::Prontuario() : id_(proximoId_++), registros_("Prontuario criado.\n") {}

int Prontuario::getId() const { return id_; }

void Prontuario::adicionarRegistro(const std::string& registro) {
    registros_ += registro + "\n";
}

void Prontuario::exibirInfo() const {
    std::cout << "--- Prontuario ID: " << id_ << " ---\n"
              << registros_ << "\n-----------------------\n";
}