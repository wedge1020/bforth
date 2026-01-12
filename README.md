# bforth

BASH-based FORTH exploration

## TABLE OF CONTENTS

  * [OVERVIEW](#OVERVIEW)
  * [FEYNMAN TECHNIQUE](#FEYNMAN-TECHNIQUE)
  * [USAGE](#USAGE)

## OVERVIEW

Recent investigations have found me  meandering in `compiler` space, then
stumbling upon `FORTH`, which I became interested in pursuing further.

As is my tendency, my go-to languages are:

  * `C`
  * `BASH`
  * assembly (these days, for the `Vircon32` fantasy console)

Although not necessarily in that order. 

The  sheer notion  of attempting  to implement  a `FORTH`  environment in
`BASH` seems absurd. And in that, is the allure.

I'm not looking to  change the world, nor have the world  jump on this to
usher in some next great revolution.  No, I'm using an environment I have
extensive experience with to explore  and better understand something I'm
not yet fully familiar with.

At the  moment, for the  purposes of this  repository, that is  a `FORTH`
environment in `BASH`. It should offer  up some unique insights on how to
wrangle `BASH` to handle some of the exceptionally low-level details that
`FORTH` transacts in.

Call it my *Feynman*-esque learning journey.

## FEYNMAN TECHNIQUE

A  quick google  query describes  a `Feynman  Technique` as  "a four-step
method for  deep learning,  named after  physicist Richard  Feynman, that
involves **choosing a  concept**, **teaching it simply  to someone else**
(like a child), **identifying knowledge  gaps**, and then **reviewing and
refining  your  understanding  until  you  can  explain  it  clearly  and
concisely, proving true comprehension  over rote memorization**. It works
by forcing you to simplify complex ideas, reveal what you don't know, and
actively engage with the material."

That's all.

### choosing a concept

Take   your    pick:   compilers/interpreter    implementation,   `FORTH`
specifically.  At  present,  both  are  concepts I  am  dabbling  in  and
exploring.

My  love of  low-level  things like  assembly also  seem  to dovetail  in
nicely.

### teaching it simply

Another  excursion of  mine  I  enjoy is  documenting.  I  find it  quite
enjoyable. So a part  of the teaching angle will be to  explain it, be it
in comments in the code, or a markdown tutorial or journal.

### identifying knowledge gaps

Currently, there are aspects of compilers  and `FORTH` that I am not sure
how  I could  pull  off  in my  desired  target  environment. Hence  this
exploration. By implementing both the  details I understand, working with
and towards  those I  do not  know, I  can hopefully  bridge that  gap to
knowing.

### reviewing and refining

This will  likely take the  form of  revising my documentation,  but also
overhauling  aspects of  the  code  as I  increase  my understanding  and
discover potential optimizations.

There's  also  the potential  future  implementation  of another  `FORTH`
environment, or  other compiler,  based on  my experiences  and knowledge
gained here.

## USAGE

Currently,  I  am  targeting a  `BASH`-implemented  `FORTH`  interpreter.
Likely a  subset of  `FORTH`, not going  out of my  way to  ensure strong
standards compliance.  I've been dabbling with  the `jonesFORTH` tutorial
and code, so I wouldn't be surprised  if the overall syntax veers more in
alignment to that.

I've        also         been        reading         the        [Starting
Forth](https://www.forth.com/starting-forth/)           book           at
[FORTH.com](https://www.forth.com/),  so  I'm  sure  that  resource  will
influence design decisions as well.

As an *interpreter*,  the current aim will  just be to run  it and you'll
get your  `ok` prompt and  can `FORTH` away. Pre-programmed  `FORTH` code
can likely be loaded via `STDIN` redirection on the command-line.

If use needs change, functionality will change.
