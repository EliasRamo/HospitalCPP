#include "Database.h"
#include "httplib.h"
#include <iostream>
#include <sstream>

using namespace std;

void iniciarServidor() {

    
        Database db;
    httplib::Server svr;

    // ENDPOINT JSON
    svr.Get("/pacientes", [&](const httplib::Request&, httplib::Response& res) {

        try {
            auto con = db.getConnection();

            unique_ptr<sql::Statement> stmt(con->createStatement());
            unique_ptr<sql::ResultSet> result(
                stmt->executeQuery("SELECT nombre, edad, atendido FROM usuarios")
            );

            stringstream json;
            json << "[";

            bool primero = true;

            while (result->next()) {

                if (!primero) json << ",";
                primero = false;

                json << "{";
                json << "\"nombre\":\"" << result->getString("nombre") << "\",";
                json << "\"edad\":" << result->getInt("edad") << ",";
                json << "\"atendido\":"
                    << (result->getBoolean("atendido") ? "true" : "false");
                json << "}";
            }

            json << "]";

            res.set_content(json.str(), "application/json");
        }
        catch (...) {
            res.set_content("{\"error\":\"Error consultando base de datos\"}", "application/json");
        }
        });

    cout << "Servidor HTTP activo en http://localhost:8085/pacientes\n";

    svr.listen("0.0.0.0", 8085);
    

}
