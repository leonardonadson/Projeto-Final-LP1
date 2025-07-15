#pragma once
#include <string>
#include <vector>

class Medico;
class Enfermeiro;

// Modela um departamento da unidade de saúde.
class Departamento {
private:
    static int proximoId_;
    int id_;
    std::string nome_;
    // Agrega listas de médicos e enfermeiros (associação).
    std::vector<Medico*> medicos_;
    std::vector<Enfermeiro*> enfermeiros_;

public:
    Departamento(const std::string& nome);
    int getId() const;
    std::string getNome() const;
    void setNome(const std::string& nome);
    void adicionarMedico(Medico* medico);
    void adicionarEnfermeiro(Enfermeiro* enfermeiro);
    void exibirInfo() const;
};