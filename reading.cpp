#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "matrix.cpp"
#include "utils.cpp"

using namespace std;

const int PIXEL_DIM = 255;
const int IMAGE_SIDE = 28;

void read_from_csv(string filename, Matrix& images, Matrix& labels) {
    // images.n_rows indicates how many images to read from the csv
    ifstream file(filename);

    if (!file.is_open())
        throw runtime_error(string_format("Read MNIST data: could not open file: " + filename));

    images.clear();
    labels.clear();

    int label_value;
    string line;
    for (int image_n = 0; image_n < images.n_rows; ++image_n) {
        getline(file, line);
        istringstream line_stream(line);

        // Read label
        line_stream >> label_value;
        labels.data[image_n][label_value] = 1; // one-hot encoding
        line_stream.ignore(); // skip comma after label

        // Read each pixel
        for (int pixel_n = 0; pixel_n < images.n_cols; ++pixel_n) {
            line_stream >> images.data[image_n][pixel_n];
            images.data[image_n][pixel_n] /= PIXEL_DIM;
            line_stream.ignore(); // skip comma after pixel value
        }
    }
    file.close();

    cout << "Done reading from " + filename << endl;
}

void print_image(const Matrix& images, const int image_n) {
    for (int pixel_n = 0; pixel_n < IMAGE_SIDE * IMAGE_SIDE; ++pixel_n) {
        if (pixel_n % IMAGE_SIDE == 0)
            cout << endl << endl;

        if (images.data[image_n][pixel_n] == 0)
            cout << "  ";
        else
            cout << int(images.data[image_n][pixel_n] * 100);
        cout << ' ';
    }
    cout << endl;
}
