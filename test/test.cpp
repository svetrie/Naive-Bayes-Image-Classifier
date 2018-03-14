//
// Created by Vet Senthil on 3/13/2018.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ImageData.h"


TEST_CASE("LoadTrainingImageData") {
    ImageData imageData;
    imageData.loadImages("../data/sample_training_images", imageData.getTrainingImages());
    imageData.loadLabels("../data/sample_training_labels", imageData.getTrainingImages());

    REQUIRE((*imageData.getTrainingImages())[0].getImageLabel() == 9);
}