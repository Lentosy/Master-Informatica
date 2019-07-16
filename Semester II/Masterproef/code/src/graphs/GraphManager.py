
import matplotlib.pyplot as plt

class GraphManager(object):
    def __init__(self, cols, rows):
        self.figure, self.axes = plt.subplots(nrows = rows, ncols = cols)
        self._currentAx = 0 # note: we access a list so we use zero based indexing
        self._axCount = cols * rows
        if cols == 1: # make axes always a 2D list
            self.axes = [self.axes]
        
    def __del__(self):
        plt.close()

    def getNextAx(self):
        if self._currentAx + 1 > self._axCount:
            raise RuntimeError(f"No more axes available.")
        
        row = int((self._currentAx) % len(self.axes))
        col = int((self._currentAx) - (row * len(self.axes[0])))

        self._currentAx += 1
        return self.axes[row][col]
 

    def show(self, fullscreen = False):
        if(fullscreen):
            mng = plt.get_current_fig_manager()
            mng.window.state('zoomed') 
        plt.show()