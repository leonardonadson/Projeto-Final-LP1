#include "ReceitaMedica.h"
#include "Medicamento.h"
#include <iostream>

int ReceitaMedica::proximoId_ = 1;

ReceitaMedica::ReceitaMedica(const std::string& prescricao) : id_(proximoId_++), prescricao_(prescricao) {}

ReceitaMedica::~ReceitaMedica() {
    // Como os medicamentos são gerenciados pelo repoMedicamentos,
    // esta classe não deve deletá-los.
}

int ReceitaMedica::getId() const { return id_; }

void ReceitaMedica::adicionarMedicamento(Medicamento* medicamento) {
    medicamentos_.push_back(medicamento);
}

void ReceitaMedica::exibirInfo() const {
    std::cout << "--- Receita ID: " << id_ << " ---\n"
              << "Prescricao: " << prescricao_ << "\n"
              << "Medicamentos:\n";
    if (medicamentos_.empty()) {
        std::cout << "  (Nenhum medicamento adicionado)\n";
    } else {
        for (const auto& med : medicamentos_) {
            std::cout << "  - " << med->getNome() << "\n";
        }
    }
}