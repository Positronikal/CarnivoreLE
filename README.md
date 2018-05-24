CarnivoreLE

See the file VERSION in this directory for version information.

CarnivoreLE is a very fast forensic data gatherer to be used against
live GNU/Linux (LIN), Macintosh (MAC), and Windows (WIN)
suspect computers to capture memory, user files, registry, logs, and
other volatile data that can be lost or rendered inaccessible once the
computer shuts down.

About this repository:

  There are some caveats about this project to be aware of:

  1. This project uses a dedicated IDE, specifically Code::Blocks, and
     not everyone will like that. This decision was made for the
     following reasons:
      * Code::Blocks is available for all the platforms CarnivoreLE
        targets.
      * Code::Blocks handles the C language well.
      * Code::Blocks helps make this project accessible to
        inexperienced coders and everyone needs to start somewhere.
      * Taking this approach reduces the potential number of various
        bugs and errors coders and builders should experience and
        provides common ground for everyone to address them.
  2. This project doesn't use typical make files, i.e. GNU make, cmake,
     etc. All makefile properties are included in the .cbp file.
     Including both a .cbp and a make file is non-trivial. Forcing
     Code::Blocks to use a makefile instead of a .cbp file has
     ramifications for this and future Code::Blocks usage on your
     platform unless you have a separate Code::Blocks installation
     specifically set up for make. This has the ramification that
     building outside of Code::Blocks and the .cbp isn't possible
     without a lot of work.
  3. This project doesn't use conditional compilation. Several
     organizational methods were attempted to get CarnivoreLE to build
     for the three target systems, i.e. GNU/Linux, MacOS/OS X, and
     Windows: conditional compilation, each target in it's own set of
     branches, etc. Each approach was abandoned and the project was
     reconfigured each time finally arriving in it's current form of
     three separate target repos inside the main repo allowing each
     target to have it's own .cbp, dependent files, compiler
     directives, etc. Each resulting source file is cleaner and
     building results in fewer bugs that may only appear for one target
     system, but may be difficult to isolate.
  4. Commits happen only in the main repo which affects all target
     repos. Pull requests come from the devlop branch only or temporary
     special branches that may be created from time to time to address
     specific concerns or bugs. The reorganizations that have happened
     (see #3) have resulted in the commit history being a little wonky.
     Admittedly it's not ideal, however it was much less painful to do
     it this way, all things considered. It's not expected to cause any
     significant amount of grief in the long run.

Tab Details:

  Code tab = All commits, branches, releases, and contributors.
  Issues tab = Bug reports, feature requests, etc.
  Pull requests tab = Requests from contributors to add their code.
  Projects tab = Tools to manage this project.
  Wiki = This project's wiki.
  Insights tab = Data visualizations and metric results.

You may encounter bugs in this software, especially if this is a
maintenance release. Please see BUGS in this directory. If you do
encounter what you believe is a bug, please report it by filing an
issue. Your bug reports in the form of issues are valuable
contributions to Positronikal since they allow us to notice and fix
problems on machines we don't have or in code we don't use often. See
the file BUGS in this directory for more information on how to report
bugs.

The software was built using Code::Blocks
(http://www.codeblocks.org/). Release binaries of platform-specific
implementations were compiled/linked using the following compilers:
  * GNU GCC (https://gcc.gnu.org/) for GNU/Linux
  * MinGW (http://www.mingw.org/) for Windows
  * Clang (https://clang.llvm.org/) for Macintosh

Note that the LIN and WIN alphas were developed on a GNU/Linux
workstation (currently Linux Mint 18.3) and the MAC alpha happened on
a Macintosh (currently MacOS 10.13.4). WIN development can probably
proceed fine on a Windows workstation, but MAC development should
most likely remain on a OS X/MacOS workstation.

All project files necessary to edit, add to, or build the same or
custom binaries using these tools are included in the repository
specific to the implementation. The file USING in this directory
contains information for both developers and practitioners.
carnivore.cbp is the main project file and is unique to each target
repo. See the docs/ directory in the main repo.

Licensing information is contained in the file COPYING in this
directory.

Hoyt Harness/Positronikal
hoyt.harness@gmail.com

Rev: 20180524

