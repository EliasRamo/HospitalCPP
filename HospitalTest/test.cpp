#include "pch.h"
#include "Database.h"
#include <gtest/gtest.h>

TEST(DatabaseTest, ConsultaPacientesNoVacia)
{
    Database db;

    std::string json = db.obtenerPacientesJSON();

    EXPECT_FALSE(json.empty());
}