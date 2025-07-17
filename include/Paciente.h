#pragma once

#include "Pessoa.h"
#include <vector>

class Prontuario;
class Consulta;

class Paciente : public Pessoa {
private:
    std::string historicoMedico_;
    Prontuario* prontuario_;
    std::vector<Consulta*> consultas_;

public:
    Paciente(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& historico);

    ~Paciente() override;

    Prontuario* getProntuario() const;
    void setHistoricoMedico(const std::string& historico);
    void adicionarConsulta(Consulta* consulta);
    void exibirInfo() const override;
    const std::vector<Consulta*>& getConsultas() const;
};