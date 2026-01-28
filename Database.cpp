#include "Database.h"
#include <iostream>

using namespace std;
using namespace sql;

Database::Database() {
    sql::mysql::MySQL_Driver* driver;
    driver = sql::mysql::get_mysql_driver_instance();

    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("hospital");
}

Database::~Database() {
    delete con;
}

void Database::guardarPaciente(const string& nombre, int edad) {
    PreparedStatement* stmt =
        con->prepareStatement("INSERT INTO usuarios(nombre, edad) VALUES (?, ?)");

    stmt->setString(1, nombre);
    stmt->setInt(2, edad);
    stmt->execute();
    delete stmt;
}

void Database::listarPacientes() {
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT nombre, edad FROM usuarios");

    while (res->next()) {
        cout << res->getString("nombre") << " - "
             << res->getInt("edad") << endl;
    }

    delete res;
    delete stmt;
}

void Database::atenderPaciente() {
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery(
        "SELECT id, nombre, edad FROM usuarios "
        "ORDER BY edad DESC LIMIT 1"
    );

    if (!res->next()) {
        cout << "No hay pacientes\n";
    } else {
        int id = res->getInt("id");
        cout << "Atendido: " << res->getString("nombre")
             << " (" << res->getInt("edad") << ")\n";

        Statement* del = con->createStatement();
        del->execute("DELETE FROM usuarios WHERE id=" + to_string(id));
        delete del;
    }

    delete res;
    delete stmt;
}
