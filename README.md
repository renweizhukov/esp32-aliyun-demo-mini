esp32-aliyun-demo-mini
======================

Based on [esp32-aliyun-demo](https://github.com/espressif/esp32-aliyun-demo), to reduce the binary size (i.e., libmain.a and main.bin), we extract the dependencies of mqtt-example from the library esp32-aliyun and compile them with mqtt-example together.

# 1. Set up the development environment on Ubuntu 16.04LTS.

## 1.1 Download the Linux toolchain.

https://esp-idf.readthedocs.io/zh_CN/latest/get-started/linux-setup.html

Assume that the toolchain archive is unpacked to `$HOME/esp/xtensa-esp32-elf`.

## 1.2 Clone this repository with its submodules.

Note that different from [esp32-aliyun-demo](https://github.com/espressif/esp32-aliyun-demo), this repository has only one submodule [esp-idf](https://github.com/espressif/esp-idf.git) and it already contains the dependencies in [esp32-aliyun](https://github.com/espressif/esp32-aliyun.git).

```bash
$ git clone --recursive https://github.com/renweizhukov/esp32-aliyun-demo-mini.git
$ cd esp32-aliyun-demo-mini/
$ git submodule update --init --recursive
```

## 1.3 Set the environment variables.

(1) Do it manually.

```bash
$ export IDF_PATH=$(pwd)/esp-idf
$ export PATH=$PATH:$HOME/esp/xtensa-esp32-elf/bin
```

(2) Use `setup_env.sh` in this repository.

```bash
$ source setup_env.sh
```

You may export the environment variables in `$HOME/.profile` so that their definitions are loaded every time you log in.

## 1.4 Set the Aliyun IoT product parameters.

Set the following macro values according to your IoT product in `main/src/mqtt_example.c`.

```c
#define PRODUCT_KEY             "xxxxxx"
#define DEVICE_NAME             "yyyyyy"
#define DEVICE_SECRET           "zzzzzzzzzzzz"
```

# 2. Compile the demo.

## 2.1 Set compile configurations.

### 2.1.1 Select the demo.

`make menuconfig` -> `choose demo` -> `mqtt-example`.

**Note that the other demo `ota-mqtt-example` in [esp32-aliyun-demo](https://github.com/espressif/esp32-aliyun-demo) is not ported here.**

### 2.1.2 Configure the WiFi connection.

`make menuconfig` -> `choose demo` -> Type the WiFi SSID and password.

### 2.1.3 Reduce the binary size.

(1) `make menuconfig` -> `Compiler options` -> `Optimization Level` -> Select `Release (-Os)`.

(2) `make menuconfig` -> `Compiler options` -> `Assertion level` -> Select `Disabled (sets -DNDEBUG)`.

(3) Disable debug logging in `Makefile` by commenting out the following line.

```
#CFLAGS += -D IOTX_DEBUG
```

(4) After `make`, strip the unneeded symbols from the library and then `make` again.

```bash
$ make
$ xtensa-esp32-elf-strip --strip-unneeded build/main/libmain.a
$ make
```

## 2.2 Compile the demo.

```bash
$ make
```

## 2.3 Flash and monitor the demo.

```bash
$ make flash monitor
```

Note that the above steps also work for Ubuntu on Windows 10, but you do need to associate the Windows serial port with Linux before you can flash the demo. For details, please refer to https://blog.csdn.net/xiaoyuluoke1/article/details/79111599.

If everything works as expected, you should see the following messages in the terminal:

```
I (3535) wifi: connected with XXXXXX, channel 1

iotx_mc_connect/1960: mqtt connect success!

************************     174704    **********************
iotx_mc_cycle/1237: PUBACK
event_handle|084 :: publish success, packet-id=24
iotx_mc_cycle/1237: PUBACK
event_handle|084 :: publish success, packet-id=29
```