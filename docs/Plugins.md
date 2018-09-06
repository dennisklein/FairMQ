← [Back](../README.md)

# 6. Plugins

The FairMQ framework allows to dynamically load plugins into processes executing a `FairMQDevice`. Plugins can be used to monitor/steer the device state machine (control) and to monitor/update the configuration of the device through the Plugin Services API.

The plugin system was designed to integrate `FairMQDevice`s with external configuration sources and/or control services. For example, one could develop a config plugin that fetches the device configuration from a file format not supported by FairMQ natively or from a remote service.

Currently, FairMQ ships a [DDS](https://github.com/FairRootGroup/DDS) plugin that is used to communicate configuration and control commands between the `FairMQDevice`s deployed by DDS and the `fairmq-dds-command-ui` command-line interface. For more detailed information on how to use the DDS plugin, see the [DDS example](../examples/DDS).

## 6.1 How to write a plugin

Plugins can be developed in your own project repositories.

## 6.2 Plugin Services API

## 6.3 How to use a plugin

← [Back](../README.md)
