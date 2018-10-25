
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

RIOT OS is an operating system aimed at low resource (ROM, RAM, power) devices.
It supports a range of use cases by achieving a number of specific design goals.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

The decisions that RIOT developers make should be consistent with each other,
and should consistently deliver the same benefits to users. Such alignment
results in a compelling product with its own unique strengths, derived from the
collective consciousness of the RIOT community.

This consensus document describes these strengths. A series of use cases are presented,
along with a short description of requirements for each use case. A series of
design goals then follows, giving: a summary of the requirements addressed by
the design goal; a description of the design goal itself; a description of any
specific tools or patterns we use to achieve the design goal; and a description of
tradeoffs with other design goals, with guidelines for resolution.

# 1. Example Use Cases

## 1.1. Environmental sensing

For environmental modelling or urban planning, a network of remote sensor nodes
can be deployed to collect data. These nodes could be distributed as standalone
devices, or retrofit to existing infrastructure. This requires a node to:

  i.   Sleep and wake up at timescales of the order of hours
  ii.  Include any required sensors (air composition, temperature, light quality,
       water quality etc)
  iii. Use long-range, low-power wireless mesh networking protocols in the case
       of very remote nodes or devices fit to publicly used infrastructure
  iv.  Interoperate with other nodes in the network if they are from a
       different vendor or running different implementations of a protocol
  v.   Send data via a user's mobile phone in the case of privately used
       infrastructure such as rental cycles
  vi.  Operate in a stable manner for timescales of the order of years, without power
       infrastructure, potentially harvesting energy from the environment.

## 1.2. Rapid prototyping, research and experimentation

For research situations, proof-of-concepts for startups, or personal projects,
sensor nodes which are not intended for mass market, but that need to be made
quickly, with a low learning curve and little specialist knowledge, can be developed.
This requires a node to:

  i.   Be up and running quickly in a situation where the developer may not
       have much, or any, experience with embedded programming
  ii.  Be highly customizable, and upgradeable after initial development and
       deployment
  iii. Be able to use a wide range of commonly available sensors, particularly those
       that are available on plug-in daughterboards
  iv.  Be based on a development board that is easily programmable and requires
       little specialist knowledge to use
  v.   Be programmable in as similar a manner as possible compared with other,
       different sensor nodes in the same deployment
  vi.  Operate without networking, if networking is not required for the
       application.

## 1.3. Logistic tracking

To manage the movement of resources, sensor nodes to record the location
and state of goods can reduce loss of value during transit can be deployed. This requires a node
to:

  i.   Last for a number of weeks without recharge
  ii.  Include any required sensors (temperature, humidity, exposure to certain
       gases and light conditions, etc)
  iii. Send data to a local gateway, which itself is connected to the vehicle's
       power source and handles GPS localization.

## 1.4. Distributed system monitoring and control

To monitor and control distributed systems, a central computer and a network of lower
resource nodes can be used. This requires a node to:

  i.   Be extremely low resource and cheap, in the case where the sensor nodes
       are very numerous and/or in a mass-market product
  ii.  Include any required sensors (pressure, torque, flow, rotary encoder,
       temperature, pressure, etc)
  iii. Include any required actuators (motors, solenoids, valves, heating
       elements, etc)
  iv.  Collect and feed back data to the control loop with a low latency or
       a timestamp based on accurate synchronization
  v.   Achieve high timing accuracy, in the case where a control loop is running
       on the node

## 1.4. Edge systems for building management and automation

To improve the comfort of occupants, reduce energy consumption, and reduce
operating costs, sensors that monitor the environmental conditions in a building
can be deployed. These sensors then influence the control of the HVAC (heating,
ventilation, and air conditioning) systems. This requires a node to:

  i.   Connect to the building's power infrastructure
  ii.  Connect to the building management system via common wired or wireless
       LAN protocols
  iii. Include any required sensors (temperature, humidity, pressure etc)
  iv.  Deliver data at a rate and time accuracy that allows stable feedback
       control of the parameters being measured.

## 1.5. Easy-fit smart home devices

For smart home applications, devices which can be fit to the home without a
power supply can be deployed. This requires a node to:

  i.   Last for a number of weeks without recharge, while continuously
       collecting data
  ii.  Include any required sensors (temperature, light, humidity, smoke, etc)
  iii. Connect to a home gateway using a widely supported wireless LAN protocol.

## 1.6. Daughterboards

To provide immediate support for functionality such as communication, sensing,
actuation, or some combination of these along with convenient or flexible application
logic, low power plug-and-play daughterboards can be produced. This requires the daughterboard to:

  i.   Support popular communication protocols
  ii.  Support popular microcontrollers, transceivers, sensors and actuators
  iii. Allow easy definition of application logic
  iv.  Operate in slave mode for board protocols which use a master-slave model.

# 2 List of design goals

RIOT's immediate users are developers. Its design goals are therefore targeted at
supporting developers to build products for the use cases above, with high
quality, short time-to-market, and low cost.

## Small memory footprint

In a number of use cases above, devices in class 1 of constrained nodes
according to the taxonomy presented in [1] are typically used. In the case
where sensors in a system are very numerous and small price differences become important, or where the energy budget is extremely
tight, it is beneficial to reduce the memory usage towards the bottom end
of this class. Over-the-air updating can reduce the available ROM
significantly.

- specifically mention the relationship with low energy
- 

RIOT aims to be usable on low-end devices starting at ~2 KiB RAM, for optimized
applications, requiring extra configuration where appropriate (which is
provided in those modules). It aims to provide out-of-the-box functionality for the
Idea:
- default config/easy to use/all required functionaliyt for the body of use
  cases above

  - tradeoff between ease of use and small memory footprint, allowing for
    configurability

- brief description of networking/sensing functionality provided 
median of class 1 devices (~10 KiB RAM, ~100 KiB ROM).
RIOT aims to provide a (keep description broad)


[specific techniques and details we use to reduce the memory footprint]
- multiple network stacks/crypto algorithms/sensors that do the same thing/etc
  so that people can select lower resource thing or higher resource thing
- configurability of individual modules to optimize memory (vs certain
  functionality)
- try and get things for free by using smart design and using good practices
- optimize API design for memory usage (by being judicious about functionality, more flexibility
  and onus on application developer to write optimized and safe code)
- trade off against run time performance leans towards optimized memory in a
  sensible manner
- Statically configured features where feasible
- keep the kernel small and build functionality on top of it

[TODO: lean towards language like "feasible", "judicious" - i.e. so that it's
guidelines not hard rules. Can give examples rather than full details. Can
shift details elsewhere and reference them]



[tradeoffs with other design goals and how to resolve]
- learning curve
- flexibility/extensibility
- never cut corners when it comes to stability (essentials of error handling for things that
  are out of the software's control)


- OTA requires twice the ROM now

## Short learning curve

Users of RIOT want to be able to develop and deploy their products in as short a
time as possible, with as little extra learning and specialized knowledge as
possible. This means support for standards such as POSIX and a range of
widely-used languages, out-of-the-box examples, simple build configuration, and
tools and platforms that support RIOT. Ease of use is, however, subject to the
robustness and resilience requirements below.

[todo: mention defining application logic only where appropriate]

Developers, likewise, should be able to start contributing in as short a time as
possible, and so the design and APIs should remain clear and generally follow
common and easy to understand principles, unless there are strong benefits that
directly achieve operational goals.

## Interoperability

In order to ensure the interoperability of devices running RIOT with ones that
do not, open network protocol standards, e.g. IETF protocols, are customarily
used. To take full advantage of the largest pool of third party software,
systems standards, e.g. the ANSI C standard (C99), are customarily used. We may
provide non-core modules which break from this (alongside modules which do not)
if there are compelling reasons that serve other design philosophies. Where
standards are phrased in such a way that particular aspects are open to be
implemented in different ways, or not implemented at all, these aspects will be
considered with reference to other design philosophies and to user needs.

## Vendor and technology independence

To achieve interoperability between heterogeneous nodes, and to protect freedom
0 of the four essential freedoms [4], RIOT is agnostic of the vendor and
technologies of the hardware. Vendor libraries are typically avoided, to
preclude lock-in and minimize code duplication. No vendor, protocol,
microcontroller, transceiver, sensor, actuator, or any other technical component
is tied into through design decisions. None is preferred over any other for any
reason other than the reasons detailed in the other design philosophies.

## Energy efficiency

RIOT nodes should be able to survive for years without running out of power.
RIOT software likewise needs to be optimized with respect to minimizing power
consumption, needs to be able to manage power and energy, and be possibly able
to support energy harvesting capabilities.

## Soft real-time capabilities

The low-frequency sensing applications targeted by RIOT do not typically have
precise timing and hard real-time requirements. RIOT therefore provides soft
real-time capabilities out-of-the-box. However, RIOT users may also wish to use
the operating system in control or high frequency data capture applications, and
in such a case, harder real-time guarantees and more accurate timing should be
achievable at the expense of power consumption and configuration difficulty.
[todo]: point out that timing needs to be accurate at low values for control
applications and also able to sleep for hours in the case of remote sensing
applications.
- If you use it correctly you can build hard real-time applications if you know
  what you're doing


## Internet security

Adequate security in all cases is non-negotiable. The success of the emerging
IoT industry is highly dependent on whether constrined nodes can be protected
against threats from sources that have far more computational resources than
them.

Note that "adequate security" use case dependent, and depends on the threats
that a device may reasonably experience as well as the penalty if those threats
are realised. RIOT however will cover potential shortcomings in programming or
configuration in all use cases and assure security nonetheless.
-OTA update addresses this

## Stability

RIOT's reputation is tied to the robustness of the products that build upon it.
The users should never be able to cut corners in such a way that the products
are not production ready, even given tight resource constraints. The use of
static memory unless absolutely necessary, and always in the kernel, facilitates
the stability of the system even given tight resource constraints.

[TODO: comms robustness - put both in this section]
Communication is typically constrained in situations where nodes are:

- Distant from each other or a gateway
- Low transmission power and separated by physical barriers such as walls.

This requires physical layer protocols that can cope with high loss and low
bandwidth.

Additionally, nodes are low resource and cannot support traditional TCP/IP stack
protocols. RIOT therefore supports emerging protocols that are the best
available to handle these challenging conditions, as well as as a validation
platform for them.

## Versatility

As indicated above, RIOT addresses a wide variety of use cases in the IoT. This
means that it is unbiased regarding the protocols and technologies supported.
8-bit to 32-bit MCUs, a wide range of boards, and a wide range of use cases are
supported. Features are implemented flexibly and, where possible, decomposably
and configurably, so that as wide a range of our addressed use cases and device
resource requirements are supported. If a protocol, sensor, actuator or
microcontroller is not yet supported, it can be implemented on top of, or
underneath, low-level APIs as easily as any other.

## Modularity

RIOT defines self-contained building blocks, to be combined in different
configurations. This caters both for versatile use cases and for memory
constraints. It also enables a highly distributed community to separate
development work while reducing the risk of knock-on effects across the system.
Related to this, it allows third parties to develop modules, expanding
development efforts from just the RIOT community and repo.

There is a balance to be struck, however: too fine-grained can come at a cost of
unnecessary complexity, higher resources, and difficulty of understanding.


## Cross-hardware portability

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

[TODO: Unified APIs - integrate this bit in this section]

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
