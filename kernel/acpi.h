#pragma once
#include "acpi_tables.h"

void *acpi_get_table(const char signature[static 4]);