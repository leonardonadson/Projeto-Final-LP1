#include "Departamento.h"
#include "Medico.h"
#include "Enfermeiro.h"
#include <iostream>

int Departamento::proximoId_ = 1;

Departamento::Departamento(const std::string& nome) : id_(proximoId_++), nome_(nome) {}

int Departamento::getId() const { return id_; }
std::string Departamento::getNome() const { return nome_; }
void Departamento::setNome(const std::string& nome) { nome_ = nome; }

void Departamento::adicionarMedico(Medico* medico) {
    medicos_.push_back(medico);
}

void Departamento::adicionarEnfermeiro(Enfermeiro* enfermeiro) {
    enfermeiros_.push_back(enfermeiro);
}

void Departamento::exibirInfo() const {
    std::cout << "ID: " << id_ << "\n";
    std::cout << "Departamento: " << nome_ << "\n";
    std::cout << "Medicos Associados (" << medicos_.size() << "):\n";
    if (medicos_.empty()) {
        std::cout << "  - Nenhum\n";
    } else {
        for (const auto& med : medicos_) {
            std::cout << "  - ID: " << med->getId() << ", Nome: " << med->getNome() << " (CRM: " << med->getCRM() << ")\n";
        }
    }

    std::cout << "Enfermeiros Associados (" << enfermeiros_.size() << "):\n";
    if (enfermeiros_.empty()) {
        std::cout << "  - Nenhum\n";
    } else {
        for (const auto& enf : enfermeiros_) {
            std::cout << "  - ID: " << enf->getId() << ", Nome: " << enf->getNome() << " (COREN: " << enf->getCoren() << ")\n";
        }
    }
}