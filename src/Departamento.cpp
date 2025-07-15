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
    std::cout << "ID: " << id_ << "\n"
              << "Departamento: " << nome_ << "\n"
              << "Medicos: " << medicos_.size() << "\n"
              << "Enfermeiros: " << enfermeiros_.size() << std::endl;
}