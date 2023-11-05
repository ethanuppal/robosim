# robosim

This is a robot simulator I built in C to learn how Kalman filtering works :)

## Usage:

```bash
cmake . -DCMAKE_BUILD_TYPE=Release \
&& make robosim \
&& ./robosim
```
don't forget to `cd dependencies/minifb` and do the `git submodule` jazz :)
