import numpy as np
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import mean_squared_error
from sklearn.metrics import r2_score
matplotlib.rcParams['font.sans-serif'] = ['SimHei']
matplotlib.rcParams['font.family'] = 'sans-serif'
matplotlib.rcParams['axes.unicode_minus'] = False

filename = "C:\\Users\\邱仔\\Desktop\\程序\\py\\3_29_QGtest\\boston_housing_data.csv"
boston_data = pd.read_csv(filename)
data = pd.DataFrame(boston_data)

# 查看特征数据
# pd.set_option('display.max_columns', None)  # 这行查看全列数据
# print(boston_data.describe().T)

# 下面做一部分预处理，已得知无空数据，
medvMedian = data["MEDV"].median()
crimMedian = data["CRIM"].median()
crimMean = data["CRIM"].mean()

err = []
for y in data.index:
    if data.loc[y, "CRIM"] > crimMean*2:  # 有些犯罪率数据很离谱，改了改了
        err.append(y)
        continue
    if data.loc[y, "MEDV"] > 45:  # 房价过高的和普通房差太多了影响模型效果而且数量也少
        err.append(y)
xdata = np.array(data[['LSTAT', 'CRIM', 'RM']])
ydata = np.array(data[['MEDV']])
xdata = np.delete(xdata, err, axis=0)
ydata = np.delete(ydata, err, axis=0)
X_train, X_test, y_train, y_test = train_test_split(xdata, ydata, test_size=0.25)
print(X_train.shape, X_test.shape, y_train.shape, y_test.shape)

# estimator = SGDRegressor(max_iter=1000)
# estimator.fit(X_train, y_train)
# y_test_pred = estimator.predict(X_test)
# y_train_pred = estimator.predict(X_train)

X_train = np.matrix(X_train)
X_test = np.matrix(X_test)
o=np.ones(302,dtype=float)
o=o[:,np.newaxis]
X_train_ = np.hstack((o,X_train))

w = (-8.8,-0.38,-0.43,5.8)
w = np.matrix(w).T
partDer = X_train_.T * (X_train_ * w - y_train)
count = 1
while count < 2000:
    for i in range(4):
        w[i] = w[i] - 0.00001 * partDer[i]
    partDer = X_train_.T * (X_train_ * w - y_train)
    count += 1
y_test_pred=np.ones(101)
y_train_pred=np.ones(302)
for i in range(302):
    y_train_pred[i]*=(w[1]*X_train[i, 0]+w[2]*X_train[i, 1]+w[3]*X_train[i, 2]+w[0])
for i in range(101):
    y_test_pred[i] *= (w[1] * X_test[i, 0] + w[2] * X_test[i, 1] + w[3] * X_test[i, 2] + w[0])
train_MAE = mean_absolute_error(y_train, y_train_pred).round(5)
print('MAE为：',train_MAE)
train_MSE=mean_squared_error(y_train, y_train_pred).round(5)  # 训练值与训练预测值之间的对比
print('MSE为：',train_MSE)
score = r2_score(y_test, y_test_pred).round(5)

fig = plt.figure(figsize=(13, 7))
plt.plot(range(y_test.shape[0]), y_test, color='red', linewidth=1, linestyle='-')
plt.plot(range(y_test.shape[0]), y_test_pred, color='blue', linewidth=1, linestyle='dashdot')
plt.legend(['真实值', '预测值'])
error = "标准差d=" + str(train_MSE)+" 方差d^2="+str(train_MAE)+" 相关指数R^2="+str(score)
plt.xlabel(error, size=18, color="green")
plt.grid()
plt.show()

plt.rcParams['font.family'] = "sans-serif"
plt.rcParams['font.sans-serif'] = "SimHei"
x1 = np.arange(0, 40)
y1 = x1
plt.xlabel(' 真实值 ', fontsize=14)
plt.ylabel(' 预测值 ', fontsize=14)
plt.plot(x1, y1)
plt.scatter(y_test, y_test_pred, color='red')
plt.grid()
plt.show()

