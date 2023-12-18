**University of Washington Bothell**
CSS 342: Data Structures, Algorithms, and Discrete Mathematics I
**Program 5: The Jolly Banker**

Purpose
This lab will serve a few purposes. First, it will provide hands-on experience using both queues
and binary search trees. It will also provide an opportunity for further program/class design as
the project does not specifically delineate class structure or design.
There are aspects of the spec below which allow interpretation—please read/design and ask
questions early to clarify any ambiguity.
A peer design review will be required to help with the latter aspect. This design review will
require a deliverable to canvas and will be part of the final grade for the lab.

**Problem Overview:**
You will build a banking application which processes transactions. This banking application consists of three phases.
1) The program will read in a string of transactions from a file into an in-memory queue. These transactions can open accounts, withdraw funds, deposit funds, transfer funds, or ask for the transactional history to be printed.
2) The program will next read from the queue and process the transactions in order.
3) When the queue has been depleted the program will print out all open accounts and balances in those accounts.
