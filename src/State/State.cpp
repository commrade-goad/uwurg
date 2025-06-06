#include "State.hpp"
#include <cstdio>

PState::PState() {}

bool PState::write_to_file(const char *file_path) {
    FILE *f = fopen(file_path, "wb");
    if (!f) return false;

    bool ok = fwrite(this, sizeof(PState), 1, f) == 1;
    fclose(f);
    return ok;
}

bool PState::read_from_file(const char *file_path) {
    FILE *f = fopen(file_path, "rb");
    if (!f) return false;

    bool ok = fread(this, sizeof(PState), 1, f) == 1;
    fclose(f);
    return ok;
}
