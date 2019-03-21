#ifndef CONTROLADORAS_HPP_INCLUDED
#define CONTROLADORAS_HPP_INCLUDED

#include "servico.hpp"
#include "dominios.hpp"
#include <stdexcept>
#include <iostream>
#include "interface.hpp"
using namespace std;

/**
* Parte do trabalho que possui a declaracao de duas classes, a primeira sendo a ControladoraApresentacao que herda os metodos da classe InterfaceApresentacao e a segunda sendo ControladoraUsuario que herda os
*metodos da classe InterfaceApresentacaoUsuario
*/

//--------------PRIMEIRA PARTE DO TRABALHO-------------------//

class ControladoraApresentacao:public CrltApresentacaoLogin
{
public:

  int menu();
};

//--------------PRIMEIRA PARTE DO TRABALHO-------------------//



class ControladoraApresentacaoUsuario:public CrltApresentacaoUsuario
{
public:
  int opcaoLeitor();
  int opcaoDesenvolvedor();
  int opcaoAdministrador();
};

#endif
