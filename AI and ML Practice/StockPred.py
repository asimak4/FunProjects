from bs4 import BeautifulSoup
import requests
import csv
import smtplib
import os



ticker = input ("Welcome. Enter a stock ticker. For example Apple: AAPL. Enter Here: ")

url = ("https://www.nasdaq.com/market-activity/stocks/" + str(ticker))

print(url)

source = requests.get(url).content
soup = BeautifulSoup(source, 'html.parser')

for prices in soup.findall('div', class_ = 'symbol-page-header__pricing-details symbol-page-header__pricing-details--current symbol-page-header__pricing-details--increase'):
    ticker1 = prices.find('span', class_= 'symbol-page-header__pricing-last-price')
    ticker = prices.find('span', class_='symbol-page-header__pricing-price')

print(ticker)
   
