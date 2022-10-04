# Tool for Automated Execution of Batches of Biological Sequences, With Adequate Parameters, Using MASA-CUDAlign

## How to use

In order to compile the tool, a Makefile is provided. Just execute the `make` command in the root of this project.

An executable called `manager` will be generated. Execute it to launch the tool.
An interface will be presented with 4 main options:

### Alignments

This is where a batch of alignments can be executed. Instructions to configure the batch of alignments are presented by the tool.

After running a batch of alignments, the results of each alignment will be in a directory with the date, time and sequence ids in the name, inside of the results directory.


### Profiling

This is where the adequate parameters are obtained. It is recommended to run this before running alignments. The benefits of running a profile are presented by the tool.

### Verbose Mode

Setting to choose how much information the MASA-CUDAlign tool should print to the terminal.

### Quit

Closes the tool.

