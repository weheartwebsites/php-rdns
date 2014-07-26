# *php-rdns* [![Build Status](https://travis-ci.org/weheartwebsites/php-rdns.svg?branch=master)](https://travis-ci.org/weheartwebsites/php-rdns) [![License](http://img.shields.io/badge/license-Apache--2.0-lightgrey.svg)](http://www.apache.org/licenses/LICENSE-2.0.html)

*php-rdns* is a PHP extension for asynchronous DNS lookups written in C. It provides a Object-oriented PHP binding for [librdns](https://github.com/vstakhov/librdns) and uses [libev](http://software.schmorp.de/pkg/libev.html) as event loop.

The usage was modelled after [dns_get_record](http://php.net/manual/en/function.dns-get-record.php).

Currently this is only a "stub" resolver, so recursion will not be supported if the DNS server does not support it.

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [php-rdns  ](#user-content-php-rdns--)
	- [Requirements](#user-content-requirements)
	- [Installation](#user-content-installation)
		- [Git](#user-content-git)
		- [Release](#user-content-release)
	- [Usage](#user-content-usage)
	- [Interface](#user-content-interface)
		- [RDNS_*](#user-content-rdns_)
		- [RDNS::addServer](#user-content-rdnsaddserver)
		- [RDNS::addRequest](#user-content-rdnsaddrequest)
		- [RDNS::getReplies](#user-content-rdnsgetreplies)
	- [Trivia](#user-content-trivia)


## Requirements

 - Unix or Linux
 - PHP 5.4 or 5.5
 - libev


## Installation

### Git

```
$ sudo apt-get install libev-dev
$ git clone https://github.com/weheartwebsites/php-rdns.git
$ cd php-rdns/
$ git submodule init
$ git submodule update
$ phpize
$ ./configure
$ make
$ make test
$ sudo make install
$ echo "extension=rdns.so" >> /etc/php.ini
``` 

### Release

```
$ sudo apt-get install libev-dev
$ wget https://github.com/weheartwebsites/php-rdns/releases/download/v0.1.0/rdns-0.1.0.tgz
$ tar xvfz rdns-0.1.0.tgz
$ cd rdns-0.1.0/
$ phpize
$ ./configure
$ make
$ sudo make install
$ sudo echo "extension=rdns.so" >> /etc/php5/mods-available/rdns.ini
$ sudo php5enmod rdns
$ /etc/init.d/php-fpm restart
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


## Interface


### RDNS_*

As soon as the module is loaded following `CONSTANTS` will be available, the usage is self explanatory:

- `RDNS_A`
- `RDNS_AAAA`
- `RDNS_MX`
- `RDNS_NS`
- `RDNS_PTR`
- `RDNS_TXT`
- `RDNS_SVR`


### RDNS::addServer

Adds a DNS server to the pool.

```php
bool RNS::addServer ( string $server [, int $port = 53 [, int $prio = 0 ]] )
```

- **server**: IP address of the DNS server (e.g. `8.8.8.8` for google's public DNS)
- **port**: Port of the DNS server (`53` per default)
- **prio**: Priority of the DNS server (`0` per default)
	- DNS servers will be selected in a "round-robin" manner, respecting the prio value.



### RDNS::addRequest

Adds a DNS query to the pool

```php
bool RDNS::addRequest ( string $hostname , int $type [, float $timeout = 5 ]] )
```

- **hostname**: Hostname to query (e.g. `gimper.net`)
- **type**: Type of query (use constants, e.g. `RDNS_A`)
- **timeout**: Timeout of the query (`5` per default)


### RDNS::getReplies

Run all queries and return the results

```php
array RDNS::getReplies ( void )
```

- returns a multidim array
- first dimension carries the same numeric index as the order in which RDNS::addRequest() was invoked
- WARNING: the first dimension is not sorted by key (in case you want to use foreach) - this is a bug (more a missing feature, patches welcome!)
- second dimension is a list of array-hashes (always a list, as some records can occur multiple, for example MX, NS, round-robin, etc.)
- array hashes are same as: [dns_get_record](http://php.net/manual/en/function.dns-get-record.php) as the return values are exactly the same


## Trivia

The "r" in *php-rdns* stands for "rapid" which was taken from the name of librdns. The initial version was developed by [Alexander Solovets](https://github.com/mbait) and sponsored by
[weheartwebsites](http://www.weheartwebsites.de), which is a tiny web developement company based in Germany.
