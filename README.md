remote-temp
===========

This is a remote temperature monitor for a NCD Particle Photon module connected to a SI7020-A20 temperature/humidity mini module sensor.

It is based on the [original example in the Temperature_Alarm library](https://github.com/ControlEverythingCom/Temperature_Alarm/tree/master/firmware).

## Usage

remote-temp provides an API via the Particle Cloud.

This [Hackster project](https://www.hackster.io/brightcontrast/remote-temperature-monitor-6d6e48) shows how you can use [Porter](http://porterapp.com/) to create a UI, including notifications and guest access.

### Variables

It exposes the following variables about the state of the device:

- `temperature`: The current temperature reading in the configure scale
- `alarm_state`: Either `normal`, `high`, or `low`, depending on wether a specific alarm or alarms are set on and the temperature is out of range.

It also exposes the following variables about the configuration of the device:

- `scale`: A 1 character string, specifying which temperature scale is being used, `C` or `F`.
- `alarm_mode`: Either `off`, `high`, `low`, or `all` depending on how the alarm mode is configured. When `off`, no temperature alarms will be monitored. When `high` or `low`, only the respective temperature alarm will be monitored. When `all`, both high and low temperature alarms will be monitored.
- `high_limit`: The limit over which a high temperature alarm will be triggered.
- `low_limit`: The limit below which a low temperature alarm will be triggered.
- `pub_mode`: Either `off`, `alarm`, `temp`, or `all`. When off, no events will be published. When `alarm`, only alarm events will be published when the `alarm_state` changes. When `temp`, only `temp` events will be published at the specified `pub_minutes` interval. When `all`, both event types will be trigged.
- `pub_minutes`: The frequency with which to publish `temp` events, if enabled.

### Functions

It provides access to a number of functions used to configure the device:

- `set_scale`: Sets the `scale` variable.
- `set_alarm`: Sets the `alarm_mode` variable.
- `set_high`: Sets the `high_limit` variable.
- `set_low`: Sets the `low_limit` variable.
- `set_publish`: Sets the `pub_mode` variable.
- `set_interval`: Sets the `pub_minutes` variable.

All of these functions return `1` if they received valid input and updated the variable, and `-1` if they received invalid input and did not update the variable.

### Events

It will publish the following events, when configured to do so:

- `temp`: The data is the current temperature in the configured scale. When enabled, this is published at the interval specified by `pub_minutes`;
- `alarm`: The data is formatted as `alarm_state: temperature`. When enabled, this is published whenever the `alarm_state` variable changes.

## Version

1.0.0

## Web IDE Build Instructions

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

## Particle Dev Build Instructions

The necessary Temperature_Alarm library files are included in the repository.

Simply select the device you wish to target, and compile and flash it to your device.
