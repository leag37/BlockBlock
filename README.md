BlockBlock
==========

Networked 3D Air Hockey Game

# Prerequisites
1. CMake
2. Clang (optional)

# Setup

1. Checkout repository
2. Open ~/.bash_profile
3. Add the following functions:
  1. Build debug:

```
#!bash

function make_debug()
{
  target_path=<path_to_checkout (eg. ~/Dev/BlockBlock)>
  original_path=$(pwd)
  cd $target_path
  cmake -DCMAKE_BUILD_TYPE=Debug .
  make
  cd $original_path
}
```
  2. Build release
```
#!bash
function make_release()
{
  target_path=<path_to_checkout (eg. ~/Dev/BlockBlock)>
  original_path=$(pwd)
  cd $target_path
  cmake -DCMAKE_BUILD_TYPE=Release .
  make
  cd $original_path
}
```
4. source ~/.bash_profile
5. You may now run these functions from any directory. You can run these steps manually, they are just helpers to setup and properly pass in target flags
6. (Optional) Setup make to run multiple jobs (this should be # of machine cores + 1)
  1. Add the following statement to your .bash_profile
```
#!bash
export MAKEFLAGS=-j<n> # Have make run on n cores for this machine (one spawner task and two workers)
```