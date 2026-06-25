
print('Starting ...')

import mysql.connector

cnx = mysql.connector.connect(user='AminGHolami',password='97806692',
                              host='127.0.0.1',database='finalproject')

cursor = cnx.cursor()

print('Connectring to website and scraping datas ...') 

print('Please wait ...')


#########################################################

prices , mileages , yearmades , names , models = [] , [] , [] , [] , []   

import requests

import re

from bs4 import BeautifulSoup

for i in range(1,11):

    r = requests.get('https://www.cars.com/shopping/results/?page=%d&page_size=20&body_style_slugs[]=&list_price_max=&maximum_distance=all&stock_type=used&zip='%i)

    soup = BeautifulSoup(r.text,'html.parser')

    price = soup.find_all('span',attrs={'class':'primary-price'})

    mileage = soup.find_all('div',attrs={'class':'mileage'})

    inf = soup.find_all('a',attrs={'class':'vehicle-card-link js-gallery-click-link'})

    for price in price :

        prices.append(price.text)

    for mileage in mileage :

        mileages.append(mileage.text)

    try :

        for s in inf :

            k = re.findall(r'(\d+) ([A-Za-z-]+) (.{1,25})',s.text)

            yearmades.append(k[0][0])

            names.append(k[0][1])

            models.append(k[0][2])

    except :

        pass


for mileage in mileages:

    if 'Mileage' in mileage :

        mileages.remove(mileage)

        continue

#########################################################################

index = 0

try :

    for price in prices :

        inserter ='INSERT INTO final VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')'%(names[index],models[index],yearmades[index],mileages[index],price)

        cursor.execute(inserter)

        cnx.commit()

        index += 1

except IndexError :

    mileages.append('23,400 mi.')

    
print('inserted datas into database successfully !')

################################## ML ##############################

from sklearn import tree

x , y = [] , []

print('This point is about to machine learning .')
print('you can enter Name , Yearmade and Mileage of a car then machine will guess the price .')

N = input('Please enter car name : ')

Y = input('Please enter Yearmade (e.x 2011) : ')

M = input('Please enter Mileage (e.x 20000) : ')


query ='SELECT Yearmade,Mileage,Price FROM final WHERE Name=\'%s\''%N

cursor.execute(query)


for Yearmade,Mileage,Price in cursor :

    try :

        m = re.findall(r'(\d+),(\d+) .*',Mileage)
    
        x.append([int(Yearmade),int(m[0][0]+m[0][1])])

        k = re.findall(r'\$(\d+),(\d+)',Price)

        y.append(int(k[0][0]+k[0][1]))

    except :

        pass


if len(x) > len(y) :

    while len(x) != len(y):

        y.append(20000)

elif len(y) > len(x) :

    while len(y) != len(x):

        x.append([2015,40000])
        


clf = tree.DecisionTreeClassifier()

clf = clf.fit(x,y)


data = [[Y,M]]

answer = clf.predict(data)

print('My price guess is : ',answer[0])


print('finished!')

cnx.close()








    

    

