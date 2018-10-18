
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

This memo describes the high level design goals of RIOT. The aim of this
document is to help developers make design decisions that are consistent with
each other, and that address the unique benefits that RIOT brings to users.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

The design goals are illustrated here via a series of example use cases,
including their requirements, from which follow a list of specific design
philosophies.

# Example Use Cases

Below are a list of potential use cases with a short description of technical
requirements for each.

Our immediate users are developers, who then create products for these use
cases. Therefore, our design requirements do not stem directly from the
requirements of these use cases. They derive from the need for developers to
develop products for these use cases as quickly, cheaply, and of high a quality
as possible.

## Environmental sensing

This requires a node to be able to wake up at a time of the order of hours and
deliver a measurement. This node should be able to operate, without being
connected to power infrastructure, for timescales of the order of years. It
should not run out of power and the timings should not drift unacceptably.

## Easy fit, power supply-free smart home devices

This requires a node to last for a number of weeks without recharge, for example
to continue operating if a user is on holiday. It should be able to send fairly
continuous data over a widely supported wireless LAN protocol, in order to
work together with a commercial home gateways.

## Communication daughterboards for low-power protocols

This requires RIOT to support popular emerging low-power protocols, and to
provide robust and stable support for commonly used microcontrollers and
transceivers.

## Logistic tracking

This requires a node to last for a number of weeks without recharge, monitor a
range of environmental conditions, and send data to a local gateway which will
be connected to the vehicle's power source and handle GPS localization.

## Wearables

This requires a node to be extremely light and low power, and to send data to a
public gateway over a very low bandwidth connection, for example LoRaWAN, or to
the user's smartphone, for example over Bluetooth. The device would require
charging perhaps every week.

## Diagnostic collection from transport and infrastructure

This requires a node to be able to be retrofitted or fitted at manufacture to a
device which may not have its own source of power. This requires the node to be
able to harvest energy from that device or last for a number of weeks or months
without charging, to perform sensing of environmental or mechanical parameters,
and to send data to a user's phone or a public wide-area network.

## Edge systems for building management and automation

This requires a node to be able to be retrofitted to an already existing
building, which may involve wireless communication but will likely involve a
provided power source to the node, for example in the case of powered
thermostats or heating meters. It will involve sensing of environmental
conditions such as temperature, air quality and composition, and be able to
feed back data at a rate that allows control of those conditions.

## Cross-hardware system integration

This involves integrated, distributed sensor and actuator systems running RIOT
on different hardware platforms. This requires software to be agnostic to the
underlying hardware and support common protocols.

## Rapid prototyping, research and experimentation

This involves RIOT acting as a platform to quickly develop demonstrators,
experimental setups, and research environments. This requires developers with
basic programming knowledge to be able to define their application logic.

# List of design philosophies

Below are a list of our design philosophies, including, where appropriate,
an indication of relative priorities.

## Energy efficiency

RIOT nodes should be able to survive for years without running out of power.
RIOT software likewise needs to be optimized with respect to minimizing power
consumption, needs to be able to manage power and energy, and be possibly able
to support energy harvesting capabilities.

## Real-time capabilities

The low-frequency sensing applications targeted by RIOT do not typically have
precise timing and hard real-time requirements. RIOT therefore provides soft
real-time capabilities out-of-the-box. However, RIOT users may also wish to use
the operating system in control or high frequency data capture applications, and
in such a case, harder real-time guarantees and more accurate timing should be
achievable at the expense of power consumption and configuration difficulty.

## Small memory footprint

RIOT aims to support constrained devices in class 1 [1]. This means that
usable RIOT applications in certain key use cases (remote sensing, for example)
consume ~ 10 KiB of RAM and ~100 KiB of ROM, or less. Larger modules are also
present to support use cases with higher resource demands. The extensive use of
the C language helps cater for low resource requirements. The use of static
memory unless absolutely necessary, and always in the kernel, facilitates the
management of available RAM.

## Constrained networks

Communication is typically constrained in situations where nodes are:

- Distant from each other or a gateway
- Low transmission power and separated by physical barriers such as walls.

This requires physical layer protocols that can cope with high loss and low
bandwidth.

Additionally, nodes are low resource and cannot support traditional TCP/IP stack
protocols. RIOT therefore supports emerging protocols that are the best
available to handle these challenging conditions, as well as as a validation
platform for them.

## Short learning curve

Users of RIOT want to be able to develop and deploy their products in as short a
time as possible, with as little extra learning and specialized knowledge as
possible. This means support for standards such as POSIX and a range of
widely-used languages, out-of-the-box examples, simple build configuration, and
tools and platforms that support RIOT. Ease of use is, however, subject to the
robustness and resilience requirements below.

Developers, likewise, should be able to start contributing in as short a time as
possible, and so the design and APIs should remain clear and generally follow
common and easy to understand principles, unless there are strong benefits that
directly achieve operational goals.

## Security

Adequate security in all cases is non-negotiable. The success of the emerging
IoT industry is highly dependent on whether constrined nodes can be protected
against threats from sources that have far more computational resources than
them.

Note that "adequate security" use case dependent, and depends on the threats
that a device may reasonably experience as well as the penalty if those threats
are realised. RIOT however will cover potential shortcomings in programming or
configuration in all use cases and assure security nonetheless.

## Modularity

RIOT defines self-contained building blocks, to be combined in different
configurations. This caters both for versatile use cases and for memory
constraints. It also enables a highly distributed community to separate
development work while reducing the risk of knock-on effects across the system.
Related to this, it allows third parties to develop modules, expanding
development efforts from just the RIOT community and repo.

There is a balance to be struck, however: too fine-grained can come at a cost of
unnecessary complexity, higher resources, and difficulty of understanding.

## Hardware abstraction and cross-hardware portability

Development should be able to be done once and run on any platform using RIOT.
Most of the code is portable across supported hardware. To achieve this with
reduced development effort in porting, the hardware is abstracted and the APIs
are uniform at as low a level as possible. The code duplication is minimized
across configurations.

## Robustness and resilience

RIOT's reputation is tied to the robustness of the products that build upon it.
The users should never be able to cut corners in such a way that the products
are not production ready, even given tight resource constraints. 

## Versatility

As indicated above, RIOT addresses a wide variety of use cases in the IoT. This
means that it is unbiased regarding the protocols and technologies supported.
8-bit to 32-bit MCUs, a wide range of boards, and a wide range of use cases are
supported. Features are implemented flexibly and, where possible, decomposably
and configurably, so that as wide a range of our addressed use cases and device
resource requirements are supported. If a protocol, sensor, actuator or
microcontroller is not yet supported, it can be implemented on top of, or
underneath, low-level APIs as easily as any other.

## Unified APIs

In order to achieve clean hardware abstraction and modularity, the APIs across
the system are as homogeneous as possible across all supported hardware, even
for hardware-accessing APIs. This caters for code portability and minimizes
code duplication. In the APIs, common functionality
is presented in exactly the same way, while more specific functionality is
presented in a way that does not break code implemented on top of the APIs of
other modules.

## Vendor and technology independence

To achieve interoperability between heterogeneous nodes, and to protect freedom
0 of the four essential freedoms [4], RIOT is agnostic of the vendor and
technologies of the hardware. Vendor libraries are typically avoided, to
preclude lock-in and minimize code duplication. No vendor, protocol,
microcontroller, transceiver, sensor, actuator, or any other technical component
is tied into through design decisions. None is preferred over any other for any
reason other than the reasons detailed in the other design philosophies.

## Use of networking and systems standards

In order to ensure the interoperability of devices running RIOT with ones that
do not, open network protocol standards, e.g. IETF protocols, are customarily
used. To take full advantage of the largest pool of third party software,
systems standards, e.g. the ANSI C standard (C99), are customarily used. We may
provide non-core modules which break from this (alongside modules which do not)
if there are compelling reasons that serve other design philosophies. Where
standards are phrased in such a way that particular aspects are open to be
implemented in different ways, or not implemented at all, these aspects will be
considered with reference to other design philosophies and to user needs.

# Acknowledgements

Thanks to

# References

[1] [IETF RFC 7228: Terminolgy for Constrained-Node Networks](https://tools.ietf.org/html/rfc7228)
[2] [RIOT OS: Towards an OS for the Internet of Things](https://www.riot-os.org/docs/riot-infocom2013-abstract.pdf)
[3] [RIOT: an Open Source Operating System for Low-end Embedded Devices in the IoT](http://ilab-pub.imp.fu-berlin.de/papers/bghkl-rosos-18-prepub.pdf)
[4] [Gnu.org: What is free software?](https://www.gnu.org/philosophy/free-sw.en.html)

# Revisions

Rev0: initial commit to master
