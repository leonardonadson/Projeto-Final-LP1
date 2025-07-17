#include "Medico.h"
#include "Consulta.h"

Medico::Medico(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& especialidade, const std::string& crm)
    : Pessoa(nome, cpf, dataNascimento), especialidade_(especialidade), crm_(crm), departamento_(nullptr) {}

std::string Medico::getEspecialidade() const { return especialidade_; }
void Medico::setEspecialidade(const std::string& especialidade) { especialidade_ = especialidade; }

std::string Medico::getCRM() const { return crm_; }
void Medico::setCRM(const std::string& crm) { crm_ = crm; }

std::string Medico::gerarRelatorioAtividade() const {
    return "Relatorio do Medico " + nome_ + " (CRM: " + crm_ + "): " + std::to_string(consultas_.size()) + " consultas realizadas.";
}

void Medico::adicionarConsulta(Consulta* consulta) {
    consultas_.push_back(consulta);
}

void Medico::exibirInfo() const {
    Pessoa::exibirInfo();
    std::cout << "Especialidade: " << especialidade_ << "\n"
              << "CRM: " << crm_ << std::endl;
}