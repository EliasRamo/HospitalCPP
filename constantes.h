#pragma once
#include <string>

namespace Constantes {

    // --- BASE DE DATOS ---
    const std::string DB_HOST = "127.0.0.1";
    const int         DB_PORT = 3306;
    const std::string DB_USER = "root";
    const std::string DB_PASS = "";
    const std::string DB_SCHEMA = "hospital";

    // --- SERVIDOR HTTP ---
    // Host y puerto (todo lo relativo al host/puerto debe venir de aquí)
    const std::string SERVER_HOST = "localhost";
    const int         SERVER_PORT = 8085;

    // --- SQL (comodines útiles, opcional) ---
  

    const std::string SQL_TODOS =
        "SELECT id, nombre, edad, atendido, fecha_registro, fecha_actualizacion "
        "FROM usuarios WHERE eliminado = 0";

    const std::string SQL_PENDIENTES =
        "SELECT id, nombre, edad FROM usuarios WHERE atendido = 0 AND eliminado = 0";

    const std::string SQL_ATENDIDOS =
        "SELECT id, nombre, edad FROM usuarios WHERE atendido = 1 AND eliminado = 0";

    const std::string SQL_SIGUIENTE =
        "SELECT id FROM usuarios WHERE atendido = 0 AND eliminado = 0 ORDER BY edad DESC LIMIT 1";
}
