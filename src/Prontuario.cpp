#include "Prontuario.h"
#include <iostream>

int Prontuario::proximoId_ = 1;

Prontuario::Prontuario() : id_(proximoId_++), registros_() {}

int Prontuario::getId() const { return id_; }

void Prontuario::adicionarRegistro(const std::string& registro) {
    if (!registros_.empty()) {
        registros_ += "\n---\n";
    }
    registros_ += registro;
}

const std::string& Prontuario::getRegistros() const {
    return registros_;
}

void Prontuario::setRegistros(const std::string& novosRegistros) {
    registros_ = novosRegistros;
}
void Prontuario::exibirInfo() const {
    std::cout << "--- Prontuario ID: " << id_ << " ---\n"
              << registros_ << "\n-----------------------\n";
}