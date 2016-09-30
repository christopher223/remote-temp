remote-temp
===========

This is a remote temperature monitor for a NCD Particle Photon module connected to a SI7020-A20 temperature/humidity mini module sensor.

It is based on the [original example in the Temperature_Alarm library](https://github.com/ControlEverythingCom/Temperature_Alarm/tree/master/firmware).

## Web IDE Instructions

If you're using the Web IDE and want to try it out:

First, click the "Create a New App" button at the bottom of the list of your Particle apps and give it a title, like "remote-temp".

Then, add the Temperature_Alarm library to your app:

1. Open the libraries pane by clicking the bookmark icon
- Select the Temperature_Alarm Library
- Click the "Include in App" button
- Select the the app you just save
- Click "Add to this App"

Finally, paste the code from the "remote-temp.ino" file into the "remote-temp.ino" tab and save your app by clicking the Folder icon on the left.

Now you're ready to compile and flash it to your Photon by clicking the Flash icon in the toolbar.

## Particle Dev Instructions

The necessary Temperature_Alarm library files are included in the repository.

Simply select the device you wish to target, and compile and flash it to your device.
