
#include "Database.h"
#include "constantes.h"
#include <iostream>
#include <sstream>
#include <memory>


using namespace std;
using namespace sql;

Database::Database() {
    driver = sql::mysql::get_mysql_driver_instance();
    string conexion = "tcp://" + Constantes::DB_HOST + ":" + to_string(Constantes::DB_PORT);
    con = driver->connect(conexion, Constantes::DB_USER, Constantes::DB_PASS);
    con->setSchema(Constantes::DB_SCHEMA);
}

Database::~Database() {
    delete con;
}

bool Database::insertarPaciente(string nombre, int edad) {
    try {
        unique_ptr<PreparedStatement> stmt(
            con->prepareStatement("INSERT INTO usuarios(nombre, edad) VALUES(?, ?)")
        );
        stmt->setString(1, nombre);
        stmt->setInt(2, edad);
        stmt->execute();
        return true;
    }
    catch (...) { return false; }
}

bool Database::atenderPaciente() {
    try {
        unique_ptr<Statement> stmt(con->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery(Constantes::SQL_SIGUIENTE));

        if (!res->next()) return false;

        int id = res->getInt("id");
        stmt->execute("UPDATE usuarios SET atendido = 1 WHERE id = " + to_string(id));
        return true;
    }
    catch (...) { return false; }
}

string Database::obtenerPacientesJSON() {
    try {
        stringstream json;
        json << "[";

        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(Constantes::SQL_TODOS);

        bool primero = true;
        while (res->next()) {
            if (!primero) json << ",";
            primero = false;

            json << "{";
            json << "\"nombre\":\"" << res->getString("nombre") << "\",";
            json << "\"edad\":" << res->getInt("edad") << ",";
            json << "\"atendido\":" << (res->getInt("atendido") ? "true" : "false");
            json << "}";
            json << "\"fecha_registro\":\""
                << res->getString("fecha_registro") << "\",";

            json << "\"fecha_actualizacion\":\""
                << res->getString("fecha_actualizacion") << "\",";
        }

        json << "]";
        delete res;
        delete stmt;
        return json.str();
    }
    catch (...) { return "{\"error\":\"db\"}"; }
}

string Database::obtenerPendientesJSON() {
    try {
        stringstream json;
        json << "[";

        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(Constantes::SQL_PENDIENTES);

        bool primero = true;
        while (res->next()) {
            if (!primero) json << ",";
            primero = false;

            json << "{";
            json << "\"nombre\":\"" << res->getString("nombre") << "\",";
            json << "\"edad\":" << res->getInt("edad");
            json << "}";
        }

        json << "]";
        delete res;
        delete stmt;
        return json.str();
    }
    catch (...) { return "{\"error\":\"db\"}"; }
}

string Database::obtenerAtendidosJSON() {
    try {
        stringstream json;
        json << "[";

        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(Constantes::SQL_ATENDIDOS);

        bool primero = true;
        while (res->next()) {
            if (!primero) json << ",";
            primero = false;

            json << "{";
            json << "\"nombre\":\"" << res->getString("nombre") << "\",";
            json << "\"edad\":" << res->getInt("edad");
            json << "}";
        }

        json << "]";
        delete res;
        delete stmt;
        return json.str();
    }
    catch (...) { return "{\"error\":\"db\"}"; }
}

bool Database::listarPacientes() {
    try {
        auto con = getConnection();
        unique_ptr<Statement> stmt(con->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery(Constantes::SQL_TODOS));

        cout << "\n--- PACIENTES ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }
        return true;
    }
    catch (...) { return false; }
}

bool Database::listarPendientes() {
    try {
        auto con = getConnection();
        unique_ptr<Statement> stmt(con->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery(Constantes::SQL_PENDIENTES));

        cout << "\n--- PENDIENTES ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }
        return true;
    }
    catch (...) { return false; }
}

bool Database::listarAtendidos() {
    try {
        auto con = getConnection();
        unique_ptr<Statement> stmt(con->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery(Constantes::SQL_ATENDIDOS));

        cout << "\n--- ATENDIDOS ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }
        return true;
    }
    catch (...) { return false; }
}

sql::Connection* Database::getConnection() {
    return con;
}


bool Database::eliminarPaciente(int id) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            con->prepareStatement(Constantes::SQL_ELIMINAR_LOGICO)
        );

        stmt->setInt(1, id);

        int filas = stmt->executeUpdate();

        return filas > 0;
    }
    catch (...) {
        return false;
    }
}

bool Database::eliminarPacienteFisico(int id) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            con->prepareStatement(Constantes::SQL_ELIMINAR_FISICO)
        );

        stmt->setInt(1, id);

        int filas = stmt->executeUpdate();

        return filas > 0;
    }
    catch (...) {
        return false;
    }
}