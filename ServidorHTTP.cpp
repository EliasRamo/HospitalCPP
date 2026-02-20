#include "Database.h"
#include "httplib.h"
#include <iostream>

using namespace std;

void iniciarServidor() {

    Database db;
    httplib::Server svr;

    // Endpoint GET /pacientes
    svr.Get("/pacientes", [&](const httplib::Request&, httplib::Response& res) {

        try {
            auto con = db.getConnection();
            unique_ptr<sql::Statement> stmt(con->createStatement());
            unique_ptr<sql::ResultSet> result(
                stmt->executeQuery("SELECT nombre, edad FROM usuarios")
            );

            string salida;

            while (result->next()) {
                salida += result->getString("nombre");
                salida += " - ";
                salida += to_string(result->getInt("edad"));
                salida += "\n";
            }

            res.set_content(salida, "text/plain");
        }
        catch (...) {
            res.set_content("Error consultando base de datos", "text/plain");
        }
        });

    cout << "Servidor HTTP activo en http://localhost:8085/pacientes\n";

    svr.listen("0.0.0.0", 8085);
}
