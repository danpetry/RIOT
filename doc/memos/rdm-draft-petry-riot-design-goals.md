
 - rdm-draft-petry-riot-design-guidelines.md
 - Title: RIOT design guidelines
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

RIOT is an operating system aimed at low resource (ROM, RAM, power) devices.
It is general purpose within the sphere of IoT, and supports a range of use
cases. To achieve that support, the design philosophies described herein are
followed.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

This document describes the design decisions that are typically made by the
RIOT community, and the reasoning behind them. The aim is to collect consensus
in order to guide future development work. It gives a description of our most
commonly addressed use cases, and a list of design philosophies that are
commonly followed.

# 1. Use Cases

RIOT is a general purpose IoT operating system. Below is a non-exhaustive list
of use cases it addresses.

## 1.1. Environmental sensing

Networks of remote sensor nodes can be deployed to study the environment or
assist with urban planning. These devices can be distributed on their own or
fit to infrastructure. The devices need to:

  - Support long-range, low-power wireless mesh networking protocols
  - Interoperate with non-RIOT nodes or gateways
  - Collect data on timescales of the order of hours
  - Sense air composition, temperature, light quality, water quality, etc
  - Potentially communicate with a smartphone
  - Potentially operate for years without power infrastructure or maintenance

## 1.2. Rapid prototyping, research and experimentation

In experimentation and hacking situations, development needs to be accessible
to amateur users. This means that the software and hardware should:

  - Let users easily run and load simple applications
  - Let users easily set up mesh networks
  - Be highly customizable and updateable
  - Support a range of plug-in sensors and actuators
  - Be usable with or without different features, including networking
  - Use commonly available, easy to use development boards
  - Come with an easy to use toolkit that has a minimum of setup time
  - Let users easily port programs to different devices.

## 1.3. Logistic tracking

Sensors that record environmental conditions can be used to manage goods in
transit. These sensors need to:

  - Last for several months without charging
  - Sense temperature, humidity, exposure to certain gases and light
    conditions, etc
  - Regularly send data to a local gateway.

## 1.4. Distributed system monitoring and control

Distributed networks of sensors and actuators can be employed in certain
control applications, coordinated by a central computer. The nodes need to:

  - Be extremely cheap, if they're in a mass-market product and there's a large
    number of them
  - Sense pressure, temperature, torque, flow, rotary position and velocity,
    etc
  - Control motors, solenoids, valves, heating elements, etc
  - Collect and send data with a low latency, or at least a well synchronized
    timestamp
  - Potentially run control algorithms themselves.

## 1.4. Edge systems for building management and automation

Various sensing and user interfacing tasks can be done by edge nodes in
buildings. The nodes need to be able to:

  - Connect to the building's power
  - Connect to the building management system, via wired or wireless
    connections
  - Sense temperature, humidity, pressure, current, etc
  - Deliver data with reasonable timing accuracy.

## 1.5. Smart home devices

Easy to use devices can let consumers monitor and control their home
automatically. The devices need to be able to:

  - Sense temperature, light, humidity, smoke, etc
  - Be usable but secure for people with no technical knowledge 
  - Connect to a commercial home gateway 
  - Often communicate with a smartphone
  - Connect to the building's power or provide their own power, depending on
    the product
  
## 1.6. Daughterboards

Plug-in boards can give devices immediate support for a protocol or standard,
or let them outsource a task from the main processor. This requires the
board to:

  - Perform its stated task reliably
  - Respond reliably to commands from the main processor
  - Include and support any relevant hardware

# 2 Design philosophies

RIOT is friendly to users, and lets them easily build and deploy stable IoT
networks. Below is a list of design philosophies that are followed to achieve
this, including a short description and any decisions and tradeoffs that
developers typically make in each area.

## Small memory footprint

Most of RIOT's targeted use cases are well addressed by devices in class 1 of
the taxonomy presented in [1]. If small price differences are important or the
energy budget is particularly tight, the available memory might be near the
bottom of this class. Over-the-air updating currently reduces the available
ROM by over half.

RIOT should provide out-of-the box support for devices with ~10 KiB of
available RAM and ~100 KiB of ROM. It should be just as possible to run it on
lower end devices, starting at ~2 KiB of RAM and ~10 KiB of ROM, with manual
optimizations and specialised modules.

Developers often go the extra mile to figure out where they can remove the last
few bytes for free. Optimisations often lean towards memory over run time
performance. APIs are simple and flexible and place the onus on the application
developer to write a good program. Modules are sometimes made build time
configurable, to give users the choice of which features they want to spend
their memory on.

## Short learning curve

To make RIOT ideal for prototyping and hacking, it doesn't require years of
professional experience to use.

Out-of-the-box examples, bindings to high level scripting languages, and
"easier" API functions and abstractions are often written in order to let users
of a wide variety of skill levels use RIOT. The easier features are written in
such a way that they aren't linked, and therefore don't use memory, if they're
not used. No user of any skill level should be tripped up because they haven't
manually configured a feature that they wouldn't understand. For users with more
experience in embedded C, RIOT should still demand as little RIOT-specific
learning as possible. Common systems and networking standards such as C99,
POSIX, libc, UDP, CoAP, IPv6, and so on are therefore supported.

## Interoperability

RIOT nodes need to communicate reliably with non-RIOT nodes. The protocols need
to be familiar to them and behave in the way they expect.

RIOT should support open network protocol standards once they have reached a certain level
of validity and popularity. If features of the specification are optional, the
implementation should be configurable to allow users to choose what they want
to use. Whatever the configuration, nodes should handle all possible traffic in
a compliant manner.

## Vendor and technology independence

All vendors and technologies are supported equally. This means users can choose
what's best for them, without any inherent bias. Moreover, RIOT is Free
Software [1], which means users are free to use it as they wish without
lock-in.

The choice of the hardware and standards RIOT supports should only depend on
how useful they are. By abstracting modules cleanly from each other, any
allegiance they may have is kept to themselves.

## Energy efficiency

RIOT nodes sometimes need to last for several years without external power, so they need
to manage energy carefully. RIOT's tickless scheduler lets devices sleep while
they aren't collecting data.

Developers often leverage the benefits and address the programming challenges
of a tickless scheduler when they write their modules. They try not to demand
that users do the same. Implementations do sometimes place some of the onus on
users by giving them modes and functions that use more or less power.

## Real-time capabilities

Different real-time guarantees are required for different use cases. Low
frequency sensing needs only soft real time support, and can handle less timing
accuracy so long as the timers support long timescales. High frequency sensing
and control applications need hard real time guarantees and sub-millisecond
timing accuracy.

RIOT should deliver soft real-time performance by default, to cover the widest
range of use cases. Programs with hard deadlines should be achievable with more
expertise. It should provide configurable timers which can competently handle the
timescales of any application.

## Internet security

It is crucial that internet connected devices are resilient against cyber
attacks.

RIOT should protect users from all the threats they're likely to experience,
including computers with many times their processing power. Security should be
as easy to use as possible while still strong. Security flaws should be patched
as quickly as possible. Convenient updating mechanisms should allow users to
apply patches to their nodes, wherever they are.

## Stability

Nodes shouldn't fail because of RIOT. Given perfect hardware and a moderately
well written application, it should be able to run indefinitely. This should
apply to all supported platforms. 

The testing and peer review processes that ensure this should be constantly
being improved, including automating it where it's possible.  To prevent out of
memory errors during runtime, dynamic allocation isn't used unless it's
absolutely necessary, and never in the kernel. Error handlers should do what's
required and no more, to save memory; bespoke error handlers and guards against
bugs elsewhere in RIOT should be avoided.

## Constrained networking

"Constrained" means that available memory, energy and processor cycles are so
reduced as to become a dominant consideration in design requirements [1]. RIOT
should deliver best-in-class bandwidth and robustness nevertheless.

Network stacks should remain up-to-date as relevant standards emerge, and some
are extensible to support this. Users should be able to adapt them and choose
between different stacks; they should be able to get the best performance and
most functionality possible from whatever resources they have available.

## Versatility

RIOT should provide everything users need, either in its code base or in
external packages we support.

New support is always welcomed. Modules should be application nonspecific,
where it's feasible. Default configurations should be as accessible to as many
users, and address as many use cases, as possible.

## Modularity

Being modular lets RIOT address many different memory, functionality, and
performance demands. It also helps development efforts to scale in a
distributed community.

Modules should be cleanly abstracted from one another. Anything needed for a
new module should be localized to its own folder. Code should not be
duplicated, unless it's unavoidable. It should be easy to manage or exploit
this modularity, for example through configuration, easy integration of
third-party source code, and different layers of modularity. The granularity of
modules is fairly stable, and similar across different types of module. In
general, users shouldn't want to split modules, but they shouldn't be
unneccesarily fine-grained either.

## Cross-hardware portability

Users might want to write a program, and then run it on a different piece of
hardware. RIOT should allow user code to be completely portable, so long as
it's valid with the hardware.

The hardware abstractions are stable and interfaces are firmly defined. New
implementations should follow these definitions. Above the HAL, the only thing
that modules should know about hardware is whether a required feature is there
or not. If it isn't, the module should adapt accordingly, or not compile.

## Unified APIs

Users don't want to be confused by semantic differences between APIs. RIOT
provides a similar "look and feel" across all our APIs.

RIOT's interfaces should only differ in the ways that their modules differ.
Where possible, layers should sit on top of modules of the same type, to give
an identical interface. Semantics and naming conventions should be the same
throughout the system.

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
