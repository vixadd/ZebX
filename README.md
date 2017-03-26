# ZebX
ZebX Desktop Environment

```python
#==============================
# l and m -> are the starting and ending indexes of the break points array respectively
# i and j -> are the starting and ending indexes of the string S array respectively
# q is the least cost which is returned
# min finds the minimum between two integers
#==============================

def breakingString(L,l,m,i,j):
  n=j-i+1
  
  if (i > j) or (l > m):
    return 0
  
  if (l == m):
    if(L[l] <= i) and (L[l] >= j):
      return 0
    
    q = 1000
    
    for k=l to m:
      if (k == m):
        q = min(q, n+breakingString(L,l,k-1,i,L[k])+breakingString(L,m,m,L[k]+1,j))
      
      elif (k==l):
        q = min(q, n+breakingString(L,l,l,i,L[k])+breakingString(L,k+1,m,L[k]+1,j))
  
  else:
    q = min(q, n+breakingString(L,l,k,i,L[k])+breakingString(L,k+1,m,L[k]+1,j))
  
  return q
  ```
