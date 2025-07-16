#include "Pessoa.h"

int Pessoa::proximoId_ = 1;

Pessoa::Pessoa(const std::string& nome, const std::string& cpf, const std::string& dataNascimento)
    : id_(proximoId_++), nome_(nome), cpf_(cpf), dataNascimento_(dataNascimento) {}

int Pessoa::getId() const { return id_; }
std::string Pessoa::getNome() const { return nome_; }
void Pessoa::setNome(const std::string& nome) { nome_ = nome; }
std::string Pessoa::getCPF() const { return cpf_; }
void Pessoa::setCPF(const std::string& cpf) { cpf_ = cpf; }
std::string Pessoa::getDataNascimento() const { return dataNascimento_; }
void Pessoa::setDataNascimento(const std::string& dataNascimento) { dataNascimento_ = dataNascimento;
}
std::string Pessoa::gerarRelatorioAtividade() const {
    return "Pessoa " + nome_ + " nao possui relatorio de atividade.";
}

void Pessoa::exibirInfo() const {
    std::cout << "ID: " << id_ << "\n"
              << "Nome: " << nome_ << "\n"
              << "CPF: " << cpf_ << "\n"
              << "Data de Nascimento: " << dataNascimento_ << std::endl;
}