#pragma once
#include <mysql/jdbc.h>
#include <string>

class Database {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    Database();
    ~Database();

    // ?? ESTE ES CLAVE PARA EL SERVIDOR HTTP
    sql::Connection* getConnection();

    bool insertarPaciente(std::string nombre, int edad);
    bool listarPacientes();
    bool atenderPaciente();
    bool listarPendientes();
    bool listarAtendidos();
};
