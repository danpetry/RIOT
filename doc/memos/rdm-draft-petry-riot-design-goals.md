
 - RDM: 1
 - Title: RIOT design goals
 - Author: Daniel Petry  
 - Date: October 2018

## Abstract

This memo describes RIOT's high level design goals. The aim is to reflect
community consensus on these goals and thereby guide technical discussion around
specific contributions.

## Status

This document is a product of the community of RIOT maintainers, and aims to 
represent the consensus within this community. The content of this document is
licensed with a Creative Commons CC-BY-SA license.

## Introduction

The primary aim of this document is to guide lower level debate and discussion.
The problems that aim to be solved are that design priorities are currently:

- Expressed as a list of points in the README.md and RIOT vision, without
  expanding on any of them individually, which gives little understanding of
  each point
- The design priorities are expressed as equals in those documents, making it
  difficult to make design decisions around them where there are tradeoffs
- Not captured in a place which explicitly focuses on users, which means that
  they don't foster an intuition of user needs, and therefore of how to make
  design decisions which lead to RIOT being a widely used product.
- Otherwise communicated via word-of-mouth, which is inefficient and leads to
  corruption of information
- Percieved differently by different people.

In other words, this document aims to increase alignment and visibility of
information on RIOT's design goals, and to increase their focus on users.

This information is illustrated via several angles:

1. A short mission statement, suitable to gather a 30 second impression of the
   operating system on a technical level, which can also be re-used in public
   documents
2. A series of example use cases
3. A series of specific design philosophies.


# 1. Mission Statement

RIOT is an open-source operating system which makes it easy to deploy sensor and
actuator networks with challenging resource requirements that can operate for
years without physical intervention.

It is designed to abstract away the hardware details of remote and low-access
sensor and actuator nodes. An identical programming interface is presented
across heterogeneous nodes, supporting underlying hardware out-of-the-box, with
a short learning curve. Those nodes are often highly constrained in power and
memory and failures cannot be tolerated due to their isolation, and the
operating system is designed to handle these constraints with fault-free long
term operation. The protocols used to communicate with them are at the leading
edge of innovation in constrained and mesh networking, to ensure data is
reliably delivered between nodes and to servers.

# 2. Example Use Cases

In all use cases, RIOT provides a base for some further development. Direct
users of RIOT will therefore be organizations who have some programming skill
available, and want to optimize quality, cost and time-to-deployment.

Below are a list of potential use cases with a short description of technical
requirements for each.

## Environmental sensing

This requires a node to be able to wake up at a time of the order of hours and
deliver a data point. This node should be able to operate, without being
connected to power infrastructure, for timescales of the order of years. It
should not run out of power and the timings should not drift unacceptably.

## Easy fit, power supply-free smart home devices

This requires a node to last for a number of weeks without recharge, for example
to continue operating if a user is on holiday. It should be able to send fairly
continuous data over a widely supported wireless LAN protocol, in order to
support commercial home gateways.

## Communication daughterboards for low-power protocols

This requires RIOT to support popular emerging low-power protocols, and to
provide robust and stable support for commonly used microcontrollers and
transcievers.

## Shipment tracking

This requires a node to last for a number of weeks without recharge, monitor a
range of environmental conditions, and send data to a local gateway which will
be connected to the vehicle's power source and handle GPS localization.

## Wearables

This requires a node to be extremely light and low power, and to send data to a
public gateway over a very low bandwidth connection, for example LoRaWAN, or to
the user's smartphone, for example over Bluetooth. The device would require
charging perhaps every week.

## Diagnostic collection and/or control of traditionally non-powered devices

This requires a node to be able to be retrofitted to a non-powered device such
as a personal transportation device or item of public infrastructure, to be able
to harvest energy from that device or last for a number of weeks or months
without charging, to perform sensing of environmental or mechanical parameters,
and to send data to a user's phone or a public wide-area network.

## Building heating, ventilation, and air conditioning (HVAC)

This requires a node to be able to be retrofitted to an already existing
building, which may involve wireless communication but will likely involve a
provided power source to the node. It will involve sensing of environmental
conditions such as temperature, air quality and composition, and be able to
feed back data at a rate that allows control of those conditions.


# 3. List of design philosophies

Below are a list of our design philosophies, including, where appropriate,
an indication of relative priorities.

## Energy efficiency

RIOT nodes should be able to survive for years without running out of power.
This means that they need to be able to be extremely conservative with power,
and harvest any available energy from the environment.

## Real-time capabilities

For non-control and low-frequency sensing applications, precise knowledge of the
data capture time is not neccessary. Nevertheless, RIOT users may wish to use
the operating system in control or high frequency data capture applications, and
in such a case, harder real-time guarantees and more accurate timing should be
achievable at the expense of power consumption and configuration difficulty.

## Small memory footprint

RIOT aims to support constrained devices in class 1 [1]. This means that
RIOT applications, including their libraries, consume ~ 10 KiB of RAM and ~100
KiB of ROM, or less. All modules provided by RIOT can be used practically in
programs of such sizes, except in exceptional circumstances.

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
tools and platforms that support RIOT.

However, RIOT's reputation is tied to the robustness of those products, and the
users should never be able to cut corners in such a way that the products are
not production ready, even given tight resource constraints. 

Developers, likewise, should be able to start contributing in as short a time as
possible, and so the design and APIs should remain clear and generally follow
common and easy to understand principles, unless there are strong benefits that
directly achieve operational goals.

## Security

Security in all cases is non-negotiable and overrides any competing design
priorities. This is because of the high importance of protecting users' privacy,
and the corresponding risk to the emerging IoT industry. We are part of the
solution, not the problem.

Note that this use case dependent, and depends on the threats that a device may
reasonably experience as well as the penalty if those threats are realised. RIOT
however will cover potential shortcomings in programming or configuration in all
use cases and assure security nonetheless.

## Modularity

Logical separation of the different modules of RIOT enables a highly distributed
community to separate development work while reducing the risk of knock-on
effects across the system. It also allows third parties to develop modules,
expanding development efforts from just the RIOT community and repo. There is a
balance to be struck, however: too fine-grained can come at a cost of
unnecessary complexity, higher resources, and difficulty of understanding.

## Independence of the underlying hardware

Development should be able to be done once and run on any platform using RIOT.
To achieve this with reduced development effort in porting, the hardware is
abstracted and the APIs are uniform at as low a level as possible.

# Acknowledgements

Thanks to

# References

[1] [IETF RFC 7228: Terminolgy for Constrained-Node Networks](https://tools.ietf.org/html/rfc7228)

# Revisions

Rev0: initial commit to master
