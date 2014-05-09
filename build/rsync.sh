#!/bin/bash
echo "Don't run this on j53sun@linux"
rsync -rtvuz --exclude .git/ ./ j53sun@linux.student.cs.uwaterloo.ca:~/cs452/

# r recursive
# t preserve modification times
# v verbose
# u update so don't copy unmodified files again
# z compression
