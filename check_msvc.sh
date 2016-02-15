#!/usr/bin/bash

winpty waf.bat configure clean build \
  --check-cxx-compiler msvc \
  --msvc_version       "msvc 14.0" \
  --msvc_targets       x64
