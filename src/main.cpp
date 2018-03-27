//
// Created by Vet Senthil on 3/10/2018.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "NaiveBayesClassifier.h"


bool loadImageData(NaiveBayesClassifier& imageClassifier) {
    string user_input = "";
    bool is_new_model;

    while (user_input != "read" && user_input != "load") {
        cout << "Would you like to read data from files and generate a new model or load an existing model?" << endl;
        cout << "(Enter read or load)" << endl;
        getline(cin, user_input);

        if (user_input == "read") {
            string training_images_file;
            string training_labels_file;
            cout << "Enter file path for training images" << endl;
            getline(cin, training_images_file);
            cout << "Enter file path for training labels" << endl;
            getline(cin, training_labels_file);

            imageClassifier.setTrainingImages(imageClassifier.loadImages(training_images_file.c_str()
                    , training_labels_file.c_str()));
            is_new_model = true;
        } else if (user_input == "load"){
            string saved_model_file;
            cout << "Enter file name of saved model" << endl;
            getline(cin, saved_model_file);

            imageClassifier.loadModel(saved_model_file.c_str());
        } else {
            cout << "Could not recognize your input. Please enter a valid option" << endl;
        }
    }

    string test_images_file;
    string test_labels_file;
    cout << "Enter the file path for the test images" << endl;
    getline(cin, test_images_file);
    cout << "Enter the file path for the test labels" << endl;
    getline(cin, test_labels_file);

    imageClassifier.setTestImages(imageClassifier.loadImages(test_images_file.c_str(), test_labels_file.c_str()));
    return is_new_model;
}

void classifyTestData(NaiveBayesClassifier& imageClassifier, bool is_new_model) {
    cout << "Will begin classifying test images...." << endl;

    if (is_new_model) {
        imageClassifier.findClassFrequencies();
        imageClassifier.findProbabilities();
        imageClassifier.findPriors();
    }
    imageClassifier.classifyImages();

    cout << "Accuracy Rate: " << imageClassifier.getAccuracyRate() * 100 << "%" << endl;
    imageClassifier.printConfusionMatrix();
}

void saveModelData(NaiveBayesClassifier& imageClassifier) {
    string should_save = "";
    string file_name;

    while(should_save != "Y" && should_save != "N") {
        cout << "Would you like to save this model? (Y/N)" << endl;
        getline(cin, should_save);

        if (should_save == "Y") {
            cout << "Enter a file name to save the current model to" << endl;
            getline(cin, file_name);

            imageClassifier.saveModel(file_name.c_str());
            cout << "Model has been saved" << endl;
        } else if (should_save != "N") {
            cout << "Could not recognize your input. Please enter a valid option";
        }
    }
}

int main() {
    NaiveBayesClassifier imageClassifier;

    bool is_new_model = loadImageData(imageClassifier);
    classifyTestData(imageClassifier, is_new_model);
    saveModelData(imageClassifier);


   /* LOADING TEST AND TRAINING DATA

    string user_input = "";

    while (user_input != "read" && user_input != "load") {
        cout << "Would you like to read data from files and generate a new model or load an existing model?" << endl;
        cout << "(Enter read or load)" << endl;
        getline(cin, user_input);

        if (user_input == "read") {
            string training_images_file;
            string training_labels_file;
            //const char* test_images_file;
            //const char* test_labels_file;

            cout << "Enter file path for training images" << endl;
            getline(cin, training_images_file);
            cout << "Enter file path for training labels" << endl;
            getline(cin, training_labels_file);

            //cin >> training_images_file >> training_labels_file >> test_images_file >> test_labels_file;

            imageClassifier.setTrainingImages(imageClassifier.loadImages(training_images_file.c_str()
                    , training_labels_file.c_str()));
            //imageClassifier.setTestImages(imageClassifier.loadImages(test_images_file, test_labels_file));
        } else if (user_input == "load"){
            //const char* saved_model_file;
            string saved_model_file;
            cout << "Enter file name of saved model" << endl;
            getline(cin, saved_model_file);

            imageClassifier.loadModel(saved_model_file.c_str());
        } else {
            cout << "Could not recognize your input. Please enter a valid option" << endl;
        }
    }

    string test_images_file;
    string test_labels_file;

    cout << "Enter the file path for the test images" << endl;
    getline(cin, test_images_file);
    cout << "Enter the file path for the test labels" << endl;
    getline(cin, test_labels_file);

    imageClassifier.setTestImages(imageClassifier.loadImages(test_images_file.c_str(), test_labels_file.c_str())); */

   /* CLASSIFICATION PROCESS

    cout << "Will begin classifying test images...." << endl;

    if (user_input == "read") {
        imageClassifier.findClassFrequencies();
        imageClassifier.findProbabilities();
        imageClassifier.findPriors();
    }

    imageClassifier.classifyImages();

    cout << "Accuracy Rate: " << imageClassifier.getAccuracyRate() * 100 << "%" << endl;
    imageClassifier.printConfusionMatrix();

    */

 /* SAVING MODEL
    string should_save = "";
    //const char* file_name;
    string file_name;

    while(should_save != "Y" && should_save != "N") {
        cout << "Would you like to save this model? (Y/N)" << endl;
        getline(cin, should_save);

        if (should_save == "Y") {
            cout << "Enter a file name to save the current model too" << endl;
            getline(cin, file_name);

            imageClassifier.saveModel(file_name.c_str());
            cout << "Model has been saved to " << file_name << endl;
        } else if (should_save != "N") {
            cout << "Could not recognize your input. Please enter a valid option";
        }
    }

  */

    /*DIRECTORY OF EXECUTABLE
    ///mnt/c/Users/Vet Senthil/CLionProjects/naivebayes-svetrie/cmake-build-debug
    */

    return 0;
}


