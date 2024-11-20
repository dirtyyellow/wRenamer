#include <iostream>
#include <filesystem>
#include <string>

#include <exiv2/exiv2.hpp>
#include "wRenamer.h"


using namespace std;
namespace fs = std::filesystem;

void wRenamer(fs::path& dataset) {

    int count = 0;

    Exiv2::XmpParser::initialize();

    if(!fs::exists(dataset) || !fs::is_directory(dataset)) {
        cerr << "Directory does not exist or is not a directory." << endl;
        return;
    }
 
    fs::directory_iterator list(dataset);
    for(auto&& iter : list) {
        if(iter.is_regular_file()) {
            string picSuffix = iter.path().extension().string();
            fs::path prePath = iter.path();          
            fs::path curPath = dataset;
            
            Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(prePath.string());
            if(!image.get()) {
                cout << "Cannot open file:  " << prePath.string() << endl;
                continue;
            }

            // Read the metadata
            image->readMetadata();

            // Access the EXIF data
            Exiv2::ExifData& exifData = image->exifData();
            if(exifData.empty()) {
                cout << setw(4) << setfill('0') << ++count << ".";
        		cout << "Not Find ExifInfo:  " << prePath.string() << endl;
        		continue;
            }

            // TESTING
            // Exiv2::ExifData::const_iterator end = exifData.end();
            // for(Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
            //     cout << i->key() << " = " << i->value() << endl;
            // }
            //
            // Exiv2::IptcData& iptcData = image->iptcData();
            // for(Exiv2::IptcData::const_iterator i = iptcData.begin(); i != iptcData.end(); ++i) {
            //     cout << i->key() << " = " << i->value() << endl;
            // }
            //
            // Exiv2::XmpData& xmpData = image->xmpData();
            // for (Exiv2::XmpData::const_iterator i = xmpData.begin(); i != xmpData.end(); ++i) {
            //     cout << i->key() << " = " << i->value() << endl;
            // }

            Exiv2::ExifKey temp = Exiv2::ExifKey("Exif.Image.DateTime");
        	Exiv2::ExifData::iterator pos = exifData.findKey(move(temp));

            if(pos == exifData.end()) {
                cout << setw(4) << setfill('0') << ++count << ".";
                cout << "Unknow:             "  << prePath.string() << endl;
                continue;
            }
            else {
                string picTime = pos->value().toString();
                // cout << "Time:" << pos->value().toString() << endl;
                string newPicName = "IMG_" + picTime.substr(0, 4) + picTime.substr(5, 2) \
                                    + picTime.substr(8, 2) + "_" + picTime.substr(11, 2) \
                                    + picTime.substr(14, 2) + picTime.substr(17, 2) + picSuffix;
                // cout << newPicName << endl;
                curPath.append(newPicName); 
            }

            try {
                fs::rename(prePath, curPath);
                cout << setw(4) << setfill('0') << ++count << ".";
                cout << "Renamed:            " << prePath.string() << " to " \
                    << curPath.filename().string() << endl;
            } 
            catch(const fs::filesystem_error& err) {
                cerr << "Error renaming file: " << err.what() << endl;
            }
        }
    }

    Exiv2::XmpParser::terminate();

    return;
}

void exifDelete(fs::path& dataset) {

    Exiv2::XmpParser::initialize();

    if(!fs::exists(dataset) || !fs::is_directory(dataset)) {
        cerr << "Directory does not exist or is not a directory." << endl;
        return;
    }
 
    fs::directory_iterator list(dataset);
    for(auto&& iter : list) {
        if(iter.is_regular_file()) {
            fs::path picPath = iter.path();          
            Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(picPath.string());
            if(!image.get()) {
                cout << "Cannot open file    " << picPath.string() << endl;
                continue;
            }

            image->readMetadata();

            Exiv2::ExifData& exifData = image->exifData();

        	if(exifData.empty()) {
        		cout << "Not Find ExifInfo    " << picPath.string() << endl;
        		continue;
            }

            // Exiv2::ExifData::iterator end = exifData.end();
            // for(Exiv2::ExifData::iterator i = exifData.begin(); i != end; ++i) {
            //    exifData.erase(i);
            // }
            Exiv2::ExifKey temp = Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude");
        	Exiv2::ExifData::iterator pos = exifData.findKey(temp);
        	if(pos != exifData.end()) {
        		exifData.erase(pos);
        		cout << "Deleted key  " << temp << "      "<< picPath.string() << endl;
        	}
        	else continue;

            image->setExifData(exifData);
	        image->writeMetadata();

            // cout << "press any key ..." << endl;
            // cin.get();
        }
    }

    Exiv2::XmpParser::terminate();
    return;
}