import numpy as np
from perceptron import Perceptron

# AND and OR datasets
X_and = np.array([[0,0],
                  [0,1],
                  [1,0],
                  [1,1]])
y_and = np.array([[0],
                  [0],
                  [0],
                  [1]])

X_or = np.array([[0,0],
                 [0,1],
                 [1,0],
                 [1,1]])
y_or = np.array([[0],
                 [1],
                 [1],
                 [1]])

# Define perceptron AND and train it
print("Training perceptron for AND dataset...")
p_and = Perceptron(X_and.shape[1], alpha = 0.1)
p_and.fit(X_and, y_and, epochs = 1000)

# Display test result after training
print("Testing perceptron after training...")
for (x, target) in zip(X_and, y_and):
	prediction = p_and.predict(x)
	print("Input = {}, Target = {}, Prediction = {}".format(x, target[0], prediction))

# Define perceptron OR and train it
print("Training perceptron for OR dataset...")
p_or = Perceptron(X_or.shape[1], alpha = 0.1)
p_or.fit(X_or, y_or, epochs = 1000)

# Display test result after training
print("Testing perceptron after training...")
for (x, target) in zip(X_or, y_or):
	prediction = p_or.predict(x)
	print("Input = {}, Target = {}, Prediction = {}".format(x, target[0], prediction))
