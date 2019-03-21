#include "controladoras.hpp"


//--------------PRIMEIRA PARTE DO TRABALHO-------------------//
/**
*Primeiramente temos o metodo validar da classe ControladoraApresentacaoUsuario. Esse metodo pede um nome, e-mail e senha do usuario do programa, jogando esses informacoes dentro de objetos criados ao inicio do  metodo
*Colocado dentro de um while, o usuario do pode logar se suas informacoes bateram com as Triggers de informacoes, existindo uma para cada tipo de usuario possivel do sistema (Leitor, desenvolvedor e administrador)
*Se as informacoes foram colocadas corretamente, o metodo ira retornar o e-mail digitado pelo usuario, onde de acordo com esse e-mail retornado para o main, o programa ira identificar qual o tipo de Usuario
*e criar os devidos objetos para cada um deles.
*
*O proximo metodo se chama opcaoLeitor(), onde esse metodo ira mostrar as opcoes para o usurio que faça o login como Leitor no sistema. O metodo consiste em um while que mostra as opcoes do sistema e so saira do while quando o
*usuario escolher uma opcao valida. Esse numero de opcao sera armazenado em uma variavel e retornado para a funcao main, onde sera aproveitado em outro metodo que veremos na aba das Stubs.cpp
*
*O proximo metodo se chama opcaoDesenvolvedor(), onde esse metodo ira mostrar as opcoes para o usurio que faça o login como Desenvolvedor no sistema. O metodo consiste em um while que mostra as opcoes do sistema e so saira do while quando o
*usuario escolher uma opcao valida. Esse numero de opcao sera armazenado em uma variavel e retornado para a funcao main, onde sera aproveitado em outro metodo que veremos na aba das Stubs.cpp
*
*O proximo metodo se chama opcaoAdministrador(), onde esse metodo ira mostrar as opcoes para o usurio que faça o login como Administrador no sistema. O metodo consiste em um while que mostra as opcoes do sistema e so saira do while quando o
*usuario escolher uma opcao valida. Esse numero de opcao sera armazenado em uma variavel e retornado para a funcao main, onde sera aproveitado em outro metodo que veremos na aba das Stubs.cpp
*/

int ControladoraApresentacao::menu()
{
  int opcao;
  while(true)
  {
    cout <<    "\n\t\t Vocabulario Controlado "   <<"\n"<<endl;
    cout << "\t1- Logar como Leitor\n";
    cout << "\t2- Logar como Desenvolvedor\n";
    cout << "\t3- Logar como Administrador\n";
    cout << "\t4- Criar conta\n\n";

    cout << "\t*Digite a opcao escolhida: ";
    cin >> opcao;

    if((opcao != 1) && (opcao != 2) && (opcao != 3) && (opcao != 4))
    {
      cout << "\n\t\tOpcao invalida, tente novamente\n\n";
    }
    else
    {
      break;
    }
  }

  return opcao;
}


//--------------PRIMEIRA PARTE DO TRABALHO-------------------//

int ControladoraApresentacaoUsuario::opcaoLeitor()
{
  int entrada;
  int aux = 0;
  while(aux == 0)
  {
      cout << "Opções para Usuario Leitor\n" << endl;
      cout << "1- Apresentar dados do Usúario\n";
      cout << "2- Editar dados do Usuario\n";
      cout << "3- Excluir Conta\n";
      cout << "4- Listar nomes dos vocabularios controlados\n";
      cout << "5- Dados do vocabulario controlado\n";
      cout << "6- Consultar Termo\n";
      cout << "7- Consultar definição de termos\n\n";
      cout << "Digite a opçāo desejada: ";
      cin >> entrada;
      cout << "\n";
      if(entrada < 1 || entrada > 7)
      {
        cout << "Erro, Opçao invalida.....\n" << endl;
        cout << "Retornando para o Menu de escolhas \n" << endl;
      }
      else
      {
        aux = 1;
      }
  }
  return entrada;
}

int ControladoraApresentacaoUsuario::opcaoDesenvolvedor()
{
  int entrada;
  int aux = 0;
  while(aux == 0)
  {
      cout << "Opções para Usuario Desenvolvedor\n" << endl;
      cout << "1- Apresentar dados do Usúario\n";
      cout << "2- Editar dados do Usuario\n";
      cout << "3- Excluir Conta\n";
      cout << "4- Listar nomes dos vocabularios controlados\n";
      cout << "5- Dados do vocabulario controlado\n";
      cout << "6- Consultar Termo\n";
      cout << "7- Consultar definição de termos\n";
      cout << "8- Cadastro desenvolvedor de vocabulario controlado\n";
      cout << "9- Criar Termo\n";
      cout << "10- Editar Termo\n";
      cout << "11- Excluir Termo\n";
      cout << "12- Criar definicao para termo\n";
      cout << "13- Excluir definicao de termo\n";
      cout << "14- Editar definicao de termo \n\n";
      cout << "Digite a opçāo desejada: ";
      cin >> entrada;
      cout << "\n";
      if(entrada < 1 || entrada > 14)
      {
        cout << "Erro, Opçao invalida.....\n" << endl;
        cout << "Retornando para o Menu de escolhas \n" << endl;
      }
      else
      {
        aux = 1;
      }
  }
  return entrada;
}






int ControladoraApresentacaoUsuario::opcaoAdministrador()
{
  int entrada;
  int aux = 0;
  while(aux == 0)
  {
      cout << "Opções para Usuario Desenvolvedor\n" << endl;
      cout << "1- Apresentar dados do Usúario\n";
      cout << "2- Editar dados do Usuario\n";
      cout << "3- Excluir Conta\n";
      cout << "4- Listar nomes dos vocabularios controlados\n";
      cout << "5- Dados do vocabulario controlado\n";
      cout << "6- Consultar Termo\n";
      cout << "7- Consultar definição de termos\n";
      cout << "8- Cadastro desenvolvedor de vocabulario controlado\n";
      cout << "9- Criar Termo\n";
      cout << "10- Editar Termo\n";
      cout << "11- Excluir Termo\n";
      cout << "12- Criar definicao para termo\n";
      cout << "13- Excluir definicao de termo\n";
      cout << "14- Editar definicao de termo \n";
      cout << "15- Criar Vocabulario controlado\n";
      cout << "16- Editar definicao de vocabulario controlado\n";
      cout << "17- Alterar idioma de vocabulario controlado\n";
      cout << "18- Excluir Vocabulario Controlado\n";
      cout << "Digite a opçāo desejada: ";
      cin >> entrada;
      cout << "\n";
      if(entrada < 1 || entrada > 18)
      {
        cout << "Erro, Opçao invalida.....\n" << endl;
        cout << "Retornando para o Menu de escolhas \n" << endl;
      }
      else
      {
        aux = 1;
      }
  }
  return entrada;
}
