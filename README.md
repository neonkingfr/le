# Le - Machine Learning Framework.

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![Platforms](https://img.shields.io/badge/platform-macos%20%7C%20linux-lightgrey.svg)
![Interfaces](https://img.shields.io/badge/interface-c%20%7C%20c%2B%2B%20%7C%20rust%20%7C%20python-blue.svg)

Le is Machine Learning framework written in Pure C. It provides library for:
* Tensor Manipulation.
* Linear Algebra.

At this moment following ML models are implemented:
* Polynomial Regression.
* Support Vector Machines (SVM).
* 1-Layer Neural Network.
* Sequential Feed-forward Neural Network (Multiple Layer Perceptron, MLP).

Optimization algorithms supported:
* Batch Gradient Descent (BGD).
* Sequential Minimal Optimization (SMO).
* Stochastic Gradient Descent (SGD) with momentum.

## Installation

### From Source

[Meson Build system](https://mesonbuild.com) is used to automate building and installation. To create build directory, type:

    meson {source_directory_name} {build_directory_name}

You can put your build directory inside of source directory:

    cd {source_directory_name}
    meson {build_directory_name}

Then use [`ninja`](https://ninja-build.org) command from your build directory to compile binaries:

    cd {build_directory_name}
    ninja

To install compiled binaries locally, type:

    sudo ninja install
    
## Tools

Le Framework comes with some usefull [tools](/tools).

## License

Copyright &copy; 2017 Kyrylo Polezhaiev and contributors. All rights reserved.

Le is released under the [MIT](LICENSE) License.
