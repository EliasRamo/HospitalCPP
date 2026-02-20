#include "Hospital.h"
#include <thread>

void iniciarServidor();  // declaración messi

int main() {

    //Lanzar servidor en segundo plano
    std::thread servidor(iniciarServidor);

    //Permitir que siga ejecutando el programa
    servidor.detach();

    //Arrancar menú hospital
    Hospital h;
    h.menu();

    return 0;
}
