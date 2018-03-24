//
// Created by Vet Senthil on 3/10/2018.
//

#include <iostream>
#include <fstream>

#include "NaiveBayesClassifier.h"

#include <vector>

int main() {
    NaiveBayesClassifier imageData;

    imageData.setTrainingImages(imageData.loadImages("../data/sample_training_images", "../data/sample_training_labels"));
    imageData.setTestImages(imageData.loadImages("../data/sample_test_images", "../data/sample_test_labels"));

    /*
    imageData.loadImageFeatures("../data/sample_training_images", imageData.getTrainingImages());
    imageData.loadImageLabels("../data/sample_training_labels", imageData.getTrainingImages());

    imageData.loadImageFeatures("../data/sample_test_images", imageData.getTestImages());
    imageData.loadImageLabels("../data/sample_test_labels", imageData.getTestImages());
*/

    imageData.findClassFrequencies();
    imageData.findProbabilities();
    imageData.findPriors();

    imageData.classifyImages();
    cout << "Accuracy Rate: " << imageData.getAccuracyRate() * 100 << "%" << endl;

    imageData.printConfusionMatrix();

    imageData.saveModel("../data/saved_model");
}
