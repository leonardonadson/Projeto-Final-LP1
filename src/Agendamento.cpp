#include "Agendamento.h"
#include "Consulta.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

Agendamento::Agendamento() {}

// O Agendamento não é dono das consultas, então o destrutor não as deleta.
// A memória das consultas é gerenciada no main
Agendamento::~Agendamento() {}

void Agendamento::agendarConsulta(Consulta* consulta) {
    consultas_.push_back(consulta);
}

Consulta* Agendamento::buscarConsultaPorId(int id) {
    for (auto& consulta : consultas_) {
        if (consulta->getId() == id) {
            return consulta;
        }
    }
    throw std::runtime_error("Consulta com ID " + std::to_string(id) + " nao encontrada.");
}

const std::vector<Consulta*>& Agendamento::getTodasConsultas() const {
    return consultas_;
}

void Agendamento::listarConsultas() const {
    std::cout << "\n--- Lista de Consultas Agendadas ---\n";
    if (consultas_.empty()) {
        std::cout << "Nenhuma consulta agendada.\n";
    } else {
        for (const auto& c : consultas_) {
            c->exibirInfo();
        }
    }
}