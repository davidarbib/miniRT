<div align="center">
    <h1>
        <img src="https://imgur.com/LIkErH7.png" width="128"/> Minilibx
    </h1>
    <h4>A normed minilibx</h4>
    <p>
        <a href="https://gitlab.com/raggesilver-42/minilibx/pipelines">
            <img src="https://gitlab.com/raggesilver-42/minilibx/badges/master/pipeline.svg" alt="Build Status" />
        </a>
        <a href="https://www.patreon.com/raggesilver">
            <img src="https://img.shields.io/badge/patreon-donate-orange.svg?logo=patreon" alt="Patreon" />
        </a>
    </p>
    <p>
        <a href="#install">Install</a> •
        <a href="#features">Features</a> •
        <a href="https://gitlab.com/raggesilver-42/minilibx/blob/master/LICENSE">License</a> •
        <a href="#credits">Credits</a>
    </p>
</div>

This is a modified version of the original minilibX which aims to follow the
norm as much as possible. It also fixes a few leaks in the original code.
This project is not a simple indentation fix like many others, I'm actually
re-writing the code following the norm. I intend to modify the behavior of
the library in some aspects in the future, until then all function calls
will be compatible with the original code and should also have the same
behavior (without leaks).

**Important disclaimer**: Both OSX and Linux sources have been modified,
most of the code is still untested so it may differ from the original minilibx.
Use at your own risk.

> The original README is [this](_README_).

## Current state

<a href="https://gitlab.com/raggesilver-42/minilibx/pipelines">
    <img src="https://img.shields.io/badge/dynamic/json?color=orange&label=linux%20warnings&query=warnings&url=https%3A%2F%2Fgitlab.com%2Fraggesilver-42%2Fminilibx%2F-%2Fjobs%2Fartifacts%2Fmaster%2Fraw%2Fbadge.json%3Fjob%3Dleak%2520check" alt="Linux warnings" />
</a>
<a href="https://gitlab.com/raggesilver-42/minilibx/pipelines">
    <img src="https://img.shields.io/badge/dynamic/json?color=red&label=linux%20errors&query=errors&url=https%3A%2F%2Fgitlab.com%2Fraggesilver-42%2Fminilibx%2F-%2Fjobs%2Fartifacts%2Fmaster%2Fraw%2Fbadge.json%3Fjob%3Dleak%2520check" alt="Linux errors" />
</a>
<a href="https://gitlab.com/raggesilver-42/minilibx/pipelines">
    <img src="https://img.shields.io/badge/osx-untested-inactive" alt="OSX state" />
</a>

This project has a CI/CD setup which compiles the Linux source. I don't know
any way to test the OSX source via CI/CD, so that part has no automated testing
(I do, however, test most of the OSX code I push).

> The flag `-Werror` will be disabled for OSX until I can fix all warnings,
> that means that warnings will pass for now (norminette ain't happy about that,
> neither am I).

## Install

My minilibx doesn't have install scripts yet. You can use it by compiling and
linking your project to the static library `libmlx.a`.

```bash
make -j # -j enables parallel building (much faster)
```

Building will produce:

```
.
├── build/    # Conatins object files and make rules for every object
├── includes/ # Contains all public headers
└── libmlx.a  # The static library
```

## Features
My minilibx currently has no additional functions, only a few tweaks to the
original code that make it safer (less leaks).

## Requirements

For the Linux build a few packages are required (all 42 Macs should have the
necessary OSX libraries installed by default):

```
Fedora:
- libXpm-devel
- libX11-devel
- libXext-devel
```

> If you use another distro and would like me to add the package list here just
> open an issue and I'll look into it.

## Credits
```
Copyright 1999 - 2015 Olivier Crouzet
Copyright 2020 Paulo Queiroz
```
