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

    imageData.loadImages("../data/sample_training_images", imageData.getTrainingImages());

    //cout << "loads training images" << endl;

    if ((*imageData.getTrainingImages())[3].getImage().size() == 28) {
        cout << "load images working correctly" << endl;
    }

    imageData.loadLabels("../data/sample_training_labels", imageData.getTrainingImages());

    //cout << "loads training labels" << endl;

    if ((*imageData.getTrainingImages())[2].getImageLabel() == 4) {
        cout << "load labels working correctly" << endl;
    }

    imageData.loadImages("../data/sample_test_images", imageData.getTestImages());

    cout << "loads test images" << endl;

    imageData.loadLabels("../data/sample_test_labels", imageData.getTestImages());

    cout << "loads test labels" << endl;

    imageData.findProbabilities();

    //cout << "probabilities working" << endl;

    imageData.findPriors();

    imageData.classifyImages();

    cout << imageData.getAccuracyRate() << endl;

    //cout << "priors working" << endl;

    //imageData.getLogPriors();

    return 0;
}
