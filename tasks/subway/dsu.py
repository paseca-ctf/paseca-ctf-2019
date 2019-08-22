class DSU:
    def __init__(self, n):
        self._p = list(range(n))
        self._sz = [1]*n
        
    def get(self, i):
        if self._p[i] == i:
            return i
        else:
            self._p[i] = self.get(self._p[i])
            return self._p[i]
        
    def join(self, i, j):
        j = self.get(j)
        i = self.get(i)
        if self._sz[j] > self._sz[i]:
            i, j = j, i
        self._p[j] = i
        self._sz[i] += self._sz[j]
        
            