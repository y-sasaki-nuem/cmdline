#!/usr/bin/bash

winpty waf.bat configure clean build \
  --check-cxx-compiler clang++
