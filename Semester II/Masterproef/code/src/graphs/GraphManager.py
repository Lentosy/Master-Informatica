
import matplotlib.pyplot as plt

class GraphManager(object):
    def __init__(self, cols, rows):
        self.figure, self.axes = plt.subplots(nrows = rows, ncols = cols)
        self._currentAx = 0 # note: we access a list so we use zero based indexing
        self._axCount = cols * rows
        self._cols = cols
        self._rows = rows

        if rows == 1: # make axes always a 2D list
            self.axes = [self.axes]
            if cols == 1:
                self.axes = [self.axes]
        
    def __del__(self):
        plt.close()

    def getNextAx(self):
        if self._currentAx + 1 > self._axCount:
            raise RuntimeError(f"No more axes available.")
        
        
        row = self._currentAx // self._cols
        col = self._currentAx % self._cols

        self._currentAx += 1
        return self.axes[row][col]
 
    def adjustSubplots(self, left=None, bottom=None, right=None, top=None, wspace=None, hspace=None):
        plt.subplots_adjust(left, bottom, right, top, wspace, hspace)

    def show(self, tightLayout = False, fullscreen = False):
        if(fullscreen):
            mng = plt.get_current_fig_manager()
            mng.window.state('zoomed') 
        plt.show()