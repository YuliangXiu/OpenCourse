Details about this assignment can be found [on the course webpage](http://cs231n.github.io/), under Assignment #1 of Winter 2016.

##some notes:

```python
np.sum(self.X_train**2,axis=1)+np.sum(X**2,axis=1,keepdims=True)
# axis=1 往左加成列
# axis=0 往下加成行
```
加法左边结果是一个5000行的列，右边结果是一个500行的列，我们最终希望的是，将他们结果的和扩展成500*5000的矩阵，这就意味着500行的列不需要变换，只需要在右侧扩展5000维即可，这个时候，我们就可以在右边的sum运算中，加上`keepdims=True`，这样就保证两者加和的时候是在500行的基础上，扩展5000列，换句话讲，两个列向量最后都要扩展为行列数目相同的相同形状的矩阵后才能算+，`keepdims`性质就是指明基准的那个。

```python
y_train_folds = np.array_split(y_train,num_folds)
>>>list[array(several_folds),array(several_folds).....]
list[...] + list[...] = list[[...],[...]]
np.array([1,1,1]) + np.array([2,2,2]) = np.array([3,3,3])
```
`np.array_split`方法是将一个大矩阵分割成n个array组，这n个组又一起组成的list，通过`[i]`可以取第i个array组，而`+`则可以直接将两个array组合并成一个list，注意，list的`+`是用来拼接的，np.array的`+`是用来做加法运算的

```python
<!--左包右不包-->
a = [1,2,3,4,5]
a[0:] = [1,2,3,4,5]
a[:4] = [1,2,3,4]
a[1:3] = [2,3]
a[20:] = []
a[:133] = [1,2,3,4,5]
```
```python
np.concatenate((a,b),axis=0) == np.vstack(a,b)
np.concatenate((a,b),axis=1) == np.hstack(a,b)

np.argsort(a)
>>>得到的是index list，index list中从左到右代表a中最小数到最大数的索引
np.argmax(a)
>>>得到的是a中最大数的索引
```
##求解SVM的梯度
<div align="center">
<img width=300px; align="center" src="http://xiublog.qiniudn.com/2016-10-09-20%3A48%3A30.jpg">
</div>

*这里1(x)为示性函数，当x为真时函数取值1，当x为假时函数取值为0.*
这个公式有点复杂，我们只需要知道，L是与W有关的，W决定了L，这样我们就可以通过最优化L来反向推出W的最优解，这是个W为横轴，L为纵轴的凸优化函数问题。

```python
for i in xrange(num_train):
    scores = X[i].dot(W)
    hscores = X[i].dot(hW)
    correct_class_score = scores[y[i]]
    for j in xrange(num_classes):
      if j == y[i]:
        continue
      # 这一行简单讲就是求错分类得分和正确分类得分的差
      margin = scores[j] - correct_class_score + 1 # note delta = 1
      # 如果这个差超过0，那么就要纠正W了，我们用dw梯度来确定纠正多少
      if margin > 0:
        loss += margin
        # y[i]对应正确分类得分correct_class_score，j对应错误分类得分score[j]
        # 我们的目的是为了缩小这个margin，所以一个自然而然的思路是
        # 加大correct_class_score，减小score[j]
        # 对应梯度应该正好反过来，即减小dW[:,y[i]]，增大dW[:, j]
        # 应该减小增大多少呢？ X[i]，L = W * X 
        # 这个调节和林轩田讲的SVM的矢量的变动规律是一致的，W(t+1)<--W(t) + {1/-1}*X(t)
        dW[:,y[i]] += -X[i]
        dW[:, j] += X[i]
```
`np.sum(a,axis=?)`
如果axis没有设置，默认为对矩阵内部所有值求总和，如果限定了axis则做行加或者列加

`(H,)`指的是1行H列

##$y=wx+b的各种梯度计算$

- dy通过loss函数获得
- dw与x有关，所以dw=dy*x
- dx与w有关，所以dx=dy*w
- db可以用dy衡量，所以db=dy的累积

```python
def affine_backward(dout, cache):
  """
  Computes the backward pass for an affine layer.

  Inputs:
  - dout: Upstream derivative, of shape (N, M)
  - cache: Tuple of:
    - x: Input data, of shape (N, d_1, ... d_k)
    - w: Weights, of shape (D, M)

  Returns a tuple of:
  - dx: Gradient with respect to x, of shape (N, d1, ..., d_k)
  - dw: Gradient with respect to w, of shape (D, M)
  - db: Gradient with respect to b, of shape (M,)
  """
  x, w, b = cache
  dx, dw, db = None, None, None
  #############################################################################
  # TODO: Implement the affine backward pass.                                 #
  #############################################################################
  x_shape = np.shape(x)
  num_training = x_shape[0]
  x = x.reshape(num_training,-1)
  dw = (x.T).dot(dout)
  dx = dout.dot(w.T)
  dx = dx.reshape(x_shape)
  db = np.sum(dout,axis=0)

  return dx, dw, db
```