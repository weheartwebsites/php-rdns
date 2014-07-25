# *php-rdns* [![Build Status](https://travis-ci.org/weheartwebsites/php-rdns.svg?branch=master)](https://travis-ci.org/weheartwebsites/php-rdns) [![License](http://img.shields.io/badge/license-Apache--2.0-lightgrey.svg)](http://www.apache.org/licenses/LICENSE-2.0.html)

*php-rdns* is a PHP extension for asynchronous DNS lookups written in C. It provides a Object-oriented PHP binding for [librdns](https://github.com/vstakhov/librdns) and uses [libev](http://software.schmorp.de/pkg/libev.html) as event loop.

The usage was modelled after [dns_get_record](http://php.net/manual/en/function.dns-get-record.php).


## Requirements

 - unix / linux
 - libev


## Installation

```
$ sudo apt-get install libev-dev
$ git clone https://github.com/weheartwebsites/php-rdns.git
$ cd php-rdns/
$ git submodule init
$ git submodule update
$ phpize
$ ./configure --with-rdns
$ make
$ make test
$ sudo make install
$ echo "extension=rdns.so" >> /etc/php.ini
``` 


## Usage

```php
<?php

$rdns = new RDNS;
$rdns->addServer('8.8.8.8');

// non blocking
$rdns->addRequest('www.example.com', RDNS_A);
$rdns->addRequest('example.com', RDNS_A);

// blocking
$replies = $rdns->getReplies();

var_dump($replies);
``` 


## Methods


### RDNS::RDNS_*


### RDNS::addServer


### RDNS::addRequest


### RDNS::getReplies


## Trivia

The "r" in *php-rdns* stands for "rapid" which was taken from the name of librdns. The initial version was developed by [Alexander Solovets](https://github.com/mbait) and sponsored by
[weheartwebsites](http://www.weheartwebsites.de), which is a tiny web developement company based in Germany.
