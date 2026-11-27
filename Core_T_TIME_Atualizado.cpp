
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h> // Para detectar tecla pressionada (_kbhit e _getch) sem pausar o loop

#include <ctime>
#include <cstdlib> // system()

using namespace std;


// CLASSE BASE: Cronometro

class Cronometro {
protected:
    int horas, minutos, segundos;
    string titulo;

public:
    Cronometro (string _titulo, int h = 0, int m = 0, int s = 0) {
        titulo = _titulo;
        horas = h;
        minutos = m;
        segundos = s;
    }

    void exibirTela(string instrucaoExtra = "") {
        system("cls");
        cout << "========================================" << endl;
        cout << "  " << titulo << endl;
        cout << "========================================" << endl;
        cout << "               "
             << setfill('0') << setw(2) << horas << ":"
             << setfill('0') << setw(2) << minutos << ":"
             << setfill('0') << setw(2) << segundos << endl;
        cout << "========================================" << endl;
        if (instrucaoExtra != "") {
            cout << instrucaoExtra << endl;
        }
    }

    void emitirBeep(string aviso) {
        cout << "\a";
        cout << "\n[AVISO]: " << aviso << endl;
    }

};

// CLASSE DERIVADA: TEMPO CRESCENTE

class CronometroLivreCrescente : public Cronometro {
private:
    const int LIMITE_SEGURANCA_HORAS = 16; //flag  16 horas
    bool flag16hDisparada = false;

public:
    CronometroLivreCrescente() : Cronometro("MODO: CRESCENTE", 0, 0, 0){}

    // Retorna o total de minutos estudados para salvar no arquivo
    int iniciar (){
        int totalSegundos = 0;

        while (true) {
            string msg = "Pressione [ESPACO] a qualquer momento para PARAR.";
            if (flag16hDisparada){
                msg += "\n[ALERTA DE SISTEMA]: Cronometro ativo ha mais de 16 horas!";
            }

            exibirTela(msg);

            // Verifica se o usuário apertou alguma tecla para parar
            if (_kbhit()){ //keyboard hit
                char tecla = _getch();
                if (tecla == ' '){
                    emitirBeep("Cronometro parado pelo usuario.");
                    break;
                }
            }

            // Verifica a flag de 16 horas (16 * 3600 = 57600 segundos)
            if (horas >= LIMITE_SEGURANCA_HORAS && !flag16hDisparada) {
                flag16hDisparada = true;
                emitirBeep("Voce esqueceu o cronometro ligado? (16h atingidas)");
            }

            totalSegundos++;
            segundos++;

            if (segundos == 60){ 
                segundos = 0; 
                minutos++; 
            }
            if (minutos == 60){ 
                minutos = 0;  
                horas++; 
            }

            this_thread::sleep_for(chrono::seconds(1));
        }

    return totalSegundos / 60; // Retorna minutos
    }
};

// CLASSE DERIVADA: TEMPO DECRESCENTE

class CronometroDecrescente : public Cronometro {
private:
    int minutosIniciais;

public:
    CronometroDecrescente(int min) : Cronometro("MODO: DECRESCENTE", min / 60, min % 60, 0) {
        minutosIniciais = min;
    }

    int iniciar (){
        int segundosRestantes = minutosIniciais * 60;
        int segundosEstudados = 0;

        while (segundosRestantes >= 0) {
            exibirTela("Pressione [ESPACO] para cancelar antes do fim.");

            if (_kbhit()){
                char tecla = _getch();
                if (tecla == ' ') {
                    emitirBeep("Contagem interrompida.");
                    break;
                }
            }

            if (segundosRestantes == 0) {
                emitirBeep("Tempo finalizado!");
                break;
            }

            segundosRestantes--;
            segundosEstudados++;

            horas = segundosRestantes / 3600;
            minutos = (segundosRestantes % 3600) / 60;
            segundos = segundosRestantes % 60;
            this_thread::sleep_for(chrono::seconds(1));
        }

    return segundosEstudados / 60;
    }
};

// CLASSE DERIVDA: POMODORO

class CronometroCiclos : public Cronometro {
private:
    int minFoco;
    int minDescanso;
    int totalCiclos;

    // Adicionamos o parâmetro 'cicloAtual' aqui
    void rodarBloco(string nomeFase, int minutosAlvo, int cicloAtual) {
        horas = 0; minutos = 0; segundos = 0;
        titulo = nomeFase;
        int alvoSegundos = minutosAlvo * 60;
        int decorrido = 0;

        while (decorrido <= alvoSegundos) {
            exibirTela();
            cout << "Ciclo " << cicloAtual << " de " << totalCiclos << endl;

            if (decorrido == alvoSegundos) {
                break;
            }

            decorrido++;
            segundos++;
            if (segundos == 60){
                segundos = 0;
                minutos++;
            }
            if (minutos == 60){
                minutos = 0;
                horas++;
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

public:
    CronometroCiclos(int _foco, int _descanso, int _ciclos) : Cronometro("MODO: CICLOS", 0, 0, 0) {
        minFoco = _foco;
        minDescanso = _descanso;
        totalCiclos = _ciclos;
    }

    int iniciar (){
        int minutosTotaisFoco = 0;

        for (int c = 1; c <= totalCiclos; c++) {
            // Passamos o 'c' como terceiro argumento
            rodarBloco("MODO CICLOS - FOCO", minFoco, c);
            minutosTotaisFoco += minFoco;
            emitirBeep("Tempo de foco concluido! Iniciando descanso em 5 segundos");
            this_thread::sleep_for(chrono::seconds(5));

            // 2. Fase de Descanso (conta de 0 até minDescanso)
            rodarBloco("MODO CICLOS - DESCANSO", minDescanso, c);

            if (c < totalCiclos) {
                emitirBeep("Descanso finalizado! Voltando aos estudos em 10 segundos");
                this_thread::sleep_for(chrono::seconds(10));
            } else {
                emitirBeep("Todos os ciclos foram concluidos! Parabens!");
            }
        }

    return minutosTotaisFoco;
    }
};

// REGISTRO SEMANAL DE ESTUDOS

// Converte minutos para horas e minutos (ex.: 90 -> 01:30).
string formatarTempo(int minutos) {
    int h = minutos / 60, m = minutos % 60;
    return (h < 10 ? "0" : "") + to_string(h) + ":" +
           (m < 10 ? "0" : "") + to_string(m);
}

// Converte o texto HH:MM novamente em minutos.
int converterMinutos(string tempo) {
    int pos = tempo.find(':');
    return stoi(tempo.substr(0, pos)) * 60 + stoi(tempo.substr(pos + 1));
}

// Cada linha representa uma materia em uma semana.
string linhaRegistro(string semana, string materia, int dias[]) {
    string linha = semana + ";" + materia;
    int total = 0;
    for (int i = 0; i < 7; i++) {
        linha += ";" + formatarTempo(dias[i]);
        total += dias[i];
    }
    return linha + ";" + formatarTempo(total) + "\n";
}

// Padroniza a chave de busca, sem alterar o nome exibido no CSV.
string normalizarMateria(string texto) {
    string acentos[] = {"áàâãä", "éèêë", "íìîï", "óòôõö", "úùûü", "ç",
                        "ÁÀÂÃÄ", "ÉÈÊË", "ÍÌÎÏ", "ÓÒÔÕÖ", "ÚÙÛÜ", "Ç"};
    string letras = "aeioucaeiouc";
    for (int i = 0; i < 12; i++) {
        for (size_t j = 0; j < acentos[i].size(); j += 2) {
            string acento = acentos[i].substr(j, 2);
            size_t pos;
            while ((pos = texto.find(acento)) != string::npos)
                texto.replace(pos, 2, 1, letras[i]);
        }
    }
    for (char &c : texto)
        if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
    return texto;
}

void registrarEstudo(string materia, int minutos, time_t dataSessao) {
    if (materia.empty() || materia.find_first_of(";\"\r\n") != string::npos || minutos < 0) {
        cout << "Materia ou tempo invalido. Registro nao salvo.\n";
        return;
    }
    tm data = *localtime(&dataSessao);
    int dia = data.tm_wday; // Domingo = 0, sabado = 6.
    data.tm_mday -= dia;
    data.tm_isdst = -1;
    mktime(&data); // Ajusta a data inclusive na troca de mes/ano.
    char inicio[11], fim[11];
    strftime(inicio, sizeof(inicio), "%Y-%m-%d", &data);
    data.tm_mday += 6;
    data.tm_isdst = -1;
    mktime(&data);
    strftime(fim, sizeof(fim), "%Y-%m-%d", &data);
    string semana = string(inicio) + " a " + fim;

    ifstream entrada("Registro.csv");
    string linha, conteudo = "\xEF\xBB\xBF" "Semana;Materia;Dom;Seg;Ter;Qua;Qui;Sex;Sab;Total\n";
    string chave = semana + ";" + normalizarMateria(materia) + ";";
    bool encontrou = false;
    if (entrada.is_open()) {
        getline(entrada, linha); // Pula o cabecalho.
        while (getline(entrada, linha)) {
            size_t fimMateria = linha.find(';', semana.size() + 1);
            if (fimMateria != string::npos &&
                normalizarMateria(linha.substr(0, fimMateria + 1)) == chave) {
                int dias[7] = {};
                size_t inicioCampo = fimMateria + 1;
                for (int i = 0; i < 7; i++) {
                    size_t fimCampo = linha.find(';', inicioCampo);
                    dias[i] = converterMinutos(linha.substr(inicioCampo, fimCampo - inicioCampo));
                    inicioCampo = fimCampo + 1;
                }
                dias[dia] += minutos;
                conteudo += linhaRegistro(semana,
                    linha.substr(semana.size() + 1, fimMateria - semana.size() - 1), dias);
                encontrou = true;
            } else if (!linha.empty()) {
                conteudo += linha + "\n";
            }
        }
        if (entrada.bad()) {
            cout << "Erro na leitura. Registro nao alterado.\n";
            return;
        }
        entrada.close();
    }
    if (!encontrou) {
        int dias[7] = {};
        dias[dia] = minutos;
        conteudo += linhaRegistro(semana, materia, dias);
    }
    ofstream saida("Registro.csv");
    saida << conteudo;
    saida.close();
    if (saida.fail()) cout << "Erro ao salvar Registro.csv.\n";
    else cout << "Registro.csv atualizado!\n";
}

// MAIN: Menu Principal

int main() {
    system("chcp 65001 > nul"); // Terminal em UTF-8 (Windows).
    int opcao;
    int minutosEstudados = 0;

    cout << "=== T-TIME: CRONOMETRO DE ESTUDOS ===" << endl;
    cout << "1. Modo Livre - Crescente (Para ao apertar tecla / Flag 16h)" << endl;
    cout << "2. Modo Livre - Decrescente (Tempo definido ate 0)" << endl;
    cout << "3. Modo Ciclos (Foco + Descanso repetidos)" << endl;
    cout << "Escolha: ";
    if (!(cin >> opcao) || opcao < 1 || opcao > 3) {
        cout << "Opcao invalida!" << endl;
        return 0;
    }
    string materia;
    cout << "Qual materia voce vai estudar? ";
    if (!getline(cin >> ws, materia) || materia.empty() ||
        materia.find_first_of(";\"\r\n") != string::npos) {
        cout << "Materia invalida!" << endl;
        return 0;
    }
    materia.erase(materia.find_last_not_of(" \t") + 1);
    time_t dataSessao = time(0);

    if (opcao == 1) {
        CronometroLivreCrescente cLivre;
        minutosEstudados = cLivre.iniciar();
    } 
    else if (opcao == 2) {
        int min;
        cout << "Digite quantos minutos deseja contar regressivamente: ";
        if (!(cin >> min) || min <= 0 || min > 35791394) {
            cout << "Tempo invalido!" << endl;
            return 0;
        }
        CronometroDecrescente cDecrescente(min);
        minutosEstudados = cDecrescente.iniciar();
    } 
    else if (opcao == 3) {
        int foco, descanso, ciclos;
        cout << "Minutos de foco: ";
        if (!(cin >> foco) || foco <= 0 || foco > 35791394) {
            cout << "Valor invalido!" << endl;
            return 0;
        }
        cout << "Minutos de descanso: ";
        if (!(cin >> descanso) || descanso < 0 || descanso > 35791394) {
            cout << "Valor invalido!" << endl;
            return 0;
        }
        cout << "Quantidade de ciclos: ";
        if (!(cin >> ciclos) || ciclos <= 0 || ciclos > 2147483647 / foco) {
            cout << "Valor invalido!" << endl;
            return 0;
        }
        
        CronometroCiclos cCiclos(foco, descanso, ciclos);
        minutosEstudados = cCiclos.iniciar();
    } 
    else {
        cout << "Opcao invalida!" << endl;
        return 0;
    }



    registrarEstudo(materia, minutosEstudados, dataSessao);

    return 0;
}