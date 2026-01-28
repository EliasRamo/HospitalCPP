#pragma once
#include <string>
#include <mysql/jdbc.h>

class Database {
private:
    sql::Connection* con;

public:
    Database();
    ~Database();

    void guardarPaciente(const std::string& nombre, int edad);
    void listarPacientes();
    void atenderPaciente();
};
