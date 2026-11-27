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

### 2. Instalando o compilador (`g++` / MinGW)
Se aparecer "g++ não é reconhecido como um comando interno...": Instale o pacote oficial do MinGW-w64 (WinLibs) diretamente pelo gerenciador de pacotes nativo do Windows (winget) rodando o comando abaixo no CMD:
Acesse o site oficial msys2.org e clique no botão de download do instalador (msys2-x86_64-....exe). No próprio site já há um tutorial, siga ele.

### 3. Como Compilar e Rodar
Crie uma pasta para o arquivo .cpp baixado. Abra essa pasta e na guia de pesquisa dela digite apenas "cmd" e aperte ENTER.
<img width="1902" height="372" alt="Captura de tela 2026-11-27 000127" src="https://github.com/user-attachments/assets/6b7d8ed6-25c5-40a3-ad09-acb8ef0da556" />

Após abrir o prompt de comando do windows, digite o seguinte:
```bash
g++ Core_T_TIME_Atualizado.cpp -o t-time.exe
```
E aperte ENTER. Esse processo cria o arquivo executável do código.
Após, digite o comando para executar ele.
```bash
t-time.exe
```

### AVISO
Se você encerrar o programa fechando o cmd, os minutos estudados daquela sessão serão perdidos, apenas termine o programa pela própria condição de parada dele "espaço"
Pronto, tudo feito. Agora sempre que for executar o cronômetro você só precisa abrir o prompt de comando pela pasta do arquivo (cmd) e digitar o executável do arquivo 
```bash
t-time.exe
```
