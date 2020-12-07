from bs4 import BeautifulSoup
import requests
import csv
import smtplib
import os

EMAIL_ADDRESS = 'pythontester6'
EMAIL_PW = 'monkeyrock1'

# csv_file = open('cars_scrape_new.csv', 'w')
csv_file = open('cars_scrape_new.csv', 'w')

csv_writer = csv.writer(csv_file)

csv_writer.writerow(['Car Year', 'Car Name', 'Price', 'Milage', 'URL', 'Unique ID'])

j = 0
k = 0
car_id = ""
###looping through multiple pages
for i in range(1, 2):
    print('Please wait, this will take a couple seconds. Searching ...')
    # + str(i) +

    #a big range of cars, most likely to be added to
    big_url = 'https://www.cars.com/for-sale/searchresults.action/?dealerType=all&mdId=58767&mkId=20089&mlgId=28869&page=' + str(i) + '&perPage=100&prMx=25000&rd=99999&searchSource=GN_REFINEMENT&sort=listed-newest&stkTypId=28881&transTypeId=28113&zc=21042'
    
    #new url that has the cars i am looking for within a 200 mile radius 
    new_url = 'https://www.cars.com/for-sale/searchresults.action/?cpoId=28444&dealerType=localOnly&mdId=58767&mkId=20089&mlgId=28869&page=' + str(i) + '&perPage=20&prMx=25000&rd=150&searchSource=GN_REFINEMENT&sort=relevance&trId=57634,30001071,57638,57636,30001072,35127046,35125683&transTypeId=28113&zc=21043'

    # source = requests.get(old_url).content
    source = requests.get(new_url).content
    soup = BeautifulSoup(source, 'html.parser')

    k = 0
#   ### looping through the cars on that particular page
    for cars in soup.find_all('div', class_ = 'shop-srp-listings__listing-container'):
        price = cars.find('div', class_ = 'payment-section').span.text.split()
        miles = cars.find('span', class_ = 'listing-row__mileage').text.split()
        car = cars.find('h2', class_ = 'listing-row__title').text.split()
        car_id = cars.find('a').attrs['href']

        uniqueID = car_id.split('/')

        k += 1
        csv_writer.writerow([car[0], car[1: ], price, miles, "cars.com" + str(car_id), uniqueID[3]])
    j += k
print("There were " + str(j) + " Cars Found")
print("Thank you\n")

csv_file.close()
savingNewCar = ""
difference = 0
row_count = 0
#### Comparing the old file to the new file to check for changes, then making an updated file with the differences between two files
try: #old then comparing it to new
    with open('cars_scrape.csv', 'r') as t1, open('cars_scrape_new.csv', 'r') as t2:
        fileOld = t1.readlines()
        fileNew = t2.readlines()

    with open('update.csv', 'w') as outFile:
        for line in fileNew:
            if line not in fileOld:
                outFile.write(line)
                savingNewCar = line

    ### counting the lines from each file
    row_count_old = sum(1
                        for row in fileOld)
    row_count_new = sum(1
                        for row in fileNew)

    difference = int((row_count_new - row_count_old) / 2)
    #print("1. There were " + str(difference) + " new cars found! ")

    t3 = open('update.csv', 'r')
    fileObject = t3.readlines()
    t3.close()
    row_count = sum(1 for row in fileObject)

    print("There were " + str(row_count) + " added to the updated file.")

    #print("Trying to delete and rename files...\n")

    os.remove('cars_scrape.csv')

except IOError:
    print("No Files were found to compare.")

if (difference > 0 or row_count > 0):
    with smtplib.SMTP('smtp.gmail.com', 587) as smtp:
        smtp.ehlo()
        smtp.starttls()
        smtp.ehlo()

        smtp.login(EMAIL_ADDRESS, EMAIL_PW)

        subject = "UPDATE: New GTI Found."
        body = savingNewCar

        msg = f'Subject: {subject}\n\n{body}'

        smtp.sendmail(EMAIL_ADDRESS, 'asimak4@gmail.com', msg)
        print("Email Sent!")

try:
    os.rename("cars_scrape_new.csv", "cars_scrape.csv")
except IOError:
    print("Could not rename.")

    
