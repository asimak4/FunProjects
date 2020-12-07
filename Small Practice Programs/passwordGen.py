from random import choice
password = ''
password.join([choice('abcdefghijklmnopqrstuvwxyz0123456789%^*(-_=+)') for i in range(20)])

print(password)
