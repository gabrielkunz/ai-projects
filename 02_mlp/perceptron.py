import numpy as np

class Perceptron:
    def __init__(self, N, alpha = 0.1):
        # N as number of columns of input matrix
        # alpha as learning rate
        # initialize the weight
        self.weight = np.random.randn(N + 1) / np.sqrt(N)
        self.alpha = alpha

    def activation(self, x):
        # Sigmoid function for activation
        y = 1 / (1 + np.exp(-x))
        return y
    
    def fit(self, X, target_prediction, epochs = 10):
        # insert a column of 1's as the last entry in the input matrix to consider the bias in the summation
        X = np.c_[X, np.ones((X.shape[0]))]

        # Loop the epochs
        for epoch in np.arange(0, epochs):
            # Loop each data input
            for (x, target) in zip(X, target_prediction):
                # Weighted input
                weighted_x = np.dot(x, self.weight)

                # Get the prediction
                p = self.activation(weighted_x)

                # Update the weight based on the error, if the error is 0, the weight will remain the same
                if p != target:
                    error = p - target
                    self.weight += -self.alpha * x * error

    def predict(self, X, add_bias = True):
        X = np.atleast_2d(X)

        if add_bias:
            X = np.c_[X, np.ones((X.shape[0]))]

        weighted_X = np.dot(X, self.weight)
        return self.activation(weighted_X)
