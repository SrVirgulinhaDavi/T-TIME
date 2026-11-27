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

## 💻 Como compilar e executar (Windows)
```bash
g++ Core_unificado.cpp -o t-time.exe
./t-time.exe
