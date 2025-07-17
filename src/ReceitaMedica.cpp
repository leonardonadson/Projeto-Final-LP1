#include "ReceitaMedica.h"
#include "Medicamento.h"
#include <iostream>
#include <algorithm>

int ReceitaMedica::proximoId_ = 1;

ReceitaMedica::ReceitaMedica(const std::string& prescricao) : id_(proximoId_++), prescricao_(prescricao) {}

ReceitaMedica::~ReceitaMedica() {
    // Como os medicamentos são gerenciados pelo repoMedicamentos,
    // esta classe não deleta eles.
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

void ReceitaMedica::removerMedicamento(int idMedicamento) {
    auto it = std::remove_if(medicamentos_.begin(), medicamentos_.end(),
                             [idMedicamento](const Medicamento* med) {
                                 return med->getId() == idMedicamento;
                             });

    if (it != medicamentos_.end()) {
        medicamentos_.erase(it, medicamentos_.end());
        std::cout << "Medicamento removido com sucesso.\n";
    } else {
        std::cout << "Medicamento com ID " << idMedicamento << " nao encontrado na receita.\n";
    }
}