
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

RIOT OS is an operating system aimed at low resource (ROM, RAM, power) devices.
It supports a range of use cases. To achieve that support, developers
typically follow the design philosophies described here.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

This document describes the consensus of RIOT design in the community, including
the decisions that are typically made and the reasoning behind them. The aim is
to guide future work by collecting and recording what has been followed in the
past.  It gives a list of our most commonly addressed use cases, followed by a
list of design philosophies.

# 1. Example Use Cases

RIOT is a general purpose IoT operating system. Below is a non-exhaustive list
of use cases we address.

## 1.1. Environmental sensing

For environmental modelling or urban planning, networks of remote sensor nodes
can be deployed to collect data. These nodes can be distributed as standalone
devices or fit to infrastructure. This requires a node to:

  - Include sensors for air composition, temperature, light quality, water
    quality, etc
  - Communicate via long-range, low-power wireless mesh networking protocols
  - Interoperate with other non-RIOT nodes or gateways
  - Collect data at timescales of the order of hours
  - Potentially communicate with a smartphone
  - Potentially operate for years without power infrastructure or user
    intervention.

## 1.2. Rapid prototyping, research and experimentation

For experimentation and hacking, nodes can be developed by developers that
don't have extensive embedded experience. This requires a node to:

  - Allow easy running and loading of simple applications
  - Allow easy setup of mesh networks
  - Be highly customizable and updateable
  - Be able to use a range of plug-in sensors and actuators
  - Be usable with or without networking
  - Be based around a common, easy to use development board
  - Be programmable in the same way as other sensor nodes with different
    hardware.

## 1.3. Logistic tracking

To manage goods in transit, sensor nodes that record the environmental
conditions of goods can be used. This requires a node to:

  - Last for several months without a charge
  - Include sensors for temperature, humidity, exposure to certain gases and
    light conditions, etc
  - Send data to a local gateway.

## 1.4. Distributed system monitoring and control

To monitor and control distributed systems, networks of sensors and
actuators can be used. This requires a node to:

  - Be extremely cheap if it is a mass-market product
  - Include sensors for pressure, temperature, torque, flow, rotary encoding,
    etc
  - Include motors, solenoids, valves, heating elements, etc
  - Collect and send data with a low latency or synchronized timestamp
  - Potentially run a control loop.

## 1.4. Edge systems for building management and automation

Edge nodes in building management systems can be used for various sensing and
user interfacing tasks. This requires a node to:

  - Be powered from the building
  - Connect to the building management system via wired or wireless links
  - Include sensors for temperature, humidity, pressure, current, etc
  - Deliver data with reasonably accurate timing.

## 1.5. Smart home devices

Easy fit, easy-to-use devices can be used by consumers to monitor and manage
their home. This requires a node to:

  - Include sensors for temperature, light, humidity, smoke, etc
  - Be usable for people with no technical knowledge but still secure
  - Connect to a commercial home gateway from a different vendor
  - Potentially communicate with a smartphone
  - Potentially not be powered from the house
  
## 1.6. Daughterboards

Daughterboards can be used by developers to get immediate support for a piece of
hardware, or to outsource a task from the main processor. This requires the
daughterboard to:

  - Be reliable from the point of view of the main processor
  - Present a usable interface to the main processor
  - Potentially include a transciever, sensor, actuator, etc.

# 2 List of design goals

RIOT is friendly to developers, and lets them easily build and deploy stable IoT
networks. Below is a list of design philosophies we follow, including a
description of how they address the use cases and some decisions that are
typically made in each area.

## Small memory footprint

Most of the use cases above are well addressed by devices in class 1 of
constrained nodes [1], i.e. those with ~10 KiB of available RAM and ~100 KiB of
ROM. RIOT supports them out of the box with minimal work. If small price
differences are important or the energy budget is particularly tight, the
available memory might be near the bottom of this class. Our current
over-the-air update implementation also reduces the available ROM by over half.
RIOT therefore is usable on devices with ~2 KiB of RAM and ~10 KiB of ROM via
user optimizations and specialised modules.

Developers go the extra mile to figure out where they can remove the last few
bytes for free. Optimisations often lean towards memory over run time
performance. APIs are simple and flexible and place the onus on the application
developer to write a good program. Easy to use, less optimized functions are
often available as well though, which aren't linked if they aren't used.
Modules can sometimes be configured at build time to use more or less memory.

## Short learning curve

To make RIOT ideal for prototyping and hacking, and to reduce development time
in general, there is a minimal amount of RIOT-specific learning needed to use
the OS.

Developers reduce the learning curve for embedded C-skilled users by following
common systems and networking standards that have reached a sufficient level of
validation. To support users with less embedded experience, out-of-the-box
examples and bindings to high level scripting languages are sometimes written,
allowing them to focus on their application logic.

## Interoperability

RIOT nodes need to communicate reliably with non-RIOT nodes. The protocols need
to be fully familiar to them and behave in a way they can handle.

Modules are made available which implement open network protocol standards. The
(optional) features required by the network depend on the deployment scenario;
default configurations try to address the most common scenarios.  Whether
certain features are implemented or not, modules handle all network traffic in a
compliant manner.

## Vendor and technology independence

A wide range of use cases are addressed, and all vendors and technologies are
supported equally. This allows users to choose what's best for them, without an
implicit bias in the operating system. Furthermore, RIOT is Free Software, and
allows users to run it as they wish, for any purpose [4]; implying freedom from
tie-in.

Choice of hardware or standards to support should be based only on their
usefulness, not on brand appeal. Abstracting modules cleanly from other modules
allows them to keep any allegiance to themselves.

## Energy efficiency

RIOT nodes need to be able to last for up to several years away from power
infrastructure, placing requirements on the node to manage energy carefully.

The tickless scheduler allows devices to deep sleep while they aren't collecting
data. Developers leverage the benefits of such a scheduler and address its
programming challenges when writing their modules. They try not to demand that
users do the same. Modules however can place some of the onus on users by
presenting low power modes and API calls.

## Real-time capabilities

The range of use cases targeted means that different real-time guarantees are
required, from soft real-time performance for low-frequency remote sensing, to
hard real-time performance for high frequency sensing and control applications.

Soft real-time support is implemented by default, and long timescales are easily
achievable at the cost of accuracy. Developers also make it possible, with more
expertise, for users to write programs with hard deadlines and more accurate
timing.

## Internet security

It is important that nodes are resilient against attacks from computers with
many times their processing power.

RIOT should protect users against the threats specific to their use case.
Security is generally implemented in a way that is as easy to use as possible
while still being strong. Security flaws are patched in a timely manner and made
available via over-the-air updates.

## Stability

Whether in remote, inaccessible deployments or control applications, nodes
shouldn't fail unexpectedly. RIOT aims for stability across all supported
hardware.

Thorough testing, both manual and automated, and thorough peer review, is done
to reduce the risk of new bugs and regressions. To prevent out of memory errors
during runtime, static memory is used unless absolutely necessary, and always in
the kernel. Stability is guaranteed while minimizing memory usage by avoiding
bespoke error handlers for modules and guards against bugs elsewhere in RIOT.

## Constrained networking

Communication can be constrained because of distance, lack of resources, or
physical barriers. RIOT aims to achieve best-in-class communication robustness
despite these constraints.

Mesh networking standards which are the best available to handle these
conditions are made available to users. Developers have implemented stacks
extensibly so that performance remains up to date. Implementations consider
requirements of real scenarios, balancing memory that is typically available
against wider architectural and robustness requirements.

## Versatility

Different use cases need different hardware, features and performance. RIOT aims
to provide everything required, either in its code base or supported packages.

Developers constantly add new support for hardware and new software packages.
Implementations are kept application nonspecific, unless one is obviously
inherent. By default, modules generally lean towards being accessible to as many
users as possible, with less common use cases addressable via manual
configuration.

## Modularity

A modular approach lets RIOT adapt to different memory, functionality, and
performance demands. It also helps helps development efforts scale in a
distributed community.

Modules are cleanly abstracted from one another, and code duplication is
minimized. Features to manage or exploit this modularity are made available,
including configuration methods, methods to integrate software from third-party
sources, and modules that are themselves modular. The granularity of modules is
fairly stable and similar across different types of module. In general,
application developers shouldn't want to split any modules, but they shouldn't
be unneccesarily fine-grained either.

## Cross-hardware portability

Users may want to write a program and re-use it on different hardware. RIOT aims
for application code to be completely portable to other platforms running RIOT,
if it's valid with the hardware.

As as low a level as possible, the hardware is abstracted and the same API is
presented to upper layers. Above this, modules are kept agnostic to the specific
hardware, only requiring knowledge of whether the hardware does or doesn't
provide certain functionality. If it doesn't, the module should handle this
accordingly or not compile.

## Unified APIs

Users don't want to be confused by semantic differences between APIs. RIOT
provides a similar "look and feel" across all our APIs.

Standard features of interfaces for modules of the same type, including naming
conventions, are defined. Layers on top of modules, such as SAUL and the Sock
API, are built as well, to make the interfaces identical.

# Acknowledgements

Thanks to

# References

[1] [IETF RFC 7228: Terminolgy for Constrained-Node
Networks](https://tools.ietf.org/html/rfc7228) [2] [RIOT OS: Towards an OS for
the Internet of
Things](https://www.riot-os.org/docs/riot-infocom2013-abstract.pdf) [3] [RIOT:
an Open Source Operating System for Low-end Embedded Devices in the
IoT](http://ilab-pub.imp.fu-berlin.de/papers/bghkl-rosos-18-prepub.pdf) [4]
[Gnu.org: What is free
software?](https://www.gnu.org/philosophy/free-sw.en.html)

# Revisions

Rev0: initial commit to master
