# 📂 Menu do Projeto

## 📄 Descrição
Administração de pacientes, equipes médicas e agendamentos em uma unidade de saúde.

---

## ✨ Classes Propostas

- **Pessoa** (Classe base)
  - **Paciente** (Herda de Pessoa)
  - **Médico** (Herda de Pessoa)
  - **Enfermeiro** (Herda de Pessoa)

- **Prontuário**
- **Departamento**
- **Consulta**
- **Receita Médica**
- **Medicamento**
- **Agendamento**

---

## 🛠️ CRUD (Create, Read, Update, Delete)
O sistema implementa o CRUD para as seguintes 5 entidades:

- **Paciente**
- **Médico**
- **Enfermeiro**
- **Departamento**
- **Medicamento**

---

## 🔗 Relacionamentos

- **1 para 1**: Paciente ↔️ Prontuário  
- **1 para N**: Médico ➝ Consulta  
- **N para M**: Médico ⇄ Paciente *(gerenciado através da classe Consulta)*

---

## 🧠 Conceitos de POO Aplicados

- **Encapsulamento**: Atributos das classes definidos como privados para proteger os dados.
- **Herança**: As classes `Paciente`, `Médico` e `Enfermeiro` herdam características da classe base `Pessoa`.
- **Polimorfismo**: Método virtual `gerarRelatorioAtividade()` implementado de formas diferentes para `Médico` e `Enfermeiro`.
- **Templates**: Uso da classe genérica `GerenciadorEntidades<T>` para gerenciar diferentes tipos de listas (Pacientes, Médicos, etc.).

---
## 👨‍💻 Autores

| [<img src="https://avatars.githubusercontent.com/u/72714982?v=4" width=115><br><sub>Leonardo Nadson</sub>](https://github.com/leonardonadson) | [<img src="https://avatars.githubusercontent.com/u/177072444?v=4" width=115><br><sub>xandecoh</sub>](https://github.com/xandecoh) |
| :---: | :---: |

