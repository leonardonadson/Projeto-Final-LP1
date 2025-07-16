#pragma once
#include <string>
#include <vector>

class Medico;
class Paciente;
class ReceitaMedica;

// Enum para os status possíveis de uma consulta
enum class StatusConsulta {
    Agendada,
    Realizada,
    Cancelada
};

// Classe de associação que conecta um Medico a um Paciente (relação N:M).
class Consulta {
private:
    static int proximoId_;
    int id_;
    std::string dataHora_;
    StatusConsulta status_;
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
    Medico* getMedico() const;
    Paciente* getPaciente() const;
    const std::string& getDataHora() const;
    StatusConsulta getStatus() const;
    void setStatus(StatusConsulta novoStatus);
};