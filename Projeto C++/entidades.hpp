#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED
#include "dominios.hpp"
/**
*FUNCOES ENTIDADE LEITOR
*setNome
*getNome
*setSobrenome
*getSobrenome
*setEmail
*getEmail
*setSenha
*getSenha
*converteNome
*converteSenha
*validaSenha
*/

class Leitor {

private:

  Nome nome;
  Sobrenome sobrenome;
  Email email;
  Senha senha;

public:

    void setNome(const Nome &nome){
        this->nome = nome;
    }

    Nome getNome() const {
        return nome;
    }

    void setSobrenome(const Sobrenome &sobrenome)
    {
      this->sobrenome = sobrenome;
    }

  Sobrenome getSobrenome()
   {
     return sobrenome;
   }

   void setEmail(const Email &email)
  {
    this->email = email;
  }

  Email getEmail()
 {
   return email;
 }

 void setSenha(const Senha &senha)
{
  this->senha = senha;
}

Senha getSenha()
{
 return senha;
}

string converteNome(string nome)
{
 for(int i = 0; i<nome.length(); i++)
 {
   nome[i] = toupper(nome[i]);
 }

 return nome;
}

string converteSenha(string senha)
{
 for(int i = 0; i<senha.length(); i++)
 {
   senha[i] = toupper(senha[i]);
 }

 return senha;
}

void validaSenha(string senha, string nome)
{
 string senhaConvertida = converteSenha(senha);
 string nomeConvertido = converteNome(nome);
 int tamanhoNome;
 int i;
 tamanhoNome = nomeConvertido.length();
 string copiaNome;
 int posicaoNome = senhaConvertida.find(nomeConvertido);
 int t = posicaoNome;
 int verifica = 0;

 for(i = 0 ; i < tamanhoNome ; i++)
 {
   copiaNome[i] = senhaConvertida[t];
   t++;
 }

 for(i = 0 ; i < tamanhoNome ; i++)
 {

   if(copiaNome[i] == nomeConvertido[i])
   {
     verifica++;
   }
 }

 if(verifica == tamanhoNome)
 {
   throw"Senha invalida, seu nome esta contido na senha\n";
 }

 cout<<"Senha Validada com sucesso\n";

}

};


////////////////////////////////////////////////////////////////////////////

/**
*
*DECLARACAO da classe DESENVOLVEDOR
*Esta classe herda a classe leitor porem com um atributo a mais
*O atributo adicionado nessa classe é um objeto do tipo Data
*
*/

/**
*FUNCOES ENTIDADE DESENVOLVEDOR
*setData
*getData
*/

class Desenvolvedor:public Leitor{
private:

  Data data;

public:
  void setData(const Data &data)
  {
    this->data = data;
  }
  Data getData()
  {
    return data;
  }
};


/**
*DECLARACAO da classe ADMINISTRADOR
*Esta classe herda todos os atributos da classe DESENVOLVEDOR que por consequencia herda os atributos
*da classe LEITOR
*Possui dois novo atributos: Telefone e Endereço que são dois objetos
*/

/**
*FUNCOES ENTIDADE ADMINISTRADOR
*setTelefone
*getTelefone
*setEndereco
*getEndereco
*/

class Administrador:public Desenvolvedor{
private:

  Telefone telefone;
  Endereco endereco;

public:

  void setTelefone(const Telefone &telefone)
  {
    this->telefone = telefone;
  }
  Telefone getTelefone()
  {
    return telefone;
  }

  void setEndereco(const Endereco &endereco)
  {
    this->endereco = endereco;
  }

  Endereco getEndereco()
  {
    return endereco;
  }

};


/**
*DECLARACAO da classe VocabularioControlado
*Essa classe possui os atributos que sao objetos: Nome, Data
*Ela diferente das outras possui um novo atributo que nao e um objeto chamado de Idioma
*/

/**
*FUNCOES ENTIDADE VOCABULARIO CONTROLADO
*setNome
*getNome
*setIdioma
*getIdioma
*setData
*getData
*/

class VocabularioControlado{
private:

  Nome nome;
  Idioma idioma;
  Data data;

public:

  void setNome(const Nome &nome)
  {
    this->nome = nome;
  }
  Nome getNome()
  {
    return nome;
  }

  void setIdioma(const Idioma &idioma)
  {
    this->idioma = idioma;
  }
  Idioma getIdioma()
  {
    return idioma;
  }

  void setData(const Data &data)
  {
    this->data = data;
  }
  Data getData()
  {
    return data;
  }

};



/**
*DECLARACAO da classe Termo
*Essa classe possui os atributos que sao objetos: Nome, Data
*Ela diferente das outras possui um novo atributo que nao e um objeto chamado de classeTermo
*/

/**
*FUNCOES ENTIDADE TERMO
*setNome
*getNome
*setClasseTermo
*getClasseTermo
*setData
*getData
*/

class Termo{
private:

  Nome nome;
  string classeDeTermo;
  Data data;

public:

  void setNome(const Nome &nome)
  {
    this->nome = nome;
  }
  Nome getNome()
  {
    return nome;
  }

  void setClasseDeTermo(string classeDeTermo)
  {
    this->classeDeTermo = classeDeTermo;
  }

  string getClasseDeTermo()
  {
    return classeDeTermo;
  }

  void setData(const Data &data)
  {
    this->data = data;
  }

  Data getData()
  {
    return data;
  }

};

/**
*DECLARACAO da classe DEFINICAO
*Essa classe possui os atributos que sao objetos: Data
*Ela diferente das outras possui um novo atributo que nao e um objeto chamado de textoDeDefinicao
*/

/**
*FUNCOES ENTIDADE DEFINICAO
*setTextoDeDefinicao
*getTextoDeDefinicao
*setData
*getData
*/

class Definicao{
private:

string textoDeDefinicao;
Data data;

public:

void setTextoDeDefinicao(string textoDeDefinicao)
{
  this->textoDeDefinicao = textoDeDefinicao;
}
string getTextoDeDefinicao()
{
  return textoDeDefinicao;
}

void setData(const Data &data)
{
  this->data = data;
}
Data getData()
{
  return data;
}

};
















#endif // ENTIDADES_H_INCLUDED
