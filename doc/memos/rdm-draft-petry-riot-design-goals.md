
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

RIOT OS is an operating system aimed at low resource (ROM, RAM, power) devices.
It supports a range of use cases. To achieve that support, developers
typically follow the design philosophies described herein.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

The decisions that developers make should ideally be generally aligned and
deliver similar benefits to users, to result in a product with clear strengths.

This document describes the consensus of RIOT design in the community, recording
the decisions that are typically made and the reasoning behind them. A series of our most commonly addressed
use cases are presented, with a short description of requirements for each. A
series of design philosophies we follow is then described, giving: a summary of
the requirements addressed; a description of the philosophy; a description of
decisions that are typically made in that area.

# 1. Example Use Cases

## 1.1. Environmental sensing

For environmental modelling or urban planning, networks of remote sensor nodes
are deployed to collect data. These nodes can be distributed as standalone
devices or fit to infrastructure. This requires a node to:

  - Include sensors for air composition, temperature, light quality, water
    quality, etc
  - Communicate via long-range, low-power wireless mesh networking protocols
  - Interoperate with other non-RIOT nodes or gateways
  - Collect data at timescales of the order of hours
  - Potentially send data via a user's mobile phone
  - Potentially operate for years without power infrastructure or user
    intervention.

## 1.2. Rapid prototyping, research and experimentation

For experimentation and hacking, nodes can be developed by developers that
don't have extensive embedded experience. This requires a node to:

  - Allow easy running and loading of simple applications
  - Allow easy setting up of mesh networks
  - Be highly customizable and updateable
  - Be able to use a range of plug-in sensors and actuators
  - Be usable with or without networking
  - Be based around a common, easy to use development board
  - Be programmable in the same way as other sensor nodes with different
    hardware.

## 1.3. Logistic tracking

For management of goods in transit, sensor nodes that record the environmental
conditions of goods are deployed. This requires a node to:

  - Last for several months without recharge
  - Include sensors for temperature, humidity, exposure to certain gases and
    light conditions, etc
  - Send data to a local gateway.

## 1.4. Distributed system monitoring and control

For monitoring and controlling distributed systems, networks of sensors and
actuators are used. This requires a node to:

  - Be extremely cheap if it is a mass-market product
  - Include sensors for pressure, temperature, torque, flow, rotary encoding,
    etc
  - Include motors, solenoids, valves, heating elements, etc
  - Collect and send data with a low latency or synchronized timestamp
  - Potentially run a control loop.

## 1.4. Edge systems for building management and automation

Edge nodes in building management systems are involved in various sensing and
user interfacing tasks. This requires a node to:

  - Be powered from the building
  - Connect to the building management system via wired or wireless links
  - Include sensors for temperature, humidity, pressure, current, etc
  - Deliver data with reasonably accurate timing.

## 1.5. Smart home devices

Easy fit, easy-to-use devices can be used by consumers to monitor and manage
their home. This requires a node to:

  - Include sensors for temperature, light, humidity, smoke, etc
  - Be secure but also usable for people with no technical knowledge
  - Connect to a commercial home gateway from a different vendor
  - Potentially not be powered from the house
  
## 1.6. Daughterboards

Daughterboards can be used by developers to get immediate support for a piece of
hardware, or to outsource a task from the main processor. This requires the
daughterboard to:

  - Be reliable from the point of view of the main processor
  - Present a usable interface to the main processor
  - Potentially include a transciever, sensor, actuator, etc.

# 2 List of design goals

RIOT's immediate users are developers. Its design goals are therefore targeted at
supporting developers to build products for the use cases above, with high
quality, short time-to-market, and low cost.

## Small memory footprint

Most of the use cases above require devices in class 1 of constrained nodes [1].
In cases where small price differences become important or the energy budget is
particularly tight, it becomes useful to reduce the memory usage towards the
bottom range of this class. Over-the-air updating can also constrain ROM if
two images are stored.

RIOT aims to be usable on low-end devices starting at ~2 KiB RAM with
optimizations and specialised modules. For the median of class 1 devices, RIOT
provides the required functionality in default configurations and main modules.

Where possible, the memory footprint is reduced for free by taking time to find
optimal solutions. The kernel is kept minimal and functionality added with
other modules. Error handling is the minimum required to guarantee stability. Implementations often lean
towards saving memory over run-time performance. APIs often implement less functions that are more flexible and place the onus on the
application developer to write a good program. However, easier to use functions
which aren't linked if they aren't used are often available as well. Where
there is a tradeoff of memory usage with versatility, build time configuration
is sometimes employed to only include certain functionality, with the default
configuration addressing the most important use cases and leaning towards a
reduced learning curve.

## Short learning curve

For prototyping and research, and to reduce the time to market of all use cases
above (for example, in a startup scenario), a short learning curve is
beneficial.

RIOT aims to require a minimal amount of RIOT-specific learning for the
developers using it to build the products above. In many cases they will be
embedded C developers without RIOT experience. In some cases, especially use
case 1.2, they may have only basic programming knowledge. In a startup
scenario, development may be done by someone who is more familiar with high
level scripting languages than with C.

For experienced C developers, the learning curve is reduced by customarily 
following systems and networking standards such as POSIX, C99, libc, and
standards defined in IETF RFCs and elsewhere that have reached a sufficient
level of validation. For less experienced developers, out-of-the-box examples
are provided which only require simple changes for their application. High level
scripting languages increase accessibility to developers from other fields,
allowing them to focus on the business logic. Where there is a tradeoff with
other design goals, a default configuration can provide a reduced learning curve
and central functionality, with more versatility or optimization available
through specific configurations.

## Interoperability

In use cases where RIOT nodes are communicating with non-RIOT nodes or
gateways, it is necessary to ensure that stable communication is possible.
In development scenarios where a third-party library or driver may be required,
it is useful for integration to be possible with a minimal development time.

RIOT nodes aim to be interoperable with other nodes, meaning that a RIOT node
provides a communication protocol which is familiar to other nodes. It either
handles communication successfully, or fails in a manner which is in accordance
with the relevant specification, if such a failure is allowed. RIOT aims to be
able to integrate third-party software components with minimal patching.

To achieve this, open network protocol standards, e.g. IETF protocols, are customarily
used. To take full advantage of the largest pool of third party software,
systems standards, e.g. C99, are customarily used. When there are compelling
reasons to optimize outside these standards, non-core modules are sometimes
developed, which do not present themselves as compliant. Where standards 
are phrased in such a way that particular parts are open to be implemented in
different ways, or not implemented at all, these can be
considered with reference to other design philosophies and the needs of the
main use cases we address.

## Vendor and technology independence

The use cases RIOT address are varied and so are the available technologies. For
each use case, there are different technologies and hardware that make the most
sense. Additionally, RIOT is Free Software and allows users to run it as they
wish, for any purpose [4].

RIOT aims to be completely agnostic of vendors and technologies, providing
support for hardware or standards based only on their ability to meet user
requirements. None is tied into through design decisions. This aims to allow users to change vendors and technologies with
minimal development effort, and also prevents code duplication.

Vendors or technologies that are preferable over others are often used for their
strengths, while avoiding lock-in.

## Energy efficiency

A number of targeted use cases require some degree of energy efficiency, but
especially remote sensing, where nodes may be remote, not connected to power
infrastructure, and required to collect data for a number of years.

RIOT aims to allow nodes to minimize energy consumption,
manage energy, and potentially harvest energy from the environment.

RIOT employs a tickless scheduler, which allows devices to sleep for longer
timescales. This trades off against learning curve in the case when a developer
is writing a nontrivial multithreaded program. Examples and higher level
abstractions are sometimes written to allow users to develop usable remote
sensing applications quickly without explicitly handling multithreading
themselves.

## Real-time capabilities

Sensing use cases require nodes to collect data with some degree of timing
accuracy. Control applications meanwhile demand harder timing constraints.

RIOT aims to achieve soft real-time guarantees for most use cases, with harder
real-time guarantees possible where required. Programs can sleep for timescales
of the order of hours, or achieve sub-millisecond accuracy.

Soft real-time capabilities
involving low frequency, less accurate ticks are therefore available with default
configurations and higher level software abstractions, to address sensing applications.
RIOT's scheduler also makes it possible with more expertise to write programs requiring
sub microsecond timing precision and harder real time guarantees, involving
specific configuration where necessary.

## Internet security

In all use cases, security is a fundamental requirement. In the case of smart
home devices, user privacy and compromise of devices for further attacks have been of
particular media interest in recent years. In the case of building management or
control applications, it is crucial for safety that the system cannot be compromised and
operated by a malicious actor.

RIOT aims to ensure the security required for each use case, depending on the
threats that a device may reasonably experience as well as the penalty if those
threats are realised. It also provides over-the-air updating to deploy security
patches.

Security can come at a cost of a learning curve. Security against reasonable
threats is however a hard requirement and implementations should reduce the
learning curve only as far as possible and guarantee security despite potential
user errors in programming or configuration.

## Stability

Remote sensing use cases demand that nodes continue to run for years without
manual intervention. Control applications demand that nodes remain stable
during their use period, or fail in a controlled way so that the failure can be
handled elsewhere in the system.

RIOT aims to achieve this stability on all supported hardware.

Extensive, continuous manual and automated testing is deployed to detect bugs.
The use of static memory unless absolutely necessary, and always in the kernel,
prevents out of memory errors during runtime. Where stability trades off
against ease of use, stability always takes precedence, and should always be
guaranteed despite potential user errors.

## Constrained networking

Communication is typically constrained in remote sensing use cases where nodes
are distant from each other, or in building automation or smart home use cases
where nodes are low transmission power and separated by physical barriers such
as walls.

RIOT aims to maintain stable communication channels, achieving the required
bandwidth in constrained mesh networking situations.

The protocols selected are the best available to handle these conditions, that
have achieved a sufficient level of validation. Where this trades off against
...

[TODO: tradeoffs]
- memory usage?
- ease of use?

## Versatility

The use cases above require a range of hardware support and different
performance. As a general purpose IoT OS, RIOT aims to provide everything required to cover
them in its code base or supported packages.

The boards and sensors we support are continuously increased while aiming for
stability on all of them. Performance is generally kept as application
nonspecific as possible, especially in default configurations.

## Modularity

To address a range of applications, and allow users to only use the memory they
need, RIOT defines self-contained building blocks, to be combined in different
configurations. These blocks can also be developed separately, which is useful
for a distributed community.

The degree of modularity is fairly stable, and aims to be similar across different types
of module. In general, application developers shouldn't want to split modules, but they
shouldn't be unneccesarily fine-grained either.

## Cross-hardware portability

[requirements of use case]
[details of design goal in RIOT context]
[tradeoffs]
Development should be able to be done once and run on any platform using RIOT.
Most of the code is portable across supported hardware. To achieve this with
reduced development effort in porting, the hardware is abstracted and the APIs
are uniform at as low a level as possible. The code duplication is minimized
across configurations.

moved from above - ## 1.5 Cross-hardware system integration

TODO: why do we do this and what use case(s) does it tie into?

This involves integrated, distributed sensor and actuator systems running RIOT
on different hardware platforms. This requires software to be agnostic to the
underlying hardware and support common protocols.

## Unified APIs

[requirements of use case]
[details of design goal in RIOT context]
[tradeoffs]
- the reason we want to have this is so that a user doesn't have to get used to
  new APIs every time they do a new module, not because we want to have
  portability. This is different from hardware abstraction APIs. This is about
  the APIs looking and feeling as similar as possible.

In order to achieve clean hardware abstraction and modularity, the APIs across
the system are as homogeneous as possible across all supported hardware, even
for hardware-accessing APIs. This caters for code portability and minimizes
code duplication. In the APIs, common functionality
is presented in exactly the same way, while more specific functionality is
presented in a way that does not break code implemented on top of the APIs of
other modules.


# Acknowledgements

Thanks to

# References

[1] [IETF RFC 7228: Terminolgy for Constrained-Node Networks](https://tools.ietf.org/html/rfc7228)
[2] [RIOT OS: Towards an OS for the Internet of Things](https://www.riot-os.org/docs/riot-infocom2013-abstract.pdf)
[3] [RIOT: an Open Source Operating System for Low-end Embedded Devices in the IoT](http://ilab-pub.imp.fu-berlin.de/papers/bghkl-rosos-18-prepub.pdf)
[4] [Gnu.org: What is free software?](https://www.gnu.org/philosophy/free-sw.en.html)

# Revisions

Rev0: initial commit to master
