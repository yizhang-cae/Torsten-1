
# Table of Contents

1.  [Torsten](#orge82e5d9)
2.  [Licensing](#orgb67ecfd)
3.  [Install](#org9c1b66c)
    1.  [Command line version](#org23e2df1)
    2.  [R version](#orge6c0fc9)
4.  [Examples](#orgb1f8c3d)
5.  [C++ Code](#org573288b)



<a id="orge82e5d9"></a>

# Torsten

Torsten is a library of C++ functions that support
applications of Stan in Pharmacometrics. The current
version provides:

-   Analytical solution for the one and two linear compartment model with a first-order absorption.
-   Matrix exponential solution for a general linear compartment model.
-   Numerical solution for general compartment model using built-in integrators:
    -   Runge-Kutta 4th/5th (rk45) order for non-stiff ODE systems.
    -   Backward Differentiation (bdf) for stiff ODE systems.
-   Mixed solver for general compartment model with a forcing PK function:
    -   Computes analytical solutions for forcing PK One and Two compartment model with a first-order absorption.
    -   Computes numerical solution for the forced compartment model using the rk45 or bdf method.

The Torsten prototype is still under development and has been
uploaded to facilitate working with the community of Stan
developers. The current version was written by 

-   [Charles Margossian](https://github.com/charlesm93)
-   [Yi Zhang](https://github.com/yizhang-cae),
-   [Bill Gillespie](https://github.com/billgillespie)

and [Metrum Research Group, LLC](https://metrumrg.com/). We have recieved extensive help from the [Stan development team](http://mc-stan.org/about/team/).

See [the user manual](example-models/torstenManual.pdf) for more information and guidance on the
examples. If you have any questions, please raise an issue
on GitHub or [send us an e-mail](mailto:billg@metrumrg.com).

This is the container for the following components of
Torsten project

-   [TorstenHeaders](https://github.com/metrumresearchgroup/TorstenHeaders)
-   [Math](https://github.com/metrumresearchgroup/math)
-   [Stan](https://github.com/metrumresearchgroup/stan)
-   [example-models](https://github.com/metrumresearchgroup/example-models)


<a id="orgb67ecfd"></a>

# Licensing

The Torsten library is open-source and licensed under the BSD 3-clause license.


<a id="org9c1b66c"></a>

# Install

We are working with Stan development team to create a
system to add and share Stan packages. In the mean time,
the current repo contains forked version of Stan with
Torsten. The latest version of Torsten (v0.84) is
compatible with Stan v2.17.1. Torsten is agnostic to which
Stan interface you use. Here we provide command line and R
interfaces.

First, download the project, the root path of the project is
your `torsten_path`.


<a id="org23e2df1"></a>

## Command line version

There is no need to install command line version. To
build a Stan model with `model_name` in `model_path`
using command line, in `torsten_path/cmdstan`, do

    make model_path/model_name


<a id="orge6c0fc9"></a>

## R version

The R version is based on [rstan](https://cran.r-project.org/web/packages/rstan/index.html), the Stan's interface for
R. To install R version of Torsten, at `torsten_path`, in R

    source('install.R')

Please ensure the R toolchain includes a C++ compiler with
C++11 support. In particular, R 3.3.0 and later is
recommended as it contains toolchain based on gcc 4.9.3. On
Windows platform, such a toolchain can be found in Rtools33 and later.

Please ensure CXXFLAGS in .R/Makevars constains flag
-std=c++11. 

For more information of installation troubleshooting,
please consult [rstan wiki](https://github.com/stan-dev/rstan/wiki).


<a id="orgb1f8c3d"></a>

# Examples

For each model, we provide the following files:

-   `modelName.stan`
-   `modelName.data.R`
-   `modelName.init.R`
-   `modelNameSimulation.R`

The simulation file can be used to create the data and
initial estimate files.

There are three Stan files for the two compartment model:
`TwoCptModel`, `LinTwoCptModel`, and `GenTwoCptModel`. We also
provide more sophisticated PK/PD
examples. `TwoCptModelPopulation` extends the two compartment
model to the case where we have data from multiple patients
with inter-individual variability.

See the manual for more assistance.

Under the R directory, we provide scripts to run the Stan
models.


<a id="org573288b"></a>

# C++ Code

The C++ code for Torsten can be found on the following repos:

-   Math Library: <https://github.com/metrumresearchgroup/math>
-   Stan Grammar: <https://github.com/metrumresearchgroup/stan>

