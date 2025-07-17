#pragma once
#include <string>

// Representa o prontuário médico de um paciente
class Prontuario {
private:
    static int proximoId_;
    int id_;
    std::string registros_;
public:
    Prontuario();
    int getId() const;
    void adicionarRegistro(const std::string& registro);
    void exibirInfo() const;
     const std::string& getRegistros() const; 
    void setRegistros(const std::string& novosRegistros); 
};