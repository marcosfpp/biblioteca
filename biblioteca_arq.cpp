#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimos{
    char data_emp[11], dat_dev[11], usuario[255];

};

struct livros{
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int opc_princ, cod, campo, cod_E, pos;
char opc;

FILE *arquivo;
FILE *arquivoAUX;

struct livros livro;

int main (){

    do {
        cout << "__________SISTEMA DAHORA DE BIBLIOTECA__________" << endl;
        cout << "1 - CADASTRO" << endl;
        cout << "2 - ALTERACAO" << endl;
        cout << "3 - EXCLUSAO" << endl;
        cout << "4 - EMPRESTIMO" << endl;
        cout << "5 - DEVOLUCAO" << endl;
        cout << "6 - CONSULTAR LIVROS" << endl;
        cout << "7 - LIVROS DISPONIVEIS" << endl;
        cout << "8 - LISTAGEM GERAL DE LIVROS" << endl;
        cout << "9 - SAIR" << endl << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opc_princ;

        switch (opc_princ)
        {
            case 1:
                cout << "Voce deseja cadastrar um livro (S ou N)? ";
                cin >> opc;
                system("cls");
                while(opc == 'S' || opc == 's'){

                    cout << "Digite o codigo do livro: ";
                    cin >> livro.codigo;
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');
                    cout << "Digite a area do livro: ";
                    cin.get(livro.area, 30);
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');
                    cout << "Digite o titulo do livro: ";
                    cin.get(livro.titulo, 255);
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');
                    cout << "Digite o autor(es) do livro: ";
                    cin.get(livro.autores, 255);
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');
                    cout << "Digite a editora do livro: ";
                    cin.get(livro.editora, 50);
                    cin.ignore(numeric_limits <streamsize>::max(), '\n');
                    cout << "Digite o numero de paginas: ";
                    cin >> livro.paginas;

                    //ABRIR O ARQUIVO --- CRIAR A VARIAVEL ARQUIVO LÁ EM CIMA COM * POR SER PONTEIRO.
                    //TESTE SE O ARQUIVO EXISTE, ABRE EM AB, SE NÃO EXISTE, CRIA UM ARQUIVO NOVO EM MODO WB
                    //PARAMÊTRO DE NOME DE ARQUIVO + MODO DE ABERTURA
                    arquivo = fopen("dados.dat", "ab");
                    if(arquivo == NULL) {
                        arquivo = fopen("dados.dat", "wb");
                    }
                    
                    //FUNÇÃO PARA GRAVAR, COM 4 PARAMETROS --> O QUE É EU QUERO GRAVAR, DADOS EM "LIVRO"
                    //PARAMETRO PARA CALCULAR O ESPAÇO "SIZEOF(NOME DA STRUCT)"
                    //QUANTIDADE DE REGISTROS QUE ESTÃO SENDO GRAVADOS
                    //ONDE EU ESTOU GRAVANDO
                    if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                        cout << "O livro " << livro.titulo << " foi cadastrado com sucesso!";
                    }else{
                        cout << "Erro ao cadastrar o livro!";
                    }
                    fclose(arquivo);

                     //CIN IGNORE IGNORAR O ULTIMO ENTER E O GET ESPERA VOCE APERTAR OUTRA TECLA PRA CONTINUAR
                    cin.ignore();
                    cin.get();
                    system("cls");
                    
                    
                    cout << "Voce deseja cadastrar um livro (S ou N)? ";
                    cin >> opc;
                    system("cls");
                }
                break;
            case 2:
                arquivo = fopen("dados.dat", "rb+");
                if(arquivo != NULL ){
                    system("cls");
                    cout << "Digite o codigo do livro que deseja alterar: " << endl;
                    cin >> cod;
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while (!feof(arquivo)) {
                        if(cod == livro.codigo){
                            //ALTERAÇÃO BEM SIMPLES, USANDO O SISTEMA DE USAR O SIZEOF NEGATIVO PRA PEGAR DESDE O COMEÇO DO ARQUIVO
                            fseek(arquivo, -sizeof(struct livros), SEEK_CUR);
                            cout << "Digite qual campo voce deseja alterar: ";
                            cout << "1- area, 2- titulo, 3- autor, 4- editora, 5- numero de paginas" << endl;
                            cin >> campo;
                            cin.get();
                            switch(campo) {

                            case 1:
                                cout << "Digite nova area: ";
                                cin.get(livro.area, 30);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                cout << "Area alterada com sucesso!" << endl;
                                cin.get();
                                fclose(arquivo);
                                break;
                            
                            case 2:
                                cout << "Digite novo titulo: ";
                                cin.get(livro.titulo, 255);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                cout << "Titulo alterada com sucesso!" << endl;
                                cin.get();
                                fclose(arquivo);
                                break;
                            
                            case 3:
                                cout << "Digite novo autor: ";
                                cin.get(livro.area, 255);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                cout << "Autor alterada com sucesso!" << endl;
                                cin.get();
                                fclose(arquivo);
                                break;
                            
                            case 4:
                                cout << "Digite nova editora: ";
                                cin.get(livro.editora, 50);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                cout << "Editora alterada com sucesso!" << endl;
                                cin.get();
                                fclose(arquivo);
                                break;

                            case 5:
                                cout << "Digite novo numero de paginas: ";
                                cin >> livro.paginas;
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                cout << "Numero de paginas alterada com sucesso!" << endl;
                                cin.get();
                                fclose(arquivo);
                                break;
                                
                            default:

                                cout << "Valor invalido!" << endl;
                                fclose(arquivo);
                                break;

                            }break;
                            
                            
                        }
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    
                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;    
            case 3:
                arquivo = fopen("dados.dat", "rb+");
                if(arquivo != NULL ){
                    //SISTEMA DE EXCLUSÃO USANDO A ESTRATEGIA ENSINADA EM SALA DE USAR UM ARQUIVO AUXILIAR
                    //PARA REESCRITA E TRANSFORMANDO ELE EM ARQUIVO PRINCIPAL
                    system("cls");
                    cout << "Deseja excluir todo o arquivo (S ou N)? ";
                    cin >> opc;
                    if(opc == 'S' || opc == 's'){
                        arquivo = fopen("dados.dat", "wb");
                        cout << "Arquivo excluido!" << endl;
                        cin.get();
                    } else if (opc == 'N' || opc == 'n'){
                        cout << "Deseja excluir um registro especifico (S ou N)? ";
                        cin >> opc;
                            if(opc == 'S' || opc == 's'){
                                cout << "Digite o codigo do livro que deseja excluir: ";
                                cin >> cod_E;
                                arquivoAUX = fopen("dadosAUX.dat", "wb");
                                fread(&livro, sizeof(struct livros), 1 ,arquivo);
                                while(!feof(arquivo)){
                                    if(cod_E != livro.codigo){
                                        fwrite(&livro, sizeof(struct livros), 1, arquivoAUX);
                                    }
                                    fread(&livro, sizeof(struct livros), 1, arquivo);
                                }
                                fclose(arquivo);
                                fclose(arquivoAUX);
                                remove("dados.dat");
                                rename("dadosAUX.dat", "dados.dat");
                                cout << "Registro excluido com sucesso!" << endl;
                                cin.ignore();
                                cin.get();

                            }break;
                }break;

                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 4:                       
                arquivo = fopen("dados.dat", "rb+");
                if(arquivo != NULL ){
                    //SISTEMA DE EMPRESTIMO, BEM PARECIDO COM DEVOLUÇÃO, PARAMETRO PARA EMPRESTIMO É TER CAMPOS COMO
                    //DATA DE DEVOLUÇÃO E DE EMPRESTIMO PREENCHIDOS, SE PREENCHIDOS O LIVRO ESTÁ EMPRESTADO
                    system("cls");
                    cout << "Digite o código do livro que deseja emprestar: ";
                    cin >> cod_E;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    pos = -1;
                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        pos++;
                        if (cod_E == livro.codigo){
                            fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                            cout << "Digite a data de emprestimo: ";
                            cin.get(livro.emp.data_emp, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite a data de devolucao: ";
                            cin.get(livro.emp.dat_dev, 10);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite o nome do usuario que pegara o livro: ";
                            cin.get(livro.emp.usuario, 255);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            fwrite(&livro, sizeof(struct livros), 1, arquivo);          
                            break;
                            }
                        }
                        fclose(arquivo);
                        }   
                        else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 5:
                //SISTEMA DE DEVOLUÇÃO, ASSUMINDO QUE O LIVRO ESTA EMPRESTADO, SUBSTUINDO OS CAMPOS CHAR
                // COMO VAZIO PARA PARAMETRO DE EMPRESTIMO, LIMPANDO DATAS E O NOME DO USUARIO
                arquivo = fopen("dados.dat", "rb+");
                if(arquivo != NULL ){
                    system("cls");
                    cout << "Digite o codigo do livro que deseja devolver: ";
                    cin >> cod_E;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pos = -1;
                        while(!feof(arquivo)){
                            fread(&livro, sizeof(struct livros), 1, arquivo);
                            pos++;
                            if(cod_E == livro.codigo){
                                fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                                //COMANDO PARA INSERIR ESPAÇOS VAZIOS DENTRO DO CHAR
                                strcpy(livro.emp.data_emp, "");
                                strcpy(livro.emp.dat_dev, "");
                                strcpy(livro.emp.usuario, "");
                                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                                break;
                            }
                        }
                    fclose(arquivo);
                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 6:
                //CONSULTA DE LIVRO ESPECIFICO, DE ACORDO COM O CODIGO VAI PERCORRER O ARQUIVO
                //E RETORNAR AS INFORMAÇÕES DAQUELE QUE TEM O CODIGO IGUAL AO QUE O USUARIO DIGITOU
                arquivo = fopen("dados.dat", "rb");
                if(arquivo != NULL ){
                    system("cls");
                    cout << "Digite o codigo do livro que deseja pesquisar: ";
                    cin >> cod_E;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    while(!feof(arquivo)){
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                        if(cod_E == livro.codigo){
                            cout << "O codigo e:" << livro.codigo << endl;
                            cout << "A area do livro e: " << livro.area << endl;
                            cout << "O titulo e: " << livro.titulo << endl;
                            cout << "Os autor(es) sao: " << livro.autores << endl;
                            cout << "O livro faz parte da editora: " << livro.editora << endl;
                            cout << "E tem cerca de " << livro.paginas << " paginas" << endl;
                            cin.get();
                            break;
                        }
                    }
                    fclose(arquivo);
                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 7:
            //LISTAGEM DE LIVROS, APENAS VERIFICAR AQUELES QUE TEM A DATA DE EMPRESTIMO VAZIA
            //SE A DATA DE EMPRESTIMO ESTIVER VAZIA O LIVRO ESTÁ DISPONIVEL, LOGO SERÁ LISTADO
                arquivo = fopen("dados.dat", "rb");
                if(arquivo != NULL ){
                    system("cls");
                    cout << "Essa é a lista de todos os livros disponiveis: " << endl;
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    while(!feof(arquivo)){
                        if(strcmp(livro.emp.data_emp, "") == 0){
                            cout << "O codigo e: " << livro.codigo << endl;
                            cout << "A area do livro e: " << livro.area << endl;
                            cout << "O titulo e: " << livro.titulo << endl;
                            cout << "Os autor(es) sao: " << livro.autores << endl;
                            cout << "O livro faz parte da editora: " << livro.editora << endl;
                            cout << "E tem cerca de " << livro.paginas << " paginas" << endl;
                            cout << "---------------------------------------------------" << endl;
                        }
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    
                    fclose(arquivo);
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 8:
                
                arquivo = fopen("dados.dat", "rb");
                if(arquivo != NULL ){
                    system("cls");
                    //FUNCAO FREAD PARA LER O ARQUIVO, LIVRO POR LIVRO, VAI LER O ARQUIVO TODO, DO TAMANHO DA STRUCT LIVROS
                    //1 LEITURA POR VEZ, E O POR ULTIMO O PONTEIRO
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    //FEOF testa quando chegar no final do arquivo, por isso a !
                    // para continuar a repetição enquanto não chegar no final
                    while(!feof(arquivo)){
                        cout << "Codigo: " << livro.codigo << endl;
                        cout << "Area: " << livro.area << endl;
                        cout << "Titulo: " << livro.titulo << endl;
                        cout << "Autores: " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "N de Paginas: " << livro.paginas << endl;
                        cout << "--------------------------------------------" << endl;
                        fread(&livro, sizeof(struct livros), 1, arquivo);
                    }
                    fclose(arquivo);
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Erro ao abrir arquivo!";
                    cin.ignore();
                    cin.get();
                }

                break;
            case 9:
                cout << "Obrigado por usar a nossa biblioteca!";
                break;                 
            default:
                cout << "Informe uma opcao valida!";
                break;
        }
        //COMANDO PARA LIMPAR A TELA NO WINDOWS
        system("cls");
        //PARA LIMPAR NO LINUX E POSICIONAR O MOUSE RESPECTIVAMENTE
        // cout << "\e[2J" << "\e[0;0H"

    } while(opc_princ != 9);
}