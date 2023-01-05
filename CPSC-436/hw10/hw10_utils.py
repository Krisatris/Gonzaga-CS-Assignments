import numpy as np
import matplotlib.pyplot as plt

def draw_line(p1, p2, style="-k", linewidth=1):
    plt.plot([p1[0], p2[0]], [p1[1], p2[1]], style, linewidth=linewidth)

def plot_data_points(X, idx):
    # plots data points in X, coloring them so that those with the same
    # index assignments in idx have the same color
    plt.scatter(X[:, 0], X[:, 1], c=idx)
    
def plot_progress_kMeans(X, centroids, previous_centroids, idx, K, i):
    # Plot the examples
    plot_data_points(X, idx)
    
    # Plot the centroids as black 'x's
    plt.scatter(centroids[:, 0], centroids[:, 1], marker='x', c='k', linewidths=3)
    
    # Plot history of the centroids with lines
    for j in range(centroids.shape[0]):
        draw_line(centroids[j, :], previous_centroids[j, :])
    
    plt.title("Iteration number %d" %i)

def preprocess_data(X):
    '''
    Proprocess the data so that the missing item is replaced by the average value of each attribute (i.e., each column)
    Args:
        X : (ndarray Shape(m,n)) data with string type
        
    Return: 
        X : (ndarray Shape(m,n)) data with float type - the missing element has been replaced by 
        the average value of each attribute
    '''
    for j in range(X.shape[1]):
        max = 0.0
        cnt = 0.0
        sum = 0.0
        for i in range(X.shape[0]):
            if X[i][j] != '?':
                cnt += 1
                val = float(X[i][j])
                if val > max:
                    max = val
                sum += val
        avg = sum/cnt

        for i in range(X.shape[0]):
            if X[i][j] == '?':
                X[i][j] = str(avg)
   
    return X.astype(float)

def load_data(filename):
    data = np.loadtxt(filename, dtype='str', delimiter=',')
    data = preprocess_data(data)
    X = data[:,0:13]

    return X