#ifndef WRENAMER_H
#define WRENAMER_H

using namespace std;
namespace fs = std::filesystem;

void wRenamer(fs::path& dataset);
void exifDelete(fs::path& dataset);

#endif