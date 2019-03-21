#ifndef COMANDOSQL_HPP_INCLUDED
#define COMANDOSQL_HPP_INCLUDED

#include <stdexcept>
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName);

int callbackRows(void *NotUsed, int argc, char **argv, char **azColName);

void conectarDbUsuario();

void desconectarDbUsuario();

int executDbUsuario(string query);

int executDbUsuarioRows(string query);

#endif
