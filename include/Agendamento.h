#pragma once
#include <vector>

class Consulta;

// Classe de serviço para gerenciar o agendamento de consultas.
class Agendamento {
private:
    std::vector<Consulta*> consultas_;

public:
    Agendamento();
    ~Agendamento();
    void agendarConsulta(Consulta* consulta);
    Consulta* buscarConsultaPorId(int id);
    const std::vector<Consulta*>& getTodasConsultas() const;
    void listarConsultas() const;
};