#pragma once

#include "Pessoa.h"
#include <vector>

class Departamento;
class Consulta;

class Medico : public Pessoa {
private:
    std::string especialidade_;
    std::string crm_;
    Departamento* departamento_;
    std::vector<Consulta*> consultas_;

public:
    Medico(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& especialidade, const std::string& crm);

    std::string getEspecialidade() const;
    void setEspecialidade(const std::string& especialidade);
    std::string getCRM() const;
    void setCRM(const std::string& crm);

    std::string gerarRelatorioAtividade() const override;
    void adicionarConsulta(Consulta* consulta);
    void exibirInfo() const override;
};