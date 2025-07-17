#include "Consulta.h"
#include "Medico.h"
#include "Paciente.h"
#include "ReceitaMedica.h"
#include <iostream>

int Consulta::proximoId_ = 1;

Consulta::Consulta(const std::string& dataHora, Medico* medico, Paciente* paciente)
    : id_(proximoId_++), dataHora_(dataHora), status_(StatusConsulta::Agendada), medico_(medico), paciente_(paciente), receita_(nullptr) {}

Consulta::~Consulta() {
    delete receita_; // A consulta é dona da receita.
    receita_ = nullptr;
}

int Consulta::getId() const { return id_; }

void Consulta::gerarReceita(const std::string& prescricao) {
    if (!receita_) {
        receita_ = new ReceitaMedica(prescricao);
    }
}

ReceitaMedica* Consulta::getReceita() const {
    return receita_;
}

// Função auxiliar para converter enum em string para exibição
std::string statusParaString(StatusConsulta status) {
    switch (status) {
        case StatusConsulta::Agendada: return "Agendada";
        case StatusConsulta::Realizada: return "Realizada";
        case StatusConsulta::Cancelada: return "Cancelada";
        default: return "Desconhecido";
    }
}

void Consulta::exibirInfo() const {
    std::cout << "--- Consulta ID: " << id_ << " ---\n"
              << "Data/Hora: " << dataHora_ << "\n"
              << "Status: " << statusParaString(status_) << "\n"
              << "Medico: " << (medico_ ? medico_->getNome() : "N/A") << " (ID: " << (medico_ ? std::to_string(medico_->getId()) : "N/A") << ")\n"
              << "Paciente: " << (paciente_ ? paciente_->getNome() : "N/A") << " (ID: " << (paciente_ ? std::to_string(paciente_->getId()) : "N/A") << ")\n";
    if (receita_) {
        receita_->exibirInfo();
    }
    std::cout << "-----------------------\n";
}


Medico* Consulta::getMedico() const { return medico_; }

Paciente* Consulta::getPaciente() const { return paciente_; }

const std::string& Consulta::getDataHora() const { return dataHora_; }

StatusConsulta Consulta::getStatus() const { return status_; }

void Consulta::setStatus(StatusConsulta novoStatus) {
    status_ = novoStatus;
}