//
// Created by Vet Senthil on 3/13/2018.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/NaiveBayesClassifier.h"
#include <string>

TEST_CASE("LoadTrainingImageData") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images", "../data/sample_training_labels"));
}