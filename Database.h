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

    bool insertarPaciente(std::string nombre, int edad);
    bool listarPacientes();
    bool atenderPaciente();
    bool listarPendientes();
    bool listarAtendidos();

    std::string obtenerPacientesJSON();
    std::string obtenerPendientesJSON();
    std::string obtenerAtendidosJSON();

    sql::Connection* getConnection();
};
