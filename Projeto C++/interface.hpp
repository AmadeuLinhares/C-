#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED


class CrltApresentacaoLogin
{
public:

  virtual int menu() = 0;

  virtual ~CrltApresentacaoLogin(){}
};


class CrltServicoLogin
{
public:

  virtual string login(int opcao,string email,string senha) = 0;

  virtual void criarUsuarioLeitor() = 0;

  virtual void criarUsuarioDesenvolvedor() = 0;

  virtual void criarUsuarioAdministrador() = 0;


  ~CrltServicoLogin(){}
};

class CrltApresentacaoUsuario
{
public:
  virtual int opcaoLeitor() = 0;

  virtual int opcaoDesenvolvedor() = 0;

  virtual int opcaoAdministrador() = 0;

  ~CrltApresentacaoUsuario(){}
};


class CrltServicoUsuarioLeitor
{
public:

virtual int consultarCadastroLeitor(string email) = 0;

virtual void excluirUsuarioLeitor(string email) = 0;

virtual void atualizarUsuarioLeitor(string email) = 0;

virtual void listNomeVocabularios() = 0;

virtual void listDadosVocabulario() = 0;

virtual void consultarTermo() = 0;

virtual void consultarDefinicaoTermo() = 0;


  virtual ~CrltServicoUsuarioLeitor(){}
};


class CrltServicoUsuarioDesenvolvedor
{
public:

virtual int consultarCadastroDesenvolvedor(string email) = 0;

virtual void excluirUsuarioDesenvolvedor(string email) = 0;

virtual void atualizarUsuarioDesenvolvedor(string email) = 0;

virtual void listNomeVocabularios() = 0;

virtual void listDadosVocabulario() = 0;

virtual void consultarTermo() = 0;

virtual void consultarDefinicaoTermo() = 0;

virtual void cadastraDesenvolvedorVocControlado(string email) = 0;

virtual void criaTermo() = 0;

virtual void editarTermo() = 0;

virtual void excluirTermo() = 0;

virtual void criaDefinicao() = 0;

virtual void excluirDefinicao() = 0;

virtual void editarDefinicao() = 0;

  virtual ~CrltServicoUsuarioDesenvolvedor(){}
};

class CrltServicoUsuarioAdministrador
{
public:

  virtual void consultarCadastroAdministrador(string email) = 0;

  virtual void excluirUsuarioAdministrador(string email) = 0;

  virtual void atualizarUsuarioAdministrador(string email) = 0;
//----------------------------------
  virtual void listNomeVocabularios() = 0;

  virtual void listDadosVocabulario() = 0;

  virtual void consultarTermo() = 0;

  virtual void consultarDefinicaoTermo() = 0;

  virtual void cadastraDesenvolvedorVocControlado(string email) = 0;

  virtual void criaTermo() = 0;

  virtual void editarTermo() = 0;

  virtual void excluirTermo() = 0;

  virtual void criaDefinicao() = 0;

  virtual void excluirDefinicao() = 0;

  virtual void editarDefinicao() = 0;
//-----------------------------------------
  virtual void criarVocabulario(string email) = 0;

  virtual void editarDefVocabulario() = 0;

  virtual void editarIdiomaVoc() = 0;

  virtual void excluirVocabulario() = 0;
};

#endif
