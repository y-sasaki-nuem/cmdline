#!/usr/bin/bash

winpty waf.bat configure clean build \
  --check-cxx-compiler msvc \
  --msvc_version       "msvc 12.0" \
  --msvc_targets       x64
