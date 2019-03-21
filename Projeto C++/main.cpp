// Exemplos desenvolvidos para ilustrar a sintaxe da linguagem.

#include <stdexcept>
#include <iostream>
#include <string>

#include "dominios.hpp"
#include "controladoras.hpp"


using namespace std;

/**
*O main primeiramente possui cinco variaveis, sendo a primeira chamada login, na qual recebe o email digitado pelo usuario. Outras tres variaveis que serao comparadas com a login, se a variavel
*loginLeitor for igual a login entao o usuario entrou como um leitor, se login for igual a variavel loginDesenvoldedor entao o usuario entrou como desenvolvedor, se login for igual a
*loginAdministrador entao o usuario logou como administrador e se nao for nenhuma dessas ela sera igual a variavel erroLogin e o programa sera encerrado.
*
*Dependendo da conta que o usuario entre no programa, objetos desta conta serao criados quando o seu tipo de conta for reconhecido pelos ifs. A duas variaveis do tipo inteiro no main.
*A primeira chamada de seleciona recebe a opcao escolhida pelo usuario nas opcoes de servico do sistema. Essa variavel e passada para o metodo que ira chamar a opcao escolhida, e entao a variavel progress
*sera acionada. Se o usuario quiser continuar com a execucao do programa ele ira escolher uma opcao e essa opcao sera armazenada pela variavel progress que ira informar o main da escolhar feita, e o mesmo
*processo ocorre se o usuario quiser encerrar o programa.
*/

int main()
{

int opcaoMenu,opcaoUsuario;
string email,senha,resultado;
CrltApresentacaoLogin *menu = new ControladoraApresentacao();
string loga = "createUser";
int progress;

  try
  {
      opcaoMenu = menu->menu();

      if(opcaoMenu != 4)
      {
        cout << "E-mail: ";
        cin >> email;

        cout << "Senha: ";
        cin >> senha;

        CrltServicoLogin *logar = new ServicoLogin();

        resultado = logar->login(opcaoMenu,email,senha);

      }
      else
      {

        CrltServicoLogin *logar = new ServicoLogin();

        resultado = logar->login(opcaoMenu,loga,loga);
      }

    if(resultado == "leitor")
    {
      CrltApresentacaoUsuario *userLogado = new ControladoraApresentacaoUsuario();
      ServicoUsuariosLeitor *servicoLeitor = new ServicoUsuariosLeitor();
      opcaoUsuario = userLogado->opcaoLeitor();
      servicoLeitor->opcaoEscolhidaLeitor(opcaoUsuario,email);
      while(true)
      {
        cout << "\t-> Para ir ao menu principal, digite 1;\n";
        cout << "\t-> Para encerrar o programa, digite 0;\n";
        cout << "Opcao desejada: ";
        cin >> progress;

        if(progress == 1)
        {
          opcaoUsuario = userLogado->opcaoLeitor();
          servicoLeitor->opcaoEscolhidaLeitor(opcaoUsuario,email);
        }
        else
        {
          if(progress == 0)
          {
            break;
          }
          else
          {
            cout << "Opcao digitada invalida...\n O programa sera encerrado.\n";
          }
        }
      }
    }
    else
    {
      if(resultado == "desenvolvedor")
      {
        CrltApresentacaoUsuario *userLogado = new ControladoraApresentacaoUsuario();
        ServicoUsuariosDesenvolvedor *servicoDesenvolvedor = new ServicoUsuariosDesenvolvedor();
        opcaoUsuario = userLogado->opcaoDesenvolvedor();
        servicoDesenvolvedor->opcaoEscolhidaDesenvolvedor(opcaoUsuario,email);

        while(true)
        {
          cout << "\t-> Para ir ao menu principal, digite 1;\n";
          cout << "\t-> Para encerrar o programa, digite 0;\n";
          cout << "Opcao desejada: ";
          cin >> progress;

          if(progress == 1)
          {
            opcaoUsuario = userLogado->opcaoDesenvolvedor();
            servicoDesenvolvedor->opcaoEscolhidaDesenvolvedor(opcaoUsuario,email);
          }
          else
          {
            if(progress == 0)
            {
              break;
            }
            else
            {
              cout << "Opcao digitada invalida...\n O programa sera encerrado.\n";
            }
          }
        }

      }
      else
      {
        if(resultado == "administrador")
        {
          CrltApresentacaoUsuario *userLogado = new ControladoraApresentacaoUsuario();
          ServicoUsuariosAdministrador *servicoAdministrador = new ServicoUsuariosAdministrador();
          opcaoUsuario = userLogado->opcaoAdministrador();
          servicoAdministrador->opcaoEscolhidaAdministrador(opcaoUsuario,email);

          while(true)
          {
            cout << "\t-> Para ir ao menu principal, digite 1;\n";
            cout << "\t-> Para encerrar o programa, digite 0;\n";
            cout << "Opcao desejada: ";
            cin >> progress;

            if(progress == 1)
            {
              opcaoUsuario = userLogado->opcaoAdministrador();
              servicoAdministrador->opcaoEscolhidaAdministrador(opcaoUsuario,email);
            }
            else
            {
              if(progress == 0)
              {
                break;
              }
              else
              {
                cout << "Opcao digitada invalida...\n O programa sera encerrado.\n";
              }
            }
          }

        }
        else
        {
          cout << "\tErro, conta digitada nao consta em nosso banco de dados...\n";
          cout << "\tEncerrando programa....\n";
          cout << "\t\tPrograma Encerrado\n\n";
        }
      }
    }


}
catch(const char *erro)
{
  cout << erro << endl;
}
return 0;
}
