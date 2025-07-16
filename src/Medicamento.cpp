#include "Medicamento.h"

int Medicamento::proximoId_ = 1;

Medicamento::Medicamento(const std::string& nome, const std::string& dosagem)
    : id_(proximoId_++), nome_(nome), dosagem_(dosagem) {}

int Medicamento::getId() const { return id_; }
std::string Medicamento::getNome() const { return nome_; }
void Medicamento::setNome(const std::string& nome) { nome_ = nome; }
std::string Medicamento::getDosagem() const { return dosagem_; }
void Medicamento::setDosagem(const std::string& dosagem) { dosagem_ = dosagem; }

void Medicamento::exibirInfo() const {
    std::cout << "ID: " << id_ << "\n"
              << "Medicamento: " << nome_ << "\n"
              << "Dosagem: " << dosagem_ << std::endl;
}