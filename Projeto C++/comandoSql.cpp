#include "comandoSql.hpp"
using namespace std;

char *mensagemCMD;
sqlite3 *DataBaseSLQ;

int ResultadoPesquisa;

int callbackRows(void *NotUsed, int argc, char **argv, char **azColName)
{
  ResultadoPesquisa = atoi(argv[0]);

  return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  cout << "\t---------------- DADOS ------------------\n\n";
  for(i = 0 ; i < argc ; i++)
  {
    cout << azColName[i] << " = ";
    if(argv[i])
    {
      cout << argv[i] << "\n";
    }
    else
    {
      cout << "Valor nao encontrado\n";
    }
  }
  cout << endl;
  return 0;
}



void conectarDbUsuario()
{
  int conect = sqlite3_open("Usuarios.db", &DataBaseSLQ);
  if(conect != SQLITE_OK)
  {
    throw "\nErro ao conectar com bando de dados\n";
  }
  else
  {
    cout << "\nConexao com banco de dados realizada com sucesso\n\n";
  }
}

void desconectarDbUsuario()
{
  int desconect = sqlite3_close(DataBaseSLQ);
  if(desconect != SQLITE_OK)
  throw "Erro ao desconectar o banco de dados\n";
}

int executDbUsuario(string query)
{
  int resultado = sqlite3_exec(DataBaseSLQ, query.c_str(), callback, 0, &mensagemCMD);

  if(resultado != SQLITE_OK)
  {
    throw "\nErro na execucao da query\n";
  }
  else
  {
    cout << "Comando executado com sucesso" << endl;
  }

  if(ResultadoPesquisa == 0)
  {
    return -1;
  }
  else
  {
    return ResultadoPesquisa;
  }

}

int executDbUsuarioRows(string query)
{
  int resultado = sqlite3_exec(DataBaseSLQ, query.c_str(), callbackRows, 0, &mensagemCMD);

  if(resultado != SQLITE_OK)
  {
    throw "\nErro na execucao da query\n";
  }
  else
  {
    cout << "Comando executado com sucesso\n" << endl;
  }

  if(ResultadoPesquisa == 0)
  {
    return -1;
  }
  else
  {
    return ResultadoPesquisa;
  }

}
