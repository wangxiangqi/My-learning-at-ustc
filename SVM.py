from sklearn import svm
import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
iris=load_iris()
n_samples, n_features=iris.data.shape
print(n_samples,n_features)
print(iris.keys())#iris 的键值
iris.target
#print(iris.target)
train_data,test_data=train_test_split(iris.data, random_state=1, train_size=0.7, test_size=0.3)
train_label,test_label=train_test_split(iris.target, random_state=1, train_size=0.7, test_size=0.3)
#划分数据集测试集
#print(train_label)
classifier=svm.SVC(C=2,kernel='rbf',gamma=10,decision_function_shape='ovr')#训练集的预测模型
#kernel是从低维到高维映射
classifier.fit(train_data,train_label.ravel())
print("classifier is=",classifier)
#测试集的预测模型
pre_train=classifier.predict(train_data)
pre_test=classifier.predict(test_data)
print("train=",accuracy_score(train_label,pre_train))
print("test:",accuracy_score(test_label,pre_test))
#混淆矩阵
cm=confusion_matrix(test_label,pre_test)
print(cm)
#一共错了三个样本

