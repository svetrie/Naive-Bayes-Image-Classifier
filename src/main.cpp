//
// Created by Vet Senthil on 3/10/2018.
//

#include <iostream>
#include <fstream>

#include "ImageData.h"

#include <vector>

using namespace std;

int main() {
    ImageData imageData;
    imageData.loadImages(imageData.getTrainingImages());
    imageData.loadLabels(imageData.getTrainingImages());

    if ((*imageData.getTrainingImages())[0].getImage().size() == 28) {
        cout << "load images working correctly" << endl;
    }

    if ((*(*imageData.getTrainingImages())[2].getImageLabel()) == 4) {
        cout << "load labels working correctly" << endl;
    }

    return 0;
}
