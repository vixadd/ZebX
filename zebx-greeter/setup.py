#!/usr/bin/env python

from distutils.core import setup
import setuptools
import os

def get_locales():
    locale_dir = 'locale'
    locales = []

    for dirpath, dirnames, filenames in os.walk(locale_dir):
        for filename in filenames:
            locales.append(
                (os.path.join('/usr/share', dirpath),
                 [os.path.join(dirpath, filename)])
            )

    return locales


setup(name='Kano Greeter',
      version='1.0',
      description='A greeter for Kano OS',
      author='Team Kano',
      author_email='dev@kano.me',
      url='https://github.com/KanoComputing/kano-greeter',
      packages=['kano_greeter'],
      scripts=['bin/kano-greeter', 'bin/kano-greeter-account'],
      package_data={'kano_greeter': ['media/css/*']},
      data_files=[
          ('/usr/share/kano-greeter/wallpapers', setuptools.findall('wallpapers')),
          ('/usr/share/xgreeters', ['config/kano-greeter.desktop']),
          ('/var/lib/lightdm', ['config/.kdeskrc'])
      ] + get_locales()
     )
