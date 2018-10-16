
 - rdm-draft-petry-riot-design-goals.md
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

This memo describes the high level design goals of RIOT. The aim is to reflect
community consensus on these goals and thereby guide technical discussion around
specific contributions.

## Status

The content of this document is licensed with a Creative Commons CC-BY-SA
license.

## Introduction

The primary aim of this document is to help developers make design decisions
that are consistent with each other, and that serve the needs of the user.

In more detail, the sub-aims are:

- To provide more detail on the design goals, to inform developers and help them
  make design decisions that are aligned with one another
- To provide information on relative importance of the design goals, to inform
  debate where there are competing design tradeoffs
- To increase developer focus on users, so they intuitively develop a system
  that is useful to end users and therefore adopted widely
- To communicate this information efficiently, clearly and unambiguously, so
  that the goals are the same for everyone.

To achieve these aims, the design requirements are illustrated here in three
different ways:

1. A short mission statement, suitable to gather a 30 second impression of the
   operating system on a technical level. This can also be re-used in public
   documents, for example the README.md
2. A series of example use cases
3. A series of specific design philosophies.


# 1. Mission Statement

RIOT is an open-source operating system which makes it easy to deploy sensor and
actuator networks with challenging resource requirements that can operate for
years without physical intervention and communicate via common Internet
standards.

It is designed to abstract away the hardware details of remote and low-access
sensor and actuator nodes, and allow software to be portable across platforms
without being locked in to any hardware vendor. An identical programming
interface is presented across heterogeneous nodes, supporting underlying
hardware out-of-the-box, with a short learning curve. Those nodes are often
highly constrained in power and memory and failures cannot be tolerated due to
their isolation. The operating system is designed to handle these constraints
with fault-free long term operation. We adopt emerging protocols in constrained
and mesh networking when they are of sufficiently high quality and validity. The
use cases for IoT systems are manifold and so are their requirements, and so we
do not preferentially support one technology or one protocol over another.

# 2. Example Use Cases

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

# 3. List of design philosophies

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
present to support use cases with higher resource demands.

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

RIOT decomposes into small modules. Logical separation of different modules
allows the OS to be tailored to user-specific needs. It also enables a highly
distributed community to separate development work while reducing the risk of
knock-on effects across the system. Related to this, it allows third parties to
develop modules, expanding development efforts from just the RIOT community and
repo.

There is a balance to be struck, however: too fine-grained can come at a cost of
unnecessary complexity, higher resources, and difficulty of understanding.

## Hardware abstraction and cross-hardware portability

Development should be able to be done once and run on any platform using RIOT.
To achieve this with reduced development effort in porting, the hardware is
abstracted and the APIs are uniform at as low a level as possible.

## Robustness and resilience

RIOT's reputation is tied to the robustness of the products that build upon it.
The users should never be able to cut corners in such a way that the products
are not production ready, even given tight resource constraints. 

## Versatility

As indicated above, RIOT addresses a wide variety of use cases in the IoT. This
means that it is unbiased regarding the protocols and technologies supported. If
a protocol, sensor, actuator or microcontroller is not yet supported, it can be
implementedon top of, or underneath, low-level APIs as easily as any other.

## Unified APIs

In order to achieve clean hardware abstraction and modularity, the APIs across
the system are as homogeneous as possible. This means that common functionality
is presented in exactly the same way, while more specific functionality is
presented in a way that does not break code implemented on top of the APIs of
other modules.

# Acknowledgements

Thanks to

# References

[1] [IETF RFC 7228: Terminolgy for Constrained-Node Networks](https://tools.ietf.org/html/rfc7228)
[2] [RIOT OS: Towards an OS for the Internet of Things](https://www.riot-os.org/docs/riot-infocom2013-abstract.pdf)
[3] [RIOT: an Open Source Operating System for Low-end Embedded Devices in the IoT](http://ilab-pub.imp.fu-berlin.de/papers/bghkl-rosos-18-prepub.pdf)

# Revisions

Rev0: initial commit to master
