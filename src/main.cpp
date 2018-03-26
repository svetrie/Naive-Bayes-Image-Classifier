//
// Created by Vet Senthil on 3/10/2018.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "NaiveBayesClassifier.h"

int main() {
    NaiveBayesClassifier imageClassifier;

    string user_input = "";

    while (user_input != "read" && user_input != "load") {
        cout << "Would you like to read data from files and generate a new model or load an existing model?" << endl;
        cout << "(Enter read or load)" << endl;
        getline(cin, user_input);

        if (user_input == "read") {
            const char* training_images_file;
            const char* training_labels_file;
            const char* test_images_file;
            const char* test_labels_file;

            cout << "Enter file names for training images and labels followed by test images and labels" << endl;
            cin >> training_images_file >> training_labels_file >> test_images_file >> test_labels_file;

            imageClassifier.setTrainingImages(imageClassifier.loadImages(training_images_file, training_labels_file));
            imageClassifier.setTestImages(imageClassifier.loadImages(test_images_file, test_labels_file));
        } else if (user_input == "load"){
            const char* saved_model_file;
            cout << "Enter file name of saved model" << endl;
            cin >> saved_model_file;

            imageClassifier.loadModel(saved_model_file);
        } else {
            cout << "Could not recognize your input. Please enter a valid option" << endl;
        }
    }

    cout << "Will begin classifying test images...." << endl;

    imageClassifier.findClassFrequencies();
    imageClassifier.findProbabilities();
    imageClassifier.findPriors();
    imageClassifier.classifyImages();

    cout << "Accuracy Rate: " << imageClassifier.getAccuracyRate() * 100 << "%" << endl;
    imageClassifier.printConfusionMatrix();


    string should_save = "";
    const char* file_name;

    while(should_save != "Y" && should_save != "N") {
        cout << "Would you like to save this model? (Y/N)" << endl;
        getline(cin, should_save);

        if (should_save == "Y") {
            cout << "Enter a file name to save the current model too" << endl;
            cin >> file_name;

            imageClassifier.saveModel(file_name);
            cout << "Model has been saved to " << file_name << endl;
        } else if (should_save != "N") {
            cout << "Could not recognize your input. Please enter a valid option";
        }
    }


/*
    NaiveBayesClassifier imageClassifier;

    imageClassifier.setTrainingImages(imageClassifier.loadImages("../data/sample_training_images", "../data/sample_training_labels"));
    imageClassifier.setTestImages(imageClassifier.loadImages("../data/sample_test_images", "../data/sample_test_labels"));

    imageClassifier.findClassFrequencies();
    imageClassifier.findProbabilities();
    imageClassifier.findPriors();

    imageClassifier.classifyImages();
    cout << "Accuracy Rate: " << imageClassifier.getAccuracyRate() * 100 << "%" << endl;

    imageClassifier.printConfusionMatrix();

    imageClassifier.saveModel("../data/saved_model");

    return 0;
 */

    //NaiveBayesClassifier imageClassifer;
    //imageClassifer.loadModel("../data/saved_model");

    /*
    ///mnt/c/Users/Vet Senthil/CLionProjects/naivebayes-svetrie/cmake-build-debug
    */
}


