#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "GerenciadorEntidades.h"
#include "Paciente.h"
#include "Medico.h"
#include "Enfermeiro.h"
#include "Departamento.h"
#include "Medicamento.h"
#include "Agendamento.h"
#include "Consulta.h"
#include "Prontuario.h"
#include "ReceitaMedica.h"

// Repositórios para as entidades com CRUD.
GerenciadorEntidades<Paciente> repoPacientes;
GerenciadorEntidades<Medico> repoMedicos;
GerenciadorEntidades<Enfermeiro> repoEnfermeiros;
GerenciadorEntidades<Departamento> repoDepartamentos;
GerenciadorEntidades<Medicamento> repoMedicamentos;

// Gerenciador para as funcionalidades de negócio.
Agendamento agendamentoGlobal;

// Função auxiliar para limpar o buffer de entrada (stdin).
void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Protótipos das funções de menu.
void menuPacientes();
void menuMedicos();
void menuEnfermeiros();
void menuDepartamentos();
void menuMedicamentos();
void menuAgendamento();
void menuProntuario();

// Função para liberar toda a memória alocada.
void limparMemoria() {
    std::cout << "Limpando memoria...\n";
    for (auto p : repoPacientes.buscarTodos()) delete p;
    for (auto m : repoMedicos.buscarTodos()) delete m;
    for (auto e : repoEnfermeiros.buscarTodos()) delete e;
    for (auto d : repoDepartamentos.buscarTodos()) delete d;
    for (auto med : repoMedicamentos.buscarTodos()) delete med;
    for (auto c : agendamentoGlobal.getTodasConsultas()) delete c;
}

void menuPacientes() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Pacientes ---\n"
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                std::string nome, cpf, dataNasc, historico;
                std::cout << "Nome: "; std::getline(std::cin, nome);
                std::cout << "CPF: "; std::getline(std::cin, cpf);
                std::cout << "Data Nascimento: "; std::getline(std::cin, dataNasc);
                std::cout << "Historico: "; std::getline(std::cin, historico);
                
                Paciente* paciente = new Paciente(nome, cpf, dataNasc, historico);
                repoPacientes.adicionar(paciente);
                std::cout << "Paciente adicionado com ID: " << paciente->getId() << std::endl;
            } else if (opcao == 2) {
                auto todos = repoPacientes.buscarTodos();
                std::cout << "\n--- Lista de Pacientes ---\n";
                if (todos.empty()) std::cout << "Nenhum paciente cadastrado.\n";
                for (const auto& p : todos) {
                    p->exibirInfo();
                    std::cout << "------------------------\n";
                }
            } else if (opcao == 3) {
                int id;
                std::cout << "ID do paciente para atualizar: ";
                std::cin >> id;
                limparBuffer();
                Paciente* paciente = repoPacientes.buscarPorId(id);
                std::string nome, historico;
                std::cout << "Novo Nome (" << paciente->getNome() << "): "; 
                std::getline(std::cin, nome);
                std::cout << "Novo Historico: ";
                std::getline(std::cin, historico);
                paciente->setNome(nome);
                paciente->setHistoricoMedico(historico);
                std::cout << "Paciente atualizado.\n";
            } else if (opcao == 4) {
                int id;
                std::cout << "ID do paciente para remover: ";
                std::cin >> id;
                limparBuffer();
                Paciente* pacienteParaRemover = repoPacientes.buscarPorId(id);
                repoPacientes.remover(id);
                delete pacienteParaRemover;
                std::cout << "Paciente removido.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuMedicos() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Medicos ---\n"
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                std::string nome, cpf, dataNasc, especialidade, crm;
                std::cout << "Nome: "; std::getline(std::cin, nome);
                std::cout << "CPF: "; std::getline(std::cin, cpf);
                std::cout << "Data Nascimento: "; std::getline(std::cin, dataNasc);
                std::cout << "Especialidade: "; std::getline(std::cin, especialidade);
                std::cout << "CRM: "; std::getline(std::cin, crm);
                
                Medico* medico = new Medico(nome, cpf, dataNasc, especialidade, crm);
                repoMedicos.adicionar(medico);
                std::cout << "Medico adicionado com ID: " << medico->getId() << std::endl;
            } else if (opcao == 2) {
                auto todos = repoMedicos.buscarTodos();
                std::cout << "\n--- Lista de Medicos ---\n";
                if (todos.empty()) std::cout << "Nenhum medico cadastrado.\n";
                for (const auto& m : todos) {
                    m->exibirInfo();
                    std::cout << "------------------------\n";
                }
            } else if (opcao == 3) {
                int id;
                std::cout << "ID do medico para atualizar: ";
                std::cin >> id;
                limparBuffer();
                Medico* medico = repoMedicos.buscarPorId(id);
                std::string especialidade;
                std::cout << "Nova Especialidade (" << medico->getEspecialidade() << "): ";
                std::getline(std::cin, especialidade);
                medico->setEspecialidade(especialidade);
                std::cout << "Medico atualizado.\n";
            } else if (opcao == 4) {
                int id;
                std::cout << "ID do medico para remover: ";
                std::cin >> id;
                limparBuffer();
                Medico* medicoParaRemover = repoMedicos.buscarPorId(id);
                repoMedicos.remover(id);
                delete medicoParaRemover;
                std::cout << "Medico removido.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuEnfermeiros() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Enfermeiros ---\n"
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                std::string nome, cpf, dataNasc, coren;
                std::cout << "Nome: "; std::getline(std::cin, nome);
                std::cout << "CPF: "; std::getline(std::cin, cpf);
                std::cout << "Data Nascimento: "; std::getline(std::cin, dataNasc);
                std::cout << "COREN: "; std::getline(std::cin, coren);
                
                Enfermeiro* enfermeiro = new Enfermeiro(nome, cpf, dataNasc, coren);
                repoEnfermeiros.adicionar(enfermeiro);
                std::cout << "Enfermeiro adicionado com ID: " << enfermeiro->getId() << std::endl;
            } else if (opcao == 2) {
                auto todos = repoEnfermeiros.buscarTodos();
                std::cout << "\n--- Lista de Enfermeiros ---\n";
                if (todos.empty()) std::cout << "Nenhum enfermeiro cadastrado.\n";
                for (const auto& e : todos) {
                    e->exibirInfo();
                    std::cout << "------------------------\n";
                }
            } else if (opcao == 3) {
                int id;
                std::cout << "ID do enfermeiro para atualizar: ";
                std::cin >> id;
                limparBuffer();
                Enfermeiro* enfermeiro = repoEnfermeiros.buscarPorId(id);
                std::string coren;
                std::cout << "Novo COREN (" << enfermeiro->getCoren() << "): ";
                std::getline(std::cin, coren);
                enfermeiro->setCoren(coren);
                std::cout << "Enfermeiro atualizado.\n";
            } else if (opcao == 4) {
                int id;
                std::cout << "ID do enfermeiro para remover: ";
                std::cin >> id;
                limparBuffer();
                Enfermeiro* enfermeiroParaRemover = repoEnfermeiros.buscarPorId(id);
                repoEnfermeiros.remover(id);
                delete enfermeiroParaRemover;
                std::cout << "Enfermeiro removido.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuDepartamentos() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Departamentos ---\n"
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                std::string nome;
                std::cout << "Nome do Departamento: "; std::getline(std::cin, nome);
                
                Departamento* depto = new Departamento(nome);
                repoDepartamentos.adicionar(depto);
                std::cout << "Departamento adicionado com ID: " << depto->getId() << std::endl;
            } else if (opcao == 2) {
                auto todos = repoDepartamentos.buscarTodos();
                std::cout << "\n--- Lista de Departamentos ---\n";
                if (todos.empty()) std::cout << "Nenhum departamento cadastrado.\n";
                for (const auto& d : todos) {
                    d->exibirInfo();
                    std::cout << "------------------------\n";
                }
            } else if (opcao == 3) {
                int id;
                std::cout << "ID do departamento para atualizar: ";
                std::cin >> id;
                limparBuffer();
                Departamento* depto = repoDepartamentos.buscarPorId(id);
                std::string nome;
                std::cout << "Novo Nome (" << depto->getNome() << "): ";
                std::getline(std::cin, nome);
                depto->setNome(nome);
                std::cout << "Departamento atualizado.\n";
            } else if (opcao == 4) {
                int id;
                std::cout << "ID do departamento para remover: ";
                std::cin >> id;
                limparBuffer();
                Departamento* deptoParaRemover = repoDepartamentos.buscarPorId(id);
                repoDepartamentos.remover(id);
                delete deptoParaRemover;
                std::cout << "Departamento removido.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuMedicamentos() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Medicamentos ---\n"
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                std::string nome, dosagem;
                std::cout << "Nome do Medicamento: "; std::getline(std::cin, nome);
                std::cout << "Dosagem: "; std::getline(std::cin, dosagem);
                
                Medicamento* med = new Medicamento(nome, dosagem);
                repoMedicamentos.adicionar(med);
                std::cout << "Medicamento adicionado com ID: " << med->getId() << std::endl;
            } else if (opcao == 2) {
                auto todos = repoMedicamentos.buscarTodos();
                std::cout << "\n--- Lista de Medicamentos ---\n";
                if (todos.empty()) std::cout << "Nenhum medicamento cadastrado.\n";
                for (const auto& m : todos) {
                    m->exibirInfo();
                    std::cout << "------------------------\n";
                }
            } else if (opcao == 3) {
                int id;
                std::cout << "ID do medicamento para atualizar: ";
                std::cin >> id;
                limparBuffer();
                Medicamento* med = repoMedicamentos.buscarPorId(id);
                std::string nome;
                std::cout << "Novo Nome (" << med->getNome() << "): ";
                std::getline(std::cin, nome);
                med->setNome(nome);
                std::cout << "Medicamento atualizado.\n";
            } else if (opcao == 4) {
                int id;
                std::cout << "ID do medicamento para remover: ";
                std::cin >> id;
                limparBuffer();
                Medicamento* medParaRemover = repoMedicamentos.buscarPorId(id);
                repoMedicamentos.remover(id);
                delete medParaRemover;
                std::cout << "Medicamento removido.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuAgendamento() {
    int opcao;
    do {
        std::cout << "\n--- Agendamento de Consultas ---\n"
                  << "1. Agendar Nova Consulta\n2. Listar Todas as Consultas\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                int pacienteId, medicoId;
                std::string dataHora;
                std::cout << "ID do Paciente: "; std::cin >> pacienteId;
                std::cout << "ID do Medico: "; std::cin >> medicoId;
                limparBuffer();
                std::cout << "Data e Hora (DD/MM/AAAA HH:MM): "; std::getline(std::cin, dataHora);

                Paciente* p = repoPacientes.buscarPorId(pacienteId);
                Medico* m = repoMedicos.buscarPorId(medicoId);

                Consulta* c = new Consulta(dataHora, m, p);
                agendamentoGlobal.agendarConsulta(c);
                p->adicionarConsulta(c);
                m->adicionarConsulta(c);

                std::cout << "Consulta agendada com sucesso! ID da Consulta: " << c->getId() << std::endl;

            } else if (opcao == 2) {
                agendamentoGlobal.listarConsultas();
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

void menuProntuario() {
    int opcao;
    do {
        std::cout << "\n--- Gerenciar Prontuarios e Receitas ---\n"
                  << "1. Adicionar Registro ao Prontuario\n2. Criar Receita para uma Consulta\n3. Adicionar Medicamento a uma Receita\n0. Voltar\n"
                  << "Escolha: ";
        std::cin >> opcao;
        limparBuffer();

        try {
            if (opcao == 1) {
                int pacienteId;
                std::cout << "ID do Paciente: "; std::cin >> pacienteId;
                limparBuffer();
                Paciente* p = repoPacientes.buscarPorId(pacienteId);
                std::string registro;
                std::cout << "Digite o novo registro para o prontuario: ";
                std::getline(std::cin, registro);
                p->getProntuario()->adicionarRegistro(registro);
                std::cout << "Registro adicionado com sucesso!\n";
            } else if (opcao == 2) {
                int consultaId;
                std::cout << "ID da Consulta para criar a receita: "; std::cin >> consultaId;
                limparBuffer();
                Consulta* c = agendamentoGlobal.buscarConsultaPorId(consultaId);
                if (c->getReceita()!= nullptr) {
                    std::cout << "Esta consulta ja possui uma receita.\n";
                    continue;
                }
                std::string prescricao;
                std::cout << "Digite a prescricao geral da receita: ";
                std::getline(std::cin, prescricao);
                c->gerarReceita(prescricao);
                std::cout << "Receita criada com sucesso para a consulta " << c->getId() << "!\n";
            } else if (opcao == 3) {
                int consultaId, medId;
                std::cout << "ID da Consulta que contem a receita: "; std::cin >> consultaId;
                Consulta* c = agendamentoGlobal.buscarConsultaPorId(consultaId);
                ReceitaMedica* r = c->getReceita();
                if (r == nullptr) {
                    throw std::runtime_error("Nao ha receita para esta consulta. Crie uma primeiro.");
                }
                std::cout << "ID do Medicamento para adicionar a receita: "; std::cin >> medId;
                Medicamento* med = repoMedicamentos.buscarPorId(medId);
                r->adicionarMedicamento(med);
                std::cout << "Medicamento '" << med->getNome() << "' adicionado a receita.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao!= 0);
}

int main() {
    int opcao;
    do {
        std::cout << "\n===== Sistema de Gestao de Saude =====\n";
        std::cout << "--- Gerenciamento de Entidades ---\n";
        std::cout << "1. Gerenciar Pacientes\n";
        std::cout << "2. Gerenciar Medicos\n";
        std::cout << "3. Gerenciar Enfermeiros\n";
        std::cout << "4. Gerenciar Departamentos\n";
        std::cout << "5. Gerenciar Medicamentos\n";
        std::cout << "--- Operacoes do Sistema ---\n";
        std::cout << "6. Agendamento de Consultas\n";
        std::cout << "7. Gerenciar Prontuarios e Receitas\n";
        std::cout << "0. Sair\n";
        std::cout << "======================================\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, insira um numero.\n";
            std::cin.clear();
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: menuPacientes(); break;
            case 2: menuMedicos(); break;
            case 3: menuEnfermeiros(); break;
            case 4: menuDepartamentos(); break;
            case 5: menuMedicamentos(); break;
            case 6: menuAgendamento(); break;
            case 7: menuProntuario(); break;
            case 0: break;
            default: std::cout << "Opcao invalida.\n"; break;
        }
    } while (opcao!= 0);

    // Libera toda a memória alocada antes de sair.
    limparMemoria();
    std::cout << "Saindo do sistema...\n";

    return 0;
}