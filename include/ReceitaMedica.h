#pragma once
#include <string>
#include <vector>

class Medicamento;

// Modela uma receita médica.
class ReceitaMedica {
private:
    static int proximoId_;
    int id_;
    std::string prescricao_;
    std::vector<Medicamento*> medicamentos_;

public:
    ReceitaMedica(const std::string& prescricao);
    ~ReceitaMedica();
    int getId() const;
    void adicionarMedicamento(Medicamento* medicamento);
    void exibirInfo() const;
    void removerMedicamento(int idMedicamento);
};