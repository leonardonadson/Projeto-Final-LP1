#include "Paciente.h"
#include "Prontuario.h"
#include "Consulta.h"

// Construtor: aloca um novo Prontuario.
Paciente::Paciente(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& historico)
    : Pessoa(nome, cpf, dataNascimento), 
      historicoMedico_(historico),
      prontuario_(new Prontuario()) {}

// Destrutor: libera a memória alocada para o Prontuario.
Paciente::~Paciente() {
    delete prontuario_;
    prontuario_ = nullptr;
}

Prontuario* Paciente::getProntuario() const { return prontuario_; }
void Paciente::setHistoricoMedico(const std::string& historico) { historicoMedico_ = historico; }

void Paciente::adicionarConsulta(Consulta* consulta) {
    consultas_.push_back(consulta);
}

void Paciente::exibirInfo() const {
    Pessoa::exibirInfo();
    std::cout << "Historico Medico: " << historicoMedico_ << std::endl;
}

const std::vector<Consulta*>& Paciente::getConsultas() const {
    return consultas_;
}