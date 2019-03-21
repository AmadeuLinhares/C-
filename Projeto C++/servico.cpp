#include "servico.hpp"

string ServicoLogin::login(int opcao, string email, string senha)
{
/**
* Implementacao da funcao login na qual recebe dois parametros, o primeiro e a opcao
* feita pelo usuario, podendo ser os numeros de um ate o quatro, cada um com sua
* respectiva funcao, os outros dois parametros sao o e-mail e senha que sao
* utilizados quando o usuario loga como leitor, desenvolvedor ou administrador,
* porem quando o usuario quer criar uma conta, esses parametros sao meramente ilustrativos
*/
  int resultado;
  string query;
  int escolhaConta;
  conectarDbUsuario();

  if(opcao == 1)
  {
    query = "select count(*) from Leitores where email='";
    query += email;
    query += "' and senha ='";
    query += senha;
    query += "';";
    resultado = executDbUsuarioRows(query);

    if(resultado != -1)
    {
      desconectarDbUsuario();
      return "leitor";
    }
  }

  if(opcao == 2)
  {
    query = "select count(*) from Desenvolvedores where email='";
    query += email;
    query += "' and senha ='";
    query += senha;
    query += "';";
    resultado = executDbUsuarioRows(query);

    if(resultado != -1)
    {
      desconectarDbUsuario();
      return "desenvolvedor";
    }
  }

  if(opcao == 3)
  {
    query = "select count(*) from Administradores where email='";
    query += email;
    query += "' and senha ='";
    query += senha;
    query += "';";
    resultado = executDbUsuarioRows(query);

    if(resultado != -1)
    {
      desconectarDbUsuario();
      return "administrador";
    }
  }

  if(opcao == 4)
  {
    while(true)
    {
      cout << "1 - Criar conta leitor\n";
      cout << "2 - Criar conta Desenvolvedor\n";
      cout << "3 - Criar conta Administrador\n\n";
      cout << "Selecione a opcao desejada: ";
      cin >> escolhaConta;

      if(escolhaConta == 1)
      {
        criarUsuarioLeitor();
        break;
      }
      else
      {
        if(escolhaConta == 2)
        {
          criarUsuarioDesenvolvedor();
          break;
        }
        else
        {
          if(escolhaConta == 3)
          {
            criarUsuarioAdministrador();
            break;
          }
          else
          {
            cout << "Opcao invalida, tente novamente...\n\n";
          }
        }
      }
    }
  }

  desconectarDbUsuario();
  return "erro";
}









//-------------------------------- LEITORES -----------------------------------------------
int ServicoUsuariosLeitor::consultarCadastroLeitor(string email)
{
  /**
  * Funcao consiste em receber o email do leitor que logou no sistema e com isso
  * executar uma query no qual os dados desse mesmo leitor serao apresentados
  * na tela
  */
  queryConsulta = "select * from Leitores where email= '";
  queryConsulta += email;
  queryConsulta += "';";
  conectarDbUsuario();

  cout << "\t\t------------- Dados do Usuario -----------------\n";

  resultadoQueryUsuario = executDbUsuario(queryConsulta);

  desconectarDbUsuario();

  return resultadoQueryUsuario;
}

void ServicoLogin::criarUsuarioLeitor()
{
  /**
  * Funcao para criar um novo usuario do tipo leitor. Primeiramente sao criados
  * objetos que fazem parte das informacoes que um leitor precisa disponibilizar para poder se cadastrar
  * no sistema, que sao eles: nome,sobrenome,email, senha. Cada uma dessas informacoes sera testada e
  * aprovada pelo sistema antes de serem jogadas dentro do banco de Dados
  * Feita a conexao com o DB, as informacoes sao pedidas e as validacoes devidamente realizadas
  * Feito isso uma query e montada para jogar as informacoes na tabela correspondente tipo de Cadastro
  * que foi realizado, nesse caso, do tipo leitor. Apos isso uma nova query e criada pesquisando pelo
  * email criado e se retornar 1, significa que o usuario foi criado com sucesso.
  */
  Nome *nome = new Nome();
  Sobrenome *sobrenome = new Sobrenome();
  Email *email = new Email();
  Senha *senha = new Senha();
  int consulta,recebe;
  string query;
  int resultado;
  string entrada;

  conectarDbUsuario();
  cin.ignore();
  while(true)
  {
    try
    {
      cout << "Nome: ";
      getline(cin, entrada);
      nome->setNome(entrada);

      cout << "Sobrenome: ";
      getline(cin, entrada);
      sobrenome->setSobrenome(entrada);

      cout << "Email: ";
      getline(cin, entrada);
      email->setEmail(entrada);
      query = "select count(*) from Leitores where email = '";
      query += email->getEmail();
      query += "';";
      resultado = executDbUsuarioRows(query);
      if(resultado != -1)
      {
        throw "Erro, email ja possui cadastro\n\n";
      }

      cout << "Senha: ";
      getline(cin, entrada);
      senha->setSenha(entrada,nome);

      break;

    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  query = "INSERT INTO Leitores (nome,sobrenome,email,senha) ";
  query += "VALUES ('";
  query += nome->getNome();
  query += "','";
  query += sobrenome->getSobrenome();
  query += "','";
  query += email->getEmail();
  query += "','";
  query += senha->getSenha();
  query += "');";

  recebe = executDbUsuario(query);

  query = "select count(*) from Leitores where email = '";
  query += email->getEmail();
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro ao criar usuario....\n\n";
  }
  else
  {
    throw "\t------------ Usuario Leitor criado com sucesso ------------\n";
  }

  desconectarDbUsuario();

}

void ServicoUsuariosLeitor::excluirUsuarioLeitor(string email)
{
  /**
  * Essa funcao recebe como parametro o email do leitor logado no sistema. Apos isso uma query e
  * montada para realizar a exclusao do cadastro, passando como parametro, o email recebido na funcao
  */
    int consulta,recebe;
    queryExclui = "delete from Leitores where email='";
    queryExclui += email;
    queryExclui +="';";

    consulta = consultarCadastroLeitor(email);

    if(consulta == -1)
    {
      throw "Erro, cadastro nao existe em nosso banco de dados\n";
    }

    conectarDbUsuario();
    recebe = executDbUsuario(queryExclui);
    desconectarDbUsuario();
}

void ServicoUsuariosLeitor::atualizarUsuarioLeitor(string email)
{
  /**
  * Essa funcao recebe com parametro o email do usuario logado no sistema. Ao executar essa Funcao
  * o usuario logado tera que editar todos os dados de seu cadastro, sem opcao de escolha, e os novos
  * dados tambem irao passar por uma verificacao antes de ocorrer a substituicao dos dados
  * Apos a validacao das informacoes, uma query e montada e com isso os novos dados sao armazenados
  * no banco de dados
  */

  Nome *nome = new Nome();
  Sobrenome *sobrenome = new Sobrenome();
  Email *emailAtualiza = new Email();
  Senha *senha = new Senha();
  //Leitor *leitor = new Leitor();
  string entrada;
  int recebe;
  while(true)
  {
      try
      {
        cout << "Nome: ";
        cin >> entrada;
        nome->setNome(entrada);
        //leitor->setNome(nome);

        cout << "Sobrenome: ";
        cin >> entrada;
        sobrenome->setSobrenome(entrada);

        cout << "Email: ";
        cin >> entrada;
        emailAtualiza->setEmail(entrada);

        cout << "Senha: ";
        cin >> entrada;
        senha->setSenha(entrada,nome);

        break;
      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

  queryAtualiza = "update Leitores set nome = '";
  queryAtualiza += nome->getNome();
  queryAtualiza += "',sobrenome = '";
  queryAtualiza += sobrenome->getSobrenome();
  queryAtualiza += "',email = '";
  queryAtualiza += emailAtualiza->getEmail();
  queryAtualiza += "',senha = '";
  queryAtualiza += senha->getSenha();
  queryAtualiza += "' where email = '";
  queryAtualiza += email;
  queryAtualiza += "';";

  conectarDbUsuario();
  recebe = executDbUsuario(queryAtualiza);
  desconectarDbUsuario();

}

void ServicoUsuariosLeitor::listNomeVocabularios()
{
  /**
  * Essa funcao acessa a tabela de vocabulario controlado, onde faz um select de todos os vocabularios
  * cadastrados e apresenta na tela para o usuario.
  */
  string queryList;
  int recebe;
  queryList = "select nomeVocabulario from Vocabulario_Controlado;";
  conectarDbUsuario();
  recebe = executDbUsuario(queryList);
  if(recebe == 0)
  {
    cout << "Erro ao executar query\n";
  }
  desconectarDbUsuario();

}

void ServicoUsuariosLeitor::listDadosVocabulario()
{
  /**
  * Nessa funcao o usuario precisa saber o que esta procurando. Para que ocorra corretamente o usuario
  * deve conhecer o nome do vocabulario que procura, passando assim quando for questionado pelo
  * programa. Passa esse nome, uma verificacao primaria e feita, para verificar se o vocabulario
  * realmente existe. Comprovando sua existencia, uma query e montada apresentando assim as informacoes
  * deste vocabulario
  */
  string nomeVocabulario;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do vocabulario desejado: ";
  cin >> nomeVocabulario;


  queryVerifica = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
  queryVerifica += nomeVocabulario;
  queryVerifica += "';";

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  if(recebe > 0)
      {
        queryVerifica = "select * from Vocabulario_Controlado where nomeVocabulario = '";
        queryVerifica += nomeVocabulario;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
  else
      {
        cout << "\nVocabulario Controlado nao consta em nosso banco de dados\n" << endl;
      }

      desconectarDbUsuario();
  }


  void ServicoUsuariosLeitor::consultarTermo()
  {
    /**
    * Nessa funcao o usuario tambem precisa saber o que esta procurando. O programa ira perguntar qual
    * termo que o usuario deseja consultar. Uma verificacao sera rodada para ver se o termo realmente
    * existe. Em caso positivo, os dados daquele termo serao apresentados na tela para o usuario
    */
    string nomeTermo;
    string queryVerifica;
    int recebe;

    cout << "Digite o nome do Termo que deseja consultar: ";
    cin >> nomeTermo;


    queryVerifica = "select count(*) from Termo where nome = '";
    queryVerifica += nomeTermo;
    queryVerifica += "';";

    conectarDbUsuario();
    recebe = executDbUsuarioRows(queryVerifica);

    if(recebe > 0)
        {
          queryVerifica = "select * from Termo where nome = '";
          queryVerifica += nomeTermo;
          queryVerifica += "';";
          recebe = executDbUsuario(queryVerifica);
        }
    else
        {
          cout << "Termo nao consta em nosso banco de dados\n" << endl;
        }

        desconectarDbUsuario();
    }

    void ServicoUsuariosLeitor::consultarDefinicaoTermo()
    {
      /**
      * Mais uma vez os termos da tabela precisam estar bem evidentes na mente de quem ira usar Essa
      * funcao. Primeiro o programa realiza o questionamento de qual termo o usuario deseja consultar
      * sua definicao. Apos isso uma verificacao ocorre a procura desse termo em duas tabelas juntas,
      * processo conhecido no SQL como inner join, para assim podermos validar a existencia do termo na
      * tabela Termo e na tabela Definicao. Tendo um resultado positivo nessa pesquisa, a tabela
      * Definicao sera acionada, procurando e mostrando as informacoes do termo em questao.
      */
      string nomeTermo;
      string queryVerifica;
      int recebe;

      cout << "Digite o nome do Termo no qual deseja consultar sua definicao: ";
      cin >> nomeTermo;


      queryVerifica = "select count(*) from Termo inner join Definicao on Termo.nome = '";
      queryVerifica += nomeTermo;
      queryVerifica += "' and Definicao.termos = '";
      queryVerifica += nomeTermo;
      queryVerifica += "';";

      cout << "QUERY: " <<  queryVerifica << endl;

      conectarDbUsuario();
      recebe = executDbUsuarioRows(queryVerifica);

      cout << "VALOR: " << recebe << endl;

      if(recebe > 0)
      {
        queryVerifica = "select texto from Definicao where termos = '";
        queryVerifica += nomeTermo;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
      else
      {
        cout << "Definicao para o termo " << nomeTermo << " nao foi encontrada" << endl;
      }

      desconectarDbUsuario();
   }

void ServicoUsuariosLeitor::opcaoEscolhidaLeitor(int opcao,string email)
{
  /**
  * Essa funcao e a funcao base para escolha de servico apresentada pelo menu. Cada if representa um
  * servico, e de acordo com o parametro recebido pela funcao, na qual o usuario escolhe a Funcao
  * desejada do sistema, esses if's sao acionados, e se necessario para o correto funcionamento das funcoes
  * o email tambem e passado.
  */
  if(opcao == 1)
  {
    int recebe;

    recebe = consultarCadastroLeitor(email);
    if(recebe != -1)
    {
      cout << "Usuario encontrado com sucesso\n";
    }
    else
    {
      cout << "Erro: Usuario nao consta em nosso banco de dados\n\n";
    }
  }

  if(opcao == 2)
  {
    atualizarUsuarioLeitor(email);
  }

  if(opcao == 3)
  {
    excluirUsuarioLeitor(email);
  }

  if(opcao == 4)
  {
    listNomeVocabularios();
  }

  if(opcao == 5)
  {
    listDadosVocabulario();
  }

  if(opcao == 6)
  {
    consultarTermo();
  }

  if(opcao == 7)
  {
    consultarDefinicaoTermo();
  }
}




//------------------------- SERVICO DESENVOLVEDORES ---------------------------//


int ServicoUsuariosDesenvolvedor::consultarCadastroDesenvolvedor(string email)
{
  /**
  * Utiliza uma query simples de pesquisa onde atraves do parametro passado pela funcao, consegue
  * exibir na tela os dados do desenvolvedor logado
  */
  queryConsulta = "select * from Desenvolvedores where email= '";
  queryConsulta += email;
  queryConsulta += "';";
  conectarDbUsuario();

  cout << "\t\t------------- Dados do Usuario -----------------\n";

  resultadoQueryUsuario = executDbUsuarioRows(queryConsulta);

  desconectarDbUsuario();

  return resultadoQueryUsuario;
}

void ServicoLogin::criarUsuarioDesenvolvedor()
{
  /**
  * Funcao responsavel pelo cadastramento de novos desenvolvedores no sistema. Primeiramente sao criados
  * instancias de objetos no qual esses objetos irao compor o cadastro do desenvolvedor. Apos isso, e pedido
  * para que o usuario digite as informacoes pedidas, e assim as mesmas passaram por um processo de validacao
  * feito o processo de validacao, essas informacoes finalmente sera gravadas no DB de desenvolvedores,
  * e apos essa gravacao uma query e executada em busca do novo membro, retornando assim o valor da pesquisa,
  * chegando a conclusao se o desenvolvedor foi criado com sucesso ou nao.
  */
    Nome *nome = new Nome();
    Sobrenome *sobrenome = new Sobrenome();
    Data *data = new Data();
    Email *email = new Email();
    Senha *senha = new Senha();
    Desenvolvedor *desenvolvedor = new Desenvolvedor();
    string entrada;
    string query;
    int resultado;
    cin.ignore();
    while(true)
    {
      try
      {
        cout << "Nome: ";
        getline(cin, entrada);
        nome->setNome(entrada);

        cout << "Sobrenome: ";
        getline(cin, entrada);
        sobrenome->setSobrenome(entrada);

        cout << "Data de Nascimento: ";
        getline(cin, entrada);
        data->setData(entrada);

        cout << "Email: ";
        getline(cin, entrada);
        email->setEmail(entrada);

        cout << "Senha: ";
        getline(cin, entrada);
        senha->setSenha(entrada,nome);

        break;

      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

    conectarDbUsuario();

    query = "insert into Desenvolvedores(nome,sobrenome,data,email,senha) ";
    query += "values('";
    query += nome->getNome();
    query += "','";
    query += sobrenome->getSobrenome();
    query += "','";
    query += data->getData();
    query += "','";
    query += email->getEmail();
    query += "','";
    query += senha->getSenha();
    query += "');";


    resultado = executDbUsuario(query);

    query = "select count(*) from Desenvolvedores where email = '";
    query += email->getEmail();
    query += "' and senha = '";
    query += senha->getSenha();
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado != -1)
    {
      throw "\t------------ Usuario desenvolvedor criado com sucesso ------------\n";
    }
    else
    {
      throw "Erro ao criar usuario...\n\n";
    }

    desconectarDbUsuario();

}

void ServicoUsuariosDesenvolvedor::excluirUsuarioDesenvolvedor(string email)
{
  /**
  * Atraves do parametro recebido pela funcao, uma query de delete e montada usando como criterio o email
  * passado no parametro para poder assim excluir a conta do desenvolvedor logado
  */
  int consulta,recebe;
  queryExclui = "delete from Desenvolvedores where email='";
  queryExclui += email;
  queryExclui +="';";

  consultarCadastroDesenvolvedor(email);

  if(consulta == 0)
  {
    throw "Erro, cadastro nao existe em nosso banco de dados\n";
  }

  cout << queryExclui << endl;

  conectarDbUsuario();
  recebe = executDbUsuario(queryExclui);
  desconectarDbUsuario();
}

void ServicoUsuariosDesenvolvedor::atualizarUsuarioDesenvolvedor(string email)
{
  /**
  * Nesse processo, similar ao do cadastro, todas as informacoes do desenvolvedor terao de ser atualizadas,
  * nem que seja para coloca-las iguais, porem irao mesmo assim passar por uma nova validacao antes de
  * serem gravadas no DB
  */
  Sobrenome *sobrenome = new Sobrenome();
  Email *emailAtualiza = new Email();
  Data *data = new Data();
  Senha *senha = new Senha();
  Nome *nome = new Nome();
  //Leitor *leitor = new Leitor();
  string entrada;
  int recebe;
  while(true)
  {
      try
      {
        cout << "Nome: ";
        cin >> entrada;
        nome->setNome(entrada);
        //leitor->setNome(nome);

        cout << "Sobrenome: ";
        cin >> entrada;
        sobrenome->setSobrenome(entrada);

        cout << "Data de Nascimento: ";
        cin >> entrada;
        data->setData(entrada);

        cout << "Email: ";
        cin >> entrada;
        emailAtualiza->setEmail(entrada);

        cout << "Senha: ";
        cin >> entrada;
        senha->setSenha(entrada,nome);

        break;
      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

  queryAtualiza = "update Leitores set nome = '";
  queryAtualiza += nome->getNome();
  queryAtualiza += "',sobrenome = '";
  queryAtualiza += sobrenome->getSobrenome();
  queryAtualiza += "',data = '";
  queryAtualiza += data->getData();
  queryAtualiza += "',email = '";
  queryAtualiza += emailAtualiza->getEmail();
  queryAtualiza += "',senha = '";
  queryAtualiza += senha->getSenha();
  queryAtualiza += "' where email = '";
  queryAtualiza += email;
  queryAtualiza += "';";

  conectarDbUsuario();
  recebe = executDbUsuario(queryAtualiza);
  desconectarDbUsuario();

  cout <<"QUERY: " << queryAtualiza << endl;
}


void ServicoUsuariosDesenvolvedor::listNomeVocabularios()
{
  /**
  * Lista todos os nomes dos vocabularios controlados ja cadastrados atraves da execucao de uma query
  */
  string queryList;
  int recebe;
  queryList = "select nomeVocabulario from Vocabulario_Controlado;";
  conectarDbUsuario();
  recebe = executDbUsuario(queryList);
  if(recebe == 0)
  {
    cout << "Erro ao executar query\n";
  }
  desconectarDbUsuario();
}

void ServicoUsuariosDesenvolvedor::listDadosVocabulario()
{
  /**
  * Primeiramente o nome do vocabulario controlado e pedido, e assim que colocado, uma pesquisa sera
  * feita no DB em busca desse nome. Se vocabulario realmente existir, uma query sera criada para
  * apresentar os dados desse vocabulario, se nao, a funcao caira no catch
  */
  string nomeVocabulario;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do vocabulario desejado: ";
  cin >> nomeVocabulario;


  queryVerifica = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
  queryVerifica += nomeVocabulario;
  queryVerifica += "';";

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  if(recebe > 0)
      {
        queryVerifica = "select * from Vocabulario_Controlado where nomeVocabulario = '";
        queryVerifica += nomeVocabulario;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
  else
      {
        cout << "\nVocabulario Controlado nao consta em nosso banco de dados\n" << endl;
      }

      desconectarDbUsuario();
}

void ServicoUsuariosDesenvolvedor::consultarTermo()
{
  /**
  * Primeiramente o nome do termo e pedido, e assim que colocado, uma pesquisa sera
  * feita no DB em busca desse nome. Se o termo realmente existir, uma query sera criada para
  * apresentar os dados desse termo, se nao, a funcao caira no catch
  */
  string nomeTermo;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do Termo que deseja consultar: ";
  cin >> nomeTermo;


  queryVerifica = "select count(*) from Termo where nome = '";
  queryVerifica += nomeTermo;
  queryVerifica += "';";

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  if(recebe > 0)
      {
        queryVerifica = "select * from Termo where nome = '";
        queryVerifica += nomeTermo;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
  else
      {
        cout << "Termo nao consta em nosso banco de dados\n" << endl;
      }

      desconectarDbUsuario();
}


void ServicoUsuariosDesenvolvedor::consultarDefinicaoTermo()
{
  string nomeTermo;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do Termo no qual deseja consultar sua definicao: ";
  cin >> nomeTermo;


  queryVerifica = "select count(*) from Termo inner join Definicao on Termo.nome = '";
  queryVerifica += nomeTermo;
  queryVerifica += "' and Definicao.termos = '";
  queryVerifica += nomeTermo;
  queryVerifica += "';";

  cout << "QUERY: " <<  queryVerifica << endl;

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  cout << "VALOR: " << recebe << endl;

  if(recebe > 0)
  {
    queryVerifica = "select texto from Definicao where termos = '";
    queryVerifica += nomeTermo;
    queryVerifica += "';";
    recebe = executDbUsuario(queryVerifica);
  }
  else
  {
    cout << "Definicao para o termo " << nomeTermo << " nao foi encontrada" << endl;
  }

  desconectarDbUsuario();
}

void ServicoUsuariosDesenvolvedor::cadastraDesenvolvedorVocControlado(string email)
{
  /**
  * Nessa funcao, um novo desenvolvedor sera cadastrado. Para se cadastrar como desenvolvedor de
  * um vocabulario controlado, primeiramente precisamos verificar se esse vocabulario existe, e
  * é isso que o programa faz. Primeiramente ele executa uma query em busca desse vocabulario, achado
  * esse vocabulario, o email do desenvolvedor e consultado na tabela desse vocabulario para verificar
  * se ele ja nao possui cadastro. Nao possuindo cadastro, agora sim, uma query sera montada para
  * realizar seu cadastro como desenvolvedor desse vocabulario
  */
  string vocabulario;
  string query;
  int resultado;

      cout << "Digite o nome do vocabulario controlado no qual deseja se cadastrar: ";
      cin >> vocabulario;

      query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
      query += vocabulario;
      query += "';";


      conectarDbUsuario();
      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, Vocabulario Controlado nao encontrado\n";
      }

        query = "select count(*) from Vocabulario_Controlado where desenvolvedores = '";
        query += email;
        query += "';";
        resultado = executDbUsuarioRows(query);

        if(resultado != -1)
        {
          throw "Usuario ja possui cadastrado\n";
        }


        query = "select count(*) from Vocabulario_Controlado where nome nomeVocabulario = '";
        query += vocabulario;
        query += "';";

        resultado = executDbUsuarioRows(query);

        if(resultado >= 10)
        {
          throw "Numero de desenvolvedores esgotado para esse Vocabulario;\n";
        }



        query = "insert into Vocabulario_Controlado (nomeVocabulario, idioma, emailAdmin)";
        query += "select nomeVocabulario, idioma, emailAdmin from Vocabulario_Controlado where nomeVocabulario = '";
        query += vocabulario;
        query += "' and desenvolvedores = '-';";

        resultado = executDbUsuario(query);

        query = "update Vocabulario_Controlado set desenvolvedores = '";
        query += email;
        query += "' where desenvolvedores is null and nomeVocabulario = '";
        query += vocabulario;
        query += "';";

        resultado = executDbUsuario(query);

        cout << "Processando comandos....\n\n";

        query = "select count(*) from Vocabulario_Controlado where desenvolvedores = '";
        query += email;
        query += "';";

          resultado = executDbUsuarioRows(query);

          if(resultado != -1)
          {
            cout << "Desenvolvedor adicionado com sucesso....\n\n";
          }
          else
          {
            throw "Erro na execução do comando\n\n";
          }

}


void ServicoUsuariosDesenvolvedor::criaTermo()
{
  /**
  * Primeiramente o programa pede para o usuario informar em qual vocabulario deseja cadastrar seu
  * termo. Informando esse detalhe, uma pesquisa e feita em busca desse vocabulario. Achando esse
  * vocabulario, e verificado se nele ja existe um termo com o mesmo nome, e se caso nao existe
  * so assim que o novo termo podera ser cadastrado.
  */
  Nome *nome = new Nome();
  Data *data = new Data();
  Termo *termo = new Termo();
int resultado;
  string vocabulario;
  string entrada;
  string query;

  cout << "Digite o nome do vocabulario no qual deseja que seu termo seja cadastrado: ";
  cin >> vocabulario;
  cin.ignore();

  query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
  query += vocabulario;
  query += "';";


  conectarDbUsuario();
  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, Vocabulario Controlado nao encontrado\n";
  }
while(true)
{
  try
  {
    cout << "Nome do termo: ";
    getline(cin, entrada);
    nome->setNome(entrada);
    termo->setNome(*nome);
    query = "select count(*) from Termo where nome = '";
    query += nome->getNome();
    query += "';";
    resultado = executDbUsuarioRows(query);
    if(resultado != -1)
    {
      throw "Erro, Termo ja consta em nosso banco de dados, tente outro Termo..\n";
    }

    cout << "Classe do Termo: ";
    getline(cin, entrada);
    termo->setClasseDeTermo(entrada);


    cout << "Data da criacao: ";
    cin >> entrada;
    data->setData(entrada);
    termo->setData(*data);

    break;
  }
  catch(const char *erro)
  {
    cout << erro << endl;
  }
}


  query = "insert into Termo (nome,classe,data,vocabulario)";
  query += "values('";
  query += nome->getNome();
  query += "','";
  query += termo->getClasseDeTermo();
  query += "','";
  query += data->getData();
  query += "','";
  query += vocabulario;
  query += "');";

  resultado = executDbUsuario(query);

  query = "select count(*)from Termo where nome = '";
  query += nome->getNome();
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado != -1)
  {
    cout << "Termo criado com sucesso...\n\n";
  }
  else
  {
    throw "Erro na criacao do Termo\n\n";
  }

  desconectarDbUsuario();
}


void ServicoUsuariosDesenvolvedor::editarTermo()
{
  /**
  * Primeiramente o programa pede ao usuario o nome do termo que deseja editar e esse e procurado
  * no DB. O termo achado, instancias de objetos serao criadas, no qual essas compoe as informacoes do
  * termo escolhido. Todas as informacoes terao que ser atualizadas e essas mesmas serao verificadas
  * antes de serem salvas no DB
  */
  Nome *nome = new Nome();
  Data *data = new Data();
  Termo *termo = new Termo();
  string termoEditar;
  string entrada;
  string query;
  string vocabulario;
  int resultado;

  cout << "Digite o nome do termo que deseja editar: ";
  getline(cin, termoEditar);
  cin.ignore();

  conectarDbUsuario();

  query = "select count(*) from Termo where nome = '";
  query += termoEditar;
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, termo nao encontrado\n\n";
  }

  cout << "\t\t--------------- Digite os novos dados do termo -----------------\n ";

  while(true)
  {
    try
    {
      cout << "Nome do termo: ";
      getline(cin, entrada);
      cin.ignore();
      nome->setNome(entrada);
      termo->setNome(*nome);
      query = "select count(*) from Termo where nome = '";
      query += nome->getNome();
      query += "';";
      resultado = executDbUsuarioRows(query);
      if(resultado != -1)
      {
        throw "Erro, Termo ja consta em nosso banco de dados, tente outro Termo..\n";
      }

      cout << "Classe do Termo: ";
      getline(cin, entrada);
      cin.ignore();
      termo->setClasseDeTermo(entrada);

      cout << "Data da criacao: ";
      cin >> entrada;
      cin.ignore();
      data->setData(entrada);
      termo->setData(*data);

      cout << "Vocabulario: ";
      cin >> vocabulario;
      query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
      query += vocabulario;
      query += "';";
      resultado = executDbUsuarioRows(query);
      if(resultado == -1)
      {
        throw "Erro, Vocabulario nao encontrado, tente outro vocabulario....\n";
      }

      break;
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

    query = "update Termo set nome = '";
    query += nome->getNome();
    query += "',classe = '";
    query += termo->getClasseDeTermo();
    query += "',data = '";
    query += data->getData();
    query += "', vocabulario = '";
    query += vocabulario;
    query += "' where nome = '";
    query += termoEditar;
    query += "';";

    resultado = executDbUsuario(query);

    query = "select count(*) from Termo where nome = '";
    query += nome->getNome();
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado != -1)
    {
      cout << "Comando executado com sucesso....\n\n";
    }
    else
    {
      throw "Erro ao executar comando\n\n";
    }

    desconectarDbUsuario();
}


void ServicoUsuariosDesenvolvedor::excluirTermo()
{
  /**
  * Primeiramente o nome do termo e pedido, e com isso comeca a procura dentro do DB. Achado o termo
  * uma query sera montada e executada para que esse termo seja excluido do Banco de dados
  */
  string query;
  string termo;
  int resultado;

  cout << "Digite o nome do termo que deseja excluir: ";
  cin >> termo;

  query = "select count(*) from Termo where nome = '";
  query += termo;
  query += "';";

  conectarDbUsuario();

  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, Termo nao encontrado\n\n";
  }

  query = "delete from Termo where nome = '";
  query += termo;
  query += "';";

  resultado = executDbUsuario(query);

  query = "select count(*) from Termo where nome = '";
  query += termo;
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado != -1)
  {
    throw "Erro na exclusao\n\n";
  }
  else
  {
    cout << "Exclusao de termo realizada com sucesso\n\n";
  }

  desconectarDbUsuario();

}


void ServicoUsuariosDesenvolvedor::criaDefinicao()
{
  /**
  * Para criar uma definicao primeiramente e necessario verificar a qual termo ela ira se aplicar.
  * informando o termo, esse mesmo sera chedado, e verificado se ele existe no banco de dados. Validando
  * sua existencia o programa pedira para o usuario digitar sua definicao para esse termo, porem lembrando
  * que se esse termo ja possuir definicao, elas serao contabilizadas, sendo 5 o numero maximo para definicoes
  * de cada termo
  */
  string query;
  string termo;
  string definicao;
  int resultado;

  cout << "Digite o termo no qual deseja aplicar um definicao: ";
  cin >> termo;
  cin.ignore();

  conectarDbUsuario();

  query = "select count(*) from Termo where nome = '";
  query += termo;
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, termo nao consta em nosso banco de dados\n";
  }

  query = "select count(*) from Definicao where termos = '";
  query += termo;
  query += "';";

  resultado = executDbUsuarioRows(query);

  cout << "Quantidade de termos retornados: " << resultado << endl;

  if(resultado == 5)
  {
    throw "\n\tErro, termo ja possui numero maximo de definicoes\n\n";
  }

  cout << "Digite a definicao para seu termo: ";
  getline(cin, definicao);

  query = "insert into Definicao(texto, termos) ";
  query += "values('";
  query += definicao;
  query += "','";
  query += termo;
  query += "');";

  resultado = executDbUsuario(query);

  cout << "\t\t ------------ Definicao aplicada com sucesso ------------------\n\n";

  desconectarDbUsuario();

}


void ServicoUsuariosDesenvolvedor::excluirDefinicao()
{
  /**
  * Para excluir a definicao de um termo, primeiro deve-se informar a qual termo ela pertence
  * informando e validando essa informacao, o programa ira apresentar a Quantidade de definicoes
  * existentes para o termo escolhido e junto com elas, um numero chamado de numeroDef, utilizado
  * para poder diferencia-las na hora da exclusao. O usuario ira selecionar aquela de deseja exluir
  * atraves desse numeroDef, executando por fim a query de exclusao.
  */
  string query;
  int resultado;
  char numeroDef;
  string termo;

  cout << "Digite o termo no qual deseja excluir sua definicao: ";
  cin >> termo;

  query = "select count(*) from Definicao where termos = '";
  query += termo;
  query += "';";

  conectarDbUsuario();

  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, termo nao existe em nosso banco de dados de definicoes\n\n";
  }

  cout << "\t\t----------- Definicoes do Termo " << termo << "-----------\n\n";

  query = "select * from Definicao where termos = '";
  query += termo;
  query += "';";

  resultado = executDbUsuario(query);

  cout << "Digite o numero que representa a definicao do termo que deseja excluir: ";
  cin >> numeroDef;

  query = "delete from Definicao where numeroDef = ";
  query += numeroDef;
  query += " and termos = '";
  query += termo;
  query += "';";

  cout << "QUERYYY: " << query << endl;

  resultado = executDbUsuario(query);

  cout << "resultado exclusao\n\n";

  query = "select * from Definicao where termos = '";
  query += termo;
  query += "';";

  resultado = executDbUsuario(query);

  desconectarDbUsuario();

}


 void ServicoUsuariosDesenvolvedor::editarDefinicao()
 {
   /**
   *  Para um definicao ser editada, primeiramente deve-se informar a qual termo pertence essa definicao
   * logo apos validar esse termo, e necessario verificar se o mesmo apresenta alguma definicao. sendo
   * apresentada alguma definicao, o usuario ira escolher a que deseja editar atraves do numeroDef Colocado
   * na definicao, para que possa alterar somente aquela que ele deseja.
   */
   string query;
   string termo;
   string definicao;
   string numeroDef;
   int resultado;

   cout << "Digite o nome do termo no qual deseja edita-lo: ";
   cin >> termo;
   cin.ignore();



   conectarDbUsuario();

   query = "select count(*) from Definicao where termos = '";
   query += termo;
   query += "';";

   resultado = executDbUsuarioRows(query);

   if(resultado == -1)
   {
     throw "Erro, termo nao encontrado\n\n";
   }

   cout << "\t ---------- Apresentando definicoes do termo escolhido ----------\n\n";

   query = "select * from Definicao where termos = '";
   query += termo;
   query += "';";

   resultado = executDbUsuario(query);

   cout << "Digite o numero(numeroDef) apresentado na frente do termo no qual deseja editar: ";
   cin >> numeroDef;
   cin.ignore();

  cout << "Digite a nova definicao para o termo escolhido: ";
  getline(cin, definicao);

  query = "update Definicao set texto = '";
  query += definicao;
  query +=  "' where termos = '";
  query += termo;
  query += "' and numeroDef = ";
  query += numeroDef;
  query += ";";

     resultado = executDbUsuario(query);

     query = "select * from Definicao where numeroDef = ";
     query += numeroDef;
     query += " and termos = '";
     query += termo;
     query += "';";

     resultado = executDbUsuario(query);

     cout << "Termo Editado com sucesso\n\n";

     desconectarDbUsuario();
 }




//------------------------- SERVICO ADMINISTRADORES ---------------------------//
/*ADMINISTRADORES -
nome text not null,
sobrenome text not null,
telefone text not null,
endereco text not null,
data text not null,
email text primary key not null,
senha text not null)*/

void ServicoLogin::criarUsuarioAdministrador()
{
  Nome *nome = new Nome();
  Sobrenome *sobrenome = new Sobrenome();
  Telefone *telefone = new Telefone();
  Endereco *endereco = new Endereco();
  Data *data = new Data();
  Email *email = new Email();
  Senha *senha = new Senha();
  string query;
  string entrada;
  int resultado;

  cin.ignore();
  while(true)
  {
    try
    {
      cout << "Nome: ";
      getline(cin, entrada);
      nome->setNome(entrada);

      cout << "Sobrenome: ";
      getline(cin, entrada);
      sobrenome->setSobrenome(entrada);

      cout << "Data de nascimento: ";
      getline(cin, entrada);
      data->setData(entrada);

      cout << "Telefone: ";
      getline(cin, entrada);
      telefone->setTelefone(entrada);

      cout << "Endereco: ";
      getline(cin, entrada);
      endereco->setEndereco(entrada);

      cout << "Email: ";
      getline(cin, entrada);
      email->setEmail(entrada);

      cout << "Senha: ";
      getline(cin, entrada);
      senha->setSenha(entrada,nome);

      break;

    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  conectarDbUsuario();

  query = "insert into Administradores(nome,sobrenome,telefone,endereco,data,email,senha) ";
  query += "values('";
  query += nome->getNome();
  query += "','";
  query += sobrenome->getSobrenome();
  query += "','";
  query += telefone->getTelefone();
  query += "','";
  query += endereco->getEndereco();
  query += "','";
  query += data->getData();
  query += "','";
  query += email->getEmail();
  query += "','";
  query += senha->getSenha();
  query += "');";

  resultado = executDbUsuario(query);

  query = "select count(*) from Administradores where email = '";
  query += email->getEmail();
  query += "' and senha = '";
  query += senha->getSenha();
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado != -1)
  {
    throw "\t---------------- Cadastrado realizado com sucesso ----------------\n";
  }
  else
  {
    throw "Erro na realizacao do cadastro...\n\n";
  }

desconectarDbUsuario();

}


 void ServicoUsuariosAdministrador::criarVocabulario(string email)
 {
   /**
   *  Para criar um novo vocabulario, sao criadas instancias dos objetos que compoe as informacoes
   * desse vocabulario. Essas informacoes sera digitadas pelo usuario porem validadas antes de serem
   * armazenadas. Apos isso uma query e executada e o vocabulario criado, tendo como administrador
   * o usuario logado, onde seu email foi repassado via parametro pela funcao.
   */
   Nome *nome = new Nome();
   Idioma *idioma = new Idioma();
   Data *data = new Data();
   string query;
   string entrada;
   string texto;
   int resultado;

   conectarDbUsuario();

   while(true)
   {
     try
     {
       cout << "Digite o nome do vocabulario controlado: ";
       cin >> entrada;
       nome->setNome(entrada);


       cout << "Digite o Idioma do vocabulario controlado: ";
       cin >> entrada;
       idioma->setIdioma(entrada);

       cout << "Digite a Data de criacao do vocabulario controlado: ";
       cin >> entrada;
       data->setData(entrada);
       cin.ignore();

       cout << "Digite o texto de definicao do vocabulario controlado: ";
       getline(cin, texto);


       break;
     }
     catch(const char *erro)
     {
       cout << erro << endl;
     }
   }


   query = "insert into Vocabulario_Controlado(nomeVocabulario, idioma, emailAdmin, desenvolvedores, data, definicao) ";
   query += "values('";
   query += nome->getNome();
   query += "','";
   query += idioma->getIdioma();
   query += "','";
   query += email;
   query += "','-','";
   query += data->getData();
   query += "','";
   query += texto;
   query += "');";

   resultado = executDbUsuario(query);

   query = "select * from Vocabulario_Controlado;";
   resultado = executDbUsuario(query);

   desconectarDbUsuario();
 }




void ServicoUsuariosAdministrador::editarDefVocabulario()
{
  /**
  * Primeiramente realiza a pesquisa para ver se o vocabulario que o usuario deseja alterar existe
  * sendo validada essa informacao, o programa pede para o usuario digitar a nova definicao para
  * esse vocabulario, que logo apos isso, sera armazenada no banco de dados.
  */
    string query;
    string vocabulario;
    string texto;
    int resultado;

    cout << "Digite o nome do vocabulario controlado no qual deseja atualizar sua definicao: ";
    cin >> vocabulario;
    cin.ignore();

    conectarDbUsuario();

    query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado == -1)
    {
      throw "Erro, vocabulario nao existe\n\n";
    }

    cout << "Digite a nova definicao do vocabulario escolhido: ";
    getline(cin, texto);

    query = "update Vocabulario_Controlado set definicao = '";
    query += texto;
    query += "' where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuario(query);

    query = "select * from Vocabulario_Controlado;";

    resultado = executDbUsuario(query);
}


void ServicoUsuariosAdministrador::editarIdiomaVoc()
{
  /**
  * Verifica a existencia do vocabulario desejado, logo apos isso, se cria uma instacia do objeto idioma, onde
  * o mesmo passa por uma validacao antes de ser atualizado no banco de dados.
  */
    string query;
    string vocabulario;
    Idioma *idioma = new Idioma();
    string entrada;
    int resultado;

    cout << "Digite o nome do vocabulario no qual deseja alterar o idioma: ";
    cin >> vocabulario;
    cin.ignore();

    conectarDbUsuario();

    query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado == -1)
    {
      throw "Erro, vocabulario nao consta em nosso banco de dados\n\n";
    }

    while(true)
    {
      try
      {
        cout << "Novo Idioma: ";
        cin >> entrada;
        idioma->setIdioma(entrada);

        break;
      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

    query = "update Vocabulario_Controlado set idioma = '";
    query += idioma->getIdioma();
    query += "' where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuario(query);

    query = "select * from Vocabulario_Controlado where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuario(query);

    desconectarDbUsuario();


}




void ServicoUsuariosAdministrador::excluirVocabulario()
{
  /**
  * Verifica a existencia do vocabulario, caso ele exista uma query de exclusao e executada
  */
    string query;
    string vocabulario;
    int resultado;

    cout << "Digite o nome do vocabulario que deseja excluir: ";
    cin >> vocabulario;
    cin.ignore();

    conectarDbUsuario();

    query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado == -1)
    {
      throw "Erro, vocabulario nao consta em nosso banco de dados\n\n";
    }

    query = "delete from Vocabulario_Controlado where nomeVocabulario = '";
    query += vocabulario;
    query += "';";

    resultado = executDbUsuario(query);

    query = "select * from Vocabulario_Controlado;";

    resultado = executDbUsuario(query);

    desconectarDbUsuario();

}

void ServicoUsuariosAdministrador::consultarCadastroAdministrador(string email)
{
  string query;
  int resultado;

  conectarDbUsuario();

  query = "select * from Administradores where email = '";
  query += email;
  query += "';";

  resultado = executDbUsuario(query);

  desconectarDbUsuario();
}

void ServicoUsuariosAdministrador::excluirUsuarioAdministrador(string email)
{
  // Ao ser excluída a conta de um administrador, são excluídos os dados dos vocabulários administrados,
  // os termos do vocabulário controlado e as definições apropriadas.
  string query;
  int resultado;

  conectarDbUsuario();

  query = "delete from Administradores where email = '";
  query += email;
  query += "';";

  resultado = executDbUsuario(query);

  desconectarDbUsuario();

}

void ServicoUsuariosAdministrador::atualizarUsuarioAdministrador(string email)
{
  Nome *nome = new Nome();
  Sobrenome *sobrenome = new Sobrenome();
  Telefone *telefone = new Telefone();
  Endereco *endereco = new Endereco();
  Data *data = new Data();
  Email *emailAtualiza = new Email();
  Senha *senha = new Senha();
  string query;
  string entrada;
  int resultado;

  cin.ignore();
  while(true)
  {
    try
    {
      cout << "Nome: ";
      cin >> entrada;
      nome->setNome(entrada);

      cout << "Sobrenome: ";
      cin >> entrada;
      sobrenome->setSobrenome(entrada);

      cout << "Data de nascimento: ";
      cin >> entrada;
      data->setData(entrada);

      cout << "Telefone: ";
      cin >> entrada;
      telefone->setTelefone(entrada);
      cin.ignore();

      cout << "Endereco: ";
      getline(cin, entrada);
      endereco->setEndereco(entrada);

      cout << "Email: ";
      cin >> entrada;
      emailAtualiza->setEmail(entrada);
      cin.ignore();

      cout << "Senha: ";
      getline(cin, entrada);
      senha->setSenha(entrada,nome);

      break;

    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  conectarDbUsuario();


  query = "update Administradores ";
  query += "set nome = '";
  query += nome->getNome();
  query += "', sobrenome = '";
  query += sobrenome->getSobrenome();
  query += "', telefone = '";
  query += telefone->getTelefone();
  query += "', endereco = '";
  query += endereco->getEndereco();
  query += "', data = '";
  query += data->getData();
  query += "', email = '";
  query += emailAtualiza->getEmail();
  query += "', senha = '";
  query += senha->getSenha();
  query += "' where email = '";
  query += email;
  query += "';";


  resultado = executDbUsuario(query);

  query = "select count(*) from Administradores where email = '";
  query += emailAtualiza->getEmail();
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado != -1)
  {
    cout << "\t ---------------- Cadastro atualizado com sucesso ----------------\n\n";
  }
  else
  {
    throw "Erro ao atualizar cadastro...\n\n";
  }



}


void ServicoUsuariosAdministrador::listNomeVocabularios()
{
  string queryList;
  int recebe;
  queryList = "select nomeVocabulario from Vocabulario_Controlado;";
  conectarDbUsuario();
  recebe = executDbUsuario(queryList);
  if(recebe == 0)
  {
    cout << "Erro ao executar query\n";
  }
  desconectarDbUsuario();
}


void ServicoUsuariosAdministrador::listDadosVocabulario()
{
  string nomeVocabulario;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do vocabulario desejado: ";
  cin >> nomeVocabulario;


  queryVerifica = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
  queryVerifica += nomeVocabulario;
  queryVerifica += "';";

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  if(recebe > 0)
      {
        queryVerifica = "select * from Vocabulario_Controlado where nomeVocabulario = '";
        queryVerifica += nomeVocabulario;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
  else
      {
        cout << "\nVocabulario Controlado nao consta em nosso banco de dados\n" << endl;
      }

      desconectarDbUsuario();
}


void ServicoUsuariosAdministrador::consultarTermo()
{
  string nomeTermo;
  string queryVerifica;
  int recebe;

  cout << "Digite o nome do Termo que deseja consultar: ";
  cin >> nomeTermo;


  queryVerifica = "select count(*) from Termo where nome = '";
  queryVerifica += nomeTermo;
  queryVerifica += "';";

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  if(recebe > 0)
      {
        queryVerifica = "select * from Termo where nome = '";
        queryVerifica += nomeTermo;
        queryVerifica += "';";
        recebe = executDbUsuario(queryVerifica);
      }
  else
      {
        cout << "Termo nao consta em nosso banco de dados\n" << endl;
      }

      desconectarDbUsuario();
}


void ServicoUsuariosAdministrador::consultarDefinicaoTermo()
{
  string nomeTermo;
  string queryVerifica;
  int recebe;
//select count(nome) from Termo inner join Definicao on Termo.nome='Ponteiro' and Definicao.termos='Ponteiro';
  cout << "Digite o nome do Termo no qual deseja consultar sua definicao: ";
  cin >> nomeTermo;


  queryVerifica = "select count(*) from Termo inner join Definicao on Termo.nome = '";
  queryVerifica += nomeTermo;
  queryVerifica += "' and Definicao.termos = '";
  queryVerifica += nomeTermo;
  queryVerifica += "';";

  cout << "QUERY: " <<  queryVerifica << endl;

  conectarDbUsuario();
  recebe = executDbUsuarioRows(queryVerifica);

  cout << "VALOR: " << recebe << endl;

  if(recebe > 0)
  {
    queryVerifica = "select texto from Definicao where termos = '";
    queryVerifica += nomeTermo;
    queryVerifica += "';";
    recebe = executDbUsuario(queryVerifica);
  }
  else
  {
    cout << "Definicao para o termo " << nomeTermo << " nao foi encontrada" << endl;
  }

  desconectarDbUsuario();
}


void ServicoUsuariosAdministrador::cadastraDesenvolvedorVocControlado(string email)
{
  string vocabulario;
  string query;
  int resultado;

      cout << "Digite o nome do vocabulario controlado no qual deseja se cadastrar: ";
      cin >> vocabulario;

      query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
      query += vocabulario;
      query += "';";


      conectarDbUsuario();
      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, Vocabulario Controlado nao encontrado\n";
      }

        query = "select count(*) from Vocabulario_Controlado where desenvolvedores = '";
        query += email;
        query += "';";
        resultado = executDbUsuarioRows(query);

        if(resultado != -1)
        {
          throw "Usuario ja possui cadastrado\n";
        }


        query = "select count(*) from Vocabulario_Controlado where nome nomeVocabulario = '";
        query += vocabulario;
        query += "';";

        resultado = executDbUsuarioRows(query);

        if(resultado >= 10)
        {
          throw "Numero de desenvolvedores esgotado para esse Vocabulario;\n";
        }



        query = "insert into Vocabulario_Controlado (nomeVocabulario, idioma, emailAdmin)";
        query += "select nomeVocabulario, idioma, emailAdmin from Vocabulario_Controlado where nomeVocabulario = '";
        query += vocabulario;
        query += "' and desenvolvedores = '-';";

        resultado = executDbUsuario(query);

        query = "update Vocabulario_Controlado set desenvolvedores = '";
        query += email;
        query += "' where desenvolvedores is null and nomeVocabulario = '";
        query += vocabulario;
        query += "';";

        resultado = executDbUsuario(query);

        cout << "Processando comandos....\n\n";

        query = "select count(*) from Vocabulario_Controlado where desenvolvedores = '";
        query += email;
        query += "';";

          resultado = executDbUsuarioRows(query);

          if(resultado != -1)
          {
            cout << "Desenvolvedor adicionado com sucesso....\n\n";
          }
          else
          {
            throw "Erro na execução do comando\n\n";
          }

}


void ServicoUsuariosAdministrador::criaTermo()
{
  Nome *nome = new Nome();
  Data *data = new Data();
  Termo *termo = new Termo();
int resultado;
  string vocabulario;
  string entrada;
  string query;

  cout << "Digite o nome do vocabulario no qual deseja que seu termo seja cadastrado: ";
  cin >> vocabulario;
  cin.ignore();

  query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
  query += vocabulario;
  query += "';";


  conectarDbUsuario();
  resultado = executDbUsuarioRows(query);

  if(resultado == -1)
  {
    throw "Erro, Vocabulario Controlado nao encontrado\n";
  }
while(true)
{
  try
  {
    cout << "Nome do termo: ";
    getline(cin, entrada);
    nome->setNome(entrada);
    termo->setNome(*nome);
    query = "select count(*) from Termo where nome = '";
    query += nome->getNome();
    query += "';";
    resultado = executDbUsuarioRows(query);
    if(resultado != -1)
    {
      throw "Erro, Termo ja consta em nosso banco de dados, tente outro Termo..\n";
    }

    cout << "Classe do Termo: ";
    getline(cin, entrada);
    termo->setClasseDeTermo(entrada);


    cout << "Data da criacao: ";
    cin >> entrada;
    data->setData(entrada);
    termo->setData(*data);

    break;
  }
  catch(const char *erro)
  {
    cout << erro << endl;
  }
}


  query = "insert into Termo (nome,classe,data,vocabulario)";
  query += "values('";
  query += nome->getNome();
  query += "','";
  query += termo->getClasseDeTermo();
  query += "','";
  query += data->getData();
  query += "','";
  query += vocabulario;
  query += "');";

  resultado = executDbUsuario(query);

  query = "select count(*)from Termo where nome = '";
  query += nome->getNome();
  query += "';";

  resultado = executDbUsuarioRows(query);

  if(resultado != -1)
  {
    cout << "Termo criado com sucesso...\n\n";
  }
  else
  {
    throw "Erro na criacao do Termo\n\n";
  }

  desconectarDbUsuario();
}


  void ServicoUsuariosAdministrador::editarTermo()
  {
    Nome *nome = new Nome();
    Data *data = new Data();
    Termo *termo = new Termo();
    string termoEditar;
    string entrada;
    string query;
    string vocabulario;
    int resultado;

    cout << "Digite o nome do termo que deseja editar: ";
    getline(cin, termoEditar);
    cin.ignore();

    conectarDbUsuario();

    query = "select count(*) from Termo where nome = '";
    query += termoEditar;
    query += "';";

    resultado = executDbUsuarioRows(query);

    if(resultado == -1)
    {
      throw "Erro, termo nao encontrado\n\n";
    }

    cout << "\t\t--------------- Digite os novos dados do termo -----------------\n ";

    while(true)
    {
      try
      {
        cout << "Nome do termo: ";
        getline(cin, entrada);
        cin.ignore();
        nome->setNome(entrada);
        termo->setNome(*nome);
        query = "select count(*) from Termo where nome = '";
        query += nome->getNome();
        query += "';";
        resultado = executDbUsuarioRows(query);
        if(resultado != -1)
        {
          throw "Erro, Termo ja consta em nosso banco de dados, tente outro Termo..\n";
        }

        cout << "Classe do Termo: ";
        getline(cin, entrada);
        cin.ignore();
        termo->setClasseDeTermo(entrada);

        cout << "Data da criacao: ";
        cin >> entrada;
        cin.ignore();
        data->setData(entrada);
        termo->setData(*data);

        cout << "Vocabulario: ";
        cin >> vocabulario;
        query = "select count(*) from Vocabulario_Controlado where nomeVocabulario = '";
        query += vocabulario;
        query += "';";
        resultado = executDbUsuarioRows(query);
        if(resultado == -1)
        {
          throw "Erro, Vocabulario nao encontrado, tente outro vocabulario....\n";
        }

        break;
      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

      query = "update Termo set nome = '";
      query += nome->getNome();
      query += "',classe = '";
      query += termo->getClasseDeTermo();
      query += "',data = '";
      query += data->getData();
      query += "', vocabulario = '";
      query += vocabulario;
      query += "' where nome = '";
      query += termoEditar;
      query += "';";

      resultado = executDbUsuario(query);

      query = "select count(*) from Termo where nome = '";
      query += nome->getNome();
      query += "';";

      resultado = executDbUsuarioRows(query);

      if(resultado != -1)
      {
        cout << "Comando executado com sucesso....\n\n";
      }
      else
      {
        throw "Erro ao executar comando\n\n";
      }

      desconectarDbUsuario();
  }


    void ServicoUsuariosAdministrador::excluirTermo()
    {
      string query;
      string termo;
      int resultado;

      cout << "Digite o nome do termo que deseja excluir: ";
      cin >> termo;

      query = "select count(*) from Termo where nome = '";
      query += termo;
      query += "';";

      conectarDbUsuario();

      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, Termo nao encontrado\n\n";
      }

      query = "delete from Termo where nome = '";
      query += termo;
      query += "';";

      resultado = executDbUsuario(query);

      query = "select count(*) from Termo where nome = '";
      query += termo;
      query += "';";

      resultado = executDbUsuarioRows(query);

      if(resultado != -1)
      {
        throw "Erro na exclusao\n\n";
      }
      else
      {
        cout << "Exclusao de termo realizada com sucesso\n\n";
      }

      desconectarDbUsuario();
    }


    void ServicoUsuariosAdministrador::criaDefinicao()
    {
      string query;
      string termo;
      string definicao;
      int resultado;

      cout << "Digite o termo no qual deseja aplicar um definicao: ";
      cin >> termo;
      cin.ignore();

      conectarDbUsuario();

      query = "select count(*) from Termo where nome = '";
      query += termo;
      query += "';";

      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, termo nao consta em nosso banco de dados\n";
      }

      query = "select count(*) from Definicao where termos = '";
      query += termo;
      query += "';";

      resultado = executDbUsuarioRows(query);

      cout << "Quantidade de termos retornados: " << resultado << endl;

      if(resultado == 5)
      {
        throw "\n\tErro, termo ja possui numero maximo de definicoes\n\n";
      }

      cout << "Digite a definicao para seu termo: ";
      getline(cin, definicao);

      query = "insert into Definicao(texto, termos) ";
      query += "values('";
      query += definicao;
      query += "','";
      query += termo;
      query += "');";

      resultado = executDbUsuario(query);

      cout << "\t\t ------------ Definicao aplicada com sucesso ------------------\n\n";

      desconectarDbUsuario();
    }


    void ServicoUsuariosAdministrador::excluirDefinicao()
    {
      string query;
      int resultado;
      char numeroDef;
      string termo;

      cout << "Digite o termo no qual deseja excluir sua definicao: ";
      cin >> termo;

      query = "select count(*) from Definicao where termos = '";
      query += termo;
      query += "';";

      conectarDbUsuario();

      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, termo nao existe em nosso banco de dados de definicoes\n\n";
      }

      cout << "\t\t----------- Definicoes do Termo " << termo << "-----------\n\n";

      query = "select * from Definicao where termos = '";
      query += termo;
      query += "';";

      resultado = executDbUsuario(query);

      cout << "Digite o numero que representa a definicao do termo que deseja excluir: ";
      cin >> numeroDef;

      query = "delete from Definicao where numeroDef = ";
      query += numeroDef;
      query += " and termos = '";
      query += termo;
      query += "';";

      cout << "QUERYYY: " << query << endl;

      resultado = executDbUsuario(query);

      cout << "resultado exclusao\n\n";

      query = "select * from Definicao where termos = '";
      query += termo;
      query += "';";

      resultado = executDbUsuario(query);

      desconectarDbUsuario();
    }


    void ServicoUsuariosAdministrador::editarDefinicao()
    {
      string query;
      string termo;
      string definicao;
      string numeroDef;
      int resultado;

      cout << "Digite o nome do termo no qual deseja edita-lo: ";
      cin >> termo;
      cin.ignore();



      conectarDbUsuario();

      query = "select count(*) from Definicao where termos = '";
      query += termo;
      query += "';";

      resultado = executDbUsuarioRows(query);

      if(resultado == -1)
      {
        throw "Erro, termo nao encontrado\n\n";
      }

      cout << "\t ------- Apresentando definicoes do termo escolhido ----------\n\n";

      query = "select * from Definicao where termos = '";
      query += termo;
      query += "';";

      resultado = executDbUsuario(query);

      cout << "Digite o numero apresentado na frente do termo no qual deseja editar: ";
      cin >> numeroDef;
      cin.ignore();

     cout << "Digite a nova definicao para o termo escolhido: ";
     getline(cin, definicao);

     query = "update Definicao set texto = '";
     query += definicao;
     query +=  "' where termos = '";
     query += termo;
     query += "' and numeroDef = ";
     query += numeroDef;
     query += ";";

        resultado = executDbUsuario(query);

        query = "select * from Definicao where numeroDef = ";
        query += numeroDef;
        query += " and termos = '";
        query += termo;
        query += "';";

        resultado = executDbUsuario(query);

        cout << "Termo Editado com sucesso\n\n";

        desconectarDbUsuario();
    }


//----------- OPCAO ESCOLHIDA DESENVOLVEDOR ---------------//
void ServicoUsuariosDesenvolvedor::opcaoEscolhidaDesenvolvedor(int opcao,string email)
{
  if(opcao == 1)
  {
    int recebe;
      recebe = consultarCadastroDesenvolvedor(email);
  }

  if(opcao == 2)
  {
    atualizarUsuarioDesenvolvedor(email);
  }

  if(opcao == 3)
  {
    excluirUsuarioDesenvolvedor(email);
  }

  if(opcao == 4)
  {
    listNomeVocabularios();
  }

  if(opcao == 5)
  {
    listDadosVocabulario();
  }

  if(opcao == 6)
  {
    consultarTermo();
  }

  if(opcao == 7)
  {
    consultarDefinicaoTermo();
  }

  if(opcao == 8)
  {
    try
    {
      cadastraDesenvolvedorVocControlado(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  if(opcao == 9)
  {
    try
    {
      criaTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  if(opcao == 10)
  {
    try
    {
      editarTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  if(opcao == 11)
  {
    try
    {
      excluirTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 12)
  {
    try
    {
      criaDefinicao();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 13)
  {
    try
    {
      excluirDefinicao();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



    if(opcao == 14)
    {
      try
      {
        editarDefinicao();
      }
      catch(const char *erro)
      {
        cout << erro << endl;
      }
    }

}



//----------- OPCAO ESCOLHIDA Administrador ---------------//
void ServicoUsuariosAdministrador::opcaoEscolhidaAdministrador(int opcao,string email)
{

  if(opcao == 1)
  {
    try
    {
      consultarCadastroAdministrador(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 2)
  {
    try
    {
      atualizarUsuarioAdministrador(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 3)
  {
    try
    {
      excluirUsuarioAdministrador(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 4)
  {
    try
    {
      listNomeVocabularios();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 5)
  {
    try
    {
      listDadosVocabulario();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 6)
  {
    try
    {
      consultarTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



  if(opcao == 7)
  {
    try
    {
      consultarDefinicaoTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



  if(opcao == 8)
  {
    try
    {
      cadastraDesenvolvedorVocControlado(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 9)
  {
    try
    {
      criaTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 10)
  {
    try
    {
      editarTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 11)
  {
    try
    {
      excluirTermo();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



  if(opcao == 12)
  {
    try
    {
      criaDefinicao();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



  if(opcao == 13)
  {
    try
    {
      excluirDefinicao();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 14)
  {
    try
    {
      editarDefinicao();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }



  if(opcao == 15)
  {
    try
    {
      criarVocabulario(email);
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 16)
  {
    try
    {
      editarDefVocabulario();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


  if(opcao == 17)
  {
    try
    {
      editarIdiomaVoc();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }

  if(opcao == 18)
  {
    try
    {
      excluirVocabulario();
    }
    catch(const char *erro)
    {
      cout << erro << endl;
    }
  }


}
