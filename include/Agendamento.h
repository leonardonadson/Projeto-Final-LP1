#pragma once
#include <vector>

class Consulta;

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