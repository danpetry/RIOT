
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry
 - Date: October 2018

## Abstract

This document presents key design aspects of the RIOT operating system: its
application contexts and design rationales.  It aims to reflect a consensus on
the reasoning behind RIOT design, in order to help new contributors get up to
speed more quickly and provide common ground for technical debates.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Terminology

Throughout this document, the term "users" refers to developers who are using
RIOT as a basis to implement application software, without editing RIOT's
source code. The term "developers" refers to contributors to the source code of
RIOT.

# 1. Introduction

This document lists a set of generalised, loose requirements for RIOT (in a
voluntary open source context, gathering strict requirements is neither
possible nor welcome). These "design goals", as they may be called, are given
as a set of use cases followed by a set of design philosophies. These
correspond loosely to user requirements and derived requirements respectively.

# 2. Use cases

RIOT is a general purpose IoT operating system for low-end devices. As a
result, its use cases are varied: below is a comprehensive, but non-exclusive
list of them, including the general requirements placed on the devices for each
use case.

## 2.1. Environmental sensing

Networks of remote sensor nodes can be deployed to monitor the environment or
assist with urban planning. These devices can be distributed on their own or
fit to infrastructure. The devices need to:

  - Sense air composition, temperature, light quality, water quality, etc
  - Support low-power wireless networking protocols
  - Interoperate with non-RIOT nodes or gateways
  - Collect data on timescales of the order of hours or longer
  - Potentially be able to send data over long ranges
  - Potentially communicate with a smartphone
  - Potentially operate for years without power infrastructure or maintenance

## 2.2. Rapid prototyping, research, and experimentation

In experimentation and hacking situations, development needs to be easily
accessible, and allow a short development time and quick results. This means
that the software and hardware should:

  - Let users prototype easily
  - Let users easily run and load simple applications
  - Let users easily set up networking
  - Let users easily port third party libraries
  - Be highly customizable and updateable
  - Support a range of plug-in sensors and actuators
  - Be usable with or without different features, including networking
  - Use commonly available, easy to use development boards
  - Come with an easy-to-use toolkit that has a minimum of setup time
  - Let users easily port programs to different devices.

## 2.3. Logistic tracking

Sensors that record environmental conditions can be used to manage goods in
transit. These sensors need to:

  - Sense position and condition of goods
  - Last for several months without charging
  - Send data over long ranges to regional infrastructure.

## 2.4. Physical system monitoring and control

Distributed networks of sensors and actuators can be employed in certain
control applications, such as automotive systems or Industry 4.0. The nodes
need to:

  - Sense various specific properties such as pressure, torque, velocity, or
    flow
  - Control various specific actuators such as motors, solenoids, or valves
  - Control motors, solenoids, valves, heating elements, etc
  - Collect and send data with a low latency, or at least a well synchronized
    timestamp
  - Potentially have a very low unit cost, particularly when the networks are
    implemented in mass market products such as automobiles
  - Potentially run control algorithms themselves.

## 2.5. Edge systems for building management and automation

Various sensing and environmental control tasks can be done by edge nodes in
buildings. The nodes need to be able to:

  - Sense temperature, light, humidity, pressure, current, etc
  - Control temperature, light, ventilation, etc
  - Connect to the building management system, via wired or wireless connectors
  - Deliver data with controllable timing and accuracy.

## 2.6. Smart home devices

Easy to use devices can let consumers monitor and control their home
automatically. The devices need to be able to:

  - Sense temperature, light, humidity, smoke, etc
  - Integrate with home appliances to control temperature, light, power usage,
    etc
  - Be usable but secure for people with no technical knowledge 
  - Connect to a commercial home gateway 
  - Communicate over common home IoT protocols such as ZigBee, Bluetooth, Wi-Fi,
    etc
  - Connect to the building's power or provide their own power, depending on
    the product
  
## 2.7. Daughterboards

Plug-in boards can give devices immediate support for a protocol or standard,
or let them outsource a task from the main processor. This requires the board
to:

  - Perform its promised task reliably
  - Integrate and communicate reliably with the main processor
  - Include and support any relevant hardware

## 2.8. Education

The broad technical scope of RIOT makes it useful as a basis for education.
This requires:

  - The presence of didactic materials related to RIOT
  - Clear and easy to find documentation
  - A general availability of supported hardware and tools

# 3. Design philosophies

RIOT satisfies the requirements of all the use cases given above, and does so
in its own unique way, a way that reflects the collective personality of the
RIOT community. RIOT is the Friendly IoT Operating System: it is friendly to
users, allowing them to easily build and deploy IoT solutions that are stable
and trouble-free.

Below are the design philosophies that are typically followed by developers to
achieve this, including descriptions of tradeoffs between them and where the
resolutions typically fall.

## Suitability for constrained devices

"Constrained" means that available memory, energy, and processor cycles are so
reduced as to become a dominant consideration in design requirements [1]. 

#### Energy efficiency

RIOT nodes sometimes need to last for several years without external power, so
they need to manage energy carefully. RIOT's tickless scheduler lets devices
sleep while they aren't collecting data.

Modules outside the core should leverage the benefits and address the
programming challenges of such a scheduler. They shouldn't demand that users do
the same.  They should, however, allow users to manage power through different
modes and functions.

#### Small memory footprint

Most of RIOT's targeted use cases are well addressed by devices in class 1 of
the taxonomy presented in [1]. If small price differences are important or the
energy budget is particularly tight, the available memory might be near the
bottom of this class. Over-the-air updating facilities may also reduce the
available ROM by over half, depending on the architecture.

RIOT should provide out-of-the-box support for devices with ~10 KiB of
available RAM and ~100 KiB of ROM. It should be just as possible to address
real use cases involving even smaller devices, starting at ~2 KiB of RAM and
~10 KiB of ROM, with manual optimizations and specialised modules. Users should
be given the choice of what they want to spend their memory on.

#### Constrained networking

RIOT should deliver best-in-class communication performance and robustness.

Network stacks should remain up-to-date as relevant standards emerge; they
should be adequately extensible to support this. Users should be able to
configure them according to technological options, and choose between
high-quality implementations which address performance tradeoffs differently.
They should be able to get the best performance and most relevant functionality
out of whatever resources they have available.

## Short learning curve

RIOT's use cases involve makers, researchers in (non-)computer science fields,
broadly skilled engineers making vertically integrated IoT proofs-of-concept,
and experienced embedded C developers.

All of these users should be comfortable using RIOT and its tooling, whatever
their platform or hardware. No user of any skill level should be tripped up
because they haven't configured something that they wouldn't reasonably be
expected to know about. Whatever the user's background, RIOT should demand as
little RIOT-specific learning as possible. It should, therefore, adhere to
common systems and networking standards.

## Vendor and technology independence

Vendors and technologies are supported with zero bias. This means users can
choose what's best for them, without being led by RIOT. Moreover, RIOT is Free
Software [2], which means users are free to use it as they wish without
lock-in.

The choice of the hardware and standards RIOT supports should depend only on
how well they support the use cases. Any allegiance that modules may have
should be kept to themselves.

## Versatility

The use cases for IoT systems are manifold, and so are their requirements.
Therefore, design decisions in RIOT should not prefer one technology or one
protocol over another. 

Default configurations should support as many users and use cases as possible.
RIOT should aim at providing everything users need, either in its code base or
in the external packages it supports. The list of hardware, algorithms and
other elements that RIOT supports should constantly be expanding.

## Modularity

RIOT decomposes into small modules. Being modular lets RIOT address many
different memory, functionality, and performance demands. It also helps
development efforts to scale in a widely distributed community.

Modules should be abstracted from one another as cleanly as possible. It should
be easy for users to manage or exploit this modularity, for example through
configuration methods, easy integration of third-party source code, or
different levels of modularity. The granularity of modules should be stable and
similar across different types of module. Users shouldn't want to split
modules, but they shouldn't be unnecessarily fine-grained either.

## Cross-hardware portability

Users might want to write a program for one piece of hardware, and later run it
on another. RIOT should let user code be completely portable, so long as it
remains valid with the hardware.

The hardware abstraction layer should be stable, well defined and consistent.
Above the HAL, the only thing that modules should know about hardware is
whether its build dependencies are provided or not. If they aren't, the module
should adapt accordingly, or not compile.

## Real-time capabilities

Different real-time guarantees are required for different use cases. Low
frequency sensing needs only soft real-time support and can handle less timing
accuracy so long as the timers support long timescales. High-frequency sensing
and control applications need hard real-time guarantees and sub-millisecond
timing accuracy.

RIOT should deliver soft real-time performance by default, to cover the widest
range of use cases. Programs with hard deadlines should be achievable with more
expertise. It should provide timers which can competently handle the timescales
of any application.

## Interoperability

RIOT nodes need to communicate reliably with non-RIOT nodes by carefully
implementing open standards or identical technological specifications.

RIOT should support open network protocol standards once they have reached a
certain level of maturity and popularity. It should be configurable so that
users can choose which (optional) features of specifications they want to
include.  Whatever the configuration, nodes should handle all possible traffic
in a compliant manner.

## Stability

Nodes shouldn't fail because of RIOT, whatever the platform. Assuming perfect
hardware and a moderately well-written application, they should be able to run
indefinitely.

The testing and peer review processes that ensure this should be under
continuous review and refinement, including automating them where it's
possible. Error handling should guarantee stability with minimal memory usage.

## Unified APIs

RIOT wants to ease development for users by providing a similar "look and feel"
across all our APIs.

RIOT's interfaces should only differ in the ways that their modules differ.
Where possible, layers should exist that sit on top of a certain class of
modules to give an identical interface to the user. Semantic and naming
conventions should be consistent throughout the system.

## Internet security

RIOT nodes need to be resilient against cyber attacks, for the sake of its
reputation and the reputation of the IoT.

It should be hard against all the threats a node is likely to experience,
depending on the situation, including those from computers with many times
their processing power. Security should be as easy to use as possible while
still strong. Security flaws should be patched as quickly as possible by
servicing a security alert channel with high priority. Convenient updating
mechanisms should allow users to apply patches to their nodes, wherever they
are.

# Acknowledgements

This document follows previous work on documenting RIOT's design priorities [3]
[4].

# References

[1] [C. Bormann, M. Ersue, A. Keranen: "Terminology for Constrained-Node
Networks.", RFC, No. 7228, RFC-Editor, May 2014.](https://tools.ietf.org/html/rfc7228) \
[2] [“What Is Free Software?” _GNU Operating System_, 15 Dec. 2018,
www.gnu.org/philosophy/free-sw.en.html.](https://www.gnu.org/philosophy/free-sw.en.html) \
[3] [Emmanuel Baccelli, Oliver Hahm, Mesut Günes, Matthias Wählisch, Thomas C.
Schmidt, "RIOT OS: Towards an OS for the Internet of Things," in Proceedings of
the 32nd IEEE International Conference on Computer Communications (INFOCOM),
Poster, p. 79–80, IEEE Press, April 2013.](https://www.riot-os.org/docs/riot-infocom2013-abstract.pdf) \
[4] [E. Baccelli, C. Gündogan, O. Hahm, P. Kietzmann, M. Lenders, H. Petersen,
K. Schleiser, T.C. Schmidt, M. Wählisch: "RIOT: an Open Source Operating System
for Low-end Embedded Devices in the IoT", IEEE Internet of Things Journal, Vol.
5, No. 6, p. 4428- 4440, IEEE, December 2018.](http://ilab-pub.imp.fu-berlin.de/papers/bghkl-rosos-18-prepub.pdf)

# Revisions

Rev0: initial commit to master
