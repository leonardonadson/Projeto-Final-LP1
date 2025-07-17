#pragma once

#include "Pessoa.h"
#include <vector>

class Departamento;

class Enfermeiro : public Pessoa {
private:
    std::string coren_;
    Departamento* departamento_;

public:
    Enfermeiro(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& coren);

    std::string getCoren() const;
    void setCoren(const std::string& coren);

    // Sobrescreve o método da base (Polimorfismo).
    std::string gerarRelatorioAtividade() const override;

    void exibirInfo() const override;
};