#include "Hospital.h"
#include <iostream>

using namespace std;

void Hospital::menu() {
    int opcion;

    do {
        cout << "\n--- HOSPITAL ---\n";
        cout << "1. Ingresar paciente\n";
        cout << "2. Atender paciente\n";
        cout << "3. Listar pacientes\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            int edad;
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Edad: ";
            cin >> edad;
            db.guardarPaciente(nombre, edad);
        }
        else if (opcion == 2) {
            db.atenderPaciente();
        }
        else if (opcion == 3) {
            db.listarPacientes();
        }

    } while (opcion != 0);
}
