#PCA is to decrease the dimension of data
#lower the data from n dimensions to k dimensions
#PCA的主要思想是将n维特征映射到k维上，
#这k维是全新的正交特征也被称为主成分，是在原有n维特征的基础上重新构造出来的k维特征。
#拥有更高的可区分度，同时还保留着部分映射之前的空间信息。
#利用方差来求样本间的间距
#对PCA目标函数，利用梯度上升求解
import numpy as np
import matplotlib.pyplot as plt
X = np.empty([100,2])
X[:,0] = np.random.uniform(0., 100., size=100)
X[:,1] = 0.75 * X[:,0] + 3. + np.random.normal(0., 10., size=100)

plt.scatter(X[:,0],X[:,1])
#plt.show()
#prepare raw data
#将均值移动，使得其归零，样本分布不会改变
def demean(X):
    # axis=0按列计算均值，即每个属性的均值，1则是计算行的均值
    return (X - np.mean(X, axis=0))

X_demean = demean(X)
# 注意看数据分布没变，但是坐标已经以原点为中心了
plt.scatter(X_demean[:, 0], X_demean[:, 1])
#plt.show()
#定义目标函数
def f(w,X):
    return np.sum((X.dot(w)**2))/len(X)
#梯度公式
def df_math(w,X):
    return X.T.dot(X.dot(w))*2./len(X)
#具体来说就是2/m*XT*(Xw)

# 验证梯度求解是否正确，使用梯度调试方法：
def df_debug(w, X, epsilon=0.0001):
    # 先创建一个与参数组等长的向量
    res = np.empty(len(w))
    # 对于每个梯度，求值
    for i in range(len(w)):
        w_1 = w.copy()
        w_1[i] += epsilon
        w_2 = w.copy()
        w_2[i] -= epsilon
        res[i] = (f(w_1, X) - f(w_2, X)) / (2 * epsilon)
    return res
#对于要求的轴，向量ω，实际上一个单位向量，即要让向量的模为1
#因此我们使用np中的线性代数库linalg里面的norm()方法，求第二范数，也就是求算术平方根
def direction(w):
    return w / np.linalg.norm(w)
#梯度上升
# 梯度上升法代码
def gradient_ascent(df, X, initial_w, eta, n_iters=1e4, epsilon=1e-8):
    w = direction(initial_w)
    cur_iter = 0
    while cur_iter < n_iters:
        gradient = df_math(w,X)
        last_w = w
        w = last_w + eta * gradient
        w = direction(w)    # 将w转换成单位向量
        if (abs(f(w,X) - f(last_w,X)) < epsilon):
            break
        cur_iter += 1
    return w

initial_w = np.random.random(X.shape[1])
eta = 0.001

w = gradient_ascent(df_debug, X_demean, initial_w, eta)
# 输出
np.array([0.76567331, 0.64322965])

plt.scatter(X_demean[:,0],X_demean[:,1])
plt.plot([0,w[0]*30],[0,w[1]*30], color='red')
plt.show()
