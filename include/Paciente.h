#pragma once

#include "Pessoa.h"
#include <vector>

class Prontuario;
class Consulta;

// Representa um paciente. Demonstra a relação de composição 1-para-1 com Prontuario.
class Paciente : public Pessoa {
private:
    std::string historicoMedico_;
    // Relação 1:1 (Composição): Paciente possui um Prontuario.
    Prontuario* prontuario_;
    std::vector<Consulta*> consultas_;

public:
    Paciente(const std::string& nome, const std::string& cpf, const std::string& dataNascimento, const std::string& historico);
    // Destrutor é crucial para liberar a memória do prontuário.
    ~Paciente() override;

    Prontuario* getProntuario() const;
    void setHistoricoMedico(const std::string& historico);
    void adicionarConsulta(Consulta* consulta);
    void exibirInfo() const override;
    const std::vector<Consulta*>& getConsultas() const;
};