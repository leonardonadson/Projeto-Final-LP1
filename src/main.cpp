#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>

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
void menuRealizarConsulta();
void menuPainelPaciente();
void inicializarDadosPadrao();
void limparMemoria();
std::string getDataHoraAtual();

std::string getDataHoraAtual() {
    time_t agora = time(0);
    tm *ltm = localtime(&agora);
    char buffer[80];
    // Formato: DD/MM/AAAA HH:MM
    strftime(buffer, 80, "%d/%m/%Y %H:%M", ltm);
    return std::string(buffer);
}

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
                std::string nome, historico, dataNasc, cpf;
                std::cout << "Novo Nome (Atual: " << paciente->getNome() << "): ";
                std::getline(std::cin, nome);
                std::cout << "Novo CPF (Atual: " << paciente->getCPF() << "): ";
                std::getline(std::cin, cpf);
                std::cout << "Nova Data de Nascimento (Atual: " << paciente->getDataNascimento() << "): "; // Solicita a Data de Nascimento
                std::getline(std::cin, dataNasc);
                std::cout << "Novo Historico Médico: ";
                std::getline(std::cin, historico);
                paciente->setNome(nome);
                paciente->setCPF(cpf);
                paciente->setDataNascimento(dataNasc);
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
                std::string nome, cpf, dataNasc, especialidade, crm;
                std::cout << "Novo Nome (Atual: " << medico->getNome() << "): ";
                std::getline(std::cin, nome);

                std::cout << "Novo CPF (Atual: " << medico->getCPF() << "): ";
                std::getline(std::cin, cpf);
                std::cout << "Nova Data de Nascimento (Atual: " << medico->getDataNascimento() << "): ";
                std::getline(std::cin, dataNasc);
                std::cout << "Nova Especialidade (Atual: " << medico->getEspecialidade() << "): ";
                std::getline(std::cin, especialidade);
                std::cout << "Novo CRM (Atual: " << medico->getCRM() << "): ";
                std::getline(std::cin, crm);
                medico->setNome(nome);
                medico->setCPF(cpf);
                medico->setDataNascimento(dataNasc);
                medico->setEspecialidade(especialidade);
                medico->setCRM(crm);
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
                std::string nome, cpf, dataNasc, coren;
                std::cout << "Novo Nome (Atual: " << enfermeiro->getNome() << "): ";
                std::getline(std::cin, nome);
                std::cout << "Novo CPF (Atual: " << enfermeiro->getCPF() << "): ";
                std::getline(std::cin, cpf);
                std::cout << "Nova Data de Nascimento (Atual: " << enfermeiro->getDataNascimento() << "): ";
                std::getline(std::cin, dataNasc);
                std::cout << "Novo COREN (Atual: " << enfermeiro->getCoren() << "): ";
                std::getline(std::cin, coren);
                enfermeiro->setNome(nome);
                enfermeiro->setCPF(cpf);
                enfermeiro->setDataNascimento(dataNasc);
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
                  << "1. Adicionar\n2. Listar\n3. Atualizar\n4. Remover\n5. Atribuir Medico a um Departamento\n6. Atribuir Enfermeiro a um Departamento\n0. Voltar\n"
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
                std::cout << "ID do Departamento para atualizar: ";
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
                std::cout << "ID do Departamento para remover: ";
                std::cin >> id;
                limparBuffer();
                Departamento* deptoParaRemover = repoDepartamentos.buscarPorId(id);
                repoDepartamentos.remover(id);
                delete deptoParaRemover;
                std::cout << "Departamento removido.\n";
            } else if (opcao == 5) {
                int idDepto, idMedico;
                std::cout << "ID do Departamento: ";
                std::cin >> idDepto;
                std::cout << "ID do Medico a ser atribuido: ";
                std::cin >> idMedico;
                limparBuffer();
                Departamento* depto = repoDepartamentos.buscarPorId(idDepto);
                Medico* medico = repoMedicos.buscarPorId(idMedico);
                depto->adicionarMedico(medico);
                std::cout << "Medico '" << medico->getNome() << "' atribuido ao departamento '" << depto->getNome() << "'.\n";
            } else if (opcao == 6) {
                int idDepto, idEnfermeiro;
                std::cout << "ID do Departamento: ";
                std::cin >> idDepto;
                std::cout << "ID do Enfermeiro a ser atribuido: ";
                std::cin >> idEnfermeiro;
                limparBuffer();
                Departamento* depto = repoDepartamentos.buscarPorId(idDepto);
                Enfermeiro* enfermeiro = repoEnfermeiros.buscarPorId(idEnfermeiro);
                depto->adicionarEnfermeiro(enfermeiro);
                std::cout << "Enfermeiro '" << enfermeiro->getNome() << "' atribuido ao departamento '" << depto->getNome() << "'.\n";
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
                std::string nome, dosagem;
                std::cout << "Novo Nome (Atual: " << med->getNome() << "): ";
                std::getline(std::cin, nome);
                std::cout << "Nova Dosagem (Atual: " << med->getDosagem() << "): ";
                std::getline(std::cin, dosagem);
                med->setNome(nome);
                med->setDosagem(dosagem);
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
        std::cout << "\n--- Menu de Consultas ---\n"
                  << "1. Agendar Nova Consulta\n"
                  << "2. Listar TODAS as Consultas\n"
                  << "3. Listar Consultas REALIZADAS\n"
                  << "4. Listar Consultas AGENDADAS\n"
                  << "0. Voltar\n"
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
            } else if (opcao >= 2 && opcao <= 4) {
                auto todas = agendamentoGlobal.getTodasConsultas();
                std::vector<Consulta*> paraListar;
                std::string titulo;

                if (opcao == 2) {
                    paraListar = todas;
                    titulo = "--- Lista de TODAS as Consultas ---";
                } else {
                    StatusConsulta filtro = (opcao == 3) ? StatusConsulta::Realizada : StatusConsulta::Agendada;
                    titulo = (opcao == 3) ? "--- Lista de Consultas REALIZADAS ---" : "--- Lista de Consultas AGENDADAS ---";
                    for (const auto& c : todas) {
                        if (c->getStatus() == filtro) paraListar.push_back(c);
                    }
                }
                std::cout << "\n" << titulo << "\n";
                if (paraListar.empty()) {
                    std::cout << "Nenhuma consulta encontrada com este criterio.\n";
                } else {
                    for (const auto& c : paraListar) c->exibirInfo();
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao != 0);
}


void menuPainelPaciente() {
    int idPaciente;
    std::cout << "\n--- Painel do Paciente ---\n";
    std::cout << "Digite o ID do Paciente: ";
    std::cin >> idPaciente;
    limparBuffer();

    try {
        Paciente* paciente = repoPacientes.buscarPorId(idPaciente);
        int opcao;
        do {
            std::cout << "\n--- Painel de " << paciente->getNome() << " ---\n";
            std::cout << "1. Visualizar Prontuario Completo\n";
            std::cout << "2. Adicionar Anotacao ao Prontuario\n";
            std::cout << "3. Editar Prontuario Completo (com cuidado)\n";
            std::cout << "4. Listar Consultas e Ver Receitas do Paciente\n";
            std::cout << "5. Corrigir Receita (de consulta nao finalizada)\n";
            std::cout << "0. Voltar ao Menu Principal\n";
            std::cout << "Escolha: ";
            std::cin >> opcao;
            limparBuffer();

            if (opcao == 1) {
                paciente->getProntuario()->exibirInfo();
            } 
            else if (opcao == 2) {
                std::string anotacao;
                std::cout << "Digite a nova anotacao:\n";
                std::getline(std::cin, anotacao);
                std::string registro = "[" + getDataHoraAtual() + "]\n" + anotacao;
                paciente->getProntuario()->adicionarRegistro(registro);
                std::cout << "Anotacao adicionada.\n";
            }
            else if (opcao == 3) {
                std::cout << "\n--- Conteudo Atual do Prontuario ---\n";
                std::cout << paciente->getProntuario()->getRegistros() << std::endl;
                std::cout << "\n-------------------------------------\n";
                std::cout << "Copie o texto acima, edite como desejar, e cole o conteudo completo abaixo.\n";
                std::cout << "Para finalizar, digite 'FIM' em uma nova linha e pressione Enter.\n";
                
                std::string novosRegistros, linha;
                while (std::getline(std::cin, linha) && linha != "FIM") {
                    novosRegistros += linha + "\n";
                }
                paciente->getProntuario()->setRegistros(novosRegistros);
                std::cout << "Prontuario atualizado com sucesso!\n";
            }
            else if (opcao == 4) {
                std::cout << "\n--- Consultas de " << paciente->getNome() << " ---\n";
                const auto& consultas = paciente->getConsultas();
                if (consultas.empty()) {
                    std::cout << "Nenhuma consulta registrada para este paciente.\n";
                }
                for (const auto& c : consultas) {
                    c->exibirInfo();
                }
            }
            else if (opcao == 5) {
                 int idConsulta;
                 std::cout << "Digite o ID da consulta cuja receita deseja corrigir: ";
                 std::cin >> idConsulta;
                 limparBuffer();
                 Consulta* consulta = agendamentoGlobal.buscarConsultaPorId(idConsulta);
                 
                 if (consulta->getStatus() != StatusConsulta::Agendada) {
                     throw std::runtime_error("ERRO: So e possivel editar a receita de uma consulta com status 'Agendada'.");
                 }
                 ReceitaMedica* receita = consulta->getReceita();
                 if (!receita) {
                    throw std::runtime_error("ERRO: Esta consulta ainda nao possui uma receita.");
                 }
                 
                 receita->exibirInfo();
                 std::cout << "1. Adicionar Medicamento\n2. Remover Medicamento\nEscolha: ";
                 int opReceita;
                 std::cin >> opReceita;
                 limparBuffer();

                 if (opReceita == 1) {
                     int idMed;
                     std::cout << "ID do medicamento a adicionar: "; std::cin >> idMed;
                     limparBuffer();
                     receita->adicionarMedicamento(repoMedicamentos.buscarPorId(idMed));
                 } else if (opReceita == 2) {
                     int idMed;
                     std::cout << "ID do medicamento a remover: "; std::cin >> idMed;
                     limparBuffer();
                     receita->removerMedicamento(idMed);
                 }
            }
        } while (opcao != 0);

    } catch (const std::exception& e) {
        std::cerr << "ERRO: " << e.what() << std::endl;
    }
}

void menuRealizarConsulta() {
    int idConsulta;
    std::cout << "\n--- Realizar Consulta ---\n";
    std::cout << "Digite o ID da consulta a ser realizada: ";
    std::cin >> idConsulta;
    limparBuffer();

    try {
        Consulta* consulta = agendamentoGlobal.buscarConsultaPorId(idConsulta);
        if (consulta->getStatus() != StatusConsulta::Agendada) {
            throw std::runtime_error("Esta consulta nao pode ser realizada (status atual: " + statusParaString(consulta->getStatus()) + ").");
        }
        Paciente* paciente = consulta->getPaciente();
        
        std::string anotacao;
        std::cout << "\nDigite as anotacoes da consulta para o prontuario de " << paciente->getNome() << ":\n";
        std::getline(std::cin, anotacao);
        std::string registro = "[" + getDataHoraAtual() + " - Consulta com " + consulta->getMedico()->getNome() + "]\n" + anotacao;
        paciente->getProntuario()->adicionarRegistro(registro);
        std::cout << "Registro adicionado ao prontuario.\n";

        char opReceita;
        std::cout << "\nDeseja criar uma receita? (s/n): ";
        std::cin >> opReceita;
        limparBuffer();
        if (opReceita == 's' || opReceita == 'S') {
            std::string prescricao;
            std::cout << "Digite a prescricao geral da receita (ex: Tomar por 7 dias): ";
            std::getline(std::cin, prescricao);
            consulta->gerarReceita(prescricao);
            std::cout << "Receita criada. Agora adicione os medicamentos.\n";
            
            ReceitaMedica* receita = consulta->getReceita();
            char opMedicamento;
            do {
                std::cout << "\nDeseja adicionar um medicamento a receita? (s/n): ";
                std::cin >> opMedicamento;
                limparBuffer();
                if (opMedicamento == 's' || opMedicamento == 'S') {
                    for(const auto& med : repoMedicamentos.buscarTodos()){
                        std::cout << "ID: " << med->getId() << " - " << med->getNome() << "\n";
                    }
                    int idMedicamento;
                    std::cout << "Digite o ID do medicamento: ";
                    std::cin >> idMedicamento;
                    limparBuffer();
                    receita->adicionarMedicamento(repoMedicamentos.buscarPorId(idMedicamento));
                }
            } while (opMedicamento == 's' || opMedicamento == 'S');
        }
        consulta->setStatus(StatusConsulta::Realizada);
        std::cout << "\nConsulta finalizada com sucesso!\n";
    } catch (const std::exception& e) {
        std::cerr << "ERRO: " << e.what() << std::endl;
    }
}


int main() {
    inicializarDadosPadrao();
    int opcao;
    do {
        std::cout << "\n===== Sistema de Gestao de Saude =====\n";
        std::cout << "1. Gerenciar Pacientes\n";
        std::cout << "2. Gerenciar Medicos\n";
        std::cout << "3. Gerenciar Enfermeiros\n";
        std::cout << "4. Gerenciar Departamentos\n";
        std::cout << "5. Gerenciar Medicamentos\n";
        std::cout << "--- Operacoes do Sistema ---\n";
        std::cout << "6. Consultas (Agendar e Listar)\n";
        std::cout << "7. Realizar Consulta\n";
        std::cout << "8. Painel do Paciente (Prontuario, Receitas)\n";
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
            case 7: menuRealizarConsulta(); break;
            case 8: menuPainelPaciente(); break;
            case 0: break;
            default: std::cout << "Opcao invalida.\n"; break;
        }
    } while (opcao != 0);

    // Libera toda a memória alocada antes de sair.
    limparMemoria();
    std::cout << "Saindo do sistema...\n";

    return 0;
}

void inicializarDadosPadrao() {
    std::cout << "Inicializando dados padrao do sistema...\n";

    // --- Criar Departamentos ---
    Departamento* deptoCardio = new Departamento("Cardiologia");
    Departamento* deptoNeuro = new Departamento("Neurologia");
    Departamento* deptoGeral = new Departamento("Clinica Geral");
    repoDepartamentos.adicionar(deptoCardio);
    repoDepartamentos.adicionar(deptoNeuro);
    repoDepartamentos.adicionar(deptoGeral);

    // --- Criar Medicos ---
    Medico* medico1 = new Medico("Dr. Joao Silva", "111.222.333-44", "10/05/1980", "Cardiologista", "CRM-12345");
    Medico* medico2 = new Medico("Dra. Ana Costa", "555.666.777-88", "22/08/1985", "Neurologista", "CRM-54321");
    Medico* medico3 = new Medico("Dr. Carlos Lima", "999.888.777-66", "15/03/1975", "Clinico Geral", "CRM-67890");
    repoMedicos.adicionar(medico1);
    repoMedicos.adicionar(medico2);
    repoMedicos.adicionar(medico3);

    // --- Criar Enfermeiros ---
    Enfermeiro* enf1 = new Enfermeiro("Mariana Oliveira", "123.456.789-10", "12/01/1990", "COREN-SP-1111");
    Enfermeiro* enf2 = new Enfermeiro("Ricardo Souza", "019.876.543-21", "30/11/1988", "COREN-RJ-2222");
    repoEnfermeiros.adicionar(enf1);
    repoEnfermeiros.adicionar(enf2);
    
    // --- Atribuir Profissionais aos Departamentos ---
    try {
        deptoCardio->adicionarMedico(medico1);
        deptoCardio->adicionarEnfermeiro(enf1);
        deptoNeuro->adicionarMedico(medico2);
        deptoGeral->adicionarMedico(medico3);
        deptoGeral->adicionarEnfermeiro(enf2);
    } catch (const std::exception& e) {
        std::cerr << "ERRO na inicializacao: " << e.what() << '\n';
    }


    // --- Criar Pacientes ---
    Paciente* paciente1 = new Paciente("Jose Bezerra", "121.232.343-45", "15/02/1995", "Asma");
    Paciente* paciente2 = new Paciente("Maria das Dores", "565.676.787-89", "20/07/1960", "Diabetes tipo 2, Hipertensao");
    Paciente* paciente3 = new Paciente("Pedro Antunes", "989.878.767-65", "01/12/2001", "Nenhuma condicao pre-existente");
    repoPacientes.adicionar(paciente1);
    repoPacientes.adicionar(paciente2);
    repoPacientes.adicionar(paciente3);
    
    // Adicionar um registro no prontuário de um paciente
    paciente2->getProntuario()->adicionarRegistro("25/06/2024: Paciente relatou dores de cabeca frequentes.");


    // --- Criar Medicamentos ---
    Medicamento* med1 = new Medicamento("Paracetamol", "750mg");
    Medicamento* med2 = new Medicamento("Ibuprofeno", "600mg");
    Medicamento* med3 = new Medicamento("Amoxicilina", "500mg");
    Medicamento* med4 = new Medicamento("Losartana", "50mg");
    repoMedicamentos.adicionar(med1);
    repoMedicamentos.adicionar(med2);
    repoMedicamentos.adicionar(med3);
    repoMedicamentos.adicionar(med4);

    std::cout << "Dados carregados com sucesso!\n";
}