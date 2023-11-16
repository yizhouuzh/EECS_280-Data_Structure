// Project UID af1f95f547e44c8ea88730dfb185559d

#include"Matrix.h"
#include "Image.h"
#include"processing.h"
#include<iostream>
#include<string>
#include <fstream>
#include <cstdlib>
using namespace std;
int main(int argc, char*argv[]) {

    if(argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" 
        << endl;
        return 1;
    }

    ifstream ins;
    string input_file = argv[1];
    string output_file = argv[2];
    int new_width = atoi(argv[3]);
    ins.open(input_file);
    if(!ins.is_open()) {
        cout << "Error opening file: " << input_file << endl;
        return 1;
    }

    Image* img = new Image;
    Image_init(img, ins);
    ins.close();

    if (new_width <= 0 || new_width > Image_width(img)) {
        cout << "New_width must be positive and less than original width" << endl;
        return 1;
    }

    if (argc == 5) {
        int new_height = atoi(argv[4]);
        if (new_height <= 0 || new_height > Image_height(img)) {
            cout << "New_height must be positive and less than original width" << endl;
            return 1;
        } else {
            seam_carve(img, new_width, new_height);
        }
    }

    if (argc == 4) {
        seam_carve_width(img, new_width);
    } 

    ofstream outs;
    outs.open(output_file);
    Image_print(img, outs);
    delete img;
    return 0;
}