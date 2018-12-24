#!/usr/bin/env python

import os

LAST_USER_PATH = '/var/lib/lightdm/.cache/kano-greeter'
LAST_USER_FILE = os.path.join(LAST_USER_PATH, 'last-user')

def get_last_user():
    try:
        with open(LAST_USER_FILE) as f:
            last_user = f.readline().strip()
    except:
        last_user = None
    return last_user

def set_last_user(last_user):
    if not os.path.exists(LAST_USER_PATH):
        os.makedirs(LAST_USER_PATH)
    with open(LAST_USER_FILE, 'w+') as f:
        f.write(last_user)
        f.write('\n')
