
#include "Database.h"
#include "constantes.h"
#include "httplib.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <memory>

using namespace std;



void iniciarServidor() {
    // Creamos la BD y el servidor en heap para que vivan mientras el programa corre.
    Database* db = new Database();           // se mantiene vivo durante toda la ejecución
    httplib::Server* svr = new httplib::Server();

    // Rutas (no son constantes globales, son variables locales como pediste)
    string rutaTodos = "/pacientes";
    string rutaPendientes = "/pacientes/pendientes";
    string rutaAtendidos = "/pacientes/atendidos";

    // ENDPOINT: todos (devuelve JSON)
    svr->Get(rutaTodos.c_str(), [db](const httplib::Request&, httplib::Response& res) {
        try {
            string json = db->obtenerPacientesJSON();
            res.set_content(json, "application/json");
        }
        catch (...) {
            res.set_content("{\"error\":\"Error consultando base de datos\"}", "application/json");
        }
        });

    // ENDPOINT: pendientes
    svr->Get(rutaPendientes.c_str(), [db](const httplib::Request&, httplib::Response& res) {
        try {
            string json = db->obtenerPendientesJSON();
            res.set_content(json, "application/json");
        }
        catch (...) {
            res.set_content("{\"error\":\"Error consultando base de datos (pendientes)\"}", "application/json");
        }
        });

    // ENDPOINT: atendidos
    svr->Get(rutaAtendidos.c_str(), [db](const httplib::Request&, httplib::Response& res) {
        try {
            string json = db->obtenerAtendidosJSON();
            res.set_content(json, "application/json");
        }
        catch (...) {
            res.set_content("{\"error\":\"Error consultando base de datos (atendidos)\"}", "application/json");
        }
        });

    string rutaEliminar = "/pacientes/eliminar";

    svr->Delete(rutaEliminar.c_str(), [db](const httplib::Request& req, httplib::Response& res) {

        if (!req.has_param("id")) {
            res.set_content("{\"error\":\"Falta id\"}", "application/json");
            return;
        }

        int id = stoi(req.get_param_value("id"));

        if (db->eliminarPaciente(id)) {
            res.set_content("{\"mensaje\":\"Paciente eliminado logicamente\"}", "application/json");
        }
        else {
            res.set_content("{\"error\":\"No se pudo eliminar\"}", "application/json");
        }
        });

    // Mostrar en consola las rutas activas (con host y puerto desde Constantes)
    cout << "Servidor HTTP activo en http://"
        << Constantes::SERVER_HOST << ":" << Constantes::SERVER_PORT << endl;
    cout << "Endpoints disponibles:" << endl;
    cout << "  - Todos:      http://" << Constantes::SERVER_HOST << ":" << Constantes::SERVER_PORT << rutaTodos << endl;
    cout << "  - Pendientes: http://" << Constantes::SERVER_HOST << ":" << Constantes::SERVER_PORT << rutaPendientes << endl;
    cout << "  - Atendidos:  http://" << Constantes::SERVER_HOST << ":" << Constantes::SERVER_PORT << rutaAtendidos << endl;

    // Iniciamos el servidor en un thread separado para no bloquear la consola
    std::thread([svr]() {
        // listen bloquea dentro del thread; si falla, imprime un error simple
        if (!svr->listen("0.0.0.0", Constantes::SERVER_PORT)) {
            cerr << "Error: no se pudo iniciar el servidor HTTP en el puerto "
                << Constantes::SERVER_PORT << endl;
        }
        }).detach();

    // Nota: no borramos 'db' ni 'svr' aquí. Se mantienen durante la ejecución
    // (en una app real harías un shutdown y cleanup ordenado).
}
