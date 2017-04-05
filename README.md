# Randomness Testing Toolkit
Randomness testing toolkit (RTT) is a tool that unites execution of various statistical batteries. Its aim is to detect non-randomness in given binary data in simple and automated manner. RTT also post-processes outputs of batteries so one does not need to cope vith various output formats these batteries use. Advanced users can even implement their own output module with minimal complications.

RTT currently implements support for following statistical tools:
* **NIST Statistical Test Suite** [home page](http://csrc.nist.gov/groups/ST/toolkit/rng/documentation_software.html)
* **Dieharder: A Random Number Test Suite** [home page](http://www.phy.duke.edu/~rgb/General/dieharder.php)
* **TestU01** [home page](http://simul.iro.umontreal.ca/testu01/tu01.html)

## Installation and usage
For instructions on how to install and use Randomness Testing Toolkit, please refer to our [wiki](https://github.com/crocs-muni/randomness-testing-toolkit/wiki).

## Authors
The framework is developed at the [Centre for Research on Cryptography and Security (formerly Laboratory of Security and Applied Cryptography)](https://www.fi.muni.cz/research/crocs/), [Masaryk University](http://www.muni.cz/), Brno, Czech Republic.

* **Petr Švenda** 2015-now (Project lead)
* **Ľubomír Obrátil** 2015-now (Development)

## License
Randomness Testing Toolkit is licenced under MIT Licence, Copyright (c) 2015 Centre for Research on Cryptography and Security. For details on MIT Licence, see file LICENSE.

## Third party libraries
Some sub-parts of the project have their own licencing conditions. The brief list of such sub-parts follows.

* **Easylogging++**  [Home page](https://github.com/muflihun/easyloggingpp)  
Simple header C++ logging library. Released under MIT license.

* **JSON for modern C++** [Home page](https://github.com/nlohmann/json)  
JSON parser for C++. Released under MIT license.

