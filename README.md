
# Table of Contents

1.  [Torsten](#org70470a3)
2.  [Licensing](#org6f3925d)
3.  [Install](#orgdc95df0)
    1.  [Command line version](#org31ea4c5)
    2.  [R version](#org4fb1038)
4.  [Examples](#orga037fdf)
5.  [C++ Code](#orgbaa4855)



<a id="org70470a3"></a>

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


<a id="org6f3925d"></a>

# Licensing

The Torsten library is open-source and licensed under the BSD 3-clause license.


<a id="orgdc95df0"></a>

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


<a id="org31ea4c5"></a>

## Command line version

There is no need to install command line version. To
build a Stan model with `model_name` in `model_path`
using command line, in `torsten_path/cmdstan`, do

    make model_path/model_name


<a id="org4fb1038"></a>

## R version

The R version is based on [rstan](https://cran.r-project.org/web/packages/rstan/index.html), the Stan's interface for
R. To install R version of Torsten, at `torsten_path`, in R

    source('install.R')


<a id="orga037fdf"></a>

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


<a id="orgbaa4855"></a>

# C++ Code

The C++ code for Torsten can be found on the following repos:

-   Math Library: <https://github.com/metrumresearchgroup/math>
-   Stan Grammar: <https://github.com/metrumresearchgroup/stan>

