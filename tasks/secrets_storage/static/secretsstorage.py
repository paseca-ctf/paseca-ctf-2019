from random import choice
from string import ascii_letters
from hashlib import md5
from secrets import token_hex as salt

salt = salt()
users = {'admin':'admin'}
tokens = {}
def create_token(login,password):
    global tokens
    tokens[login] = md5((salt+login+password).encode()).hexdigest()

create_token('admin',users['admin'])

users_secrets = {tokens['admin']:'<redacted>'}
access_denied = ['admin']

def registration():
    login = input('New login: ')
    if login not in users:
        password = input('Password: ')
        users[login] = password
        create_token(login,password)
        print('Success!')
    else:
        print('User already exsist.')
def authed(login, password):
    global tokens
    global users_secrets
    token = tokens[login]
    print('Welcome back {0}!'.format(login))
    while True:
        choice_0 = input('[1] - Show secret\n[2] - New secret\n')
        if choice_0 == '1':
            if token in users_secrets:
                print('Your secret: {0}'.format(users_secrets[token]))
            else:
                print('You have not secrets.')
        elif choice_0 == '2':
            secret = input('Enter your secret: ')
            users_secrets[token] = secret
    

print('Welcome to the SecretsStore!')
while True:
    print('[1] - login\n[2] - registration\n[3] - quit')
    choice = input()
    if choice == '1':
        login = input('Login: ')
        if login in users and login != 'admin':
            password = input('Password: ')
            if users[login] == password:
                authed(login,password)
            else:
                print('Wrong password!')
        else:
            print('No such user.')
    elif choice == '2':
        registration()
    elif choice == '3':
        print('Bye!')
        exit()
