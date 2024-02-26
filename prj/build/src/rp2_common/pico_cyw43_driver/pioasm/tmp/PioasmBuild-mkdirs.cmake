# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/crott/pico/pico-sdk/tools/pioasm"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/pioasm"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/crott/Documents/spring24/cpe1/DriversLab/prj/build/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()