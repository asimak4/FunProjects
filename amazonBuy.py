from selenium import webdriver
import smtplib
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys  

import time
import json
import os,os.path

EMAIL_ADDRESS = "pythontester6@gmail.com"
PASSWORDEMAIL= "monkeyrock1"
SEND_ADDRESS = "asimak4@gmail.com"

def send_email(subject, msg):
                try:
                    server = smtplib.SMTP('smtp.gmail.com:587')
                    server.ehlo()
                    server.starttls()
                    
                    server.login(EMAIL_ADDRESS, PASSWORDEMAIL)
                    message = 'Subject: {}\n\n{}'.format(subject, msg)
                    server.sendmail(EMAIL_ADDRESS, SEND_ADDRESS, message)
                    server.quit()
                    print("Success: Email sent!")
                except:
                    print("Email failed to send.")

with open('amazonJson.json','r') as f:
	data=json.load(f)

USERNAME = data["username"]
PASSWORD = data["password"]
DRIVER_PATH = data["driverPath"]


options = Options()  
options.add_argument("--headless")  
#options.binary_location = '/Applications/Google Chrome Canary.app/Contents/MacOS/Google Chrome Canary'
options.binary_location = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome'
driver = webdriver.Chrome(executable_path=os.path.abspath(DRIVER_PATH), options=options)  

driver.get('https://www.amazon.com/ap/signin?openid.pape.max_auth_age=0&openid.return_to=https%3A%2F%2Fwww.amazon.com%2F%3Fref_%3Dnav_signin&openid.identity=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.assoc_handle=usflex&openid.mode=checkid_setup&openid.claimed_id=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.ns=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0&')

#type in email
driver.find_element_by_id("ap_email").send_keys(USERNAME)

#click continue
driver.find_element_by_id("continue").click()

time.sleep(2)

#type in password
driver.find_element_by_id("ap_password").send_keys(PASSWORD)

#remember me
driver.find_element_by_xpath("//*[@id='authportal-main-section']/div[2]/div/div/div/form/div/div[2]/div/div/label/div/label/input")

#click login
driver.find_element_by_id("signInSubmit").click()
time.sleep(20)

# after we have logged in go to ps5 Digital page
driver.get('https://www.amazon.com/gp/product/B08FC6MR62?pf_rd_r=P14TSP3M1F5VADATCCMA&pf_rd_p=edaba0ee-c2fe-4124-9f5d-b31d6b1bfbee&th=1')

time.sleep(5)
bought = False
while(not bought):
    try:
        print("Trying to click on buy now")
        driver.get('https://www.amazon.com/gp/product/B08FC6MR62?pf_rd_r=P14TSP3M1F5VADATCCMA&pf_rd_p=edaba0ee-c2fe-4124-9f5d-b31d6b1bfbee&th=1')
        time.sleep(1)
        driver.find_element_by_id("buy-now-button").click()
        time.sleep(3)
        driver.get("https://www.amazon.com/gp/buy/spc/handlers/display.html?hasWorkingJavascript=1")
        time.sleep(1)
        driver.find_element_by_xpath("//*[@id='bottomSubmitOrderButtonId']/span/input").click()
        send_email("PS5 Bought!","!Woohoo!")
        bought = True

    except:
        print("Could not click, PS5 is not avaliable")
        time.sleep(1)
    


