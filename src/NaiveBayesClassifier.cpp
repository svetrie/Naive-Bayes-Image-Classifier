//
// Created by Vet Senthil on 3/10/2018.
//

#include "NaiveBayesClassifier.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <complex>
#include <math.h>


NaiveBayesClassifier::NaiveBayesClassifier() {
    probabilities = vector<vector<vector<double>>>(NUM_CLASSES
            ,vector<vector<double>>(Image::IMAGE_SIZE, vector<double>(Image::IMAGE_SIZE, 0)));

    priors = vector<double>(NUM_CLASSES);
    class_frequencies = vector<int>(NUM_CLASSES);
    confusion_matrix = vector<vector<double>>(NUM_CLASSES, vector<double>(NUM_CLASSES, 0));
}

vector<Image> NaiveBayesClassifier::getTrainingImages() {
    return training_images;
}

vector<Image> NaiveBayesClassifier::getTestImages() {
    return test_images;
}

void NaiveBayesClassifier::setTrainingImages(vector<Image> images) {
    training_images = images;
}

void NaiveBayesClassifier::setTestImages(vector<Image> images) {
    test_images = images;
}

/*
vector<Image>* NaiveBayesClassifier::getTrainingImages() {
    vector<Image>* training_images_ptr = &training_images;
    return training_images_ptr;
}*/

/*
vector<Image>* NaiveBayesClassifier::getTestImages() {
    vector<Image>* testing_images_ptr = &test_images;
    return testing_images_ptr;
}*/

/*
 * MAke this return an image vector so you dont have to pass in a pointer

void NaiveBayesClassifier::loadImageFeatures(const char *file_name, vector<Image> *images) {
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
         cout << "Unable to open file datafile.txt" << endl;
    }

    vector<vector<bool>> training_image;
    string line;

    for(int i = 0; getline(inFile, line); i = (i + 1) % 28) {
        vector<bool> row(28, false);

        for (int j = 0; j < line.size(); ++j) {
            row[j] = (line[j] != ' ');
        }

        training_image.push_back(row);

        if (i == 27) {
            Image image(training_image);
            images->push_back(image);

            training_image.clear();
        }
    }

    inFile.close();
}

 */

vector<Image> NaiveBayesClassifier::loadImageFeatures(const char *file_name) {
    vector<Image> images;

    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
        cout << "Unable to open file " << file_name << endl;
    }

    vector<vector<bool>> image_features;
    string line;

    for(int i = 0; getline(inFile, line); i = (i + 1) % 28) {
        vector<bool> row(28, false);

        for (int j = 0; j < line.size(); ++j) {
            row[j] = (line[j] != ' ');
        }

        image_features.push_back(row);

        if (i == 27) {
            Image image(image_features);
            images.push_back(image);

            image_features.clear();
        }
    }

    inFile.close();
    return images;
}

/*
 * Return an int vector of labels and use a helper method to assign labels
 * to images. Don't pass in a pointer


void NaiveBayesClassifier::loadImageLabels(const char *file_name, vector<Image> *images) {
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
        cout << "Unable to open file datafile.txt" << endl;
    }

    string image_label;
    int i = 0;

    while (getline(inFile, image_label)) {
        stringstream strstream(image_label);
        int label_num = 0;
        strstream >> label_num;

        (*images)[i++].setImageLabel(label_num);
    }

    inFile.close();
}
*/

vector<int> NaiveBayesClassifier::loadImageLabels(const char *file_name) {
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
        cout << "Unable to open file" << file_name << endl;
    }

    vector<int> image_labels;
    string label;

    while (getline(inFile, label)) {
        stringstream strstream(label);
        int label_num = 0;
        strstream >> label_num;

        image_labels.push_back(label_num);
    }

    inFile.close();
    return image_labels;
}

vector<Image> NaiveBayesClassifier::loadImages(const char* img_file_name, const char* labels_file_name) {
    vector<Image> images;
    vector<int> labels;

    images = loadImageFeatures(img_file_name);
    labels = loadImageLabels(labels_file_name);

    for (int i = 0; i < images.size(); ++i) {
        images[i].setImageLabel(labels[i]);
    }

    return images;
}

void NaiveBayesClassifier::loadModel(const char* file_name) {
    ifstream myFile;
    myFile.open(file_name);

    cout << "Seg fault 1 avoided" << endl;

    string feature_probabiltity;

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); ++j) {
            for (int k = 0; k < probabilities[0][0].size(); ++k) {
                //myFile.getline(feature_probabiltity, 10);
                getline(myFile, feature_probabiltity);
                cout << feature_probabiltity << endl;
                probabilities[i][j][k] = stod(feature_probabiltity);
            }
        }
    }

    cout << "Seg fault 2 avoided" << endl;

    string prior_value;

    for (int m = 0; m < priors.size(); ++m) {
        getline(myFile, prior_value);
        priors[m] = stod(prior_value);
        cout << prior_value << endl;
    }

    cout << "Seg fault 3 avoided" << endl;

    myFile.close();

    cout << "Closed file" << endl;
}

void NaiveBayesClassifier::saveModel(const char* file_name) {
    ofstream newFile;
    newFile.open(file_name);

    for (vector<vector<double>> class_features : probabilities) {
        for (vector<double> row_features : class_features) {
            for (double feature_value : row_features) {
                newFile << feature_value << endl;
            }
        }
    }

    for (double class_prior : priors) {
        newFile << class_prior << endl;
    }

}

void NaiveBayesClassifier::findClassFrequencies() {
    for (Image image : training_images) {
        class_frequencies[image.getImageLabel()]++;
    }
}

int NaiveBayesClassifier::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    for (Image image : training_images) {
        if (image.getImageLabel() == class_num && image.getFeatures()[row][col]) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void NaiveBayesClassifier::findProbabilities() {
    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); j++) {
            for (int k = 0; k < probabilities[0][0].size(); k++) {
                probabilities[i][j][k] = ((LAPLACE_VALUE + getFeaturesSum(i, j, k))
                                          / (2 * LAPLACE_VALUE + class_frequencies[i]));
            }
        }
    }
}

void NaiveBayesClassifier::findPriors() {
    for (int i = 0; i < priors.size(); ++i) {
        priors[i] = double(class_frequencies[i] * 1.0) / training_images.size();
    }
}

vector<double> NaiveBayesClassifier::getLogPriors() {
    vector<double> log_priors(NUM_CLASSES);

    for (double class_probability : priors) {
        log(class_probability);
    }

    return log_priors;
}

int NaiveBayesClassifier::getMostProbableClass(vector<double> class_probabilities) {
    int class_num = 0;

    for (int i = 1; i < NUM_CLASSES; i++) {
        if (class_probabilities[i] > class_probabilities[class_num]) {
            class_num = i;
        }
    }

    return class_num;
}

double NaiveBayesClassifier::findImageClassProbability(Image img, int class_num) {
    //Image test_img = img;
    Image& test_img = img;
    double class_probability;

    for (int i = 0; i < test_img.getFeatures().size(); ++i) {
        for (int j = 0; j < test_img.getFeatures()[0].size(); ++j) {
            if (test_img.getFeatures()[i][j]) {
                class_probability += log(probabilities[class_num][i][j]);
            } else {
                class_probability += log(1 - probabilities[class_num][i][j]);
            }
        }
    }

    cout << class_probability << endl;

    return class_probability;
   /*
    for (int k = 0; k < test_images[i].getImage().size(); ++k) {
        for (int m = 0; m < test_images[i].getImage()[0].size(); ++m) {
            if (test_images[i].getFeatures()[k][m]) {
                class_probabilities[j] += log(probabilities[j][k][m]);
            } else {
                class_probabilities[j] += log(1 - probabilities[j][k][m]);
            }
        }
    }*/
}

void NaiveBayesClassifier::classifyImages() {
    vector<double> class_probabilities;
    vector<double> initial_probabilities = getLogPriors();
    class_probabilities = initial_probabilities;

    for (int i = 0; i < test_images.size(); i++) {
        for (int j = 0; j < NUM_CLASSES; ++j) {
            //Image img = test_images[i];
            //Image& test_img = test_images[i];
            class_probabilities[j] = findImageClassProbability(test_images[i], j);
            /* create helper function for these two for loops
            for (int k = 0; k < test_images[i].getImage().size(); ++k) {
                for (int m = 0; m < test_images[i].getImage()[0].size(); ++m) {
                    if (test_images[i].getFeatures()[k][m]) {
                        class_probabilities[j] += log(probabilities[j][k][m]);
                    } else {
                        class_probabilities[j] += log(1 - probabilities[j][k][m]);
                    }
                }
            }*/
        }

        test_images[i].setPredictedLabel(getMostProbableClass(class_probabilities));
        class_probabilities = initial_probabilities;
    }
}

// changed enhanced for loop
double NaiveBayesClassifier::getAccuracyRate() {
    int num_correct_predictions = 0;

    for (auto &test_img : test_images) {

        cout << test_img.getPredictedLabel() << endl;
        cout << test_img.getImageLabel() << endl;
        cout << endl;

        if (test_img.getPredictedLabel() == test_img.getImageLabel()) {
            num_correct_predictions++;
        }
    }

    return ((double)(num_correct_predictions) / test_images.size());
}

void NaiveBayesClassifier::printConfusionMatrix() {
    vector<double> test_class_frequencies(NUM_CLASSES,0);

    for (auto &test_img : test_images) {
        test_class_frequencies[test_img.getImageLabel()]++;
        confusion_matrix[test_img.getImageLabel()][test_img.getPredictedLabel()]++;
    }

    for (int i = 0; i < confusion_matrix.size(); ++i) {
        for (int j = 0; j < confusion_matrix[0].size(); ++j) {
            confusion_matrix[i][j] = (confusion_matrix[i][j] / test_class_frequencies[i]) * 100;
            confusion_matrix[i][j] = floor(confusion_matrix[i][j] * 100 + 0.5) / 100;

            cout << confusion_matrix[i][j] << "   ";
        }
        cout << endl;
    }
}