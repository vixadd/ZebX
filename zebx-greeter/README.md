# ZebX Greeter
## kano-greeter

Python greeter for Kano OS. Uses LightDM to handle user sessions.

![Main Greeter Screen](https://cloud.githubusercontent.com/assets/5371014/4885460/bc09eb72-6374-11e4-84e1-ac6115f28404.png)
![Password Entry Screen](https://cloud.githubusercontent.com/assets/5371014/4885461/bc0a2b8c-6374-11e4-982b-497245e69330.png)

## Installation

To install

```
python setup.py install
```

To use as the greeter, go to `/etc/lightdm/lightdm.conf` and change the
`greeter-session` option to

```
greeter-session=kano-greeter
```


Alternatively, build the Debian package with

```
debuild -us -uc -b
```

And install by running

```
sudo dpkg -i <file_just_created>
```

# Developing

## Environment Setup

Copy `kano-greeter.desktop` to `/usr/share/xgreeters`

```
sudo cp config/kano-greeter.desktop /usr/share/xgreeters/kano-greeter-devel.desktop
```

Change the `Exec` parameter in it to the path to the executable (change the path
to the cloned repo to be just that)

```
sudo sed -i 's|^\(Exec\=\).*|\1'`pwd`'/bin/kano-greeter|' /usr/share/xgreeters/kano-greeter-devel.desktop
```

Copy the LightDM config file and change the greeter to be the development one

```
cp /etc/lightdm/lightdm.conf lightdm-devel.conf
sudo sed -i 's|^\(greeter-session\=\).*|\1kano-greeter-devel|' lightdm-devel.conf
```

## Testing

The greeter can be run after installation, for testing, as a regular X
application with

```
lightdm --test-mode --debug --config=/path/to/lightdm-devel.conf
```

This will run as an unprivileged user and skip anything that requires root
permissions.

# Contributing

Before undertaking a big feature, contact us to discuss features that might be
useful so that you don't waste your time!

1. Fork it ( http://github.com/KanoComputing/kano-greeter/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
