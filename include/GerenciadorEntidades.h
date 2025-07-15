#pragma once

#include <map>
#include <vector>
#include <string>
#include <stdexcept> // Para exceções padrão como std::runtime_error

// Gerenciador genérico que implementa as operações CRUD em memória.
// Atende ao requisito de "Templates".
// A posse dos ponteiros (e a responsabilidade de 'delete') é externa a esta classe.
template <typename T>
class GerenciadorEntidades {
private:
    // Armazena ponteiros brutos para as entidades em um mapa de ID para a entidade.
    std::map<int, T*> entidades_;

public:
    GerenciadorEntidades() = default;
    ~GerenciadorEntidades() = default;

    // Adiciona um ponteiro de entidade ao mapa.
    void adicionar(T* entidade) {
        if (!entidade) {
            throw std::invalid_argument("Erro: A entidade nao pode ser nula.");
        }
        entidades_[entidade->getId()] = entidade;
    }

    // Busca uma entidade por ID, lança exceção se não encontrar.
    T* buscarPorId(int id) {
        auto it = entidades_.find(id);
        if (it!= entidades_.end()) {
            return it->second;
        }
        throw std::runtime_error("Erro: Entidade com ID " + std::to_string(id) + " nao encontrada.");
    }

    // Retorna um vetor com todos os ponteiros de entidades.
    std::vector<T*> buscarTodos() {
        std::vector<T*> todos;
        for (const auto& par : entidades_) {
            todos.push_back(par.second);
        }
        return todos;
    }

    // Remove um ponteiro de entidade do mapa. Não deleta o objeto.
    void remover(int id) {
        auto it = entidades_.find(id);
        if (it!= entidades_.end()) {
            entidades_.erase(it);
        } else {
            throw std::runtime_error("Erro: Entidade com ID " + std::to_string(id) + " nao encontrada ao tentar remover.");
        }
    }
};