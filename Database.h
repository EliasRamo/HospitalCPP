
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
    bool atenderPaciente();

    std::string obtenerPacientesJSON();
    std::string obtenerPendientesJSON();
    std::string obtenerAtendidosJSON();
    bool listarPacientes();
    bool listarPendientes();
    bool listarAtendidos();
    bool eliminarPaciente(int id);
    bool eliminarPacienteFisico(int id);


    sql::Connection* getConnection();
};
