#include "Enfermeiro.h"

Enfermeiro::Enfermeiro(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& coren)
    : Pessoa(nome, cpf, dataNascimento), coren_(coren), departamento_(nullptr) {}

std::string Enfermeiro::getCoren() const { return coren_; }
void Enfermeiro::setCoren(const std::string& coren) { coren_ = coren; }

// Implementação polimórfica específica para Enfermeiro.
std::string Enfermeiro::gerarRelatorioAtividade() const {
    return "Relatorio do Enfermeiro " + nome_ + " (COREN: " + coren_ + "): Atividades de suporte.";
}

void Enfermeiro::exibirInfo() const {
    Pessoa::exibirInfo();
    std::cout << "COREN: " << coren_ << std::endl;
}