#pragma once
#include <string>
#include <vector>

class Medico;
class Paciente;
class ReceitaMedica;

// Classe de associação que conecta um Medico a um Paciente (relação N:M).
class Consulta {
private:
    static int proximoId_;
    int id_;
    std::string dataHora_;
    std::string status_;
    // Ponteiros não proprietários para os participantes.
    Medico* medico_;
    Paciente* paciente_;
    // Ponteiro proprietário para a receita.
    ReceitaMedica* receita_;

public:
    Consulta(const std::string& dataHora, Medico* medico, Paciente* paciente);
    ~Consulta();
    
    int getId() const;
    void gerarReceita(const std::string& prescricao);
    ReceitaMedica* getReceita() const;
    void exibirInfo() const;
};