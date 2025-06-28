#!/usr/bin/env python
# coding: utf-8

# In[1]:


import math
import csv
from random import shuffle
#import counter to find the most common element in a list
from collections import Counter


# In[2]:


class DataHandler:
    def __init__(self, filepath):
        # Constructor to initialize the filepath
        self.filepath = filepath

    def read_csv(self):
        # Read data from a CSV file and store it in a list
        with open(self.filepath, 'r') as file:
            csv_reader = csv.reader(file)
            next(csv_reader)  # Skip the header row
            dataset = [row for row in csv_reader]
        return dataset

    def train_test_split(self, dataset, test_size=0.2):
        # Shuffle the dataset to ensure randomness
        shuffle(dataset)
        # Determine the split index based on the test size
        split_index = int(len(dataset) * (1 - test_size))
        # Split the dataset into training and testing sets
        return dataset[:split_index], dataset[split_index:]

    def separate_features_labels(self, dataset):
        # Separate the features and labels from the dataset
        # Convert the feature values to floats for computation
        features = [list(map(float, data[:-1])) for data in dataset]  # Exclude only label, which is the last column; do not exclude the first column since there's no id
        labels = [data[-1] for data in dataset]  # The label is the last element in each row
        return features, labels


# In[3]:


#define a base class, so that both algorithm classes can use the normalization and report method
#No constructor needed
class PredictionResult:
    def normalizing_feature_values(self, X):
    # The purpose of this method is to modify the feature data, so that all values are between 0 and 1.
        # list that store maximum values of X1, X2.... (columns)
        max_X = []
        # list that store minimum values of X1, X2.... (columns)
        min_X = []
        # list that store final normalized data
        modified_X = []
        # count how many columns of features are there in total
        n = 0
        for index, value in enumerate(X[0]):
            n = index + 1
        # calculate maximum and minimum values of each columns, then add them into max_X and min_X lists respectively
        for current_column in range(n):
            # calculate max
            max = 0
            for feature in X:
                if feature[current_column] > max:
                    max = feature[current_column]
            max_X.append(max)
            # calculate min
            min = 10000
            for feature in X:
                if feature[current_column] < min:
                    min = feature[current_column]
            min_X.append(min)
        # start to append normalized data into modified_X list
        for feature in X:
            new_feature = []
            for current_column in range(n):
                # Normalization formula: zi = (xi – min (x)) / (max (x) – min (x))
                new_value = (feature[current_column] - min_X[current_column]) / (max_X[current_column] - min_X[current_column])
                new_feature.append(new_value)
            modified_X.append(new_feature)
        return modified_X
    
    def classification_report(self, y_true, y_pred):
        # Generate a classification report for the predictions
        unique_labels = set(y_true)
        report = {}
        for label in unique_labels:
            tp = sum(1 for i in range(len(y_true)) if y_true[i] == label and y_pred[i] == label)
            fp = sum(1 for i in range(len(y_true)) if y_true[i] != label and y_pred[i] == label)
            fn = sum(1 for i in range(len(y_true)) if y_true[i] == label and y_pred[i] != label)
            tn = sum(1 for i in range(len(y_true)) if y_true[i] != label and y_pred[i] != label)

            # Calculate precision, recall, and F1-score for each class
            precision = tp / (tp + fp) if tp + fp > 0 else 0
            recall = tp / (tp + fn) if tp + fn > 0 else 0
            f1 = 2 * (precision * recall) / (precision + recall) if precision + recall > 0 else 0
            accuracy = (tp + tn) / len(y_true)

            report[label] = {
                'Precision': precision,
                'Recall': recall,
                'F1-score': f1,
                'Accuracy': accuracy
            }

        return report


# In[4]:


#NaiveBayes Algorithm
class NaiveBayesClassifier(PredictionResult):
    def __init__(self):
        # Initialize dictionaries to store the means, standard deviations,
        # and class probabilities for each class
        self.means = {}
        self.stds = {}
        self.class_probabilities = {}

    def fit(self, X, y):
        # Train the classifier by calculating the class probabilities
        # and the means and standard deviations for each feature
        self._calculate_class_probabilities(y)
        self._calculate_means_stds(X, y)

    def _calculate_class_probabilities(self, y):
        # Calculate the probability of each class based on label frequency
        class_counts = {label: y.count(label) for label in set(y)}
        total_count = len(y)
        self.class_probabilities = {label: count / total_count for label, count in class_counts.items()}

    def _calculate_means_stds(self, X, y):
        # Calculate the mean and standard deviation for each class and each feature
        for label in self.class_probabilities:
            # Extract features for instances of the current class
            label_features = [X[i] for i in range(len(X)) if y[i] == label]
            # Calculate mean and standard deviation for each feature
            self.means[label] = [sum(f) / len(f) for f in zip(*label_features)]
            self.stds[label] = [math.sqrt(sum([(x - mean)**2 for x in f]) / len(f)) for mean, f in zip(self.means[label], zip(*label_features))]

    def _calculate_probability(self, x, mean, std):
        # Calculate the probability of a feature value with a Gaussian distribution
        exponent = math.exp(-(math.pow(x-mean,2)/(2*math.pow(std,2))))
        return (1 / (math.sqrt(2*math.pi) * std)) * exponent          
            
    def predict_single(self, input_features):
        # Predict the class of a single feature set
        probabilities = {}
        for label, _ in self.means.items():
            # Start with the prior probability of the class
            probabilities[label] = self.class_probabilities[label]
            # Multiply by the probability of each feature
            for i, feature in enumerate(input_features):
                probabilities[label] *= self._calculate_probability(feature, self.means[label][i], self.stds[label][i])
        # Return the class with the highest probability
        return max(probabilities, key=probabilities.get)

    def predict(self, X):
        # Predict a list of feature sets
        return [self.predict_single(features) for features in X]


# In[5]:


#K-Nearest neighbour Algorithm
class KNN(PredictionResult):
    def __init__(self, K_value):
    # Create the constructor
    # Store the K value as property
        self.K = K_value
    
    # X: train feature which we hope to find label   X_list: all train features    y_list: all train labels
    def find_correspond_label(self, X, X_list, y_list):
    # The purpose of this method is to figure out which label does a feature belong to
        for index, value in enumerate(X_list):
            if value == X:
                y = y_list[index]
        return y
        
    def calculate_distance_single(self, single_test_X, train_X, train_y):
    # Calculate the distance between a single test feature and every train features with Euclidean distance formula
    # Here's a list that used to store distances between the test feature and multiple train features, and also what label does that train feature belong to
        distances = []
        # train_X represents a list of features, single_train_X represents a single feature inside this list
        for single_train_X in train_X:
            # Here's a list that used to store the squre of differences between test feature value and train feature value
            single_distances = []
            for index, value in enumerate(single_train_X):
                # Calculate (p1 - q1)^2, then append it to the "single_distances" list
                single_distances.append((single_test_X[index] - value)**2)
            # Step 1: Calculate the square root of (p1 - q1)^2 + (p2 - q2)^2...,
            # Step 2: use the find_correspond_label method to find the label of current feature
            # Step 3: include these two items into a tuple and append it into the "distances" list (I use tuple only because it will improve readability when testing codes)
            new_tuple = (math.sqrt(sum(single_distances)), self.find_correspond_label(single_train_X, train_X, train_y))
            distances.append(new_tuple)
        # Once all distances are calculated, call the predict function to return the prediction of the current test feature's label
        return self.predict(distances)
    
    def predict(self, distances):
    # Predict the label given the distances between test feature and train features
    # Create another list with ascending sorted order version first, then find the first K features with closest distances
        sorted_distances = distances
        sorted_distances.sort()
        smallest_distances = sorted_distances[:self.K]
        label_list = []
        # Among these features, count which label appear most frequently; the label with highest frequency will be the predicted label
        for feature in smallest_distances:
            # index 0 contains distance, index 1 contains the label, therefore in order to include lables inside the label_list I need to read index 1
            label_list.append(feature[1])
        # return the most frequent label
        return self.find_most_frequent_label(label_list)
            
    def find_most_frequent_label(self, label_list):
    # This method will find out which label appears most frequently in the label_list
        counted_list = Counter(label_list)
        most_common_label, label_count = counted_list.most_common(1)[0]
        return most_common_label
    
    def calculate_distance_multiple(self, test_X, train_X, train_y):
    # This method will calculate distances and predict labels in batches
        return [self.calculate_distance_single(single_test_X, train_X, train_y) for single_test_X in test_X]


# In[6]:


def main():
    # User Interface
    exit_program = False
    while exit_program == False:
        # Following lines of codes will be rexecuted after each iteration of loop to randomlize the data, so it will generate different prediction result everytime
        # Define the path to the CSV file containing the Iris dataset
        filepath = 'Breast_cancer_data.csv'

        # Initialize the data handler with the filepath
        # This object will handle all data operations
        data_handler = DataHandler(filepath)

        # Read the dataset from the CSV file using the read_csv method
        # The dataset is returned as a list of lists, where each sublist is a row from the file
        dataset = data_handler.read_csv()

        # Split the dataset into training and testing parts using the train_test_split method
        # Default split is 80% training and 20% testing
        train_set, test_set = data_handler.train_test_split(dataset)

        # Separate features and labels for the training set
        # train_features will contain the data attributes, and train_labels will contain the target labels
        train_features, train_labels = data_handler.separate_features_labels(train_set)

        # Separate features and labels for the testing set
        # This setup mirrors the training separation
        test_features, test_labels = data_handler.separate_features_labels(test_set)
        
        # Start Printing the actual user interface
        print("1: NaiveBayes, 2: K-Nearest Neighbors, x: exit the program")
        user_input = input("Please enter the prediction algorithm you would like to use: ")
        # If user enter 1, call NaiveBayes programs
        if user_input == "1":
            # Initialize the Naive Bayes Classifier
            # This object will perform all classification tasks
            classifier = NaiveBayesClassifier()
            
            # Ask user if they would like to normalize data
            if UserPromptNormalization() == "1":
                # Normalizing the values of all features so that they are more suitable for data analysis
                # This will sometimes lead to higher test accuarcy, but may also let accuarcy become unstable
                train_features = classifier.normalizing_feature_values(train_features)
                test_features = classifier.normalizing_feature_values(test_features)

            # Fit the classifier on the training data
            # This process involves calculating necessary statistical parameters for the Naive Bayes algorithm
            classifier.fit(train_features, train_labels)

            # Predict the class labels for the test set features
            # The predict method uses the trained model to estimate the labels of unseen data
            predictions = classifier.predict(test_features)

            # Generate a classification report comparing the true labels and predicted labels
            # This report includes precision, recall, F1-score, and accuracy for each class
            report = classifier.classification_report(test_labels, predictions)

            # Print out the classification report for each class
            print("Classification Report:")
            for label, metrics in report.items():
                print(f"Class {label}:")
                for metric, value in metrics.items():
                    print(f"  {metric}: {value:.2f}")
                print()
        # If user enter 2, call KNN programs
        elif user_input == "2":
            # First, receive the K value from the user (Observation: K value doesn't have significant impact on test accuracy)
            while True:
                k = input("What k value would you like to use? Enter 3 or 7.")
                if k == "3" or k == "7":
                    k = int(k)
                    break
                else:
                    print("invalid input, please try again.")
            # Initialize the KNN Algorithm
            # This object will perform all classification tasks
            classifier = KNN(k)

            # Ask user if they would like to normalize data
            if UserPromptNormalization() == "1":
                # Normalizing the values of all features so that they are more suitable for data analysis
                # This will sometimes lead to higher test accuarcy, but may also let accuarcy become unstable
                train_features = classifier.normalizing_feature_values(train_features)
                test_features = classifier.normalizing_feature_values(test_features)

            # Predict test labels
            # The predict method will calculate the distance between test feature and each of the train feature,
            # then takes the nearest K train features, and find out the most common labels carried by these features(Euclidean distance)
            predicted_test_labels = classifier.calculate_distance_multiple(test_features, train_features, train_labels)

            # Generate a classification report comparing the true labels and predicted labels
            # This report includes precision, recall, F1-score, and accuracy for each class
            report = classifier.classification_report(test_labels, predicted_test_labels)

            # Print out the classification report for each class
            print("Classification Report:")
            for label, metrics in report.items():
                print(f"Class {label}:")
                for metric, value in metrics.items():
                    print(f"  {metric}: {value:.2f}")
                print()
        # If user enter x, exit the program
        elif user_input == "x":
            print("Exiting...")
            exit_program = True
        # If user enter invalid input, print the error message restart the program
        else:
            print("Error - invalid input, please try again")

#This function will receive user input to determine if the program will normalize the data or not
def UserPromptNormalization():
    while True:
        Normalize_data = input("Would you like to normalize data before the prediction? Enter 1 if yes, 0 if no.")
        if Normalize_data == "0" or Normalize_data == "1":
            break
        else:
            print("invalid input, please try again.")
    return Normalize_data

#This block checks if this script is the main program and runs the main function
if __name__ == "__main__":
    main()


# In[ ]:





# In[ ]:




