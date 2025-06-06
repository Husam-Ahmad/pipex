I did Pipex as a way to learn and practice low-level Unix programming, specifically focusing on how piping and forking work under the hood.
This project helped me understand the intricacies of process control, file descriptor manipulation, and the inner workings of the shell pipeline.

**How to Build**
Clone the repository and build using the Makefile.

**Example**
`````
./pipex infile "grep hello" "wc -l" outfile
`````
This is equivalent to:

`````
< infile grep hello | wc -l > outfile
`````
