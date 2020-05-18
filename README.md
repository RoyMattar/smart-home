# SMART HOME MANAGEMENT PLATFORM

## Motivation
New technologies, mobile devices, the Internet of Things (IoT), and big data are rapidly creating a world with levels of connectivity and access to data never seen before.
The intelligence derived from such data can bring unprecedented visibility and optimization to building operations.
The ability to collect data from environmental sensors such as HVAC, lighting, fire safety and other sources combined with the ability to extract, aggregate, analyze, and make decisions based on that data - makes a building a "smart building".

## Summary
SmartHome is a next generation platform for managing IoT enhanced smart buildings.
The platform serves as the controller and integration hub for modules, devices, controllers and sensors that will enable efficient and comfortable operation of the building.
SmartHome is implemented using C++ for a POSIX compliant system.

## Main Components
The system includes the following components:
* A central hub, which is a server application serving as a host for software agents (below). It provides an efficient mechanism to receive events from sensors and dispatch these events to relevant controllers.
* Software agents, mediating communication with the external hardware devices. These devices can act either as sensors - monitoring and measuring a physical phenomena - or as controllers - executing an operation, usually affecting the environment.

Sensor agents generate events which will be routed to the controller agents interested in acting upon them.
Generated events contain at least: the event type, the event location, a timestamp and a data payload.

## Startup
Agents are loaded at system startup according to a configuration file (.ini).
Each agent shall be implemented as a dynamic object (.so) and shall implement and expose the required interfaces for communicating with the central hub (as defined by the agent SDK).
Agents may communicate with their respective driver using a network protocol or through any other IPC mechanism.
