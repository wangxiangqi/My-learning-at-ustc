import numpy as np
import math
def tanh(x):
    return np.tanh(x)
def softmax(x):
    exp=np.exp(x-x.max())
    return exp/exp.sum()
dimensions=[28*28,10]# This is the dimension of the layer
avtivation=[tanh,softmax]
distribution=[
    {'b':[0,0]},

]