# ⏱️ T-TIME: Cronômetro de Estudos em C++

Aplicação de linha de comando (CLI) desenvolvida em C++ orientado a objetos para gerenciamento de sessões de estudo e geração automática de histórico semanal em planilha (`.csv`).

## 🚀 Funcionalidades
* **Modo Livre Crescente:** Contagem progressiva com alerta de segurança após 16 horas contínuas.
* **Modo Livre Decrescente:** Contagem regressiva personalizada em minutos.
* **Modo Ciclos (Pomodoro):** Alternância automatizada entre blocos de foco e descanso com avisos sonoros.
* **Persistência Semanal (`Registro.csv`):** Agrupa automaticamente as horas estudadas por semana (Domingo a Sábado) e por matéria.

## 🛠️ Tecnologias e Conceitos Utilizados
* C++ (POO com Herança e Encapsulamento)
* Bibliotecas padrão: `<chrono>`, `<thread>`, `<fstream>`, `<ctime>`, `<iomanip>` e `<conio.h>` (Windows).

## 💻 Pré-requisitos, Compilação e Execução (Windows)

Este projeto utiliza a biblioteca `<conio.h>`, portanto foi desenvolvido para rodar nativamente no **Windows**.

### 1. Verificar ou instalar o compilador (`g++` / MinGW)
Antes de compilar, abra o **Prompt de Comando (CMD)** ou **PowerShell** e verifique se você já possui o compilador instalado digitando:
```bash
g++ --version
```
Se aparecer a versão do GCC/g++: Você já tem tudo pronto! Pode pular para o passo 2.
