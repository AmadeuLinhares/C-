#ifndef SERVICO_HPP_INCLUDED
#define SERVICO_HPP_INCLUDED


#include "comandoSql.hpp"
#include "dominios.hpp"
#include "controladoras.hpp"
#include "entidades.hpp"
#include "interface.hpp"

using namespace std;


class ServicoLogin:public CrltServicoLogin
{
public:
  string login(int opcao, string email, string senha);

  void criarUsuarioLeitor();

  void criarUsuarioDesenvolvedor();

  void criarUsuarioAdministrador();


};


class ServicoUsuariosLeitor:public CrltServicoUsuarioLeitor
{
private:
  int  resultadoQueryUsuario;
  string queryConsulta;
  string queryCria;
  string queryExclui;
  string queryAtualiza;
public:

    void opcaoEscolhidaLeitor(int opcao,string email);

    int consultarCadastroLeitor(string email);

    void excluirUsuarioLeitor(string email);

    void atualizarUsuarioLeitor(string email);

    void listNomeVocabularios();

    void listDadosVocabulario();

    void consultarTermo();

    void consultarDefinicaoTermo();

};


class ServicoUsuariosDesenvolvedor:public CrltServicoUsuarioDesenvolvedor
{
private:
  int  resultadoQueryUsuario;
  string queryConsulta;
  string queryCria;
  string queryExclui;
  string queryAtualiza;
public:

    void opcaoEscolhidaDesenvolvedor(int opcao,string email);

    int consultarCadastroDesenvolvedor(string email);

    void excluirUsuarioDesenvolvedor(string email);

    void atualizarUsuarioDesenvolvedor(string email);

    void listNomeVocabularios();

    void listDadosVocabulario();

    void consultarTermo();

    void consultarDefinicaoTermo();

    void cadastraDesenvolvedorVocControlado(string email);

    void criaTermo();

    void editarTermo();

    void excluirTermo();

    void criaDefinicao();

    void excluirDefinicao();

    void editarDefinicao();
};

class ServicoUsuariosAdministrador:public CrltServicoUsuarioAdministrador
{
private:
  int  resultadoQueryUsuario;
  string queryConsulta;
  string queryCria;
  string queryExclui;
  string queryAtualiza;

public:

   void consultarCadastroAdministrador(string email);

   void excluirUsuarioAdministrador(string email);

   void atualizarUsuarioAdministrador(string email);

   //----------------------------------
   void listNomeVocabularios();

   void listDadosVocabulario();

   void consultarTermo();

   void consultarDefinicaoTermo();

   void cadastraDesenvolvedorVocControlado(string email);

   void criaTermo();

   void editarTermo();

   void excluirTermo();

   void criaDefinicao();

   void excluirDefinicao();

   void editarDefinicao();
   //-----------------------------------------

   void opcaoEscolhidaAdministrador(int opcao,string email);

   void criarVocabulario(string email);

   void editarDefVocabulario();

   void editarIdiomaVoc();

   void excluirVocabulario();
};
#endif
