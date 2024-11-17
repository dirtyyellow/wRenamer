#include <iostream>
#include <filesystem>
#include <string>

#include <exiv2/exiv2.hpp>
#include "include/wRenamer.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    // cout << "Hello World!" << endl;

    // try {
    //     Exiv2::XmpParser::initialize();
    //     cout << "Exiv2" << endl;
    //     Exiv2::XmpParser::terminate();
    //     // return 0;
    // }
    // catch(const Exiv2::Error &err) {
    //     cerr << "error" << err.what() << endl;
    //     // return 1;
    // }

    fs::path dataset("C:\\Users\\10549\\Desktop\\testa");
    wRenamer(dataset);
    // exifDelete(dataset);

    return 0;
}