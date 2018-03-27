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

TEST_CASE("FindClassFrequenciesTest") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));
    imageClassifier.findClassFrequencies();

    vector<int> expected_frequencies = {3, 10, 4, 3, 5, 5, 4, 4, 5, 4};

    for (int i = 0; i < imageClassifier.getClassFrequencies().size(); ++i) {
        REQUIRE(imageClassifier.getClassFrequencies()[i] == expected_frequencies[i]);
    }
}

TEST_CASE("CalculatePriorsTest") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));
    imageClassifier.findClassFrequencies();
    imageClassifier.findPriors();

    vector<double> expected_priors = {.0638, .2128, .0851, .0638, .1064, .1064, .0851, .0851, .1064, .0851};

    for (int i = 0; i < imageClassifier.getPriors().size(); ++i) {
        REQUIRE(std::abs(imageClassifier.getPriors()[i] - expected_priors[i]) < 0.0001);
    }
}

TEST_CASE("FindLogPriorsTest") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));
    imageClassifier.findClassFrequencies();
    imageClassifier.findPriors();

    vector<double> log_priors = imageClassifier.findLogPriors();

    for (int i = 0; i < imageClassifier.getPriors().size(); ++i) {
        REQUIRE(log(imageClassifier.getPriors()[i]) == log_priors[i]);
    }
}

TEST_CASE("GetFeaturesSum") {
    NaiveBayesClassifier imageClassifier;
    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images"
            , "../data/sample_training_labels"));

    REQUIRE(imageClassifier.getFeaturesSum(9, 11, 16) == 4);
    REQUIRE(imageClassifier.getFeaturesSum(1, 12, 13) == 9);
    REQUIRE(imageClassifier.getFeaturesSum(0, 15, 15) == 0);
}

