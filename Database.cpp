#include "Database.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace sql;

string Database::obtenerPacientesJSON() {
    try {
        std::stringstream json;
        json << "[";

        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(
            "SELECT nombre, edad, atendido FROM usuarios"
        );

        bool primero = true;

        while (res->next()) {
            if (!primero) json << ",";
            primero = false;

            json << "{";
            json << "\"nombre\":\"" << res->getString("nombre") << "\",";
            json << "\"edad\":" << res->getInt("edad") << ",";
            json << "\"atendido\":" << res->getInt("atendido");
            json << "}";
        }

        json << "]";

        delete res;
        delete stmt;

        return json.str();
    }
    catch (sql::SQLException& e) {
        return "{\"error\":\"No se pudo obtener pacientes\"}";
    }
}


Database::Database() {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("hospital");
}

Database::~Database() {
    delete con;
}

bool Database::listarPendientes() {
    try {
        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(
            "SELECT nombre, edad FROM usuarios WHERE atendido = 0"
        );

        cout << "\n--- PACIENTES PENDIENTES ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }

        delete res;
        delete stmt;
        return true;
    }
    catch (sql::SQLException& e) {
        cout << "Error listar pendientes: " << e.what() << endl;
        return false;
    }
}

bool Database::listarAtendidos() {
    try {
        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(
            "SELECT nombre, edad FROM usuarios WHERE atendido = 1"
        );

        cout << "\n--- PACIENTES ATENDIDOS ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }

        delete res;
        delete stmt;
        return true;
    }
    catch (sql::SQLException& e) {
        cout << "Error listar atendidos: " << e.what() << endl;
        return false;
    }
}


bool Database::insertarPaciente(string nombre, int edad) {
    try {
        unique_ptr<PreparedStatement> stmt(
            con->prepareStatement(
                "INSERT INTO usuarios(nombre, edad) VALUES(?, ?)"
            )
        );

        stmt->setString(1, nombre);
        stmt->setInt(2, edad);
        stmt->execute();

        return true;
    }
    catch (SQLException& e) {
        cout << "Error insertar: " << e.what() << endl;
        return false;
    }
}

bool Database::listarPacientes() {
    try {
        unique_ptr<Statement> stmt(con->createStatement());
        unique_ptr<ResultSet> res(
            stmt->executeQuery("SELECT nombre, edad FROM usuarios")
        );

        cout << "\n--- PACIENTES ---\n";
        while (res->next()) {
            cout << res->getString("nombre")
                << " - " << res->getInt("edad") << endl;
        }

        return true;
    }
    catch (SQLException& e) {
        cout << "Error listar: " << e.what() << endl;
        return false;
    }
}

bool Database::atenderPaciente() {
    try {
        unique_ptr<Statement> stmt(con->createStatement());

        unique_ptr<ResultSet> res(
            stmt->executeQuery(
                "SELECT id, nombre, edad FROM usuarios "
                "ORDER BY edad DESC LIMIT 1"
            )
        );

        if (!res->next()) {
            cout << "No hay pacientes\n";
            return false;
        }

        int id = res->getInt("id");
        string nombre = res->getString("nombre");
        int edad = res->getInt("edad");

        stmt->execute("UPDATE usuarios SET atendido = TRUE WHERE id = " + to_string(id));


        cout << "Paciente atendido: "
            << nombre << " (" << edad << " años)\n";

        return true;
    }
    catch (SQLException& e) {
        cout << "Error atender: " << e.what() << endl;
        return false;
    }
}

sql::Connection* Database::getConnection() {
    return con;
}
