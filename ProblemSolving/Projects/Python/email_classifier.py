"""email_classifier.py - Classify emails using various ML algorithms

Attempts to compare the various binary classification machine learning algorithms
to classify emails as spam or not-spam.

The result(s) are published in the paper.
DataModel will help build the feature vector which is then
processed by various algorithms to train and test the ML models.
"""
#Author: Vikas Pachisia
#Email: vikas.pachisia@gmail.com
#Date: 22-Nov-2019

from typing import (Any, Callable, Dict, Generic, Iterator, List, Optional, Sequence, Tuple, Type,
                    TypeVar, Union)

from os import path, listdir
from collections import Counter
import re
import pickle
from sklearn.naive_bayes import GaussianNB #type: ignore
from sklearn import svm #type: ignore
from sklearn.metrics import accuracy_score #type: ignore
import numpy #type: ignore

class DataModel:
    """
    Dummy class used for my learning purposes.
    The functions here will help build the feature vector in any case.
    """

    @staticmethod
    def getSanitizedData(data: List[str]) -> List[str]:
        sanitizedData = list(filter(lambda item: len(item) > 1 and item.isalpha(), data))
        sanitizedData.sort(key=str.lower)
        sanitizedData = sorted(sanitizedData)
        return sanitizedData

    @staticmethod
    def get_dictionary(root_dir : str) -> List[Tuple[str,int]]:
        """
        Build a dictionary of the most common 3000 words occuring in the data and return it.

        Keyword arguments:
        root_dir -- The full directory path that contains the actual email files.
        """

        all_words_temp = []
        all_words : List[str] = []
        dictionary : List[Tuple[str,int]]
        [parent_dir, child_dir] = path.split(root_dir)
        cached_filename = path.join(parent_dir, child_dir + '.pickle')

        if path.exists(cached_filename):
            with open(cached_filename, 'rb') as cached_file:
                dictionary = pickle.load(cached_file)

        #compute feature matrix if data not found in cache.
        else:
            email_files = [path.join(root_dir, f) for f in listdir(root_dir)]
            for email_file in email_files:
                all_words += re.findall(r'\w+', open(email_file).read())                
                                    
            #all_words = DataModel.getSanitizedData(all_words)
            dictionary = Counter(word for word in all_words if len(word) > 1 and word.isalpha()).most_common(3000)

            #cache the computed dictionary in a file.
            #delete the file manually to clear the cache.
            #auto-cache-update implementation is pending.
            #with open(cached_filename, 'wb') as cached_file:
                #pickle.dump(dictionary, cached_file, pickle.HIGHEST_PROTOCOL)

        return dictionary

    @staticmethod
    def get_features(root_dir: str, dictionary: List[Tuple[str,int]]) -> Any:
        """
        Build a feature vector from the email samples.
        The feature vector are the most common words occuring in the email.
        Returns the feature matrix.

        Keyword arguments:
        root_dir -- The full directory path that contains the actual email files.
        dictionary -- The dictionary to use for frequency
        """

        #dictionary = DataModel.get_dictionary(root_dir)
        enum_dictionary = enumerate(dictionary)
        email_files = [path.join(root_dir, f) for f in listdir(root_dir)]

        data_labels = numpy.zeros(len(email_files))
        feature_matrix = numpy.zeros((len(email_files), 3000))

        for i, email_file in enumerate(email_files):
            line2 = open(email_file).readlines()[2]
            all_words = re.findall(r'\w+', open(email_file).readlines()[2])
            #all_words = Counter(DataModel.getSanitizedData(all_words))
            #all_words = Counter(all_words)

            j = 0
            for j, word in enumerate(dictionary):
                if word[0] in all_words :
                #if all_words[word] > 0 :                    
                    feature_matrix[i, j] = all_words.count(word[0])                    
                    #feature_matrix[i, j] = all_words[word]
            if path.basename(email_file).startswith('spmsg'):
                data_labels[i] = 1
        return feature_matrix, data_labels

ROOT_FOLDER = ("C:\\MyDrive\\Learning\\AL_ML_CLOUD_BIGDATA_BLOCKCHAIN\\"
               "MacineLearning\\medium\\ml101-savanpatel\\machine-learning-101-master\\chapter1\\")

#DM = DataModel()
dictionary = DataModel.get_dictionary(path.join(ROOT_FOLDER, 'train-mails'))
[TRAIN_FEATURES, TRAIN_LABELS] = DataModel.get_features(path.join(ROOT_FOLDER, 'train-mails'), dictionary)
[TEST_FEATURES, TEST_LABELS] = DataModel.get_features(path.join(ROOT_FOLDER, 'test-mails'), dictionary)

ftrainindices = [index for index, value in numpy.ndenumerate(TRAIN_FEATURES) if value > 0]
fttestindices = [index for index, value in numpy.ndenumerate(TEST_FEATURES) if value > 0]

#Naive Bayes Algorithm
MODEL = GaussianNB()

print("Train Model (Naive Bayes)...")
MODEL.fit(TRAIN_FEATURES, TRAIN_LABELS)

print("Test Model (Naive Bayes)...")
PREDICTED_LABELS = MODEL.predict(TEST_FEATURES)

print("Compute Accuracy (Navie Bayes): ")
print(accuracy_score(TEST_LABELS, PREDICTED_LABELS))

#SVM Algorithm
MODEL = svm.SVC()

print("Train Model (SVM)...")
MODEL.fit(TRAIN_FEATURES, TRAIN_LABELS)

print("Test Model (SVM)...")
PREDICTED_LABELS = MODEL.predict(TEST_FEATURES)

print("Compute Accuracy (SVM)...")
print(accuracy_score(TEST_LABELS, PREDICTED_LABELS))
