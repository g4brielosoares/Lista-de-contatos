#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

typedef struct contato {
    contato() {
        ant = NULL;
        prox = NULL;
    }
    string nome;
    string numTel;
    string email;
    contato *prox;
    contato *ant;
} Contato;


int novoContatoOrdenado(Contato **lista, string nome, string numTel, string email) {
    Contato *novo = new Contato;
    if (novo == NULL) return 0;

    novo->nome = nome;
    novo->numTel = numTel;
    novo->email = email;

    if (*lista == NULL || (*lista)->nome > novo->nome) {
        novo->prox = *lista;

        if (*lista != NULL)
            (*lista)->ant = novo;

        *lista = novo;
    } else {
        Contato *aux = *lista;

        while (aux->prox && aux->prox->nome < novo->nome)
            aux = aux->prox;

        novo->prox = aux->prox;
        novo->ant = aux;

        if (aux->prox) 
            aux->prox->ant = novo;

        aux->prox = novo;
    } 

    return 1;
}

void receberDados(Contato **lista) {
    ifstream entrada;
    string linha, nome, numTel, email, i;
    entrada.open("../dados/dados.txt", ios::in);

    if (entrada.is_open()) {
        while (getline(entrada, linha)) {
            stringstream string(linha);
            getline(string, nome, ';');
            getline(string, numTel, ';');
            getline(string, email, ';');
            novoContatoOrdenado(lista, nome, numTel, email);
        }

        entrada.close();
    } else {
        cout << "Dados de contato nao fornecidos.";
        getchar();
    }

    return;
}

void salvarDados(Contato **lista) {
    ofstream saida;
    Contato *aux = *lista;
    saida.open("../dados/dados.txt", ios::out);

    while (aux) {
        saida << aux->nome << ";" << aux->numTel << ";" << aux->email << endl;
        aux = aux->prox;
    }

    saida.close();
}

int busca(Contato **lista, string nome) {
    if (*lista == NULL) return 0;

    Contato *aux = *lista;

    while (aux->prox && aux->nome != nome) {
        aux = aux->prox;
    }

    if (aux->nome == nome) return 1;

    return 0;
}

int removerContato(Contato **lista, string nome) {
    if (busca(lista, nome) == 0) return 0;

    if ((*lista)->prox == NULL) {
        delete *lista;
        *lista = NULL;
    } else {
        Contato *aux = *lista;

        while (aux->prox && aux->nome != nome)
            aux = aux->prox;

        if (aux->prox == NULL) {
            aux->ant->prox = NULL;
        } else if (aux->ant == NULL) {
            *lista = (*lista)->prox;
            (*lista)->ant = NULL;
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
        }

        delete aux;    
    }

    return 1;
}

void mostrarLista(Contato *lista) {
    cout << "\n\t        CONTATOS\n\n";
    cout << "------------------------------------------" << endl;


    if (lista == NULL) {
        cout << "\n\t       Lista vazia\n\n";
        cout << "------------------------------------------" << endl;
        return;
    }

    Contato *aux = lista;

    int i = 0;
    while (aux) {
        cout << "  " << ++i << ". " + aux->nome << endl;
        cout << "------------------------------------------" << endl;
        aux = aux->prox;
    }

    cout << "\n\t       Fim da lista\n\n";
    cout << "------------------------------------------" << endl;
}

int menuEditarInfo(Contato *aux) {
    int opc = 0;

    system(CLEAR);
    cout << "\n\t    FICHA  DE CONTATO\n\n";
    cout << "------------------------------------------" << endl;
    cout << "\n  Nome:" << endl;
    cout << "    [" << aux->nome << "]" << endl;
    cout << "  Numero: " << endl;
    cout << "    [" << aux->numTel << "]" << endl;
    cout << "  E-mail: " << endl;
    aux->email != "x" ? 
        cout << "    [" << aux->email << "]":
        cout << "    [ ]";
    cout << endl;

    cout << "\n------------------------------------------" << endl;
    cout << "  [1] - Editar numero." << endl;

    if (aux->email == "x") {
        cout << "  [2] - Adicionar E-mail." << endl;
    } else {
        cout << "  [2] - Editar E-mail." << endl;
        cout << "  [3] - Remover E-mail." << endl;
    }

    cout << "  [0] - Voltar." << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Escolha uma opcao: ";
    cin >> opc;
    cout << "------------------------------------------" << endl;

    return opc;
}

void editarInfo(Contato *aux) {
    while (true) {
        switch (menuEditarInfo(aux)) {
            case 0:
                return;
            case 1:
                cout << "  Novo numero: ";
                cin >> aux->numTel;
                break;
            case 2:
                cout << "  E-mail: ";
                cin >> aux->email;
                break;
            case 3:
                aux->email = "x";
                break;
            default:
                cout << "  Opcao invalida.";
                getchar();
                break;
        }
    }
}

int menuAbrirContato(Contato *aux) {
    int opc = 0;

    system(CLEAR);    
    cout << "\n\t    FICHA  DE CONTATO\n\n";
    cout << "------------------------------------------" << endl;
    cout << "\n  Nome:" << endl;
    cout << "    [" << aux->nome << "]" << endl;
    cout << "  Numero: " << endl;
    cout << "    [" << aux->numTel << "]" << endl;
    cout << "  E-mail: " << endl;
    aux->email != "x" ? 
        cout << "    [" << aux->email << "]":
        cout << "    [ ]";
    cout << endl;

    cout << "\n------------------------------------------" << endl;
    cout << "  [1] - Editar informacoes." << endl;
    cout << "  [0] - Voltar." << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Escolha uma opcao: ";
    cin >> opc;

    return opc;
}

void abrirContato(Contato **lista, string nome) {
    Contato *aux = *lista;

    while (aux->nome != nome) aux = aux->prox;

    while (true) {
        switch (menuAbrirContato(aux)) {
            case 0:
                return;
            case 1:
                editarInfo(aux);
                break;
            default:
                cout << "  Opcao invalida.";             
                getchar();
                break;
        }
    }
}

int menuPrincipal(Contato *lista) {
    int opc = 0;

    system(CLEAR);
    mostrarLista(lista);
    cout << "  [1] - Adicionar contato." << endl;
    cout << "  [2] - Remover contato." << endl;
    cout << "  [3] - Abrir contato." << endl;
    cout << "  [0] - Sair." << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Escolha uma opcao: ";
    cin >> opc;
    cout << "------------------------------------------" << endl;

    return opc;
}

int main() {
    Contato *lista = NULL;
    string nome, numTel, email = "x";
    char SN = 'N';

    receberDados(&lista);

    while (true) {
        switch (menuPrincipal(lista)) {
            case 0:
                cout << "  Deseja mesmo sair? [s/n] ";
                cin >> SN;
                cout << endl;

                if (SN == 's' || SN == 'S') {
                    salvarDados(&lista);
                    return 0;
                }

                break;
            case 1:
                cin.ignore();

                cout << "  Nome completo: ";
                getline(cin, nome);
                cout << "  Numero: ";
                getline(cin, numTel);
                cout << endl;

                if (busca(&lista, nome)) {
                    cout << "  Contato já existente.";
                } else {
                    if (novoContatoOrdenado(&lista, nome, numTel, email)) {
                        cout << "  Contato adicionado.";
                    } else {
                        cout << "  Falha ao adicionar contato.";
                    }

                    email = "x";
                }

                break;
            case 2:
                cin.ignore();

                if (lista != NULL) {
                    cout << "  Qual contato deseja remover?" << endl;
                    cout << "  Nome completo: ";
                    getline(cin, nome);
                    cout << endl;

                    if (removerContato(&lista, nome)) {
                        cout << "  Contato removido.";
                    } else {
                        cout << "  Contato nao existe.";
                    }
                } else {
                    cout << "  Lista vazia.";
                }
                
                break;
            case 3:
                cin.ignore();

                if (lista != NULL) {
                    cout << "  Qual contato deseja abrir?" << endl;
                    cout << "  Nome completo: ";
                    getline(cin, nome);
                    cout << endl;

                    if (busca(&lista, nome) == 0) {
                        cout << "  Contato nao existe.";
                    } else {
                        abrirContato(&lista, nome);
                    }
                } else {
                    cout << "  Lista vazia.";
                }

                break;
            default:
                cout << "  Opcao invalida.";
                getchar();
                break;
        }
        
        getchar();
        cin.clear();
    }

    return 0;
}