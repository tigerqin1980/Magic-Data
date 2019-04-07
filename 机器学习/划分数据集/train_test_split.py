# -*- coding: utf-8 -*-
"""
Created on Sat Sep  8 08:39:12 2018

@author: o
"""

import pandas as pd
import os
from sklearn.ensemble import RandomForestClassifier
from sklearn import metrics
os.chdir(r'C:\Users\o\Desktop\breast_cancer_data')
data = pd.read_csv(r'data.csv')
data.drop('Unnamed: 32',inplace = True,axis = 1)
data.drop('id',inplace = True,axis=1)
y = data['diagnosis']
x = data.drop('diagnosis',axis = 1)
model = RandomForestClassifier()
#hold-out
from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.33, random_state=42)
print(x_train.shape)
print(x_test.shape)
model.fit(x_train,y_train)
prediction = model.predict(x_test)
print(metrics.accuracy_score(prediction,y_test))

#k-fold
import numpy as np
from sklearn. model_selection import KFold
kf = KFold(n_splits = 10)
accuracy = [ ]
for train_index,test_index in kf.split(x):
    x_train,x_test = x.loc[train_index],x.loc[test_index]
    y_train,y_test = y.loc[train_index],y.loc[test_index]
    model.fit(x_train,y_train)
    prediction = model.predict(x_test)
    acc=metrics.accuracy_score(prediction,y_test)
    accuracy.append(acc)
print(accuracy)
print(np.average(accuracy))

#LOO
from sklearn.model_selection import LeaveOneOut,LeavePOut
loo = LeaveOneOut()
accuracy = []
for train_index,test_index in loo.split(x):
    x_train,y_train,x_test,y_test = x.loc[train_index],y.loc[train_index],x.loc[test_index],y.loc[test_index]   
    model.fit(x_train,y_train)
    prediction = model.predict(x_test)
    acc=metrics.accuracy_score(prediction,y_test)
    accuracy.append(acc)
print(np.average(accuracy))

#shufflesplit
from sklearn.model_selection import ShuffleSplit
rs = ShuffleSplit(n_splits = 10,test_size = 0.3)
accuracy = []
for train_index,test_index in rs.split(x):
     x_train,y_train,x_test,y_test = x.loc[train_index],y.loc[train_index],x.loc[test_index],y.loc[test_index]
     model.fit(x_train,y_train)
     prediction = model.predict(x_test)
     acc=metrics.accuracy_score(prediction,y_test)
     accuracy.append(acc)
print(np.average(accuracy))
