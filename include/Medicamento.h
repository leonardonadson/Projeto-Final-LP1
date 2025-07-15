#pragma once
#include <string>
#include <iostream>

// Modela um medicamento individual.
class Medicamento {
private:
    static int proximoId_;
    int id_;
    std::string nome_;
    std::string dosagem_;

public:
    Medicamento(const std::string& nome, const std::string& dosagem);
    int getId() const;
    std::string getNome() const;
    void setNome(const std::string& nome);
    void exibirInfo() const;
};