#include "Consulta.h"
#include "Medico.h"
#include "Paciente.h"
#include "ReceitaMedica.h"
#include <iostream>

int Consulta::proximoId_ = 1;

Consulta::Consulta(const std::string& dataHora, Medico* medico, Paciente* paciente)
    : id_(proximoId_++), dataHora_(dataHora), medico_(medico), paciente_(paciente), status_("Agendada"), receita_(nullptr) {}

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

void Consulta::exibirInfo() const {
    std::cout << "--- Consulta ID: " << id_ << " ---\n"
              << "Data/Hora: " << dataHora_ << "\n"
              << "Status: " << status_ << "\n"
              << "Medico: " << (medico_? medico_->getNome() : "N/A") << " (ID: " << (medico_? std::to_string(medico_->getId()) : "N/A") << ")\n"
              << "Paciente: " << (paciente_? paciente_->getNome() : "N/A") << " (ID: " << (paciente_? std::to_string(paciente_->getId()) : "N/A") << ")\n";
    if (receita_) {
        receita_->exibirInfo();
    }
    std::cout << "-----------------------\n";
}