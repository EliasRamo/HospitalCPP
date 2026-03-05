#include "pch.h"
#include <gtest/gtest.h>
#include "Database.h"

TEST(DatabaseTest, ConsultaPacientesNoVacia)
{
    Database db;
    std::string json = db.obtenerPacientesJSON();
    EXPECT_FALSE(json.empty());
}