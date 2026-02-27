#include "Hospital.h"
#include <iostream>

using namespace std;

void Hospital::menu() {
    Database db;
    int opcion;

    do {
        cout << "\n--- HOSPITAL ---\n";
        cout << "1. Ingresar paciente\n";
        cout << "2. Atender paciente (por edad)\n";
        cout << "3. Mostrar pacientes\n";
        cout << "4. Mostrar pacientes pendientes\n";
        cout << "5. Mostrar pacientes atendidos\n";
        cout << "6. Eliminar paciente\n";
        cout << "7. Eliminar paciente definitivamente\n";
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

            if (db.insertarPaciente(nombre, edad))
                cout << "Paciente guardado correctamente\n";
            else
                cout << "Error al guardar paciente\n";
        }

        else if (opcion == 2) {
            if (!db.atenderPaciente())
                cout << "No se pudo atender paciente\n";
        }

        else if (opcion == 3) {
            if (!db.listarPacientes())
                cout << "Error al listar pacientes\n";
        }

        else if (opcion == 4) {
            if (!db.listarPendientes())
                cout << "Error al listar pacientes pendientes\n";
        }

        else if (opcion == 5) {
            if (!db.listarAtendidos())
                cout << "Error al listar pacientes atendidos\n";
        }

        else if (opcion == 6) {
            int id;
            cout << "ID del paciente a eliminar: ";
            cin >> id;

            if (db.eliminarPaciente(id))
                cout << "Paciente eliminado logicamente\n";
            else
                cout << "No se pudo eliminar el paciente\n";
        }


        else if (opcion == 7) {
            int id;
            cout << "ID del paciente a eliminar definitivamente: ";
            cin >> id;
            if (db.eliminarPacienteFisico(id))
                cout << "Paciente eliminado definitivamente\n";
            else
                cout << "No se pudo eliminar el paciente\n";
		}

    } while (opcion != 0);
}