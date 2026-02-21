#include "Database.h"
#include "httplib.h"
#include <iostream>

using namespace std;

void iniciarServidor() {

    Database db;
    httplib::Server svr;

    // TODOS LOS PACIENTES
    svr.Get("/pacientes", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(db.obtenerPacientesJSON(), "application/json");
        });

    // SOLO PENDIENTES
    svr.Get("/pendientes", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(db.obtenerPendientesJSON(), "application/json");
        });

    // SOLO ATENDIDOS
    svr.Get("/atendidos", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(db.obtenerAtendidosJSON(), "application/json");
        });

    cout << "Servidor HTTP activo en:\n";
    cout << "http://localhost:8085/pacientes\n";
    cout << "http://localhost:8085/pendientes\n";
    cout << "http://localhost:8085/atendidos\n";

    svr.listen("0.0.0.0", 8085);
}

