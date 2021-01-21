# sample-lwc-rabbitmq

# LightWave Client RabbitMQ Sample
This LightWave Client sample illustrates how to publish and get messages from queues on a
[RabbitMQ](https://www.rabbitmq.com/) instance. This sample may be used as a basis for
developing custom appications that work with RabbitMQ.

## Related Documentation
+ [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT)
+ [RabbitMQ](https://www.rabbitmq.com/documentation.html)
+ [RabbitMQ REST API](https://pulse.mozilla.org/api/)


## Sample Prerequisites

+ NonStop C Compiler.
+ An installed instance of [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT) version 1.1.2 or greater.
+ An installed RabbitMQ instance. The vhost, queue, routing-key names and queue credentials must be known.

*Note: LightWave Client does not support the use of '/' as a URI path parameter and is not able to invoke
RabbitMQ REST API operations on the default vhost. You must have an
additional vhost configured.*

The following values must be configured in the SETENV TACL macro after UNPAKing the sample files:

+ lwc-isv - The installation subvolume of your LightWave Client software.
+ base-url - The base URL of your RabbitMQ instance.
+ http-credentials - The credentials required to access the target queues. The credentials may be supplied in *username:password* format, or by specifying a credentials file in the form *+enscribe-file*. See
[Using Credentials Files](https://docs.nuwavetech.com/display/LWCLIENT/Using+Credentials+Files)

The values for pathmon-name and server-class may also be customized
if they are not appropriate for your system.

## Install & Build

The RMQ sample client must be built from source. The source files are present in the repository for convenient viewing.
In addition, a PAK archive containing all of the source files is available for transfer to your NonStop system.

| Repository File | NonStop File |
| -- | -- |
| macros/build.txt | build |
| macros/loadddl.txt | loadddl |
| macros/logcfg.txt | logcfg |
| macros/setenv.txt | setenv |
| macros/startpw.txt | startpw |
| macros/stoppw.txt | stoppw |
| macros/unsetenv.txt | unsetenv |
| resources/rmqapi.json | rmqapi |
| resources/rmqddl.txt | rmqddl |
| src/rmq.c | rmqc |
| rmqpak.bin | rmqpak |

#### Transfer the PAK archive to your NonStop System

Download `rmqpak.bin` from this repository to your local system, then upload to your NonStop server using binary transfer mode.

Note: to download the PAK file, click `rmqpak.bin` in the file list to display the file details, then click the *Download* button.

Logon to TACL on your NonStop system to peform the installation and build steps.

#### Unpak the PAK archive
```
TACL > UNPAK rmqpak ($*.*.*), VOL $vol.subvol, LISTALL, MYID
```
#### Build the application
```
TACL > RUN LOADDDL
TACL > RUN BUILD
```
## Running the application
Customize the SETENV macro for your environment and run the macro to set the required PARAMs.
```
TACL> T/EDIT SETENV
TACL> RUN SETENV
```
Start the LightWave Client Pathway
```
TACL > RUN STARTPW
```
Run the application. When run with no argumments, usage information
is displayed. In these examples, the RabbitMQ vhost, queue, and
routing-key are all "sample".
```
TACL> run rmq

LightWave Client(tm) - RabbitMQ sample client.

Usage:
        rmq get <vhost> <queue>
  or
        rmq pub <vhost> <queue> <routing-key> <quoted-message>

where:
        <vhost> the virtual host name (may not be "/")
        <queue> the name of the queue
        <routing-key> the message routing key
        <quoted-message> the message to publish, enclosed in quotes.

TACL> run rmq pub sample sample sample "Hello RabbitMQ!"

LightWave Client(tm) - RabbitMQ sample client.

15 byte message published: Hello RabbitMQ!

Request completed in 0.258806 seconds.

TACL> run rmq pub sample sample sample "Hello again ..."

LightWave Client(tm) - RabbitMQ sample client.

15 byte message published: Hello again ...

Request completed in 0.21998 seconds.

TACL> run rmq get sample sample

LightWave Client(tm) - RabbitMQ sample client.

15 byte message retrieved: Hello RabbitMQ!

Request completed in 0.216403 seconds.

TACL> run rmq get sample sample

LightWave Client(tm) - RabbitMQ sample client.

15 byte message retrieved: Hello again ...

Request completed in 0.056043 seconds.

```
When done with the sample, stop the LightWave Client Pathway.
```
TACL> RUN STOPPW
```