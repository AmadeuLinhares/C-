#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

/**
*DECLARACAO CLASSE NOME
*/
class Nome{
private:
  string nome;
  void verificaNome(string nome);
public:

  void setNome(string nome);
  string getNome();
};

/**
*DECLARACAO CLASSE SOBRENOME
*/

class Sobrenome{
private:

  string sobrenome;
  void vereficaSobrenome(string nome);

public:

  void setSobrenome(string sobrenome);
  string getSobrenome();

};

/**
*DECLARACAO CLASSE TELEFONE
*/

class Telefone{
private:

  string telefone;
  void vereficaTelefone(string numero);

public:

  void setTelefone(string telefone);
  string getTelefone();

};

/**
*DECLARACAO CLASSE ENDERECO
*/

class Endereco{
private:

  string endereco;
  void verificaEndereco(string endereco);

public:

  void setEndereco(string endereco);
  string getEndereco();

};


/**
*DECLARACAO CLASSE DATA
*/

class Data{
private:

  string data;

public:

  void setData(string data);
  string getData();
  void verificaData(string data);
};

/**
*DECLARACAO CLASSE E-MAIL
*/

class Email{
private:

  string email;

public:

  void setEmail(string email);
  string getEmail();
  void verificaEmail(string email);
};


/**
*DECLARACAO CLASSE SENHA
*/

class Senha{
private:

  string senha;

public:

  void setSenha(string senha,Nome *nome);
  string getSenha();
  string converteNome(string nome);
  string converteSenha(string senha);
  void validaSenha(string senha, string nome);

};


/**
*DECLARACAO CLASSE TEXTO DE DEFINICAO
*/

class Texto{
private:

  string texto;

public:

  void setTexto(string texto);
  string getTexto();
  void verificaTexto(string texto);
};



/**
*DECLARACAO CLASSE IDIOMA
*/

class Idioma{
private:

  string idioma;

public:

  void setIdioma(string idioma);
  string getIdioma();
  void verificaIdioma(string idioma);
};




/**
*DECLARACAO CLASSE - CLASSE DE TERMO
*/

class ClasseTermo{
private:

  string termo;

public:

  void setTermo(string termo);
  string getTermo();
  void verificaTermo(string termo);

};


#endif
