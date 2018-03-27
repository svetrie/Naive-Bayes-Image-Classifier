//
// Created by Vet Senthil on 3/13/2018.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/NaiveBayesClassifier.h"
#include <string>



TEST_CASE("LoadImageLabelsTest") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));

    REQUIRE(imageClassifier.getTrainingImages()[0].getImageLabel() == 9);
    REQUIRE(imageClassifier.getTrainingImages()[29].getImageLabel() == 8);
    REQUIRE(imageClassifier.getTrainingImages()[46].getImageLabel() == 5);
}

TEST_CASE("LoadImageFeaturesTest") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));

    REQUIRE(imageClassifier.getTrainingImages()[2].getFeatures()[0][12] == 0);
    REQUIRE(imageClassifier.getTrainingImages()[0].getFeatures()[7][14] == 1);
    REQUIRE(imageClassifier.getTrainingImages()[2].getFeatures()[11][14] == 0);
}