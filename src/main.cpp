//
// Created by Vet Senthil on 3/10/2018.
//

#include <iostream>
#include <fstream>

#include "ImageData.h"

#include <vector>

int main() {
    ImageData imageData;

    imageData.loadImages("../data/sample_training_images", imageData.getTrainingImages());
    imageData.loadLabels("../data/sample_training_labels", imageData.getTrainingImages());

    imageData.loadImages("../data/sample_test_images", imageData.getTestImages());
    imageData.loadLabels("../data/sample_test_labels", imageData.getTestImages());

    imageData.findClassFrequencies();
    imageData.findProbabilities();
    imageData.findPriors();

    imageData.classifyImages();

    imageData.saveModel("../data/saved_model");
    imageData.loadModel("../data/saved_model");

    return 0;
}
