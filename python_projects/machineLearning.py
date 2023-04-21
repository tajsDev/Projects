# Header files


import pandas as pd   
from sklearn.model_selection import train_test_split 
from sklearn.linear_model import LogisticRegression
from sklearn.datasets import load_iris
def main():
   iris = load_iris()
   sepal_length = input("Enter Sepal Length: ")
   sepal_width = input("Enter sepal width: ")
   petal_length= input("Enter petal length: " )
   petal_width = input("Enter petal_width: ")


   sepal_length= int(sepal_length)
   sepal_width= int(sepal_width)
   petal_length= int(petal_length)
   petal_width= int(petal_width)

   df = pd.DataFrame(iris.data,columns = iris.feature_names)
   df['target']= iris.target
   x_train,x_test,y_train,y_test = train_test_split(iris.data,iris.target,test_size=0.1 )
   model = LogisticRegression(solver = "lbfgs",max_iter=10000)
   model.fit(x_train,y_train)
   print(model.score(x_test,y_test))
   show = model.predict([[sepal_length,sepal_width ,petal_length,petal_width]])
   print(iris.target_names[show[0]])




main = main()