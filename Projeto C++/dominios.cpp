#include "dominios.hpp"

/**
*funcoes da classe NOME
*setNome
*getNome
*verificaNome
*/

void Nome::setNome(string nome)
{
    verificaNome(nome);
    this->nome = nome;

}

string Nome::getNome()
{
  return this->nome;
}

// Função de validação do nome //
void Nome::verificaNome(string nome)
{
  int testeMaiuscula = nome[0];
  int tamanhoNome = nome.length();
  int contador;

  if(testeMaiuscula < 65 || testeMaiuscula > 90)
  {
    throw "\nErro: A primeira letra do nome deve ser maiuscula\n\n";
  }
  if(tamanhoNome > 20)
  {
    throw "\nErro: Quantidade de caracteres superior ao permitido\n\n";
  }
  for(contador = 0 ; contador < tamanhoNome ; contador++)
  {
      int analisaLetra = nome[contador];
      if((analisaLetra < 65 || analisaLetra > 90) && (analisaLetra < 97 || analisaLetra > 122) )
      {
        throw "\nElementos que nao fazem parte do alfabeto estao presentes\n\n";
      }
  }

}


/**
*Funcoes da classe SOBRENOME
*setNome
*getNome
*verificaNome
*/

void Sobrenome::setSobrenome(string sobrenome)
{

    vereficaSobrenome(sobrenome);
    this->sobrenome = sobrenome;

}

string Sobrenome::getSobrenome()
{
  return this->sobrenome;
}

// Função de validação do sobrenome //
void Sobrenome::vereficaSobrenome(string nome)
{
  int testeMaiuscula = nome[0];
  int tamanhoNome = nome.length();
  int contador;

  if(testeMaiuscula < 65 || testeMaiuscula > 90)
  {
    throw "Erro: A primeira letra do nome deve ser maiuscula\n\n";
  }
  if(tamanhoNome > 20)
  {
    throw "Erro: Quantidade de caracteres superior ao permitido\n\n";
  }
  for(contador = 0 ; contador < tamanhoNome ; contador++)
  {
      int analisaLetra = nome[contador];
      if((analisaLetra < 65 || analisaLetra > 90) && (analisaLetra < 97 || analisaLetra > 122) )
      {
        throw "Elementos que nao fazem parte do alfabeto estao presentes\n\n";
      }
  }
}


/**
*Funcoes da classe Telefone
*setTelefone
*getTelefone
*vereficaTelefone
*/

void Telefone::setTelefone(string telefone)
{

    vereficaTelefone(telefone);
    this->telefone = telefone;

}

string Telefone::getTelefone()
{
  return this->telefone;
}

// Função verefica Telefone //
void Telefone::vereficaTelefone(string numero)
{
  int tamanhoNome = numero.length();
  int contador;
  int armazenaCaracter;

  if(tamanhoNome > 13)
  {
    throw "Erro: Numero de telefone invalido\n\n";
  }

  for(contador = 0 ; contador < tamanhoNome ; contador++)
  {
      armazenaCaracter = numero[contador];
      if(numero[contador] == ' ' || numero[contador] == '-')
      {
          contador = contador + 1;
          armazenaCaracter = numero[contador];
      }

      if(armazenaCaracter < 48 || armazenaCaracter > 57)
        {
          cout<<numero[contador]<<"\n";
          throw "Erro: Numero de telefone invalido\n\n";
        }
    }
 }


/**
*Funcoes da classe ENDEREÇO
*setEndereco
*getEndereco
*verificaEndereco
*/

void Endereco::setEndereco(string endereco)
{

    verificaEndereco(endereco);
    this->endereco = endereco;

}

string Endereco::getEndereco()
{
  return this->endereco;
}

// Função que valida o Endereço //
void Endereco::verificaEndereco(string endereco)
{
  int tamanhoEndereco = endereco.length();
  int contador;
  int armazenaCaracterInt;
  char armazenaCaracter;

  if(tamanhoEndereco > 20)
  {
    throw "Erro: Tamanho do endereço invalido\n\n";
  }

  if(endereco[0] == ' ' || endereco[tamanhoEndereco - 1] == ' ')
  {
    throw "Erro: Atenção, o endereço digitado não deve começar ou terminar com espaços em branco\n\n";
  }

  //for para verificar se todas as letras sao pertencentes ao alfabeto
  for(contador = 0 ; contador < tamanhoEndereco ; contador++)
  {
      armazenaCaracterInt = endereco[contador];
      if(armazenaCaracterInt == 32)
      {

      }
      else
      {
        if((armazenaCaracterInt < 65 || armazenaCaracterInt > 90) && (armazenaCaracterInt < 97 || armazenaCaracterInt > 122))
        {
          cout<<endereco[contador]<<" ///";
          throw "Erro: Endereço invalido\n\n";
        }
      }
  }

  //for para verificar se possui dois ou mais espaços em branco em sequencia
  for(contador = 0 ; contador < tamanhoEndereco ; contador++)
  {
    armazenaCaracter = endereco[contador];

    if(armazenaCaracter == ' ')
    {
      if(endereco[contador + 1] == ' ')
      {
        throw "Erro: Espaços sequenciais encontrados no endereço\n\n";
      }
    }
  }

}


//Funcoes da classe Data

void Data::setData(string data)
{

    verificaData(data);
    this->data = data;

}

string Data::getData()
{
  return this->data;
}

void Data::verificaData(string data)
{
  int tamanho = data.length();
  if(tamanho > 10)
  {
    throw"Erro - Data Invalida\n";
  }

  //verifica mês
  int dia1 = data[0];
  int dia2 = data[1];
  int mes1 = data[3];
  int mes2 = data[4];
  int ano1 = data[6];
  int ano2 = data[7];
  int ano3 = data[8];
  int ano4 = data[9];
  char teste1 = data[2];
  char teste2 = data[5];

  if(dia1 > 51 || dia2 > 57)
  {
    throw"Erro - Data Invalida\n";
  }

  if( (mes1 > 49 || mes2 > 50) && (mes1 > 48 || mes2 > 57)  )
  {
    throw"Erro - Data Invalida\n";
  }

  if( ano1 == 50 )
  {
    if( (ano2 != 48) || (ano3 > 57) || (ano4 > 57))
    {
      throw"Erro - Data Invalida\n";
    }
  }

  if(ano1 == 49)
  {
    if( (ano2 != 57) || (ano3 < 48) || (ano4 < 48))
    {
      throw"Erro - Data Invalida\n";
    }
  }


  if( (teste1 != '/') || ( teste2 != '/') )
  {
    throw"Erro - Data Invalida\n";
  }

}


//Funcoes da classe Email

void Email::setEmail(string email)
{
  verificaEmail(email);
  this->email = email;

}

string Email::getEmail()
{
  return this->email;
}

void Email::verificaEmail(string email)
{
  int tamanhoEmail = email.length();
  int verifica = 0;
  int i,z;
  char auxiliar;
  int teste = 0;
  int guardaPosicao;

  //verifica se o primeiro nem o ultimo caracter é um ponto
  for(i = 0 ; i < tamanhoEmail ; i++)
  {
    if(email[i] == '@')
    {
      guardaPosicao = i;
    }

  }

  if( (email[0] == '.') || (email[guardaPosicao - 1] == '.') || (email[guardaPosicao + 1] == '-') || (email[tamanhoEmail - 1] == '-') )
  {
    throw"\nErro: Formato de Email Invalido\n";

  }

  //verifica se existe @ no dominio
  for(i = 0 ; i < tamanhoEmail ; i++)
  {
    if(email[i] == '@')
    {
      verifica = 1;
    }

  }

  if(verifica != 1)
  {
    throw"\nErro: Formato de Email Invalido\n";

  }

  //Verifica se existe letras no dominio
  for(i = 0 ; i < tamanhoEmail ; i++)
  {
    if(email[i] == '@')
    {
      z = i;
      while(z < tamanhoEmail)
      {
        if(isalpha(email[z]))
        {
          teste = 1;
        }
        z++;
      }
    }
  }

  if(teste == 0)
  {
    throw"\nErro: Formato de Email Invalido\n";

  }

}

//Funcoes da classe Senha

void Senha::setSenha(string senha, Nome *nome)
{

    validaSenha(senha,nome->getNome());
    this->senha = senha;

}

string Senha::getSenha()
{
  return this->senha;
}


string Senha::converteNome(string nome)
{
 for(int i = 0; i<nome.length(); i++)
 {
   nome[i] = toupper(nome[i]);
 }

 return nome;
}

string Senha::converteSenha(string senha)
{
 for(int i = 0; i<senha.length(); i++)
 {
   senha[i] = toupper(senha[i]);
 }

 return senha;
}

void Senha::validaSenha(string senha, string nome)
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
   throw"\nSenha invalida, seu nome esta contido na senha\n";
 }

 cout<<"\nSenha Validada com sucesso\n";

}


//Funcoes da classe Texto de Definicao

void Texto::setTexto(string texto)
{
  verificaTexto(texto);
  this->texto = texto;
}

string Texto::getTexto()
{
  return this->texto;
}

void Texto::verificaTexto(string texto)
{
  int tamanho;
  tamanho = texto.length();
  if(tamanho > 30)
  {
    throw"Erro: Texto Invalido\n";
  }
}

//Funcoes da classe Idioma

void Idioma::setIdioma(string idioma)
{
  verificaIdioma(idioma);
  this->idioma = idioma;
}

string Idioma::getIdioma()
{
  return this->idioma;
}

void Idioma::verificaIdioma(string idioma)
{
  if( (idioma != "ENG") && (idioma != "FRA") && (idioma != "GER") && (idioma != "ITA") && (idioma != "POR") && (idioma != "SPA") )
  {
    throw"Erro: Idioma Invalido\n Formato correto para Idioma: ENG / FRA / ITA / POR\n Por favor escolha um dos idiomas listados acima\n";
  }

}

//Funcoes da classe - Classe de Termo

void ClasseTermo::setTermo(string termo)
{
  verificaTermo(termo);
  this->termo = termo;
}

string ClasseTermo::getTermo()
{
  return this->termo;
}

void ClasseTermo::verificaTermo(string termo)
{
  if((termo != "PT") && (termo != "NP"))
  {
    throw"Erro: Termo Invalido\n";
  }
}
