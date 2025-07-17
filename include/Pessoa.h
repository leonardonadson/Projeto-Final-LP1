#pragma once

#include <string>
#include <iostream>

// Classe base para um indivíduo aplicando a Herança
class Pessoa {
private:
    static int proximoId_;
    
protected:
    int id_;
    std::string nome_;
    std::string cpf_;
    std::string dataNascimento_;

public:
    Pessoa(const std::string& nome, const std::string& cpf, const std::string& dataNascimento);
    virtual ~Pessoa() = default;

    int getId() const;
    std::string getNome() const;
    void setNome(const std::string& nome);
    std::string getCPF() const;
    void setCPF(const std::string& cpf);
    std::string getDataNascimento() const;
    void setDataNascimento(const std::string& dataNascimento);

    // Método virtual para o Polimorfismo.
    virtual std::string gerarRelatorioAtividade() const;

    virtual void exibirInfo() const;
};